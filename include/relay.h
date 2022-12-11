//setup the relays
#ifdef relay

    void relay_setup() {
        #ifdef relay1
            pinMode(relay1, OUTPUT);
            mqtt_client.subscribe(mqtt_topic_relay1);
            Serial.println("relay1 setup");
        #endif
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

    //loop for the relays
    void relay_loop() {
        #ifdef relay1
        if (mqtt_topic == mqtt_topic_relay1) {
            if (mqtt_payload == "true") {
            digitalWrite(relay1, HIGH);
            Serial.println("relay1 on");
            }
            else if (mqtt_payload == "false") {
            digitalWrite(relay1, LOW);
            Serial.println("relay1 off");
            }
            mqtt_topic = "";
            mqtt_payload = "";
        }
        #endif
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