/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include "DHT.h"
#include <ESP8266WiFi.h>


#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "HOST"; // add your host of network
const char* password = "PASSWORD"; // add your password of net

const char* host = "maker.ifttt.com";
const char *privateKey = "privateKey "; // add your privateKey .
const char *event = "IOTMONITOR";
String value1, value2, value3;
String postData = "";

void setup() {
  Serial.begin(115200);  
  dht.begin();
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void loop() {

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();   
  senddatatoIFTTT(String(t),String(h));
  delay(5000);
}

