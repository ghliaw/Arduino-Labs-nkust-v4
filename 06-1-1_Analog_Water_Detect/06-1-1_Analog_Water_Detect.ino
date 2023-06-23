/*
 * LED ON/OFF by water level (Analog)
*/
#define WATER_THRESHOLD 0
#define DELTA 10

// constants won't change. They're used here to set pin numbers:
const int waterAnalogPin = A2;
const int ledPin =  LED_BUILTIN;      // the number of the LED pin

// variables will change:
int waterAnalogValue;
int threshold = WATER_THRESHOLD;
bool is_high = false;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("start (analog)!");
}

void loop() {
  waterAnalogValue = analogRead(waterAnalogPin);
  Serial.println(waterAnalogValue);
  if(waterAnalogValue >= threshold) {
    Serial.print("detected: ");
    Serial.println(waterAnalogValue);
    digitalWrite(ledPin, HIGH);
    if (!is_high) {
      threshold -= DELTA;
      is_high = true;
    }
  }
  else {
    digitalWrite(ledPin, LOW);
    if(is_high) {
      threshold += DELTA;
      is_high = false;
    }
  }
}
