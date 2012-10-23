#include <SPI.h>
#include <MIDI.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
  #include "SoftwareSerial.h"
  SoftwareSerial port(12,13);
#else // Arduino 0022 - use modified NewSoftSerial
  #include "WProgram.h"
  #include "NewSoftSerial.h"
  NewSoftSerial port(12,13);
#endif
 
#include "EasyVR.h"
#define LED 11   


EasyVR easyvr(port);
 
  
 enum Knob{LOOSER};
 enum Level{EASY};
 
//Groups and Commands
enum Groups
{
   GROUP_3  = 0,
};
 
enum Group0 
{
  G0_ARDUINO = 0,
};
 
/*enum Group 
{
  G1_LED_AN = 0,
  G1_LED_AUS = 1,
};*/
 
 
EasyVRBridge bridge;
 
int8_t group, idx;
 
void setup()
{
  // bridge mode?
  if (bridge.check())
  {
    cli();
    bridge.loop(0, 1, 12, 13);
  }
  // run normally
  Serial.begin(9600);
  port.begin(9600);
// MIDI.begin();
 
  if (!easyvr.detect())
  {
    Serial.println("EasyVR not detected!");
    for (;;);
  }
 
  easyvr.setPinOutput(EasyVR::IO1, LOW);
  Serial.println("EasyVR detected!");
  easyvr.setTimeout(5);
  easyvr.setLanguage(3);
 
  group = EasyVR::TRIGGER; //&amp;lt;-- start group (customize)
   
   
  pinMode(LED, OUTPUT); 
  digitalWrite(LED, LOW);    // set the LED off
   
}
 
void action();
 
void loop()
{
  easyvr.setPinOutput(EasyVR::IO1, HIGH); // LED on (listening)
 
  Serial.print("Say a command in Group");
  Serial.println(group);
  easyvr.recognizeCommand(group);
 
  do
  {
    // can do some processing while waiting for a spoken command
  }
  while (!easyvr.hasFinished());
   
  easyvr.setPinOutput(EasyVR::IO1, LOW); // LED off
 
  idx = easyvr.getWord();
  if (idx>= 0)
  {
    // built-in trigger (ROBOT)
    // group = GROUP_X; &amp;lt;-- jump to another group X
    return;
  }
  idx = easyvr.getCommand();
  if (idx>= 0)
  {
    // print debug message
    uint8_t train = 0;
    char name[32];
    Serial.print("Command:");
    Serial.print(idx);
    if (easyvr.dumpCommand(group, idx, name, train))
    {
      Serial.print("= ");
      Serial.println(name);
    }
    else
      Serial.println();
    easyvr.playSound(0, EasyVR::VOL_FULL);
    // perform some action
    action();
  }
  else // errors or timeout
  {
    if (easyvr.isTimeout())
      Serial.println("Timed out, try again...");
    int16_t err = easyvr.getError();
    if (err >= 0)
    {
      Serial.print("Error ");
      Serial.println(err, HEX);
    }
     
     
    group = GROUP_3;
  }
}
 
void action()
{

  if (idx < 8 ){
//MIDI.sendNoteOn(42,127,1);
  digitalWrite(LED,LOW);
   delay(1000);
   digitalWrite(LED,HIGH);
   delay(500);
   digitalWrite(LED,LOW);
   delay(1000);
   digitalWrite(LED,HIGH);
   delay(500);
    digitalWrite(LED,LOW);
   delay(1000);
   digitalWrite(LED,HIGH);
   delay(500);
  if (MIDI.read()) {
     MIDI.sendNoteOn(42,127,1);  // Send a Note (pitch 42, velo 127 on channel 1)
    delay(1000);		// Wait for a second
    MIDI.sendNoteOff(42,0,1);}   // Stop the note
   }else{
   digitalWrite(LED,HIGH);}}
  
/* if (MIDI.read()) {
   MIDI.sendNoteOn(42,127,1);  // Send a Note (pitch 42, velo 127 on channel 1)
    delay(1000);		// Wait for a second
    MIDI.sendNoteOff(42,0,1);   // Stop the note*/
  

 
