import React from 'react';
import { StyleSheet, Text, View, TextInput, TouchableOpacity } from 'react-native';

export default class LoginScreen extends React.Component {
  state={
    email:"",
    password:""
  }
  render(){
    return (
    <View style={styles.container}>
        <Text style={styles.logo}>Sign Up</Text>
        <View style={styles.inputView} >
        <TextInput  
            style={styles.inputText}
            placeholder="Email..." 
            placeholderTextColor="#456268"
            onChangeText={text => this.setState({email:text})}/>
        </View>
        <View style={styles.inputView} >
        <TextInput  
            style={styles.inputText}
            placeholder="Password..." 
            placeholderTextColor="#456268"
            onChangeText={text => this.setState({email:text})}/>
        </View>
        <View style={styles.inputView} >
        <TextInput secureTextEntry 
            style={styles.inputText}
            placeholder="Confirm Password..." 
            placeholderTextColor="#456268"
            onChangeText={text => this.setState({password:text})}/>
        </View>
        <TouchableOpacity style={styles.loginBtn} onPress={() => this.props.navigation.navigate('Home')}>
            <Text style={styles.loginText}>Sign Up</Text>
        </TouchableOpacity>
        <TouchableOpacity>
            <Text style={styles.loginText} onPress={() => this.props.navigation.navigate('Login')}>Back</Text>
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
    fontSize:40,
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
    marginTop:30,
    marginBottom:10
  },
});
