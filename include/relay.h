//setup the relays
#ifdef relay

// This function sets up a series of relays, potentially on an Arduino board.
void relay_setup() {
    // Check if the relay1 define is present.
    #ifdef relay1
        // If present, set the corresponding pin as an output.
        pinMode(relay1, OUTPUT);
        // Subscribe to the MQTT topic for this relay.
        mqtt_client.subscribe(mqtt_topic_relay1);
        // Print a message to the serial output indicating that the relay has been set up.
        Serial.println("relay1 setup");
    #endif

    // Repeat the above steps for the other relays, if they are defined.
    #ifdef relay2
        pinMode(relay2, OUTPUT);
        mqtt_client.subscribe(mqtt_topic_relay2);
        Serial.println("relay2 setup");
    #endif
    #ifdef relay3
        pinMode(relay3, OUTPUT);
        mqtt_client.subscribe(mqtt_topic_relay3);
        Serial.println("relay3 setup");
    #endif
    #ifdef relay4
        pinMode(relay4, OUTPUT);
        mqtt_client.subscribe(mqtt_topic_relay4);
        Serial.println("relay4 setup");
    #endif
}


    // This function provides the main loop for the relays.
void relay_loop() {
    // Check if the relay1 define is present.
    #ifdef relay1
        // If the MQTT topic for this relay is received...
        if (mqtt_topic == mqtt_topic_relay1) {
            // If the MQTT payload is "true"...
            if (mqtt_payload == "true") {
                // Set the corresponding pin to HIGH (i.e., turn on the relay).
                digitalWrite(relay1, HIGH);
                // Print a message to the serial output indicating that the relay is on.
                Serial.println("relay1 on");
            }
            // If the MQTT payload is "false"...
            else if (mqtt_payload == "false") {
                // Set the corresponding pin to LOW (i.e., turn off the relay).
                digitalWrite(relay1, LOW);
                // Print a message to the serial output indicating that the relay is off.
                Serial.println("relay1 off");
            }
            // Clear the MQTT topic and payload variables.
            mqtt_topic = "";
            mqtt_payload = "";
        }
    #endif

    // Repeat the above steps for the other relays, if they are defined.
    #ifdef relay2
        if (mqtt_topic == mqtt_topic_relay2) {
            if (mqtt_payload == "true") {
                digitalWrite(relay2, HIGH);
                Serial.println("relay2 on");
            }
            else if (mqtt_payload == "false") {
                digitalWrite(relay2, LOW);
                Serial.println("relay2 off");
            }
            mqtt_topic = "";
            mqtt_payload = "";
        }
    #endif
    #ifdef relay3
        if (mqtt_topic == mqtt_topic_relay3) {
            if (mqtt_payload == "true") {
                digitalWrite(relay3, HIGH);
                Serial.println("relay3 on");
            }
            else if (mqtt_payload == "false") {
                digitalWrite(relay3, LOW);
                Serial.println("relay3 off");
            }
            mqtt_topic = "";
            mqtt_payload = "";
        }
    #endif
    #ifdef relay4
        if (mqtt_topic == mqtt_topic_relay4) {
            if (mqtt_payload == "true") {
                digitalWrite(relay4, HIGH);
                Serial.println("relay4 on");
            }
            else if (mqtt_payload == "false") {
                digitalWrite(relay4, LOW);
                Serial.println("relay4 off");
            }
            mqtt_topic = "";
            mqtt_payload = "";
        }
    #endif
}


#endif