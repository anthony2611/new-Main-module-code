
![Logo](img/1280px-Aperture_Laboratories_Logo_wiht.png)


Aperture Science Sweet Home System modul code  

This is the main modul code for mqtt clients in the Sweet Home System


## Features

- Motion detection
- OTA updates
- LDR sensor
- Temperature sensor 

## To do:

- Relay moule

- Optimizations


## Variables you need to change

There are some values you need to change 

`Serial_baudrate` if you what to use serial/USB (default is 115200)

`WIFI_SSID1` main wifi to connect to

`WIFI_PASSWORD1` is the password of this wifi

`WIFI_SSID2` is the backup wifi if the main is not in reach or goes offline

`WIFI_PASSWORD2` is the password of the backup wifi

`mqtt_server_ip` is the IP of the MQTT broker server

`mqtt_port` sets the port of the broker

`device_name`  This is the name of the module that is shown on the server that's connecting to and this is also the name of the module in the wifi network 

`main_topic` this is the main topic under every module is shown in the broker 




## Variables Refernce

| Parameter | Type     | is a change Required?              |
| :-------- | :------- | :------------------------- |
| `Serial_baudrate` | `int` | **Not Required** default is 115200  |
| `WIFI_SSID1` | `const char*` | **Required**.  |
| `WIFI_PASSWORD1` | `const char*` | **Required**. |
| `WIFI_SSID2` | `const char*` | **Required**.  |
| `WIFI_PASSWORD2` | `const char*` | **Required**.  |
| `mqtt_server_ip` | `const char*` | **Required**.  |
| `mqtt_port` | `uint16_t` | **Not Required** If you have default mqtt port  |
| `device_name` | `char*` | **Required**. this needs to be unique for every module  |
| `main_topic` | `string` | **Not Required** default is `sensor/`  |


## Some more explenation

</p><p>The <code>Serial_baudrate</code> variable defines the baud rate used for serial communication with the device.</p><p>The <code>WIFI_SSID1</code> and <code>WIFI_PASSWORD1</code> variables define the credentials for the device's primary WiFi connection. The <code>WIFI_SSID2</code> and <code>WIFI_PASSWORD2</code> variables define the credentials for a fallback WiFi connection in case the primary connection fails.</p><p>The <code>mqtt_server_ip</code> and <code>mqtt_port</code> variables define the IP address and port number of the MQTT server that the device will connect to. The <code>device_name</code> and <code>main_topic</code> variables define the name of the device and the main topic for all devices, respectively.</p><p>The code also includes several <code>#define</code> statements that can be used to enable or disable certain features, such as the use of a Dallas temperature sensor, an LDR sensor, and a motion detector. These features can be enabled or disabled by commenting out the <code>#define</code> statement for the corresponding feature.</p><p>In order to use this code, the user will need to modify the <code>WIFI_SSID1</code>, <code>WIFI_PASSWORD1</code>, <code>WIFI_SSID2</code>, <code>WIFI_PASSWORD2</code>, <code>mqtt_server_ip</code>, <code>mqtt_port</code>, <code>device_name</code>, and <code>main_topic</code> variables to match their own setup. The user may also need to comment out or uncomment the <code>#define</code> statements for the desired features.</p>