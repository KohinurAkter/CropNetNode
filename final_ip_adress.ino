#include <Arduino.h>
#include "ESP8266WiFi.h"
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <SX1278.h>
#include <SPI.h>

#define LORA_MODE  10
#define LORA_CHANNEL  CH_6_BW_125
#define LORA_ADDRESS            4
#define LORA_SEND_TO_ADDRESS    2
#define LORA_SEND_TO_ADDRESS    5
#define LORA_LED                0

int e;
char my_packet[120];
cahr payload[10];

// WiFi parameters to be configured
const char* ssid = "belkin.3e67";
const char* password = "d4d8d66c";

void setup()
{
  Serial.begin(9600);
  // Connect to WiFi
  WiFi.begin(ssid, password);

  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());

  delay(500);

  loraSetup();

}
void loop() {


  receivedData();
  delay(100);

  HTTPClient http;

  Serial.print("[HTTP] begin...\n");
  // configure traged server and url

  http.begin("http://amlan.pythonanywhere.com/project47/default/send_sensor_data.json");

  Serial.print("[HTTP] POST...\n");
  // start connection and send HTTP header
  int httpCode = http.GET(); //For Receiving data from web
  cahr payload = http.getChar(); //string type data is being receiving from web
// payload is a variable
  serial.println(getchar);
serial.println("------------------------------------------------------------");

  //http.addHeader("content-type", "text/json");
  int httpCode = http.POST(my_packet);
  Serial.println(httpCode);
    // httpCode will be negative on error
    if (httpCode > 0) {
      Serial.println("The HTTP code: ");
      Serial.print(httpCode);
      Serial.println("Working on HTTP Connection : - OK");
      Serial.println();
      // HTTP header has been send and Server response header has been handled
      //USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        //USE_SERIAL.println(my_packet);
      }
    } else {
      //USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      Serial.println("Got an Error !");
    }
    Serial.println("#########################################################################################");
    Serial.println();
sendData(payload);
}



void loraSetup()
{
  pinMode(LORA_LED, OUTPUT);

  // Open serial communications and wait for port to open:
  //Serial.begin(9600);

  // Print a start message
  Serial.println(F("sx1278 module and Arduino: receiving packets"));

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

  // Print a success message
  Serial.println(F("sx1278 configured finished"));
  Serial.println();
}


void receiveData();
{
  // Receive message for 10 seconds
  e = sx1278.receivePacketTimeout(10000);
  if (e == 0) {
    digitalWrite(LORA_LED, HIGH);
    delay(500);
    digitalWrite(LORA_LED, LOW);

    Serial.println(F("Package received!"));

    for (unsigned int i = 0; i < sx1278.packet_received.length; i++) {
      my_packet[i] = (char)sx1278.packet_received.data[i];
    }

    Serial.print(F("Message: "));
    Serial.println(my_packet);
    digitalWrite(LORA_LED, HIGH);
    delay(500);
    digitalWrite(LORA_LED, LOW);
  } else {
    Serial.print(F("Package received ERROR\n"));
  }
}


void sendData(char payload[]) {
  Serial.print("Message to be sent: ");

  e = sx1278.sendPacketTimeout(0, payload);
  Serial.println(F("Packet sent....."));
  if (e == 0) {
    digitalWrite(LORA_LED, HIGH);
    delay(500);
    digitalWrite(LORA_LED, LOW);
  }
}
