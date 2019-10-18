#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <SX1278.h>
#include <SPI.h>

#define LORA_MODE  10
#define LORA_CHANNEL  CH_6_BW_125
#define LORA_ADDRESS            4
#define LORA_SEND_TO_ADDRESS    2
#define LORA_LED                5

int e;
/*char my_packet[120];

char my_packet[100];  
*/  
char message [10];

const char* ssid = "HUAWEI GT3";
const char* password = "froozen2028";

void setup()
{
  pinMode(LORA_LED, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  
  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("connecting..");                                                           
  }
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(F("sx1278 module and Arduino: receives and transmits packets")); // Print a start message

  loraSetup();
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
        payload.toCharArray(message,10);
      
    } else {
      
      Serial.println("Got an Error !");
      Serial.print(httpCode);
    }

    Serial.println("#########################################################################################");
   sendData(message);
  delay(1000);
}

void loraSetup() {
  // Power ON the module
  if (sx1278.ON() == 0) {
    Serial.println(F("Setting power ON: SUCCESS "));
  } else {
    Serial.println(F("Setting power ON: ERROR "));
  }

  // Set transmission mode and print the result
  if (sx1278.setMode(LORA_MODE) == 0) {
    Serial.println(F("Setting Mode: SUCCESS "));
  } else {
    Serial.println(F("Setting Mode: ERROR "));
  }

  // Set header
  if (sx1278.setHeaderON() == 0) {
    Serial.println(F("Setting Header ON: SUCCESS "));
  } else {
    Serial.println(F("Setting Header ON: ERROR "));
  }

  // Select frequency channel
  if (sx1278.setChannel(LORA_CHANNEL) == 0) {
    Serial.println(F("Setting Channel: SUCCESS "));
  } else {
    Serial.println(F("Setting Channel: ERROR "));
  }

  // Set CRC
  if (sx1278.setCRC_ON() == 0) {
    Serial.println(F("Setting CRC ON: SUCCESS "));
  } else {
    Serial.println(F("Setting CRC ON: ERROR "));
  }

  // Select output power (Max, High, Intermediate or Low)
  if (sx1278.setPower('M') == 0) {
    Serial.println(F("Setting Power: SUCCESS "));
  } else {
    Serial.println(F("Setting Power: ERROR "));
  }

  // Set the node address and print the result
  if (sx1278.setNodeAddress(LORA_ADDRESS) == 0) {
    Serial.println(F("Setting node address: SUCCESS "));
  } else {
    Serial.println(F("Setting node address: ERROR "));
  }

  // Print a success


  Serial.println(F("sx1278 configured finished"));
  Serial.println();
}
void sendData(char message[]) {
  Serial.print("Message to be sent: ");

  /*e = sx1278.sendPacketTimeout(0, message);
  Serial.println(F("Packet sent....."));
  */
  e = sx1278.sendPacketTimeout(0,message);
  if (e == 0) {
    digitalWrite(LORA_LED, HIGH);
    delay(500);
    digitalWrite(LORA_LED, LOW);
  }
  Serial.println("sent...");
  delay(5000);
  
}