import React from 'react';  
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
          description="Your bike is located here"
        />
        </MapView>
    );
  }
}