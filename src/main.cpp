//this code uses better comments extaion (vscode) for better understanding and reading
//################################################# LIBRARIES ##############################################################
//!do not change the libraries!
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <PubSubClient.h>
  #include <ArduinoOTA.h>
  #include <DNSServer.h>
  #include <ESP8266WebServer.h>
  #include <WiFiManager.h> 

//################################################# Discription ##############################################################

//?.█████╗.██████╗.███████╗██████╗.████████╗██╗...██╗██████╗.███████╗....███████╗.██████╗██╗███████╗███╗...██╗.██████╗███████╗
//?██╔══██╗██╔══██╗██╔════╝██╔══██╗╚══██╔══╝██║...██║██╔══██╗██╔════╝....██╔════╝██╔════╝██║██╔════╝████╗..██║██╔════╝██╔════╝
//?███████║██████╔╝█████╗..██████╔╝...██║...██║...██║██████╔╝█████╗......███████╗██║.....██║█████╗..██╔██╗.██║██║.....█████╗..
//?██╔══██║██╔═══╝.██╔══╝..██╔══██╗...██║...██║...██║██╔══██╗██╔══╝......╚════██║██║.....██║██╔══╝..██║╚██╗██║██║.....██╔══╝..
//?██║..██║██║.....███████╗██║..██║...██║...╚██████╔╝██║..██║███████╗....███████║╚██████╗██║███████╗██║.╚████║╚██████╗███████╗
//?╚═╝..╚═╝╚═╝.....╚══════╝╚═╝..╚═╝...╚═╝....╚═════╝.╚═╝..╚═╝╚══════╝....╚══════╝.╚═════╝╚═╝╚══════╝╚═╝..╚═══╝.╚═════╝╚══════╝

//Moudule code for IOT systems form Aperture Science
/*
IoT system code for an ESP8266 microcontroller that uses Wi-Fi and MQTT to communicate with a server. It includes the ability to read data from various sensors and control actuators (relays).
There are several configurations that need to be set up, including serial communication baud rate, Wi-Fi SSIDs and passwords, MQTT server IP and port, and device name.
The sensors and actuators that are used are also configured in the code. The sensors that can be used are: Dallas temperature sensor, LDR sensor, and motion detector.
*/

//################################################# Config ##############################################################

//serial config
  #define Serial_baudrate 115200        //baudrate for serial communication
  //comment the line below if you dont want to see the logo and also save some memory
  #define logo                            //logo for the serial monitor

//wifi config
  #define WIFI_SSID1 ""              //wifi name 1
  #define WIFI_PASSWORD1 ""                     //wifi password 1
  //fallback wifi config                
  #define WIFI_SSID2 ""         //wifi name 2
  #define WIFI_PASSWORD2 ""                    //wifi password 2
  //wifi attemts to connect
  #define WIFI_ATTEMPTS 5

//mqtt config
  #define mqtt_server_ip "192.168.178.44"     //mqtt server ip
  #define mqtt_port 1883                      //mqtt port
  char* device_name = "XXX_ESP8266";          //device name PLEASE CHANGE 
  String main_topic = "sensor/";              //the main topic for all devices
  String relay_tpoic = "relays/";             //the relay topic for the relays if defined
  #define mqtt_attempts 5                      //mqtt attemts to connect


//please config the sensors you whant to have
//uncomment the sensors you have and set the pin number for the sensors and unncomment the sensor topic
  #define dallas_temp                         //dell temperature sensor if you have one 
        #define dallas_temp_pin  2                //dell fan sensor if you have one 
  #define LDR                                 //LDR sensor if you have one
        #define LDR_pin A0                        //LDR pin (analog pin / ADC)
  #define motion_detector                     //motion detector if you have one
        #define motion_detector_pin  3            //motion detector pin

//please config the actuators you whant to have
 #define relay                            //relay if you have one or more uncomment the relays you have and set the pin number for the relays 
                                          //and unncomment the main relay topic
        #define relay1 4                   //relay 1 pin (digital pin)
        #define relay2 5                   //relay 2 pin (digital pin)
        #define relay3 14                  //relay 3 pin (digital pin)
        #define relay4 12                  //relay 4 pin (digital pin)   



//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!DO NOT CHANGE anything below this line unless you know what you are doing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//################################################# Libraries to setup and some string genrating ##############################


  //setup for wifi and mqtt
    WiFiClient espClient;                 //create the wifi object
    PubSubClient mqtt_client(espClient);  //create the mqtt client object
    bool send_data = false;               //send data is for the moduls to now when to send data to the server 
    int connect_attempts = 0;             //mqtt connect attemps at first run
    #define mqtt_client_id device_name    //set mqtt client id (normaly the device name)
    String mqtt_topic;
    String mqtt_payload;

      //gereating the mqtt_device_topic_string and any other mqtt stuff
      String device_topic = main_topic + device_name;
      const char* mqtt_topic_ip = (device_topic + "/ip").c_str();
      const char* mqtt_topic_mac = (device_topic + "/mac").c_str();
      const char* mqtt_topic_command = (device_topic + "/command").c_str();
      const char* mqtt_topic_status = (device_topic + "/status").c_str();

//################################################# MY Headers/Libs and some more string genrating ##############################################################
#ifdef logo
  #include <LOGO.h>
#endif
  #include <OTAupdater.h>
  #include <WIFI.h>
  #include <MQTT.h>
  #include <Serial.h>



  //includs for the sensor that are enabled
    #ifdef dallas_temp
      //topic for the dell temp sensor
      const char* mqtt_device_topic_temp = (device_topic + "/temp").c_str();
      #include <dells_temp.h>
    #endif

    #ifdef LDR
      //topic for the LDR
      const char* mqtt_device_topic_LDR = (device_topic + "/LDR").c_str();
      #include <LDR.h>
    #endif

    #ifdef motion_detector
       //topic for the motion detector
      const char* mqtt_device_topic_motion_detector = (device_topic + "/motion_detector").c_str();
      #include <motion_detector.h>
    #endif

    #ifdef relay
      //topic for the relays
      String relay_topic = relay_tpoic + device_name;
      //making topic for eche defined relay
      #ifdef relay1
        const char* mqtt_topic_relay1 = (relay_topic + "/relay1").c_str();
      #endif
      #ifdef relay2
        const char* mqtt_topic_relay2 = (relay_topic + "/relay2").c_str();
      #endif
      #ifdef relay3
        const char* mqtt_topic_relay3 = (relay_topic + "/relay3").c_str();
      #endif
      #ifdef relay4
        const char* mqtt_topic_relay4 = (relay_topic + "/relay4").c_str();
      #endif
      //includs for the relays
      #include <relay.h>
    #endif



//################################################# MAIN Arduino code ##############################################################
  void setup() {
    Serial_setup();
    WIFI_setup();
    myOTAupdatesetup();
    PubSubClient_setup();
   

    //setup for the motion detection if enabled
    #ifdef motion_detector
      motion_detector_setup(motion_detector_pin);
    #endif 
    //setup for the relays if enabled 
    #ifdef relay
      relay_setup();
    #endif

  }

  void loop() {
    myOTAupdateloop();
    PubSubClient_reconnect();
    mqtt_client.loop();

    //includs for the sensors if enabled
    #ifdef LDR
      LDR_sensor(LDR_pin,send_data);
    #endif

    #ifdef dallas_temp
      dallas_temps_loop(dallas_temp_pin,send_data);
    #endif

    #ifdef motion_detector
      motino_detector_loop(motion_detector_pin,send_data);
    #endif
    
    #ifdef relay
      relay_loop();
    #endif


    //sets the send_data bool to false because  this is the last code in the loop and 
    //any data to send should be allready sended to the mqtt server
    if (send_data)
    {
      send_data = false;
    }
    
  }
    