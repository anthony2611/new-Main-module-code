 int last_motion;


//handels the motion sensor and sends the data to the server if ask or if the detector chanced value (connet a resistor to the pin to gound it)
void motino_detector_loop(int motino_pin, bool send){
    if (send)
    {
        //setup motion detector
        int motion_detector_state = digitalRead(motino_pin);
        //send motion value
        mqtt_client.publish(mqtt_device_topic_motion_detector, String(motion_detector_state).c_str());
    }

    //sends a 1 or a 0 if the state of the motion detector is chanced
    if (last_motion != digitalRead(motino_pin))
    {
        last_motion = digitalRead(motino_pin);
        //send motion value
        mqtt_client.publish(mqtt_device_topic_motion_detector, String(last_motion).c_str());

    }
    


}


//handels the pin setup for the motion detector
void motion_detector_setup(int motion_pin){
    pinMode(motion_pin,INPUT);

}