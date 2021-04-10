#include <Wire.h>
#include <TimerOne.h>
 
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
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
// Set register address
Wire.beginTransmission(Address);
Wire.write(Register);
Wire.write(Data);
Wire.endTransmission();
}
 
// Initial time
long int ti;
volatile bool intFlag=false;
 
// Initializations
void setup()
{
// Arduino initializations
Wire.begin();
Serial.begin(9600);
 
// Set accelerometers low pass filter at 5Hz
I2CwriteByte(MPU9250_ADDRESS,29,0x06);

// Configure accelerometers range
I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_16_G);
 
pinMode(13, OUTPUT);
Timer1.initialize(10000); // initialize timer1, and set a 1/2 second period
Timer1.attachInterrupt(callback); // attaches callback() as a timer overflow interrupt
 
 
// Store initial time
ti=millis();
}
 
// Counter
long int cpt=0;
int16_t pax;
int16_t pay;
int16_t paz;
 
void callback()
{ 
intFlag=true;
digitalWrite(13, digitalRead(13) ^ 1);
}
 
// Main loop, read and display data
void loop()
{
while (!intFlag);
intFlag=false;

 
// ____________________________________
// ::: accelerometer and gyroscope :::
 
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
}
else {
  Serial.print (ax-pax,DEC); 
  Serial.print ("\t");
  Serial.print (ay-pay,DEC);
  Serial.print ("\t");
  Serial.print (az-paz,DEC); 
  Serial.print ("\t");
  pax = ax;
  pay = ay;
  paz = az;
}

cpt ++;
 
// Display values
 

// End of line
Serial.println("");
// delay(100); 
}
