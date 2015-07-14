/* Flood Sensor

This sketch will light up the LED on Pin 13 and send an RF signal, when water (anything conductive) bridges the gap in the sensor. 
  
incmve pimatic


*/

// Includes
#include <PimaticProbe.h> // Thanks to Oitzu for making the Generic class

#define senderPin 4 //
const int floodSensors = 2;     // the number of the Flood Sensor pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int floodSensorState = 0;         // variable for reading the floodSensors status

// RF part
long codeKit = 1111;  // Your unique ID for your Arduino node
int Bytes[30]; 
int BytesData[30]; 
int maximumRange = 200; // Maximum range sonar
int minimumRange = 0; // Minimum range sonar
long duration, distance; // Duration used to calculate distance
PimaticProbe probe = PimaticProbe(senderPin, codeKit);


void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the flood Sensor pin as an input:
  pinMode(floodSensors, INPUT);     
  pinMode(senderPin, OUTPUT);
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop(){
  Serial.println("Start loop");
  // read the state of the flood Sensor value:
  floodSensorState = digitalRead(floodSensors);

  // check if the flood Sensor is wet.
  // if it is, the floodSensorState is HIGH:
  if (floodSensorState == LOW) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
    int type = 3;
    int BytesType[] = {0,0,1,1}; //transmit value as sensor 3
    probe.transmit(true, floodSensorState, type, 6); // ([postive/negative], CounterValue, [type], 6)
    Serial.println(floodSensorState);
    delay(30000);
  } 
  
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
}
