import * as React from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';
import {
    createDrawerNavigator,
    DrawerContentScrollView,
    DrawerItemList,
    DrawerItem,
  } from '@react-navigation/drawer';

import LoginScreen from './Login';
import HomeScreen from './Home';
import SignUpScreen from './SignUp';
import CalibrateScreen from './Calibrate'

const {Navigator, Screen} = createStackNavigator();
const Drawer = createDrawerNavigator();

const NavStack = () => (
  <Navigator headerMode="none">
    <Screen name="Login" component={LoginScreen} />
    <Screen name="Home" component={HomeScreen} />
    <Screen name="SignUp" component={SignUpScreen} />
  </Navigator>
);

function MyDrawer() {
  return (
    <Drawer.Navigator>
      <Drawer.Screen name="Home" component={HomeScreen} />
      <Drawer.Screen name="Calibrate" component={CalibrateScreen} />
      <Drawer.Screen name="Logout" component={LoginScreen} />
      <Drawer.Screen name="Close Menu" component={NavStack} />
    </Drawer.Navigator>
  );
}

const ScreensNavigator = () => (
  <NavigationContainer>
    <MyDrawer />
  </NavigationContainer>
);

export default ScreensNavigator;
