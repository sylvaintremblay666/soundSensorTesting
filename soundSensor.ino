#include "Arduino.h"

int trigThreshold = 10;
int tolerance = 10;

int runningCounter = 0;
int stoppedCounter = 0;

bool isRunning = false;

int ledPin=D2;
int digitalSensorPin=D5;
bool prevIsSoundDetected = false;


void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(digitalSensorPin, INPUT);

  digitalWrite(ledPin, HIGH);

  prevIsSoundDetected = digitalRead(digitalSensorPin);

  Serial.begin (115200);
}

void loop (){

	bool isSoundDetected = digitalRead(digitalSensorPin);
/*
	Serial.print("curValue: ");
	Serial.print(curValue);
	Serial.print(" prevValue: ");
	Serial.println(prevValue);
	Serial.print("isRunning: ");
	Serial.println(isRunning);
	Serial.print("runningCounter: ");
	Serial.print(runningCounter);
	Serial.print(" stoppedCounter: ");
	Serial.println(stoppedCounter);
	Serial.println("----");
*/

	prevIsSoundDetected = isSoundDetected;

	if (!isRunning) {   // pump is not running
		if (isSoundDetected) { // Sound is detected
			stoppedCounter = 0;
			if (runningCounter++ >= trigThreshold) {
				runningCounter = 0;
				isRunning = true;
				digitalWrite(ledPin, LOW);
			}
		} else {
			if (stoppedCounter++ >= tolerance) {
				runningCounter = 0;
				stoppedCounter = 0;
			}
		}

	} else {  // pump is running
		if (!isSoundDetected) {
			if (stoppedCounter++ >= trigThreshold) {
				stoppedCounter = 0;
				isRunning = false;
				digitalWrite(ledPin, HIGH);
			}
		} else {
			stoppedCounter = 0;
		}
	}

  delay(50);
}
