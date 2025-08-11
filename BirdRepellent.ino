#include <Arduino.h>
#include <ESP32Servo.h>
#include "servoControl.h"
#include "SlideSwitch.h"
#include "DFPlayerControl.h"
int systemStatus;
int testStatus;

void setup() {
  Serial.begin(115200);
  //Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17 for UART2

  initializeLeds();
  initServos();
  initializeDFPlayer();
  
}

void loop() {
    
 //systemStatus = systemOn();
 systemStatus = 403;// No test mode
 
 if (systemStatus==1){
  //System Active, Activate Deterrents
  //Serial.println("Deterrence Activated: ONLine ");
  //Servo 
  handleSerialCommands();

  //DF Player Control
  //processSerialCommands();
  checkPotVolume();
  handleRandomPlayback();

 }else if (systemStatus==0 ){
  testStatus = testMode();
  if (testStatus==1){
    //Test Deterrents in Test Mode
    //Serial.println("System in Test Mode");
    test_system();
    checkPotVolume();
    
  }else{
    //Serial.println("System OFFLine ");
  } 
 } 
}
