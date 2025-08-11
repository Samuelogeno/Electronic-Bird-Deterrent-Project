#ifndef DFPLAYERCONTROL_H
#define DFPLAYERCONTROL_H

#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>

// HardwareSerial for DFPlayer
extern HardwareSerial mySerial;
extern DFRobotDFPlayerMini myDFPlayer;

// Pins and configuration
extern const int potPin;
extern int lastVolume;
extern int numberSounds;
extern bool serialVolumeSet;

// Random playback
extern unsigned long lastSoundTime;
extern unsigned long soundInterval;

// Function declarations
void initializeDFPlayer();
void playRandomSound();
void printHelpMenu();
void checkPotVolume();
//void processSerialCommands();
void handleRandomPlayback();

#endif
