/*
 * Print out Light value (Analog input)
*/

// constants won't change. They're used here to set pin numbers:
const int lightAnalogPin = A0;
const int ledPin =  LED_BUILTIN;      // the number of the LED pin

// variables will change:
int lightAnalogValue;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("start (analog)!");
}

void loop() {
  lightAnalogValue = analogRead(lightAnalogPin);
  Serial.println(lightAnalogValue);    
  delay(1000);
}
