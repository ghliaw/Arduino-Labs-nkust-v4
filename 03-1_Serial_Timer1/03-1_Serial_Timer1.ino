int count=0;

void setup() {
  // opens serial port, set data rate to 9600 bps
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Start timing!");
}

void loop() {
  delay(1000);
  count = count + 1;
  Serial.print("Current time: ");
  Serial.println(count);
}
