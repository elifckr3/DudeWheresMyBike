#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>        
#include "TinyGPS++.h"
//#include "SoftwareSerial.h"

int start =1;
int bs = 0; //bike stolen flag
int ws = 0; //wheel stolen flag
int x_acc = 0;
int y_acc = 0;
int z_acc = 0;
int state = 0;
int counter = 1;
int gpsflag = 0;
int u1 = 0; //ultrasonic
int u2 = 0; //ultrasonic
int ack = 0; 
double firstlat;
double firstlong;
double latitude, GLOBAL_LAT;
double longitude, GLOBAL_LON;
double avglat;
double avglong;

const int buzzer = 7;
//Doesnt work arduino MKR 1010 also will not work with the boron since it does not support the library
//SoftwareSerial serial_connection(10, 11); // RX = pin 11, TX = pin 10
TinyGPSPlus gps;



// I2C from accelerometer
Adafruit_LIS3DH lis = Adafruit_LIS3DH();



int gps_feed_check()
{
//  while (serial_connection.available()) {
//    gps.encode(serial_connection.read());
//  }
  if (Serial1.available() > 0) {
    // read the incoming byte:
    gps.encode(Serial1.read());
  }



  if (gps.location.isUpdated() && gps.location.isValid()) {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    Serial.println(latitude);
    Serial.println(longitude);

    // half of the time,
    if (counter % 2 == 1) {
      // just set average values to be the current reading
      avglat = latitude;
      avglong = longitude;
    }
    // the other half of the time
    else {
      // calculate average lat and long from last two values
      avglat += latitude;
      avglat /= 2;
      avglong += longitude;
      avglong /= 2;
      // if this is the first time calculating avg lat and long
      // every 5 goes, reset first values
      if ((counter + 3) % 5 == 0) {
        firstlat = avglat;
        firstlong = avglong;
      }
      // if not the first time calculating averages
      else {
        // if the current values are more than 0.00001 away from first
        if (abs(avglat - firstlat) > 0.00002 || abs(avglong - firstlong) > 0.00002) {
          gpsflag = 1;
          delay(2000);
          Serial.println("Device moved");
        }
      }
    }


    counter ++;

  }


  GLOBAL_LAT = avglat;
  GLOBAL_LON = avglong;
  return gpsflag;

}


bool check_acc(){
  //read in data 
  lis.read();      // get X Y and Z data at once

   /* Or....get a new sensor event, normalized */ 
  sensors_event_t event; 
  lis.getEvent(&event);
  for (int i=0;i<9;i++) {
     x_acc += event.acceleration.x;
     y_acc += event.acceleration.y;
     z_acc += event.acceleration.z;
  }
  Serial.println(x_acc);
  Serial.println(y_acc);
  Serial.println(z_acc);
  x_acc = x_acc/10.0;
  y_acc = y_acc/10.0;
  z_acc = z_acc/10.0;
  
  

  
  if ((x_acc > 1) | (y_acc > 1) | (z_acc > 1)) {
    return true;
  }
  else 
    return false;
  
 
  delay(200); 

}

void sound_alarm(){
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec"

}






void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  pinMode(buzzer,OUTPUT);

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  
  //init location of bike  
  //int initial_loc = gps_feed_check();  
  

  Serial1.begin(9600);
  while (!Serial1) {
    ;
  }
  //serial_connection.begin(9600);
  Serial.print("GPS Start");


}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(gps_feed_check());

   switch (state) {
      case 0: //init state
      Serial.println("init state");
      delay(200);
        if (start){
          state =1;
          start = 0;
          break;
        }
        else 
          break;
          
      case 1: //secuirty state 
      Serial.println("secuirty state");
      delay(200);
        if (check_acc()) {
          state = 2;
          break;
        } else {
          break;
        }
        
      case 2: //check gps state 
      Serial.println("check_gps state");
      delay(200);
        if (gps_feed_check()) { //or mag lock opened
          state = 3; 
          delay(300);
          break;  
        }
        else if(u1 > 5 && u2 > 5) { //random limits for two ultrasonics waiting on parts 
          state = 5;
          break;
          
        }
        else { //false alarm state 
          state =1;
          break;
        }
        
      case 3: //send signal state
      Serial.println("send_signal state");
      delay(200);
        //return gps data to backend to track the bike (send to particle cloud)
        if (bs) {
          Serial.println("bike stolen");
          delay(200);
          
        }
        else {
          Serial.println("wheel stolen");
          delay(200);
        }
        state =4;
        break;
        
      case 4: //sound alarm state 
      Serial.println("sound_alarm state");
      delay(200);
        if(ack) { //ack 
          state = 0;
          ack = 0;
          break;
        }
        else {
          sound_alarm();
          ack = 1;
          break;
        }
      case 5: //wheel stolen
      Serial.println("wheel_stolen state");
      delay(200); 
        if (check_acc()) {
          bs = 1;
          state = 3;
        }
        else if (u1 == 5 && u2 == 5) { //false alarm
          state = 1;
        }
        else {
          ws = 1;
          state = 3;
        }
          
       



    
   }

    
    
}
  
