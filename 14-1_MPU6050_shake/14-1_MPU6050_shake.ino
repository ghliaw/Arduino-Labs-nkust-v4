#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 accelgyro;
int16_t ax, ay, az;
int time_interval = 100;    //ms
unsigned long current, lastTime = 0;
int count = 0;
float acc_threshold = 2.5;  //The thresholds for shake/fall detection
float last_sum, current_sum;
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Start!!");
  accelgyro.initialize();
  accelgyro.getAcceleration(&ax, &ay, &az);
  last_sum = (ax/16384.0)*(ax/16384.0) + (ay/16384.0)*(ay/16384.0) + (az/16384.0)*(az/16384.0);
  lastTime = millis();
}

void loop()
{
  current = millis();                 //Set for every interval
  if(current - lastTime >= time_interval)
  {
    float current_sum, diff;
    lastTime = current;
    accelgyro.getAcceleration(&ax, &ay, &az);
    current_sum = (ax/16384.0)*(ax/16384.0) + (ay/16384.0)*(ay/16384.0) + (az/16384.0)*(az/16384.0);
    if (current_sum > last_sum) diff = current_sum - last_sum;
    else diff = last_sum - current_sum;
    //Serial.println(diff);
    if( diff > acc_threshold ) {
      Serial.print("Shake: ");
      Serial.println(count++);
    }
    last_sum = current_sum;
  }
}
