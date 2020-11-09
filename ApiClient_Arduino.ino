#include "Arduino.h"
#include "heltec.h"
#include <WiFi.h>
#include "secrets.h"
#include "src/ApiClient.h"



//counter for connectiong animation
int loadingstep=0;

ApiClient* apiClient;

//display connection animation
//display task and comment below
void loadingAnimation(String task, String comment){
  Heltec.display->clear();

  //create animation step
  switch (loadingstep%4) {
    case 0:
      Heltec.display->drawString(0, 0, task);
      Heltec.display->drawString(0, 10, comment);
      break;
    case 1:
      Heltec.display->drawString(0, 0, task + ".");
      Heltec.display->drawString(0, 10, comment);
      break;
    case 2:
      Heltec.display->drawString(0, 0, task + "..");
      Heltec.display->drawString(0, 10, comment);
      break;
    case 3:
      Heltec.display->drawString(0, 0, task + "...");
      Heltec.display->drawString(0, 10, comment);
      break;
  }

  Heltec.display->display();
  loadingstep++;
  delay(100);
}

//connect to serial
void connectToSerial(){
  while (!Serial){ // wait for serial port to connect. Needed for native USB
    loadingAnimation("Connecting", "to Serial");
  }
}

//connect to wifi
void connectToWifi(String ssid, String password){
  //configure
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true); 

  //start connection
  WiFi.begin(SSID, PASSWORD);

  //wait for connectiom
  while(WiFi.status() != WL_CONNECTED){
    loadingAnimation("Connecting", "to " + ssid);
  }

}

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);

  //init disaly 
  Heltec.display->setContrast(255);
  Heltec.display->clear();

  connectToSerial();
  connectToWifi(SSID, PASSWORD);

  Heltec.display->clear();
  Heltec.display->display();

  WiFiClient wifiClient;
  apiClient = new ApiClient();
  //Serial.println(apiClient->connect("https://api.spotify.com"));
}

void loop() {
  
}

