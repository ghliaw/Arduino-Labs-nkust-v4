#include <string.h>

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // opens serial port, set data rate to 9600 bps
  Serial.begin(9600);
  while(!Serial); // wait until serial port is ready
  Serial.println("Program Start!!");      
}

void loop() {
  static char buf[200];
  static int  length = 0;
  int incoming_byte; 

  // If there is any data incoming, read a byte and put it on string buffer
  if(Serial.available() > 0) { // check if there is incoming data
    incoming_byte = Serial.read();  // read the incoming byte
    buf[length++] = incoming_byte;  // put the incoming byte to string buffer
    if(incoming_byte == '\n') { // check if LF is incoming
      // append '\0' to buf[] as the end of the string
      buf[length++] = '\0';
      // do job
      if(strcmp(buf, "on\n")==0) { // check if the incoming string is "on"
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("LED is on.");
      }
      else if(strcmp(buf, "off\n")==0) { // check if the incoming string is "on"
        digitalWrite(LED_BUILTIN, LOW);       
        Serial.println("LED is off.");
      }
      else { // Otherwise, it is unknown command
        Serial.print("Unknown command: ");
        Serial.println(buf);
      }
      length = 0; // reset the length for receiving next string
    }
  }
}
