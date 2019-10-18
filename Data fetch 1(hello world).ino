//#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

//#include "SX1278.h"
//#include <SPI.h>

/*
#define LORA_MODE  10
#define LORA_CHANNEL  CH_6_BW_125
#define LORA_ADDRESS            4
#define LORA_SEND_TO_ADDRESS    2
#define LORA_LED                5

int e;
char my_packet[120];
*/


const char* ssid = "HUAWEI GT3";
const char* password = "froozen2028";

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  
  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("connecting..");

  }
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address
  /*Serial.println(WiFi.localIP());

  delay(500);

  loraSetup();
*/
}


void loop() {

/*
  receivedData();
  delay(100);
*/

  HTTPClient http;

  Serial.print("[HTTP] begin...\n");
  // configure traged server and url

  http.begin("http://web2py.com/examples/simple_examples/hello1");

  //Serial.print("[HTTP] POST...\n");

  // start connection and send HTTP header
  int httpCode = http.GET(); //For Receiving data from web
  
if (httpCode>0) {
      Serial.println("The HTTP code: ");
      Serial.print(httpCode);
      Serial.println("Working on HTTP Connection : - OK");
      Serial.println();
      String payload = http.getString();
        Serial.println(payload);
      
    } else {
      
      Serial.println("Got an Error !");
      Serial.print(httpCode);
    }

    Serial.println("#########################################################################################");

 delay(1000);
}