
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
