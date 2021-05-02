// #include <Wire.h>
// #include <SPI.h>
//#include <Adafruit_LIS3DH.h>
//#include <Adafruit_Sensor.h>        

// GPS MODULE CRAP
#include "TinyGPS++.h"
// #include "SoftwareSerial.h"

// ACCELEROMETER CRAP
// #include <TimerOne.h>
 
#define MPU9250_ADDRESS 0x68
 
#define ACC_FULL_SCALE_2_G 0x00 
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18
 
// This function read Nbytes bytes from I2C device at address Address. 
// Put read bytes starting at register Register in the Data array. 
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
// Set register address
Wire.beginTransmission(Address);
Wire.write(Register);
Wire.endTransmission();
 
// Read Nbytes
Wire.requestFrom(Address, Nbytes); 
uint8_t index=0;
while (Wire.available())
Data[index++]=Wire.read();
}
 
 
// Write a byte (Data) in device (Address) at register (Register)
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data) //might have to change this
{
// Set register address
Wire.beginTransmission(Address);
Wire.write(Register);
Wire.write(Data);
Wire.endTransmission();
}
volatile bool intFlag=false;
// accelerometer counter
long int cpt=0;
int16_t pax;
int16_t pay;
int16_t paz;

// ULTRASONIC CRAP
#define TRIG 4
#define ECHO 5
int ultraBV = 25; // change later


int start =1;
int bs = 0; //bike stolen flag
int ws = 0; //wheel stolen flag
int x_acc = 0;
int y_acc = 0;
int z_acc = 0;
int state = 0;
int gpsflag = 0;
int u1 = 0; //ultrasonic
int u2 = 0; //ultrasonic
int ack = 0; 
  int counter = 0; // this and below is GPS
  float firstlat;
  float firstlong;
  float latitude;
  float longitude;
  float avglat;
  float avglong;
  int filterNum = 4;
  float GLOBAL_LAT;
  float GLOBAL_LON;

const int buzzer = 7;
//Doesnt work arduino MKR 1010 also will not work with the boron since it does not support the library
//will use Serial1 WITH the boron
// SoftwareSerial serial_connection(10, 11); // RX = pin 11, TX = pin 10
// Serial1 
TinyGPSPlus gps;



// I2C from accelerometer
//Adafruit_LIS3DH lis = Adafruit_LIS3DH();


bool gps_feed_check()
{
  while (Serial1.available()) {
    gps.encode(Serial1.read());
  }
//  if (Serial1.available() > 0) {
//    // read the incoming byte:
//    gps.encode(Serial1.read());
//  }



 if (gps.location.isUpdated() && gps.location.isValid()) {
   latitude = gps.location.lat();
   longitude = gps.location.lng();
   Serial.print("Latitude: ");
   Serial.print(latitude);
   Serial.print(", Longitude: ");
   Serial.println(longitude);
   //publish latitude and longitude
  Particle.publish("update", String::format("{\"latitude\":%d,\"longitude\":%d}", latitude, longitude), PRIVATE);

//    Serial.println(latitude);
//    Serial.println(longitude);

   // half of the time,
   if (counter % 2 == 1) {
     // just set average values to be the current reading
     avglat = latitude;
     avglong = longitude;
     counter ++;
   }
   // the other half of the time
   else {
     // calculate average lat and long from last two values
     avglat += latitude;
     avglat /= 2;
     avglong += longitude;
     avglong /= 2;
     counter ++;
    //  if (setValues){
    GLOBAL_LAT = avglat;
    GLOBAL_LON = avglong;
    return true;
    //  }
//      // if this is the first time calculating avg lat and long
//      // every 5 goes, reset first values
//      if ((counter + 3) % 5 == 0) {
//        firstlat = avglat;
//        firstlong = avglong;
//      }
     // if not the first time calculating averages
     //else {
       // if the current values are more than 0.00001 away from first
       if (abs(avglat - GLOBAL_LAT) > 0.00002 || abs(avglong - GLOBAL_LON) > 0.00002) {
//          gpsflag = 1;
//          delay(2000);
//          Serial.println("Device moved");
           return true;
       }
     //}
   }


 }


  if (gps.location.isUpdated() && gps.location.isValid()){
    latitude = gps.location.lat();
    longitude = gps.location.lng();

    if (counter == 0){
      firstlat = latitude;
      firstlong = longitude;
    }

    // 
    if (counter % filterNum == 0){
      // just set average values to be the current reading
      avglat = latitude;
      avglong = longitude;
    }
    // the other half of the time
    else{
      // calculate average lat and long from last two values
      avglat *= (counter%filterNum-1);
      avglat += latitude;
      avglat /= counter%filterNum;
      avglong *= (counter%filterNum-1);
      avglong += longitude;
      avglong /= counter%filterNum;
      // if this is the first time calculating avg lat and long

      // if not the first time calculating averages
        if (abs(avglat - firstlat) > 0.00001 || abs(avglong-firstlong) > 0.00001){
          firstlat = avglat;
          firstlong = avglong;
          return true;
        }
    }
      
    counter ++;
    
  }

  return false;

}

bool gpsLoop(){
  for (int i=0; i<20; i++){
    if (gps_feed_check()){
      return true;
    }
  }
  return false;
}


bool check_acc(){
  // Read accelerometer and gyroscope
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS,0x3B,14,Buf);
   
  // Create 16 bits values from 8 bits data
   
  // Accelerometer
  int16_t ax=-(Buf[0]<<8 | Buf[1]);
  int16_t ay=-(Buf[2]<<8 | Buf[3]);
  int16_t az=Buf[4]<<8 | Buf[5];
  
  if (cpt == 0){
    pax = ax;
    pay = ay;
    paz = az;
    cpt++;
    return false;
  }
  else {
    if (abs(ax-pax) > 10 || abs(ay-pay) > 10 || abs(az-paz) > 10){
      cpt = 0;
      return true;
    }
//    Serial.print (ax-pax,DEC); 
//    Serial.print ("\t");
//    Serial.print (ay-pay,DEC);
//    Serial.print ("\t");
//    Serial.print (az-paz,DEC); 
//    Serial.print ("\t");
    pax = ax;
    pay = ay;
    paz = az;
    return false;
  }


}

//void sound_alarm(){
//  tone(buzzer, 1000); // Send 1KHz sound signal...
//  delay(1000);        // ...for 1 sec
//  noTone(buzzer);     // Stop sound...
//  delay(1000);        // ...for 1sec"
//
//}


bool check_ultra(){
  
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(20);

  digitalWrite(TRIG, LOW);
  int distance = pulseIn(ECHO, HIGH);   //26000?

  distance = distance/58;

  if (distance - ultraBV > 5){
    return true;
  }
  else{
    return false;
  }

  delay(50);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  // serial_connection.begin(9600);
//  pinMode(buzzer,OUTPUT);

  // ACCELEROMETER SETUP
  Wire.begin();
  // Set accelerometers low pass filter at 5Hz
  I2CwriteByte(MPU9250_ADDRESS,29,0x06);
  
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_16_G);

  // ULTRASONIC SETUP
   pinMode(TRIG, OUTPUT);
   pinMode(ECHO, INPUT_PULLUP);
  
  //init location of bike  
  //int initial_loc = gps_feed_check();  
 
 // particle subscribe 
  
    Particle.subscribe("hook-response/update", callback, MY_DEVICES);



}
void callback(const char* event, const char* data) {

    // modulate state machine from callback
    Serial.print("Message arrived [");
    Serial.print("hook-response/update");
    Serial.print("] ");
    Serial.println("payload obtained from server:");

    // Some stuff to make with the payload obtained
        //
   //
}
void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(gps_feed_check());

   switch (state) {
    Serial.print(state);
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
      Serial.println("security state");
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
        if (gpsLoop()) { //or mag lock opened
          state = 3; 
          delay(300);
          break;  
        }
        else if(check_ultra()) { //random limits for two ultrasonics waiting on parts 
          state = 5;
          break;
          
       }
        else { //false alarm state 
          //state =1;
          break;
        }
        
      case 3: //send signal state / bike stolen state
      Serial.println("send_signal state");
      delay(200);
        //return gps data to backend to track the bike (send to particle cloud)
//        if (bs) {
//          Serial.println("bike stolen");
//          delay(200);
//          
//        }
//        else {
//          Serial.println("wheel stolen");
//          state =4;
//          delay(200);
//          break;
//        }
      if(ws==1) {
        Serial.println("wheel stolen");
        ws=0;
      }
      else {
       Serial.println("bike stolen");
      }

       state = 4;
       delay(200);
       break;
        
        
        
      case 4: //sound alarm state 
      Serial.println("sound_alarm state");
      delay(200);
//        if(ack) { //ack 
//          state = 0;
//          ack = 0;
//          break;
//        }
//        else {
//          for (int i=0; i<10;i++) {
//            sound_alarm();
//          }
//          ack = 1;
//          break;
//        }
      Serial.println("wee woo alarm boop");
      break;
        
      case 5: //wheel stolen
      Serial.println("wheel_stolen state");
      delay(200); 
//        if (check_acc()) {
//          bs = 1;
//          state = 3;
//        }
//        else if (check_ultra()) { //false alarm
//          state = 1;
//        }
//        else {
//          ws = 1;
//          state = 3;
//        }
      Serial.println("Wheel stolen");
      ws =1;
      state = 4;
      delay(200);
      break;
    
   }
   
}