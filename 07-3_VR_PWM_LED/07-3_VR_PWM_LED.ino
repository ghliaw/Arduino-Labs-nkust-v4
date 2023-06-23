#define RED_LED 9
#define POTENTIOMETER A0
void setup() {
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
}

void loop() {
  int value;

  value = analogRead(POTENTIOMETER);
  Serial.println(value);
  analogWrite(RED_LED, map(value, 0, 1023, 0, 255));
}
