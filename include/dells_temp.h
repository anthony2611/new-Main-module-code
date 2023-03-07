#include <OneWire.h> 
#include <DallasTemperature.h>


//dalas temps are temp-sensors white a onewire bus, so you need to add a 4,7kohm resistor between 5v and the data/bus pin
//the void handels the setup of the onewire bus and gets the data form the sensor and sends it to the server
void dallas_temps_loop(int bus_pin, bool send){
    if (send)
    {
        //setup dallas temp sensor
        OneWire oneWire(bus_pin);
        DallasTemperature sensors(&oneWire);
        sensors.begin();
        //add /temp to mqtt_device_topic
        sensors.requestTemperatures(); 
        float tempC = sensors.getTempCByIndex(0);
        Serial.print("Temp: ");
        Serial.println(tempC);
        Serial.println("Sending temp to server");
        //send temp value
        mqtt_client.publish(mqtt_device_topic_temp, String(tempC).c_str());
        
    }

}

