import React from 'react';  
import { StyleSheet, Text, View, TouchableOpacity, Switch} from 'react-native';
import MapView, {Marker} from 'react-native-maps';
import {
  createDrawerNavigator,
  DrawerContentScrollView,
  DrawerItemList,
  DrawerItem,
} from '@react-navigation/drawer';
import { NavigationContainer } from '@react-navigation/native';
import Icon from 'react-native-vector-icons/Ionicons';

Icon.loadFont();

export default class HomeScreen extends React.Component {
  constructor(props) {
    super(props);
    this.state = { 
      showStatus: false,
      isEnabled: false,
      address: null,
      latitude: 37.78825,
      longitude: -122.4324,
    };
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
              >
                <Icon name={"menu"}  size={30} color="#456268" />
              </TouchableOpacity>
          
            <Marker
            coordinate={{latitude: this.state.latitude, longitude: this.state.longitude}}
            // title="Bike"
            // description="Your bike is located here" 
            onPress={(e) => {e.stopPropagation(); this.changeState()}
          }>
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