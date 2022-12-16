//!this code uses better comments extaion (vscode) for better understanding and reading
//################################################# LIBRARIES ##############################################################
//!do not change the libraries!
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <PubSubClient.h>
  #include <ArduinoOTA.h>

//################################################# Discription ##############################################################

//?.█████╗.██████╗.███████╗██████╗.████████╗██╗...██╗██████╗.███████╗....███████╗.██████╗██╗███████╗███╗...██╗.██████╗███████╗
//?██╔══██╗██╔══██╗██╔════╝██╔══██╗╚══██╔══╝██║...██║██╔══██╗██╔════╝....██╔════╝██╔════╝██║██╔════╝████╗..██║██╔════╝██╔════╝
//?███████║██████╔╝█████╗..██████╔╝...██║...██║...██║██████╔╝█████╗......███████╗██║.....██║█████╗..██╔██╗.██║██║.....█████╗..
//?██╔══██║██╔═══╝.██╔══╝..██╔══██╗...██║...██║...██║██╔══██╗██╔══╝......╚════██║██║.....██║██╔══╝..██║╚██╗██║██║.....██╔══╝..
//?██║..██║██║.....███████╗██║..██║...██║...╚██████╔╝██║..██║███████╗....███████║╚██████╗██║███████╗██║.╚████║╚██████╗███████╗
//?╚═╝..╚═╝╚═╝.....╚══════╝╚═╝..╚═╝...╚═╝....╚═════╝.╚═╝..╚═╝╚══════╝....╚══════╝.╚═════╝╚═╝╚══════╝╚═╝..╚═══╝.╚═════╝╚══════╝

//Moudule code for IOT systems form Aperture Science

//################################################# Config ##############################################################

//serial config
  #define Serial_baudrate 115200        //baudrate for serial communication

//wifi config
  #define WIFI_SSID1 ""              //wifi name 1
  #define WIFI_PASSWORD1 ""                     //wifi password 1
  //fallback wifi config                
  #define WIFI_SSID2 ""         //wifi name 2
  #define WIFI_PASSWORD2 ""                    //wifi password 2

//mqtt config
  #define mqtt_server_ip "192.168.178.44"     //mqtt server ip
  #define mqtt_port 1883                      //mqtt port
  char* device_name = "XXX_ESP8266";         //device name PLEASE CHANGE 
  String main_topic = "sensor/";              //the main topic for all devices
  String relay_tpoic = "relays/";              //the relay topic for the relays if defined


//please config the sensors you whant to have
//uncomment the sensors you have and set the pin number for the sensors and unncomment the sensor topic
  #define dallas_temp                         //dell temperature sensor if you have one 
        #define dallas_temp_pin  2                //dell fan sensor if you have one 
  #define LDR                                 //LDR sensor if you have one
        #define LDR_pin A0                        //LDR pin (analog pin / ADC)
  #define motion_detector                     //motion detector if you have one
        #define motion_detector_pin  3            //motion detector pin

//please config the actuators you whant to have
 #define relay                            //relay if you have one or more uncomment the relays you have and set the pin number for the relays and unncomment the relay topic
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
    String mqtt_device_topic_string = main_topic + device_name;           //device topic as string if needed
    const char* mqtt_device_topic = mqtt_device_topic_string.c_str();     //device topic as char* if needed
    String mqtt_topic_IP_string = mqtt_device_topic_string + "/ip";       //constructing the IP adress string
    const char* mqtt_topic_IP = mqtt_topic_IP_string.c_str();             //converting IP string to a char*
    String mqtt_topic_MAC_string = mqtt_device_topic_string + "/mac";     //constructing the Mac adress string
    const char* mqtt_topic_MAC = mqtt_topic_MAC_string.c_str();           //converting the mac string to a char*
    String mqtt_topic_sub_string = mqtt_device_topic_string + "/command"; //constructing the command line string
    const char* mqtt_topic_sub = mqtt_topic_sub_string.c_str();           //converting the command string to a char*
    String mqtt_topic_pub_string = mqtt_device_topic_string + "/pub";     //not needed yet
    const char* mqtt_topic_pub = mqtt_topic_pub_string.c_str();           //not needed yet
    String mqtt_topic_pub_status_string = mqtt_device_topic_string + "/status"; //constructing the status string
    const char* mqtt_topic_pub_status = mqtt_topic_pub_status_string.c_str();   //converting status string to a char*




//################################################# MY Headers/Libs and some more string genrating ##############################################################
  #include <LOGO.h>
  #include <OTAupdater.h>
  #include <WIFI.h>
  #include <MQTT.h>
  #include <Serial.h>


  //includs for the sensor that are enabled
    #ifdef dallas_temp
      #include <dells_temp.h>
    #endif
    #ifdef LDR
      #include <LDR.h>
    #endif
    #ifdef motion_detector
      #include <motion_detector.h>
    #endif
    #ifdef relay
      //topic for the relays
      String mqtt_topic_relay_string = relay_tpoic + device_name;           //device topic as string if needed
      const char* mqtt_topic_relay = mqtt_topic_relay_string.c_str();       //device topic as char* if needed

      //making topic for eche defined relay
      #ifdef relay1
        String mqtt_topic_relay1_string = mqtt_topic_relay_string + "/relay1";   //constructing the relay1 string
        const char* mqtt_topic_relay1 = mqtt_topic_relay1_string.c_str();   //converting relay1 string to a char*
      #endif
      #ifdef relay2
        String mqtt_topic_relay2_string = mqtt_topic_relay_string + "/relay2";   //constructing the relay2 string
        const char* mqtt_topic_relay2 = mqtt_topic_relay2_string.c_str();   //converting relay2 string to a char*
      #endif
      #ifdef relay3
        String mqtt_topic_relay3_string = mqtt_topic_relay_string + "/relay3";   //constructing the relay3 string
        const char* mqtt_topic_relay3 = mqtt_topic_relay3_string.c_str();   //converting relay3 string to a char*
      #endif
      #ifdef relay4
        String mqtt_topic_relay4_string = mqtt_topic_relay_string + "/relay4";   //constructing the relay4 string
        const char* mqtt_topic_relay4 = mqtt_topic_relay4_string.c_str();   //converting relay4 string to a char*
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
    PubSubClient_first_connet();

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
    