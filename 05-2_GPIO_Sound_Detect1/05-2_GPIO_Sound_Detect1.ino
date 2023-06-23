/*
 * Toggle LED ON/OFF by sound (Polling)
*/
#define DO_NOTHING_INTERVAL 50 //ms

// constants won't change. They're used here to set pin numbers:
const int soundPin = 2;     // the number of the sound-detector pin
const int ledPin =  LED_BUILTIN;      // the number of the LED pin

// variables will change:
int soundState = 0;         // variable for reading the sound-detector status
int ledState = 0;
bool allowCheck = true;
unsigned long startDoNothingTime;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the sound-detctor pin as an input:
  pinMode(soundPin, INPUT);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("start!");
}

void loop() {
  if(allowCheck) {
    // read the state of the sound-detector value:
    soundState = digitalRead(soundPin);

    // check if the sound-detecto output HIGH. If it is, the soundState is HIGH:
    if (soundState == LOW) {
      Serial.println("detected!");
      // toggle LED
      digitalWrite(ledPin, !ledState);
      ledState = !ledState;
    }
    allowCheck = false;
    startDoNothingTime = millis();
  }
  else {
    if(millis() - startDoNothingTime >= DO_NOTHING_INTERVAL)
      allowCheck = true;
  }
}
