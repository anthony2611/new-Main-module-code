
//The LDR is an analog sensor and must be connetet to a ADC (pleace use a resistor to ground the analog pin) 
void LDR_sensor(int pin_analog,bool send){
    if (send)
    {
        //get LDR value
        int LDR_value = analogRead(pin_analog);
        //send LDR value
        mqtt_client.publish(mqtt_device_topic_LDR, String(LDR_value).c_str());
        Serial.println("sending LDR value to server");
    }
    

}