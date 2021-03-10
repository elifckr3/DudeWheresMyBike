import * as React from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';

import LoginScreen from './Login';
import HomeScreen from './Home';

const {Navigator, Screen} = createStackNavigator();

const NavStack = () => (
  <Navigator headerMode="none">
    <Screen name="Login" component={LoginScreen} />
    <Screen name="Home" component={HomeScreen} />
  </Navigator>
);

const ScreensNavigator = () => (
  <NavigationContainer>
    <NavStack />
  </NavigationContainer>
);

export default ScreensNavigator;
