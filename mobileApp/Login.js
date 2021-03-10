import React, { Component } from 'react';;
import { StyleSheet, Text, View, TextInput, TouchableOpacity } from 'react-native';

export default class LoginScreen extends Component {
  state={
    email:"",
    password:""
  }
  render(){
    return (
    <View style={styles.container}>
        <Text style={styles.logo}>Dude, Where's My Bike?</Text>
        <View style={styles.inputView} >
        <TextInput  
            style={styles.inputText}
            placeholder="Email..." 
            placeholderTextColor="#456268"
            onChangeText={text => this.setState({email:text})}/>
        </View>
        <View style={styles.inputView} >
        <TextInput secureTextEntry 
            style={styles.inputText}
            placeholder="Password..." 
            placeholderTextColor="#456268"
            onChangeText={text => this.setState({password:text})}/>
        </View>
        <TouchableOpacity>
            <Text style={styles.forgot}>Forgot Password?</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.loginBtn} onPress={() => this.props.navigation.navigate('Home')}>
            <Text style={styles.loginText}>LOGIN</Text>
        </TouchableOpacity>
        <TouchableOpacity>
            <Text style={styles.loginText}>Signup</Text>
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
    marginTop:40,
    marginBottom:10
  },
});