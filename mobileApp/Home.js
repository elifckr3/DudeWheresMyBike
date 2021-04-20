import React from 'react';  
import { StyleSheet, Text, View, TouchableOpacity, Switch} from 'react-native';
import MapView, {Marker} from 'react-native-maps';
import init from 'react_native_mqtt';
import AsyncStorage from '@react-native-async-storage/async-storage';

import Icon from 'react-native-vector-icons/MaterialIcons';

Icon.loadFont();

init({
  size: 10000,
  storageBackend: AsyncStorage,
  defaultExpires: 1000 * 3600 * 24,
  enableCache: true,
  reconnect: true,
  sync : {
  }
});

export default class HomeScreen extends React.Component {
  constructor(props) {
    super(props);
    this.onMessageArrived = this.onMessageArrived.bind(this);
    this.onConnectionLost = this.onConnectionLost.bind(this);

    const client = new Paho.MQTT.Client('ws://test.mosquitto.org:8080/mqtt', 'maker');
    client.onMessageArrived = this.onMessageArrived;
    client.onConnectionLost = this.onConnectionLost;
    client.connect({ 
      onSuccess: this.onConnect,
      useSSL: false ,
      // userName: 'yourUser',
      // password: 'yourPass',
      onFailure: (e) => {console.log("here is the error" , e); }

    });

    this.state = { 
      showStatus: false,
      isEnabled: false,
      address: null,
      latitude: 34.0191459656,
      longitude: -118.2909164429,
      forceRefresh: 0,
    };

    this.mqtt_state = {
      message: [''],
      client,
      messageToSend:'',
      isConnected: false,
    };
  }

  hasJsonStructure(str) {
    if (typeof str !== 'string') return false;
    try {
        const result = JSON.parse(str);
        const type = Object.prototype.toString.call(result);
        return type === '[object Object]' 
            || type === '[object Array]';
    } catch (err) {
        return false;
    }
}

  toggleForceRefresh(){
    if(this.state.forceRefresh == 0){
      this.state.forceRefresh = 1;
    }
    else{
      this.state.forceRefresh = 0;
    }
  }
  onMessageArrived(entry) {
    console.log("onMessageArrived:"+entry.payloadString);
    if(this.hasJsonStructure(entry.payloadString)){
      json = JSON.parse(entry.payloadString);
      if(json.latitude){
        console.log("changed latitude to: " + json.latitude);
        this.state.latitude = parseFloat(json.latitude);
      }
      if(json.longitude){
        console.log("changed longitutde to: " + json.longitude);
        this.state.longitude = parseFloat(json.longitude);
      }
      
      this.toggleForceRefresh();

    }
    else{
      console.log("not a json");
    }
    
    // this.setState({message: [...this.mqtt_state.message, entry.payloadString]});

  }


  onConnect = () => {
    const { client } = this.mqtt_state;
    console.log("Connected!!!!");
    client.subscribe('DudeWheresMyBike');
    this.setState({isConnected: true, error: ''})
  };


  sendMessage(){
    message = new Paho.MQTT.Message(this.state.messageToSend);
    message.destinationName = "DudeWheresMyBike";

    if(this.state.isConnected){
      this.state.client.send(message);    
    }else{
      this.connect(this.state.client)
        .then(() => {
          this.state.client.send(message);
          this.setState({error: '', isConnected: true});
        })
        .catch((error)=> {
          console.log(error);
          this.setState({error: error});
        });
  }
  }


  onConnectionLost(responseObject) {
    if (responseObject.errorCode !== 0) {
      console.log("onConnectionLost:"+responseObject.errorMessage);
      this.setState({error: 'Lost Connection', isConnected: false});
    }
  }

  changeState(){
    this.setState({
      showStatus: !this.state.showStatus
    });
  }
  enableSwitch(){
    this.setState({
      isEnabled: !this.state.isEnabled
    });
  }

  render(){
    return (
        <MapView
         key={this.state.forceRefresh}
          style={{flex: 1}}
          initialRegion={{
            latitude: this.state.latitude,
            longitude: this.state.longitude,
            latitudeDelta: 0.0922,
            longitudeDelta: 0.0421,
          }}
            showsUserLocation={true}
          >
             <TouchableOpacity
                style={styles.menu}
                onPress={() => this.props.navigation.openDrawer()}
              >
                <Icon name={"menu"}  size={30} color="#456268" />
              </TouchableOpacity>
          
            <Marker
            coordinate={{latitude: this.state.latitude, longitude: this.state.longitude}}
            // title="Bike"
            // description="Your bike is located here" 
            onPress={(e) => {e.stopPropagation(); this.changeState()}
          }>
            <Icon name={"pedal-bike"}  size={30} color="#456268" />
            </Marker>
            {
              this.state.showStatus ? 
              <View style={styles.bottomView}>
                <TouchableOpacity style={styles.cancel} onPress={() => this.changeState()}>
                <Icon
                  name="close"
                  color="#456268"
                  size={30}
                  
                />
                </TouchableOpacity>
                <Text style={styles.statusHeading}> Your Bike</Text>
                <Text style={styles.statusSubHeading}> Bike Status</Text>
                <Text style={styles.statusSubHeading}> System Status </Text>
                <View style={styles.switch}>
                  <Switch
                    trackColor={{ false: "#fcf8ec", true: "#d0e8f2" }}
                    thumbColor={"white"}
                    ios_backgroundColor="#fcf8ec"
                    onValueChange={(value) => this.enableSwitch()}
                    value={this.state.isEnabled}
                  />
                </View>
              </View>
              :
              <View></View>
            }
          </MapView>
    );
  }
}

const styles = StyleSheet.create({
  bottomView: {
    width: '100%',
    height: '40%',
    backgroundColor: '#fcf8ec',
    borderRadius:25,
    position: 'absolute',
    bottom: 0,
    shadowColor: "#000",
    shadowOffset: {
	      width: 0,
	      height: 2,
    },
    shadowOpacity: 0.25,
    shadowRadius: 3.84,
    elevation: 5,   
  },
  cancel: {
    height: 30,
    width: 30,
    marginTop: 8,
    right: 8,
    alignItems:"center",
    justifyContent:"center",
    alignSelf: 'flex-end',
    position: 'absolute',
    backgroundColor: '#fcf8ec',
  },
  statusHeading:{
    fontWeight:"bold",
    fontSize:50,
    color:"#79a3b1",
    marginTop:20,
    marginLeft: 10,
    textAlign: 'left',
  },
  statusSubHeading:{
    fontWeight:"bold",
    fontSize:30,
    color:"#79a3b1",
    margin:10,
    textAlign: 'left',
  },
  switch:{
    flex: 1,
    alignItems: "center",
  },
  menu:{
    alignItems:'center',
    justifyContent:'center',
    width:40,
    height:40,
    backgroundColor:'#fcf8ec',
    borderRadius: 10,
    marginTop: 40,
    marginLeft: 15,
    textAlign: 'center',
  }
});