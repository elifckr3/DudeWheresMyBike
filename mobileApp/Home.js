import React from 'react';  
import { StyleSheet, Text, View, TouchableOpacity} from 'react-native';
import MapView, {Marker} from 'react-native-maps';

export default class HomeScreen extends React.Component {
  render(){
    return (
      <MapView
        style={{flex: 1}}
        initialRegion={{
          latitude: 37.78825,
          longitude: -122.4324,
          latitudeDelta: 0.0922,
          longitudeDelta: 0.0421,
        }}
          showsUserLocation={true}
        >
        
          <Marker
          coordinate={{latitude: 37.78825, longitude: -122.4324}}
          title="Bike"
          description="Your bike is located here" onPress={(e) => {e.stopPropagation(); statusComponent()}
        }>
          </Marker>
        </MapView>
    );
  }
}

function statusComponent(){
  console.log("status hehe");
  return(
    <View style={styles.bottomView}>
      <Text> Bottom Hi</Text>
    </View>
  )
}

const styles = StyleSheet.create({
  bottomView: {
    width: '100%',
    height: '50%',
    backgroundColor: '#EE5407',
    justifyContent: 'center',
    alignItems: 'center',
    position: 'absolute', //Here is the trick
    bottom: 0, //Here is the trick
  },
});