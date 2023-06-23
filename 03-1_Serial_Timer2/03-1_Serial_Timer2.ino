#define PERIOD  1000 //ms

int count=0;
unsigned long last;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // opens serial port, set data rate to 9600 bps
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Start timing!");
  last = millis();
}

void loop() {
  unsigned long current;
  
  current = millis();
  if(current-last >= PERIOD) { // check if time is up
    // output to serial port
    count = count + 1;
    Serial.print("Current time: ");
    Serial.println(count);
    // flash LED
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    // update last time record
    last = current;
  }
}
