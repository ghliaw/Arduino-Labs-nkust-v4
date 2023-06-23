#define BRIGHT_MAX  630

const int ledPin = 9;
const int lightPin = A0; 
void setup() {
  Serial.begin(115200);
  while(!Serial);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int value;

  value = analogRead(lightPin);
  Serial.println(value);
  analogWrite(ledPin, map(value, 0, BRIGHT_MAX, 255, 0));
}
