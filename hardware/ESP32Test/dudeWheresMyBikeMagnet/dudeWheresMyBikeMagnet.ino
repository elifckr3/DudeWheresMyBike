//Simple sketch to access the internal hall effect detector on the esp32.
//values can be quite low. 
//Brian Degger / @sctv  
int externalHallPin = 2;    //hall sensor digital pin connected to D2
int val = 0, externalHallVal = 0;
void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = hallRead();
  externalHallVal = digitalRead(externalHallPin);
  // print the results to the serial monitor:
  //Serial.print("sensor = ");
  Serial.println(val);//to graph 
//  Serial.println(externalHallVal);
  delay(100);
}
