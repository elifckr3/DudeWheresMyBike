#include "TinyGPS++.h"
#include "SoftwareSerial.h"

  int counter = 1;
  double firstlat;
  double firstlong;
  double latitude;
  double longitude;
  double avglat;
  double avglong;

SoftwareSerial serial_connection(10, 11); // RX = pin 11, TX = pin 10
TinyGPSPlus gps;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serial_connection.begin(9600);
  Serial.print("GPS Start");


}

void loop() {
  // put your main code here, to run repeatedly:
  while (serial_connection.available()){
    gps.encode(serial_connection.read());
  }
  
  if (gps.location.isUpdated()){
    latitude = gps.location.lat();
    longitude = gps.location.lng();

    // half of the time,
    if (counter % 2 == 1){
      // just set average values to be the current reading
      avglat = latitude;
      avglong = longitude;
    }
    // the other half of the time
    else{
      // calculate average lat and long from last two values
      avglat += latitude;
      avglat /= 2;
      avglong += longitude;
      avglong /= 2;
      // if this is the first time calculating avg lat and long
      // every 5 goes, reset first values
      if ((counter+3) % 5 == 0){
        firstlat = avglat;
        firstlong = avglong;
      }
      // if not the first time calculating averages
      else{
        // if the current values are more than 0.00001 away from first
        if (abs(avglat - firstlat) > 0.00002 || abs(avglong-firstlong) > 0.00002){
          Serial.println("Device moved");
        }
      }
    }
      


    counter ++;
    
  }
}
