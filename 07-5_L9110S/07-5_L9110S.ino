#define SPEED1  100
#define SPEED2  200

const int motorPinA = 5;
const int motorPinB = 6;

void setup() {
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
}

void loop() {

  // clockwise, SPEED1 for 5 seconds
  analogWrite(motorPinA, 0);
  analogWrite(motorPinB, SPEED1);

  delay(5000);
  
  // clockwise, SPEED2 for 5 seconds
  analogWrite(motorPinA, 0);
  analogWrite(motorPinB, SPEED2);
  delay(5000);

  // stop for 3 second
  analogWrite(motorPinA, 0);
  analogWrite(motorPinB, 0);
  delay(3000);

  // counterclockwise, SPEED1 for 3 seconds
  analogWrite(motorPinA, SPEED1);
  analogWrite(motorPinB, 0);
  delay(5000);
  
  // counterclockwise, SPEED2 for 3 seconds
  analogWrite(motorPinA, SPEED2);
  analogWrite(motorPinB, 0);
  delay(5000);

  // stop for 1 second
  analogWrite(motorPinA, 0);
  analogWrite(motorPinB, 0);
  delay(3000);
}
