/*
 * Observe the relation between analog input value and water level 
*/

// constants won't change. They're used here to set pin numbers:
const int waterAnalogPin = A2;

// variables will change:
int waterAnalogValue;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("start (analog)!");
}

void loop() {
  waterAnalogValue = analogRead(waterAnalogPin);
  Serial.println(waterAnalogValue);    
}
