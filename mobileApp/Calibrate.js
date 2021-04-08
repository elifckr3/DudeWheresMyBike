import React from 'react';
import { StyleSheet, Text, View, TextInput, TouchableOpacity } from 'react-native';

export default class CalibrateScreen extends React.Component {
  state={
    ultrasonic1:"",
    ultrasonic2:"",
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
            placeholder="Ultrasonic2 Distance..." 
            placeholderTextColor="#456268"
            onChangeText={text => this.setState({ultrasonic2:text})}/>
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