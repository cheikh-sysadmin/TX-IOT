#include <SPI.h>
#include <LoRa.h>
#include <HCSR04.h>

int TRIGGER=13, ECHO=12;
long distance;
UltraSonicDistanceSensor distanceSensor(TRIGGER, ECHO);

void setup() {
  Serial.begin(9600);
  //Ultrasonic sensor

  while (!Serial);

  Serial.println("LoRa Sender");
 if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  distance=distanceSensor.measureDistanceCm();
Serial.println(distance);
Serial.print("Sending packet: ");
String data="2:";
data+=distance;
Serial.println(data); 

  // send packet
  LoRa.beginPacket();
  LoRa.print(data);
  //LoRa.print(counter);
  LoRa.endPacket();

  delay(10000);
}
