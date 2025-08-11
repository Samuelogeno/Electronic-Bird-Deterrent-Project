#include "Arduino.h"
#include "SlideSwitch.h"

// Define the pins connected to the switches and LEDs
const int swPins[NUM_SWITCHES] = {2, 5, 18, 19};   // Pins for switches
const int ledPins[NUM_SWITCHES] = {2, 5, 18, 19};  // Pins for LEDs
int switchState;

void initializeLeds() {
  for (int i = 0; i < NUM_SWITCHES; i++) {
    pinMode(swPins[i], INPUT_PULLUP);
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Ensure LEDs are off initially
  }
}

void updateLeds() {
  for (int i = 0; i < NUM_SWITCHES; i++) {
    switchState = digitalRead(swPins[i]);

    if (switchState == LOW) {
      digitalWrite(ledPins[i], HIGH);  // Turn on the LED
      // Serial.print("Switch ");
      // Serial.print(i + 1);
      // Serial.println(" is pressed - LED ON");
    } else {
      digitalWrite(ledPins[i], LOW);   // Turn off the LED
      // Serial.print("Switch ");
      // Serial.print(i + 1);
      // Serial.println(" is open - LED OFF");
    }
  }
}
int systemOn() {

  switchState = digitalRead(swPins[0]);
  digitalWrite(ledPins[0], HIGH);

    if (switchState == LOW) {
      digitalWrite(ledPins[1], LOW);  // Turn on the LED
      //Serial.println("System OFFLine ");
      // Serial.print(i + 1);
      // Serial.println(" is pressed - LED ON");
      return 0;
    } else {
      digitalWrite(ledPins[1], HIGH);   // Turn off the LED
      //Serial.println("Deterrence Activated: ONLine ");
      return 1;
      // Serial.print(i + 1);
      // Serial.println(" is open - LED OFF");
    }
  }
int testMode() {

  switchState = digitalRead(swPins[2]);
  digitalWrite(ledPins[2], HIGH);

    if (switchState == LOW) {
      digitalWrite(ledPins[3], LOW);  // Turn on the LED
      //Serial.println("Test Mode OFF ");
      // Serial.print(i + 1);
      // Serial.println(" is pressed - LED ON");
      return 0;
    } else {
      digitalWrite(ledPins[3], HIGH);   // Turn off the LED
      //Serial.println("System in Test Mode");
      return 1;
      // Serial.print(i + 1);
      // Serial.println(" is open - LED OFF");
    }
  }