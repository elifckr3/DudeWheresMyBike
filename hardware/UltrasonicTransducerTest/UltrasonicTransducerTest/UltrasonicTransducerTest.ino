#define TRIG 11
#define ECHO 12

void setup(){
   Serial.begin(9600);
   pinMode(TRIG, OUTPUT);
   pinMode(ECHO, INPUT_PULLUP);
}

void loop() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(20);

  digitalWrite(TRIG, LOW);
  int distance = pulseIn(ECHO, HIGH, 26000);

  distance = distance/58;

  Serial.print("Distance " );
  Serial.print(distance);
  Serial.println("cm");

  delay(50);
  
}
