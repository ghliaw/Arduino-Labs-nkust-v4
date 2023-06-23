// Common anode RGB LED
const int Red = 9;
const int Green = 10;
const int Blue = 11;

void setup() {
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
}

void loop() {
  analogWrite(Red,0);
  analogWrite(Green,255);
  analogWrite(Blue,255);
  delay(1000);
  analogWrite(Red,255);
  analogWrite(Green,0);
  analogWrite(Blue,255);
  delay(1000);
  analogWrite(Red,255);
  analogWrite(Green,255);
  analogWrite(Blue,0);
  delay(1000);
}
