//Setup the mqtt mqtt_client

String payloadString = "";

//the callback function for the mqtt mqtt_client
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived at tpic: ");
  Serial.print(topic);
  Serial.print("   Message:");
  for (int i = 0; i < length; i++) {
      payloadString += (char)payload[i];
  }
  Serial.println(payloadString);
  //checks if the topic is the command topic
  if (String(topic) == mqtt_topic_sub) {

        // if the payload is "hello mqtt_client" then print "hello server" to status topic
      if (payloadString == "hello mqtt_client") {
          mqtt_client.publish(mqtt_topic_pub_status, "hello server");
          Serial.println("hello server");
          payloadString.clear();
      }
      //if the payload is "get" send data is set to true of the sensors
      //the send data bool is the main trigger to send data of any connetet sensor 
      if (payloadString == "get") {
          send_data = true;
          Serial.println("send data to server");
          payloadString.clear();
      }
      //if the payload is "Get IP" publish the ip to the mqtt topic "info/ip"
      if (payloadString == "get ip") {
          String ip = WiFi.localIP().toString().c_str();
          mqtt_client.publish(mqtt_topic_IP,ip.c_str());
          Serial.println("send ip to server");
          payloadString.clear();
      }
      //if the payload is "Get MAC" publish the mac to the mqtt topic "info/mac"
      if (payloadString == "get mac") {
          String mac = WiFi.macAddress().c_str();
          mqtt_client.publish(mqtt_topic_MAC,mac.c_str());
          Serial.println("send mac to server");
          payloadString.clear();
      }
      //if the payload is not clear the print "unknown command" to the mqtt topic "info/status"
      if (payloadString != "") {
          mqtt_client.publish(mqtt_topic_pub_status, "unknown command");
          Serial.println("unknown command");
          payloadString.clear();
      }
      //clean the command topic
      mqtt_client.publish(mqtt_topic_sub, "");
  }
  //make topic and payload global
  mqtt_topic = topic;
  mqtt_payload = payloadString;
  //clear the payloadString
  payloadString.clear();
  


}

//mqtt reconnect function
void PubSubClient_reconnect() {
  if (!mqtt_client.connected() && connect_attempts < 8) {
    mqtt_client.connect(device_name);
    Serial.print("Attempting MQTT connection...");
    if (mqtt_client.connect(device_name)) {
      Serial.println("connected");
      mqtt_client.subscribe(mqtt_topic_sub);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
      connect_attempts++;
    }
  }
  if (connect_attempts == 7) {
    Serial.println("MQTT connection failed");
    Serial.println("Restarting ESP8266");
    delay(5000);
     ESP.restart();
  }

}


// the setup function runs once when you press reset or power the board
void PubSubClient_setup() {
  mqtt_client.setServer(mqtt_server_ip, mqtt_port);
  mqtt_client.setCallback(callback);
  //mqtt_client.connect(mqtt_client_id.c_str());
  delay(100);
  PubSubClient_reconnect();
  }


//called at the modul setup to send the server the ip and mac of the modul
void PubSubClient_first_connet() {
        String ip = WiFi.localIP().toString().c_str();
        mqtt_client.publish(mqtt_topic_IP,ip.c_str());
        Serial.println("send ip to server");
        String mac = WiFi.macAddress().c_str();
        mqtt_client.publish(mqtt_topic_MAC,mac.c_str());
        Serial.println("send mac to server");

}


