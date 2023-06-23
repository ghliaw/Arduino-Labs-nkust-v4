// Common anode RGB LED
const int Red = 9;
const int Green = 10;
const int Blue = 11;
 
#define FADE_DELAY 5
 
void setup() {
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
}
 
void loop() {
  int r, g, b;
 
  for (r = 0; r < 256; r++) { 
    analogWrite(Red, r);
    delay(FADE_DELAY);
  } 
  for (b = 255; b > 0; b--) { 
    analogWrite(Blue, b);
    delay(FADE_DELAY);
  } 
  for (g = 0; g < 256; g++) { 
    analogWrite(Green, g);
    delay(FADE_DELAY);
  } 
  for (r = 255; r > 0; r--) { 
    analogWrite(Red, r);
    delay(FADE_DELAY);
  } 
  for (b = 0; b < 256; b++) { 
    analogWrite(Blue, b);
    delay(FADE_DELAY);
  } 
  for (g = 255; g > 0; g--) { 
    analogWrite(Green, g);
    delay(FADE_DELAY);
  } 
}
