import React from 'react';
import { StyleSheet, Text, View, TextInput, TouchableOpacity } from 'react-native';

export default class CalibrateScreen extends React.Component {
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

  }

  onConnect = () => {
    const { client } = this.state.mqtt_state;
    console.log("Connected!!!!");
    client.subscribe('DudeWheresMyBike');
    this.state.mqtt_state.isConnected = true;
  };

  onMessageArrived(entry) {
    console.log("onMessageArrived:"+entry.payloadString);
    
    // this.setState({message: [...this.mqtt_state.message, entry.payloadString]});

  }

  sendMessage(){
    message = new Paho.MQTT.Message(this.state.mqtt_state.messageToSend);
    message.destinationName = "DudeWheresMyBike";

    if(this.state.mqtt_state.isConnected){
      this.state.mqtt_state.client.send(message);    
    }else{
      this.connect(this.state.mqtt_state.client)
        .then(() => {
          this.state.mqtt_state.client.send(message);
          // this.setState({error: '', isConnected: true});
        })
        .catch((error)=> {
          console.log(error);
          // this.setState({error: error});
        });
  }
  }


  onConnectionLost(responseObject) {
    if (responseObject.errorCode !== 0) {
      console.log("onConnectionLost:"+responseObject.errorMessage);
      this.setState({error: 'Lost Connection', isConnected: false});
    }
  }

  state={
    ultrasonic:"",
    accel:"",
  }
  render(){
    return (
    <View style={styles.container}>
        <Text style={styles.logo}>Sensors Calibration</Text>
        <View style={styles.inputView} >
        <TextInput  
            style={styles.inputText}
            placeholder="Ultrasonic1 Distance..." 
            placeholderTextColor="#456268"
            onChangeText={text => this.setState({ultrasonic1:text})}/>
        </View>
        <View style={styles.inputView} >
        <TextInput  
            style={styles.inputText}
            placeholder="Accelerometer Distance..." 
            placeholderTextColor="#456268"
            onChangeText={text => this.setState({accel:text})}/>
        </View>
        <TouchableOpacity style={styles.loginBtn} onPress={() => this.props.navigation.navigate('Home')}>
            <Text style={styles.loginText}>Calibrate!</Text>
        </TouchableOpacity>
    </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#79a3b1',
    alignItems: 'center',
    justifyContent: 'center',
  },
  logo:{
    fontWeight:"bold",
    fontSize:50,
    color:"#fcf8ec",
    marginBottom:40,
    textAlign: 'center',
  },
  inputView:{
    width:"80%",
    backgroundColor:"#d0e8f2",
    borderRadius:25,
    height:50,
    marginBottom:20,
    justifyContent:"center",
    padding:20
  },
  inputText:{
    height:50,
    color:"#79a3b1"
  },
  forgot:{
    color:"#456268",
    fontSize:11,
  },
  loginText:{
    color:"#456268"
  },
  loginBtn:{
    width:"80%",
    backgroundColor:"#fcf8ec",
    borderRadius:25,
    height:50,
    alignItems:"center",
    justifyContent:"center",
    // marginTop:40,
    marginBottom:10
  },
});