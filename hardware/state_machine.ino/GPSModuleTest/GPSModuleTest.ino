#include "TinyGPS++.h"
#include "SoftwareSerial.h"

  int counter = 0;
  float firstlat;
  float firstlong;
  float latitude;
  float longitude;
  float avglat;
  float avglong;
  int filterNum = 4;

SoftwareSerial serial_connection(10, 11); // RX = pin 11, TX = pin 10
TinyGPSPlus gps;





void gps_feed_check()
{
  while (serial_connection.available()){
    gps.encode(serial_connection.read());
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
        // if the current values are more than 0.00001 away from first
        Serial.print("First lat / long ");
        Serial.print(firstlat, 10);
        Serial.print(" ");
        Serial.print(firstlong, 10);
        Serial.print("\t");
        Serial.print("Average lat / long ");
        Serial.print(avglat, 10);
        Serial.print(" ");
        Serial.println(avglong, 10);
        delay(200);
        if (abs(avglat - firstlat) > 0.00001 || abs(avglong-firstlong) > 0.00001){
          firstlat = avglat;
          firstlong = avglong;
          Serial.println("Device moved");
          }
    }
      


    counter ++;
    
  }

}






void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serial_connection.begin(9600);
  Serial.print("GPS Start");


}

void loop() {
  // put your main code here, to run repeatedly:

 gps_feed_check();  
  

}
