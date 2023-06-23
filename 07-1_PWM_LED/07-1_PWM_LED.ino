#include <string.h>

const int ledPin = 9;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);
  // opens serial port, set data rate to 9600 bps
  Serial.begin(115200);
  while(!Serial); // wait until serial port is ready
  Serial.println("Program Start!!");      
}

void loop() {
  static char buf[200];
  static int  length = 0;
  int incoming_byte;
  int value; 

  // If there is any data incoming, read a byte and put it on string buffer
  if(Serial.available() > 0) { // check if there is incoming data
    incoming_byte = Serial.read();  // read the incoming byte
    buf[length++] = incoming_byte;  // put the incoming byte to string buffer
    if(incoming_byte == '\n') { // check if LF is incoming
      // append '\0' to buf[] as the end of the string
      buf[length++] = '\0';
      // do job
      value = atoi(buf);
      Serial.print("I got: ");
      Serial.println(value);
      if(value >= 0 && value <=255) analogWrite(ledPin, value);
      length = 0; // reset the length for receiving next string
    }
  }
}
