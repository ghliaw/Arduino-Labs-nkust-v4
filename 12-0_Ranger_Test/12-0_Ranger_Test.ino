#define CURRENT_TEMPERATURE 26.0

#define PIN_TRIG 13    //Trig Pin
#define PIN_ECHO 12    //Echo Pin
double distance_per_us; // unit: cm
unsigned long duration, cm;
 
void setup() {
  Serial.begin (115200);           
  pinMode(PIN_TRIG, OUTPUT); 
  pinMode(PIN_ECHO, INPUT);
  distance_per_us = (331.5 + 0.607 * CURRENT_TEMPERATURE) * 0.0001;
}
 
void loop()
{
  // Generate 10-us pulse on Trig pin
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);    
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // Get the duration of HIGH at Echo pin
  duration = pulseIn(PIN_ECHO, HIGH);   // 收到高電位時的時間

  // Compute the diatance
  cm = (duration/2) * distance_per_us;

  Serial.print("Round-Trip time: ");  
  Serial.print(duration);
  Serial.print("us, Distance: ");
  Serial.print(cm);
  Serial.println("cm");
  
  delay(250);
}
