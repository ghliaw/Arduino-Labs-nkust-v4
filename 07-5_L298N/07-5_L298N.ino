#define SPEED1  100
#define SPEED2  200

const int motorPinENA = 3;
const int motorPinIN1 = 4;
const int motorPinIN2 = 5;

void setup() {
  pinMode(motorPinENA, OUTPUT);
  pinMode(motorPinIN1, OUTPUT);
  pinMode(motorPinIN2, OUTPUT);
}

void loop() {

  // clockwise, SPEED1 for 5 seconds
  analogWrite(motorPinENA, SPEED1);
  digitalWrite(motorPinIN1, HIGH);
  digitalWrite(motorPinIN2, LOW);
  delay(5000);
  
  // Stop for 1 seconds
  analogWrite(motorPinENA, 0);
  delay(1000);

  // clockwise, SPEED2 for 5 seconds
  analogWrite(motorPinENA, SPEED2);
  digitalWrite(motorPinIN1, HIGH);
  digitalWrite(motorPinIN2, LOW);
  delay(5000);

  // stop for 3 second
  analogWrite(motorPinENA, 0);
  delay(3000);

  // counterclockwise, SPEED1 for 5 seconds
  analogWrite(motorPinENA, SPEED1);
  digitalWrite(motorPinIN1, LOW);
  digitalWrite(motorPinIN2, HIGH);
  delay(5000);

  // Stop for 1 seconds
  analogWrite(motorPinENA, 0);
  delay(1000);
  
  // counterclockwise, SPEED2 for 5 seconds
  analogWrite(motorPinENA, SPEED2);
  digitalWrite(motorPinIN1, LOW);
  digitalWrite(motorPinIN2, HIGH);
  delay(5000);

  // stop for 3 second
  analogWrite(motorPinENA, 0);
  delay(3000);
}
