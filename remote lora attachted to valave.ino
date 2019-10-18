#include "SX1278.h"
#include <SPI.h>


#define LORA_MODE             10
#define LORA_CHANNEL          CH_6_BW_125
#define LORA_ADDRESS          5
//#define LORA_SEND_TO_ADDRESS  2
#define LORA_LED              0

int e;
cahr payload[10];

void setup()
{
  Serial.begin(9600);
  
  loraSetup();

}

void loop() {


  receivedData();
  delay(100);
    Serial.println("#########################################################################################");
    Serial.println("");
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


void receivedData()
{
  // Receive message for 10 seconds
  e = sx1278.receivePacketTimeout(10000);
  if (e == 0) {
    digitalWrite(LORA_LED, HIGH);
    delay(500);
    digitalWrite(LORA_LED, LOW);

    Serial.println(F("Package received!"));

     for (unsigned int i = 0; i < sx1278.packet_received.length; i++) {
      payload[i] = (char)sx1278.packet_received.data[i];
    }
    

    Serial.print(F("Message: "));
    Serial.println(payload);
    digitalWrite(LORA_LED, HIGH);
    delay(500);
    digitalWrite(LORA_LED, LOW);
  } else {
    Serial.print(F("Package received ERROR\n"));
  }
}