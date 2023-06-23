/*
 * Set LED ON if too dark and Set LED OFF if too bright 
*/
#define BRIGHT_THRESHOLD  500
#define DARK_THRESHOLD  200

// constants won't change. They're used here to set pin numbers:
const int lightAnalogPin = A0;
const int ledPin =  9;      // the number of the LED pin
int lightAnalogValue;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
}

void loop() {
    lightAnalogValue = analogRead(lightAnalogPin);
    if(lightAnalogValue > BRIGHT_THRESHOLD) 
      digitalWrite(ledPin, LOW);
    else if (lightAnalogValue < DARK_THRESHOLD)
      digitalWrite(ledPin, HIGH);
}
