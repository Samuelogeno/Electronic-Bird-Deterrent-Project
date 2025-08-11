#ifndef SLIDESWITCH_H
#define SLIDESWITCH_H

// Define the pins connected to the switches and LEDs
const int NUM_SWITCHES = 4;
extern const int swPins[NUM_SWITCHES];
extern const int ledPins[NUM_SWITCHES];

// Function declarations
void initializeLeds();
void updateLeds();
int systemOn(); 
int testMode();

#endif