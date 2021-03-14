import * as React from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';

import LoginScreen from './Login';
import HomeScreen from './Home';
import SignUpScreen from './SignUp';

const {Navigator, Screen} = createStackNavigator();

const NavStack = () => (
  <Navigator headerMode="none">
    <Screen name="Login" component={LoginScreen} />
    <Screen name="Home" component={HomeScreen} />
    <Screen name="SignUp" component={SignUpScreen} />
  </Navigator>
);

const ScreensNavigator = () => (
  <NavigationContainer>
    <NavStack />
  </NavigationContainer>
);

export default ScreensNavigator;
