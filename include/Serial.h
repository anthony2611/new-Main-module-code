//voids setup serial monitor
void Serial_setup() {
  Serial.begin(Serial_baudrate);
#ifdef logo
  LOGO();
#endif
  Serial.println("");

  //print the config to the serial monitor
    Serial.println("#############################################################");
    Serial.print("monitor speed: ");
    Serial.println(Serial_baudrate);
    Serial.print("device name: ");
    Serial.println(device_name);
    Serial.print("mqtt server ip: ");
    Serial.println(mqtt_server_ip);
    Serial.print("mqtt port: ");
    Serial.println(mqtt_port);
    Serial.print("mqtt topic command: ");
    Serial.println(mqtt_topic_command);
    Serial.print("mqtt topic pub status: ");
    Serial.println(mqtt_topic_status);
    Serial.print("mqtt client id: ");
    Serial.println(mqtt_client_id);
    Serial.println("#############################################################");
    
}
