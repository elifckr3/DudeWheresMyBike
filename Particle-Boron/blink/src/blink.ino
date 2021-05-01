
void callback(const char* event, const char* data);

// configuration settings
int LOOP_DELAY = 10000; // time is in milliseconds
bool ON = false;

void setup() {
    // LED pin setup
    Particle.subscribe("hook-response/update", callback, MY_DEVICES);
}

void callback(const char* event, const char* data) {

    // modulate state machine from callback
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    Serial.println("payload obtained from server:");

    // Some stuff to make with the payload obtained
        //
   //
}

void loop() {
    // We are sending the temperature and humidity level in one publish
    // sample latitude/longitude/acceleration

    lati = 34.99;
    longi = -118.99;
    acc = 3;

    Particle.publish("update", String::format("{\"latitude\":%d,\"longitude\":%d,\"acceleration\":%d}", lati, longi, acc), PRIVATE);
    delay(LOOP_DELAY);
}
