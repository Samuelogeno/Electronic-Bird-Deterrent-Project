#include "DFPlayerControl.h"
#include "servoControl.h"

// Initialize shared variables
HardwareSerial mySerial(2); // UART2: RX=GPIO16, TX=GPIO17
DFRobotDFPlayerMini myDFPlayer;

const int potPin = 13;
int lastVolume = -1;
int numberSounds = 19;
bool serialVolumeSet = false;

unsigned long lastSoundTime = 0;
unsigned long soundInterval = 0;

void initializeDFPlayer() {
  //Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, 16, 17);

  Serial.println("Initializing DFPlayer Mini...");
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer Mini not detected!");
    while (true);
  }

  Serial.println("DFPlayer Mini ready.");
  myDFPlayer.volume(30); // Default startup volume Max
}

void playRandomSound() {
  int randomTrack = random(1, numberSounds);
  Serial.print("Playing track: ");
  Serial.println(randomTrack);
  myDFPlayer.play(randomTrack);
}

void printHelpMenu() {
  Serial.println("\n=== DFPlayer Command Menu ===");
  Serial.println("help         - Show this help menu");
  Serial.println("play         - Play a random sound");
  Serial.println("track <n>    - Play specific track number <n>");
  Serial.println("vol <n>      - Set volume (0 - 30)");
  Serial.println("pot vol      - Re-enable potentiometer volume control");
  Serial.println("==============================\n");
}

void checkPotVolume() {
  if (serialVolumeSet) return;

  int potValue = analogRead(potPin);
  int volume = map(potValue, 0, 4095, 0, 30);

  if (abs(volume - lastVolume) >= 2) {
    myDFPlayer.volume(volume);
    Serial.print("Volume adjusted via potentiometer: ");
    Serial.println(volume);
    lastVolume = volume;
  }
}

// void processSerialCommands() {
//   if (Serial.available()) {
//     String input = Serial.readStringUntil('\n');
//     input.trim();

//     if (input == "play") {
//       playRandomSound();
//     } else if (input == "help") {
//       printHelpMenu();
//     } else if (input.startsWith("track ")) {
//       int track = input.substring(6).toInt();
//       if (track > 0 && track < numberSounds) {
//         myDFPlayer.play(track);
//         Serial.print("Playing track ");
//         Serial.println(track);
//       } else {
//         Serial.println("Invalid track number.");
//       }
//     } else if (input.startsWith("vol ")) {
//       int vol = input.substring(4).toInt();
//       vol = constrain(vol, 0, 30);
//       myDFPlayer.volume(vol);
//       Serial.print("Volume set via serial: ");
//       Serial.println(vol);
//       lastVolume = vol;
//       serialVolumeSet = true;
//     } else if (input == "pot vol") {
//       serialVolumeSet = false;
//       Serial.println("Potentiometer volume control re-enabled.");
//     } else {
//       Serial.println("Unknown command. Try: play, track <n>, vol <n>, pot vol");
//     }
//   }
// }

void handleRandomPlayback() {
  if (millis() - lastSoundTime > soundInterval) {
    playRandomSound();
    lastSoundTime = millis();
    soundInterval = random(5000, 7000); // Next sound in 5–7 seconds
  }
}
