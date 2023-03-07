//Setup the mqtt mqtt_client

String payloadString = "";

/*this is the main MQTT function 
this runs any time the server sends a command or String to the client

#################################################################################
avelable commands are:
  hello mqtt_client     - the server will respond with hello server
  get                   - the server will respond with the data of the sensors
  get ip                - the server will respond with the ip of the mqtt_client
  get mac               - the server will respond with the mac of the mqtt_client 
#################################################################################
this commands are only avalable on the mqtt command topic (mqtt_topic_command: [main_tpoic]/[device_name]/command)
any other tpics will be ignored or processed somewhere else in the code for example the relays in the relay.h file
 */

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
  if (String(topic) == mqtt_topic_command) {

        // if the payload is "hello mqtt_client" then print "hello server" to status topic
      if (payloadString == "hello mqtt_client") {
          mqtt_client.publish(mqtt_topic_status, "hello server");
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
          mqtt_client.publish(mqtt_topic_ip,ip.c_str());
          Serial.println("send ip to server");
          payloadString.clear();
      }
      //if the payload is "Get MAC" publish the mac to the mqtt topic "info/mac"
      if (payloadString == "get mac") {
          String mac = WiFi.macAddress().c_str();
          mqtt_client.publish(mqtt_topic_mac,mac.c_str());
          Serial.println("send mac to server");
          payloadString.clear();
      }
      //if the payload is not clear the print "unknown command" to the mqtt topic "info/status"
      if (payloadString != "") {
          mqtt_client.publish(mqtt_topic_status, "unknown command");
          Serial.println("unknown command");
          payloadString.clear();
      }
      //clean the command topic
      mqtt_client.publish(mqtt_topic_command, "");
  }
  //make topic and payload global
  mqtt_topic = topic;
  mqtt_payload = payloadString;
  //clear the payloadString
  payloadString.clear();
  


}

//mqtt reconnect function
void PubSubClient_reconnect() {
  while (!mqtt_client.connected() && connect_attempts <= mqtt_attempts) {
    mqtt_client.connect(device_name);
    Serial.print("Attempting MQTT connection...");
    if (mqtt_client.connect(device_name)) {
      Serial.println("connected");
      mqtt_client.subscribe(mqtt_topic_command);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
      connect_attempts++;
    }
  }

  if (connect_attempts >= mqtt_attempts) {
    Serial.println("MQTT connection failed");
    Serial.println("Restarting in 5 seconds");
    delay(5000);
     ESP.restart();
  }

  String ip = WiFi.localIP().toString().c_str();
  mqtt_client.publish(mqtt_topic_ip,ip.c_str());
  Serial.println("send ip to server");
  String mac = WiFi.macAddress().c_str();
  mqtt_client.publish(mqtt_topic_mac,mac.c_str());
  Serial.println("send mac to server");

}


// the setup function runs once when you press reset or power the board
void PubSubClient_setup() {
  mqtt_client.setServer(mqtt_server_ip, mqtt_port);
  mqtt_client.setCallback(callback);
  //mqtt_client.connect(mqtt_client_id.c_str());
  delay(100);
  PubSubClient_reconnect();
  }




