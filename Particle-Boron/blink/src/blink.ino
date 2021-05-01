#include "MQTT.h"

void callback(char* topic, byte* payload, unsigned int length);
MQTT client("test.mosquitto.org", 9001, callback);

// configuration settings
int LOOP_DELAY = 10000; // time is in milliseconds
bool ON = false;

void setup() {
    // LED pin setup
    client.connect("sparkclient");
    if (client.isConnected()) {
        client.subscribe("fromMobile/message");
    }
}

callback(char* topic, byte& payload, unsigned int length) {

    // modulate state machine from callback
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    Serial.println("payload obtained from server:");
    for (int i=0;i<length;i++) {
        if (payload[i]) {
            ON = true;
        } else {
            ON = false;
        }
    }
    // Some stuff to make with the payload obtained
        //
   //
}

void loop() {
    // We are sending the temperature and humidity level in one publish
    // sample latitude/longitude/acceleration
    if (client.isConnected()) {

        lati = 34.99;
        longi = -118.99;
        acc = 3;
        
        Particle.publish("update", String::format("{\"latitude\":%d,\"longitude\":%d,\"acceleration\":%d}", lati, longi, acc), PRIVATE);
        delay(LOOP_DELAY);
    }
}
