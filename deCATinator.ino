#include "Timer.h"

// Declare Constants

int zoneSensor[] = { 2, 3, 4, 5, 6 };
int zoneValve[] = { 8, 9, 10, 11, 12 };
//int sensorValveMap[] = {};

int numZones = 5;

const int ledPin =   13;             // Built-in LED
const int ledBlinkTime = 500;      // Blink one for half a second while calibrating

Timer t;
Timer secondTimer;

// Wait for the seonsor to calibrate (20 - 60 seconds according to datasheet)
// 60 Seconds in milliseconds
const unsigned int calibrationTime = 120000;
const unsigned int fifteenSecs = 5000;

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  
  for (int currentPin = 0; currentPin < numZones; currentPin++) {
    pinMode(zoneSensor[currentPin], INPUT);
    pinMode(zoneValve[currentPin], OUTPUT);
//    sensorValveMap[zoneSensor[currentPin]] = zoneValve[currentPin];
  }

  // We need to wait one minute for the sensor to calibrate
  // Get out of view of the sensor for this duration!
  
  // Blink the LED while calibrating
  for (unsigned int i=0; i<calibrationTime; i+=ledBlinkTime*2) {
    digitalWrite(ledPin, HIGH);
    delay(ledBlinkTime);
    digitalWrite(ledPin, LOW);
    delay(ledBlinkTime);
  }

  t.every(1000, checkActivity);

}

void checkActivity() {
  for (int currentPin = 0; currentPin < numZones; currentPin++) {
    if (sensorActive(zoneSensor[currentPin])) {
      Serial.println(zoneSensor[currentPin]);
//      openValve(sensorValveMap[zoneSensor[currentPin]], milliSecs, HIGH, 1);
      openValve(zoneValve[currentPin], fifteenSecs);
    }
  }
}


bool sensorActive(int pinNumber) {
  if (digitalRead(pinNumber) == HIGH) {
    return true;
  }
  return false;
}


void openValve(int pinNumber, int milliSecs) {

  secondTimer.oscillate(pinNumber, milliSecs, HIGH, 1);
}


void loop() {
  t.update();
  secondTimer.update();

/*  // Constantly check the state of pin 2
  // If it is HIGH the sensor is detecting motion
  if (digitalRead(2) == HIGH) {
    // Turn the LED on
    digitalWrite(ledPin, HIGH);
    digitalWrite(2, HIGH);
    
    // Tell the host computer we detected motion
    Serial.print(1);
    
    // Sleep for a second to prevent flooding the serial
    delay(1000);
  } else {
    // Turn the LED off
    digitalWrite(ledPin, LOW);
    digitalWrite(2, LOW);
  }

*/  
}

