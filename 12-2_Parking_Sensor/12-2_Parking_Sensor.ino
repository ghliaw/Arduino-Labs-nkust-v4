#include <NewPing.h>
#include <NewTone.h>

#define CURRENT_TEMPERATURE 26.0
#define PIN_TRIG  13       //Trig Pin
#define PIN_ECHO  12       //Echo Pin
#define PIN_BUZZER  8
#define MAX_DISTANCE  200 // cm
#define DISTANCE_FAR  30  // cm 
#define DISTANCE_NEAR 10  // cm
#define BUZZER_PERIOD_FAR     1000  // ms
#define BUZZER_PERIOD_MEDIUM  500  // ms
#define BUZZER_FREQ     1000 // Hz
#define BUZZER_DURATION 100 // ms

double distance_per_us; // unit: cm
unsigned long duration, cm;
NewPing sonar(PIN_TRIG, PIN_ECHO, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
unsigned long last_time;
 
void setup() {
  Serial.begin (115200);           
  distance_per_us = (331.5 + 0.607 * CURRENT_TEMPERATURE) * 0.0001;
  Serial.println("Program start.");
  last_time = millis();
}
 
void loop()
{
  unsigned long duration, distance;
  unsigned long current_time, period;

  // Get round-trip time and compute the distance
  duration = sonar.ping();
  distance = (duration/2.0) * distance_per_us;
  Serial.print("Distance = ");
  Serial.println(distance);
  if (distance == 0) return;
  
  // According to distant range, play buzzer sound with corresponding period
  if (distance > DISTANCE_FAR)
    period = BUZZER_PERIOD_FAR;
  else if (distance < DISTANCE_NEAR)
    period = 0;
  else
    period = BUZZER_PERIOD_MEDIUM;

  if (period > 0) {
    current_time = millis();
    if (current_time - last_time >= period) {
      noNewTone(PIN_BUZZER);
      NewTone(PIN_BUZZER, BUZZER_FREQ, BUZZER_DURATION);
      last_time = current_time;
    }
  }
  else {
    NewTone(PIN_BUZZER, BUZZER_FREQ);
  }
  delay(100);
}
