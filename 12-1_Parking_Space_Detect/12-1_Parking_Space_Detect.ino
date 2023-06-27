#include <NewPing.h>

#define CURRENT_TEMPERATURE 26.0
#define PIN_TRIG  13       //Trig Pin
#define PIN_ECHO  12       //Echo Pin
#define PIN_RGB_RED   9
#define PIN_RGB_GREEN 10
#define PIN_RGB_BLUE  11
#define RGB_ON  0
#define RGB_OFF 255
#define MAX_DISTANCE  200 
#define CONFIRM_DELAY 5000  // delay before final conform
#define DISTANCE_EMPTY  30  // cm
#define DISTANCE_FULL   10  // cm 


double distance_per_us; // unit: cm
unsigned long duration, cm;
NewPing sonar(PIN_TRIG, PIN_ECHO, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
bool need_confirm = false;
bool is_empty = true;
 
void setup() {
  pinMode(PIN_RGB_RED, OUTPUT);
  pinMode(PIN_RGB_GREEN, OUTPUT);
  pinMode(PIN_RGB_BLUE, OUTPUT);
  Serial.begin (115200);           
  distance_per_us = (331.5 + 0.607 * CURRENT_TEMPERATURE) * 0.0001;
  Serial.println("Program start. Parking space is empty.");
  analogWrite(PIN_RGB_RED, RGB_OFF);
  analogWrite(PIN_RGB_GREEN, RGB_ON);
  analogWrite(PIN_RGB_BLUE, RGB_OFF);
}
 
void loop()
{
  unsigned long duration, distance;
  unsigned long current_time;
  static unsigned long last_time;

  // Get round-trip time and compute the distance
  duration = sonar.ping();
  distance = (duration/2) * distance_per_us;
  
  if (is_empty) { // if the space is empty
    if (distance <= DISTANCE_FULL) {
      if (!need_confirm) {  // if not in comfirming state, set the state to need_confirm
        Serial.print("Distance = ");
        Serial.print(distance);
        Serial.println(", Comfirming ......");
        need_confirm = true;
        last_time = millis(); 
      }
      else { // if confirm is on going
        current_time = millis();
        if (current_time - last_time >= CONFIRM_DELAY) { // the time for confirming is over such that the space is confirmed as full
          is_empty = false; 
          need_confirm = false;
          Serial.println("Comfirm finished. Parking space is full now.");
          analogWrite(PIN_RGB_RED, RGB_ON);
          analogWrite(PIN_RGB_GREEN, RGB_OFF);
          analogWrite(PIN_RGB_BLUE, RGB_OFF);
        }
      }
    }
    else {
      if (need_confirm) {
        Serial.print("Distance = ");
        Serial.print(distance);
        Serial.println(", Comfirm cancelled.");
        need_confirm = false;
      }
    }
  }
  else { // if the space is full
    if (distance >= DISTANCE_EMPTY) {
      if (!need_confirm) {  // if not in comfirming state, set the state to need_confirm
        Serial.print("Distance = ");
        Serial.print(distance);
        Serial.println(", Comfirming ......");
        need_confirm = true;
        last_time = millis(); 
      }
      else { // if confirm is on going
        current_time = millis();
        if (current_time - last_time >= CONFIRM_DELAY) { // the time for confirming is over such that the space is confirmed as empty
          is_empty = true; 
          need_confirm = false;
          Serial.println("Comfirm finished. Parking space is empty now.");
          analogWrite(PIN_RGB_RED, RGB_OFF);
          analogWrite(PIN_RGB_GREEN, RGB_ON);
          analogWrite(PIN_RGB_BLUE, RGB_OFF);
        }
      }
    }
    else {
      if (need_confirm) {
        Serial.print("Distance = ");
        Serial.print(distance);
        Serial.println(", Comfirm cancelled.");
        need_confirm = false;
      }
    }
  }
  delay(200);
}
