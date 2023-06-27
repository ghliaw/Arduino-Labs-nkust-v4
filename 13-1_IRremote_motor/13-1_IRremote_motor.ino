#include <Arduino.h>
#include <IRremote.h>

#define IR_RECEIVE_PIN  2
#define SPEED1  80
#define SPEED2  160
#define SPEED3  240

const int motorPinA = 5;
const int motorPinB = 6;

void setup() {
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Start!!");
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(IR_RECEIVE_PIN);
  analogWrite(motorPinA, 0);
  analogWrite(motorPinB, 0);
}

void loop() {
  byte command;
  if (IrReceiver.decode()) {
    // Print a short summary of received data
    IrReceiver.printIRResultShort(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();
    IrReceiver.resume(); // Enable receiving of the next value
    command = IrReceiver.decodedIRData.command;
    Serial.print("Command is ");
    Serial.println(command, HEX);
    switch(command) {
      case 0x16:  // 0
        analogWrite(motorPinA, 0);
        analogWrite(motorPinB, 0);
      break;
      case 0xC:   // 1
        analogWrite(motorPinA, SPEED1);
        analogWrite(motorPinB, 0);
      break;
      case 0x18:  // 2
        analogWrite(motorPinA, SPEED2);
        analogWrite(motorPinB, 0);
      break;      
      case 0x5E:  // 3
        analogWrite(motorPinA, SPEED3);
        analogWrite(motorPinB, 0);
      break;
      default: {} 
    }
  }
}
