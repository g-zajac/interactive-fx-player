#include <Arduino.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playWav1;       //xy=533,331
AudioAmplifier           amp1;           //xy=702,298
AudioAmplifier           amp2;           //xy=702,372
AudioOutputAnalogStereo  dacs1;          //xy=846,331
AudioConnection          patchCord1(playWav1, 0, amp1, 0);
AudioConnection          patchCord2(playWav1, 1, amp2, 0);
AudioConnection          patchCord3(amp1, 0, dacs1, 0);
AudioConnection          patchCord4(amp2, 0, dacs1, 1);
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
// #define SDCARD_CS_PIN    10
// #define SDCARD_MOSI_PIN  7
// #define SDCARD_SCK_PIN   14

// Use these with the Teensy 3.5 & 3.6 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used

// Use these for the SD+Wiz820 or other adaptors
//#define SDCARD_CS_PIN    4
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_SCK_PIN   13

void setup() {
  Serial.begin(9600);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);


  amp1.gain(0.1);
  amp2.gain(0.1);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}

void playFile(const char *filename)
{
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav1.play(filename);

  // A brief delay for the library read WAV info
  delay(5);

  // Simply wait for the file to finish playing.
  while (playWav1.isPlaying()) {
    // uncomment these lines if you audio shield
    // has the optional volume pot soldered
    //float vol = analogRead(15);
    //vol = vol / 1024;
    // sgtl5000_1.volume(vol);
  }
}


void loop() {
  playFile("1.WAV");  // filenames are always uppercase 8.3 format
  delay(1500);
}
