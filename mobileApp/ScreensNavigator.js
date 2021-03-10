import * as React from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';

import LoginScreen from './Login';
import HomeScreen from './Home';

const {Navigator, Screen} = createStackNavigator();

const AuthStack = () => (
  <Navigator headerMode="none">
    <Screen name="Login" component={LoginScreen} />
    <Screen name="Home" component={HomeScreen} />
  </Navigator>
);

const ScreensNavigator = () => (
  <NavigationContainer>
    <AuthStack />
  </NavigationContainer>
);

export default ScreensNavigator;
