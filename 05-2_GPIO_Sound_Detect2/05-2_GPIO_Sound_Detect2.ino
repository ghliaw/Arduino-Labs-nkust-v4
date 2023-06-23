/*
 * Toggle LED ON/OFF by sound (Interrupt)
*/
#define DO_NOTHING_INTERVAL 10 //ms

// constants won't change. They're used here to set pin numbers:
const int soundPin = 2;     // the number of the sound-detector pin
const int ledPin =  LED_BUILTIN;      // the number of the LED pin

// variables will change:
int soundState = 0;         // variable for reading the sound-detector status
int ledState = 0;
bool allowCheck = true;
volatile bool detected = false;
unsigned long startDoNothingTime;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the sound-detctor pin as an input:
  pinMode(soundPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(soundPin), toggle, FALLING);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("start!");
}

void loop() {
  if(allowCheck && detected) {
    Serial.print(millis());
    Serial.println(": detected!");
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    allowCheck = false;
    detected = false;
    startDoNothingTime = millis();
  }
  else if(!allowCheck) {
    if((millis()-startDoNothingTime) >= DO_NOTHING_INTERVAL) allowCheck = true;
  }
}

void toggle()
{
  if(allowCheck) detected = true;
}
