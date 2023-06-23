// Pin Assignment
#define PIN_RED     3
#define PIN_YELLOW  7
#define PIN_GREEN   11

// System State
#define STATE_RED           1
#define STATE_GREEN         2
#define STATE_GREEN_FLASH   3
#define STATE_YELLOW        4

// Duration at each state (ms)
#define DURATION_RED          15000
#define DURATION_GREEN        15000  
#define DURATION_GREEN_FLASH  5000
#define DURATION_YELLOW       3000

// Period of flashing green light
#define PERIOD_GREEN_FLASH    100

// Global Vairables
int led_state;
unsigned long start_time, current_time, flash_start_time;
int toggle;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);

  // At first, set red LED on and the others off
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_YELLOW, LOW);
  digitalWrite(PIN_GREEN, LOW);
  Serial.println("Start: RED");
  start_time = millis();   
  led_state = STATE_RED;
}
 
void loop() {
  // Check if the time in current led state is up.
  // If time is up, cheange led state to the next one.
  current_time = millis();
  switch (led_state) {
    case STATE_RED:
      if(current_time - start_time >= DURATION_RED) {
        Serial.println("RED --> GREEN");
        start_time = current_time; 
        digitalWrite(PIN_RED, LOW);
        digitalWrite(PIN_GREEN, HIGH);
        led_state = STATE_GREEN;
      }
      break;
    case STATE_GREEN:
      if(current_time - start_time >= DURATION_GREEN) {
        Serial.println("GREEN --> GREEN_FLASH");
        start_time = current_time;
        flash_start_time = current_time;
        toggle = HIGH; 
        led_state = STATE_GREEN_FLASH;
      }
      break;
    case STATE_GREEN_FLASH:
      if(current_time - start_time >= DURATION_GREEN_FLASH) {
        Serial.println("GREEN_FLASH --> GREEN_YELLOW");
        start_time = current_time; 
        digitalWrite(PIN_RED, LOW);
        digitalWrite(PIN_GREEN, LOW);
        digitalWrite(PIN_YELLOW, HIGH);
        led_state = STATE_YELLOW;
      }
      else {
        if(millis() - flash_start_time >= PERIOD_GREEN_FLASH) {
          flash_start_time = millis();
          toggle = !toggle;
          digitalWrite(PIN_GREEN, toggle);
        }
      }
      break;
    case STATE_YELLOW:
      if(current_time - start_time >= DURATION_YELLOW) {
        Serial.println("YELLOW --> RED");
        start_time = current_time; 
        digitalWrite(PIN_RED, HIGH);
        digitalWrite(PIN_GREEN, LOW);
        digitalWrite(PIN_YELLOW, LOW);
        led_state = STATE_RED;
      }
      break;
    default:
      break;
  }
}
