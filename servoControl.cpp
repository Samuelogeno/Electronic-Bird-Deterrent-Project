#include "servoControl.h"
#include <ESP32Servo.h>
#include <DFPlayerControl.h>

extern int pitchDir = 2;
extern int yawDir = 4;

Servo servoPitch;
Servo servoYaw;

extern int pitchPos = 90;
extern int yawPos = 90;

void initServos() {
  Serial.println("------------------------------");
  Serial.println("    The servo sketch has started    ");
  Serial.println(" Enter angles as: pitch,yaw ");
  Serial.println("------------------------------");
  
  if (!servoPitch.attach(26)) Serial.println("Attaching servoPitch to pin 26");
  if (!servoYaw.attach(27))   Serial.println("Attaching servoYaw to pin 27");

  servoPitch.write(pitchPos);
  servoYaw.write(yawPos);
}


void handleSerialCommands() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    int commaIndex = input.indexOf(',');

    if (commaIndex > 0) {
      int pitch = input.substring(0, commaIndex).toInt();
      int yaw   = input.substring(commaIndex + 1).toInt();

      pitchPos = constrain(pitch, 0, 180);
      yawPos   = constrain(yaw, 0, 180);

      updateServos();

      Serial.print("Moved to: Pitch=");
      Serial.print(pitchPos);
      Serial.print(", Yaw=");
      Serial.println(yawPos);
    } 
  //Handle Sound Playback Serial Commands
    else if (input == "play") {
      playRandomSound();
    } else if (input == "help") {
      printHelpMenu();
    } else if (input.startsWith("track ")) {
      int track = input.substring(6).toInt();
      if (track > 0 && track < numberSounds) {
        myDFPlayer.play(track);
        Serial.print("Playing track ");
        Serial.println(track);
      } else {
        Serial.println("Invalid track number.");
      }
    } else if (input.startsWith("vol ")) {
      int vol = input.substring(4).toInt();
      vol = constrain(vol, 0, 30);
      myDFPlayer.volume(vol);
      Serial.print("Volume set via serial: ");
      Serial.println(vol);
      lastVolume = vol;
      serialVolumeSet = true;
    } else if (input == "pot vol") {
      serialVolumeSet = false;
      Serial.println("Potentiometer volume control re-enabled.");
    } else {
      Serial.println("Unknown command. Try: play, track <n>, vol <n>, pot vol");
      Serial.println("Invalid input format. Use: pitch,yaw");
    }
  }
}

void updateServos() {
  servoPitch.write(pitchPos);
  servoYaw.write(yawPos);
}

void moveServos() {
  Serial.println("    The servo is in test mode   ");
  pitchPos += pitchDir;
  // rollPos += rollDir;
  yawPos += yawDir;

  if (pitchPos < 0 || pitchPos > 180) {
    pitchDir = -pitchDir;
    pitchPos = constrain(pitchPos, 0, 180);
  }

  if (yawPos < 0 || yawPos > 180) {
    yawDir = -yawDir;
    yawPos = constrain(yawPos, 0, 180);
  }
  servoPitch.write(pitchPos);
  // servoRoll.write(rollPos);
  servoYaw.write(yawPos);
}

// Timers
unsigned long lastServoMove = 0;
unsigned long lastSoundPlay = 0;
unsigned long lastLaserToggle = 0;
bool laserState = false;

void test_system() {
  unsigned long currentMillis = millis();

  // Move servos every 20ms (smoother motion)
  if (currentMillis - lastServoMove >= 20) {
    moveServos();
    lastServoMove = currentMillis;
  }

  // Play random sound every 5-15 seconds
  if (currentMillis - lastSoundPlay >= random(5000, 15000)) {
    int randomInt = random(1, 4);
    if(randomInt==1){
      playRandomSound();
    }else{
      myDFPlayer.play(20);
    }
    lastSoundPlay = currentMillis;
  }
}



  


