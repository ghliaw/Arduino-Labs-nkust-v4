#include "DHT.h"
#include <LiquidCrystal_PCF8574.h>

#define DHTPIN 2     // what pin we're connected to
#define LEDPIN  8
#define PERIOD_DHT  15000

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_PCF8574 lcd(0x20); // set the LCD address to 0x27 for a 16 chars and 2 line display
unsigned long dht_last_time;

void setup() 
{
    // Initialize Serial port
    Serial.begin(9600); 

    // Set LED pins as output
    pinMode(LEDPIN, OUTPUT);

    // Initialize DHT & LCD
    dht.begin();
    lcd.begin(16, 2);
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();

    // record the current time for DHT timer
    dht_last_time = 0;
}

void loop() 
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    static char buf[200];
    static int  length = 0;
    int incoming_byte; 
    float h, t;
    unsigned long current_time;

    current_time = millis();
    
    // if timeout, read temperature and humidity once and output
    if(current_time - dht_last_time >= PERIOD_DHT) {
      h = dht.readHumidity();
      t = dht.readTemperature();
  
      // check if returns are valid, if they are NaN (not a number) then something went wrong!
      if (!isnan(t) && !isnan(h)) 
      {
          // Print Temperature & Humidity data on Serial port
          Serial.print(t,1);
          Serial.print(",");
          Serial.println(h,1); 
  
          // Print Temperature & Humidity data on LCD
          lcd.home();
          lcd.print("Temp: ");
          if(t<10.0) lcd.print(" ");
          lcd.print(t, 1);
          lcd.print(" C");
          lcd.setCursor(0, 1);
          lcd.print("Hum : ");
          if(h<10.0) lcd.print(" ");
          lcd.print(h, 1);
          lcd.print(" \%");
      }
      dht_last_time = current_time;
    }

    // If there is any data incoming, read a byte and put it on string buffer
    if(Serial.available() > 0) { // check if there is incoming data
      incoming_byte = Serial.read();  // read the incoming byte
      buf[length++] = incoming_byte;  // put the incoming byte to string buffer
      if(incoming_byte == '\n') { // check if LF is incoming
        // append '\0' to buf[] as the end of the string
        buf[length++] = '\0';
        // do job
        if(strcmp(buf, "on\n")==0) { // check if the incoming string is "on"
          digitalWrite(LEDPIN, HIGH);
        }
        else if(strcmp(buf, "off\n")==0) { // check if the incoming string is "on"
          digitalWrite(LEDPIN, LOW);       
        }
        length = 0; // reset the length for receiving next string
      }
    }
}
