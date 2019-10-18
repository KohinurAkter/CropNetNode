#include "SX1278.h"
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include<dht.h>


#define LORA_MODE             10
#define LORA_CHANNEL          CH_6_BW_125
#define LORA_ADDRESS          3
#define LORA_SEND_TO_ADDRESS  4
#define LORA_LED              0


//sensor pin

#define temperature           7

#define DHT11_PIN             4
#define moisture              A0
dht DHT;
OneWire oneWire(temperature);
DallasTemperature sensors(&oneWire);

//variable declare
float tempC = 0;
int e;
int z;
int lightValue = 0;
int CO2value = 0;
String json="";

String DEVICE_ID = "NODE-700";

char my_packet[100];    
char message [100];


void setup()
{
  pinMode(LORA_LED, OUTPUT);

  pinMode(temperature  , INPUT);

  pinMode(DHT11_PIN, INPUT);

  pinMode(moisture , INPUT);

  sensors.begin();
  Serial.begin(115200);                                                           // Open serial communications and wait for port to open:
  Serial.println(F("sx1278 module and Arduino: receives and transmits packets")); // Print a start message

  loraSetup();
}

void loop(void)
{
  //temperature
  sensors.requestTemperatures();
  tempC = sensors.getTempCByIndex(0);
  delay(1000);
  Serial.print("Tempeture:    ");
  Serial.print(tempC);
  Serial.println();

  //humidity
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Humidity:     " );
  Serial.print(DHT.humidity, 1);
  Serial.println();

  delay(1000);

  //moisture
  int moistureValue = analogRead(moisture);
   Serial.print("moisture:     ");
  Serial.print(moistureValue);
  Serial.println("");
  delay(1);

 // String json="{\"temperature\":\""+ tempC +"\",\"Humidity\":\""+DHT.humidity+"\",\"Moisture\":\""+moistureValue+"\"}";
json+="{\"node_id\":\"";
json+=DEVICE_ID;
json+="\",\"temperature\":\"";
json+=tempC;
json+="\",\"humidity\":\"";
json+=DHT.humidity;
json+="\",\"mosture\":\"";
json+=moistureValue;
json+="\",\"light\":\"";
json+=lightValue;
json+="\",\"co2gas\":\"";
json+=CO2value;
json+="\"}";
Serial.println("Printing Main Json");
 Serial.println(json);
 //Serial.println(json);
  
  //String buff = DEVICE_ID + " " + "Temperature:" + tempC + " Humidity:" + DHT.humidity + "Moisture:" + moistureValue ;
  json.toCharArray(message, 120);
  Serial.println("Transfered Data to Message : ");
  Serial.println(message);

  
 // Serial.println(tempC);
 //Serial.println(DHT.humidity);
 //Serial.println(moistureValue);

  sendData(message);
  
//  receiveData();
  delay(500);
  Serial.println("####################################################################################################");
json="";
//message='';  
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

  e = sx1278.sendPacketTimeout(0, message);
  Serial.println(F("Packet sent....."));
  if (e == 0) {
    digitalWrite(LORA_LED, HIGH);
    delay(500);
    digitalWrite(LORA_LED, LOW);
  }
}

/*
void receiveData() {
  z = sx1278.receivePacketTimeout(10000);
  if (z == 0) {
    digitalWrite(LORA_LED, HIGH);
    delay(1000);
    digitalWrite(LORA_LED, LOW);

    Serial.println(F("Package received!"));

    for (unsigned int i = 0; i < sx1278.packet_received.length; i++) {
      my_packet[i] = (char)sx1278.packet_received.data[i];
      yield();
    }

    Serial.print(F("Message:  "));
    Serial.println(my_packet);
  } else {
    // Serial.print(F("Package received ERROR\n"));
  }
}
*/



