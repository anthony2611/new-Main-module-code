//################################################# LIBRARIES ##############################################################
//do not change the libraries
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <PubSubClient.h>
  #include <ArduinoOTA.h>

//################################################# logo ##############################################################

//.█████╗.██████╗.███████╗██████╗.████████╗██╗...██╗██████╗.███████╗....███████╗.██████╗██╗███████╗███╗...██╗.██████╗███████╗
//██╔══██╗██╔══██╗██╔════╝██╔══██╗╚══██╔══╝██║...██║██╔══██╗██╔════╝....██╔════╝██╔════╝██║██╔════╝████╗..██║██╔════╝██╔════╝
//███████║██████╔╝█████╗..██████╔╝...██║...██║...██║██████╔╝█████╗......███████╗██║.....██║█████╗..██╔██╗.██║██║.....█████╗..
//██╔══██║██╔═══╝.██╔══╝..██╔══██╗...██║...██║...██║██╔══██╗██╔══╝......╚════██║██║.....██║██╔══╝..██║╚██╗██║██║.....██╔══╝..
//██║..██║██║.....███████╗██║..██║...██║...╚██████╔╝██║..██║███████╗....███████║╚██████╗██║███████╗██║.╚████║╚██████╗███████╗
//╚═╝..╚═╝╚═╝.....╚══════╝╚═╝..╚═╝...╚═╝....╚═════╝.╚═╝..╚═╝╚══════╝....╚══════╝.╚═════╝╚═╝╚══════╝╚═╝..╚═══╝.╚═════╝╚══════╝

//Moudule code for IOT systems form Aperture Science

//################################################# Config ##############################################################

//serial config
  #define Serial_baudrate 115200        //baudrate for serial communication

//wifi config
  #define WIFI_SSID1 "zimmi w-lan"              //wifi name 1
  #define WIFI_PASSWORD1 ""                     //wifi password 1
  //fallback wifi config                
  #define WIFI_SSID2 "fritz-rep-klein"         //wifi name 2
  #define WIFI_PASSWORD2 ""                    //wifi password 2

//mqtt config
  #define mqtt_server_ip "192.168.178.44"     //mqtt server ip
  #define mqtt_port 1883                      //mqtt port
  char* device_name = "XXX_ESP8266";         //device name PLEASE CHANGE 
  String main_topic = "sensor/";              //the main topic for all devices

//please config the sensors you whant to have
  #define dallas_temp                         //dell temperature sensor if you have one 
        #define dallas_temp_pin  2                //dell fan sensor if you have one 
  #define LDR                                 //LDR sensor if you have one
        #define LDR_pin A0                        //LDR pin (analog pin / ADC)
  #define motion_detector                     //motion detector if you have one
        #define motion_detector_pin  3            //motion detector pin
  //#define relay                            //not yet implemented
        //#define relay1
        //#define relay2
        //#define relay3
        //#define relay4



//################################################# Libraries to setup and some string gerneating ##############################

//DO NOT CHANGE anything below this line unless you know what you are doing
  //setup for wifi and mqtt
    WiFiClient espClient;                 //create the wifi object
    PubSubClient mqtt_client(espClient);  //create the mqtt client object
    bool send_data = false;               //send data is for the moduls to now when to send data to the server 
    int connect_attempts = 0;             //mqtt connect attemps at first run
    #define mqtt_client_id device_name    //set mqtt client id (normaly the device name)

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




//################################################# MY Headers/Libs ##############################################################
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
      #include <relay.h>
    #endif



//################################################# MAIN Arduino code ##############################################################
  void setup() {
    Serial_setup();
    WIFI_setup();
    myOTAupdatesetup();
    PubSubClient_setup();
    PubSubClient_first_connet();

    #ifdef motion_detector
      motion_detector_setup(motion_detector_pin);
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


    //sets the send_data bool to false because  this is the last code in the loop and 
    //any data to send should be allready sended to the mqtt server
    if (send_data)
    {
      send_data = false;
    }
    
  }
    