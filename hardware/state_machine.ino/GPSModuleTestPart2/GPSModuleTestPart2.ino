#include "TinyGPS++.h"
#include "SoftwareSerial.h"

  double latitude,GLOBAL_LAT;
  double longitude,GLOBAL_LON;

SoftwareSerial serial_connection(10, 11); // RX = pin 11, TX = pin 10
TinyGPSPlus gps;





bool gps_feed_check(bool setValues)
{
  while (serial_connection.available()){
    gps.encode(serial_connection.read());
  }


if (gps.location.isUpdated() && gps.location.isValid()){

  if (setValues){
    GLOBAL_LAT = gps.location.lat();
    GLOBAL_LON = gps.location.lng();
    return true;
  }

    latitude = gps.location.lat();
    longitude = gps.location.lng();

  if (abs(latitude - GLOBAL_LAT) > 0.00002 || abs(longitude - GLOBAL_LON) > 0.00002) {
    return true;
  }
  else{
    return false;
  }
    
}
}






void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serial_connection.begin(9600);
  Serial.print("GPS Start");
  gps_feed_check(true);


}

void loop() {
  // put your main code here, to run repeatedly:
  if (gps_feed_check(false)){
    Serial.println("device moved you bum");
  }

}
