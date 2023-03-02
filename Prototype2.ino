#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioPlaySdWav  playSdWav1;
AudioOutputI2S  i2s1; 
AudioConnection patchCord1 (playSdWav1, 0, i2s1, 0);
AudioConnection patchCord2 (playSdwav1, 1, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;


int buttonPin = 0;
int xFadePot = A0;

#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 11
#define SDCARD_SCK_PIN 13


void setup (){
  Serial.begin (9600);
  AudioMemory (8);
  sgtl5000_1.enable(); 
  sgtl5000_1.volume (0.75); 
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK (SDCARD_SCK_PIN);
  if (!(SD.begin (SDCARD_CS_PIN))){
    while (1) { 
      Serial.println ("Unable to access the SD card");
      delay (500);
    } 
  } 
    delay (1000); 

    PinMode (buttonPin, INPUT_PULLUP); 

}

void loop() { 

  int knob = analogRead (A1);
  float vol = knob / 1023.0;
  sgtl5000_1.volume (vol);

  int xFadeVal = analogRead (xFadePot); 
  float xFadeScale = xFadeVal / 1023.0; 
  float xFadeScale2 = 1.0 - xFadeScale; 

  mixer1.gain(0, xFadeScale); 
  mixer1.gain(1, xFadeScale2); 
  mixer2.gain(0, xFadeScale);
  mixer2.gain(1, xFadeScale2); 
  
  
  bool buttonRead = digigtalRead(buttonPin); 

  if (buttonRead == LOW) { 
    if (playSdWav1.isPlaying() == false) { 
      playSdwav.play ("drmSamp.wav")
    }
    if (playSdWav2.isPlaying() == false) { 
      playSdwav2.play ("AmnSamp.wav")
      delay(5);
  }
  else {
    playSdWav1.stop();
    playSdWav2.stop();
    }
  }
}
