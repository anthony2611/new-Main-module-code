#include <Arduino.h>
//try to connect to wifi

void wifi_connect(const char* ssid, const char* password, int attempts) { 
  //  Serial.println("Connecting to WiFi network...");
  int trys = 0;
  while (trys <= attempts && WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, password);
    int i = 0;
    while (WiFi.status() != WL_CONNECTED && i < 10) {
      delay(500);
      Serial.print(".");
      i++;
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
    }
    trys++;
  }
}


void WIFI_setup() {
  WiFi.mode(WIFI_STA);
  WiFi.hostname(device_name);
  wifi_connect(WIFI_SSID1, WIFI_PASSWORD1, 5);
  if (WiFi.status() != WL_CONNECTED) {
    wifi_connect(WIFI_SSID2, WIFI_PASSWORD2, 5);
  }
  
}