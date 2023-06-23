#include "DHT.h"
#include <LiquidCrystal_PCF8574.h>

#define DHTPIN 2     // what pin we're connected to
#define TEMP_LIMIT  30.0
#define HUM_LIMIT   60.0
#define LED_TEMP  8
#define LED_HUM   9

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_PCF8574 lcd(0x20); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() 
{
    // Initialize Serial port
    Serial.begin(9600); 

    // Set LED pins as output
    pinMode(LED_TEMP, OUTPUT);
    pinMode(LED_HUM, OUTPUT);

    // Initialize DHT & LCD
    dht.begin();
    lcd.begin(16, 2);
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();

    Serial.println("Lab 7 start!");
}

void loop() 
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    char buf[17];
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // check if returns are valid, if they are NaN (not a number) then something went wrong!
    if (isnan(t) || isnan(h)) 
    {
        Serial.println("Failed to read from DHT");
    } 
    else 
    {
        // Print Temperature & Humidity data on Serial port
        Serial.print("Humidity: "); 
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: "); 
        Serial.print(t);
        Serial.println(" *C");

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
        
        // if value > limit, LED on; else LED off
        if(t >= TEMP_LIMIT)
          digitalWrite(LED_TEMP, HIGH);
        else
          digitalWrite(LED_TEMP, LOW);
        if(h >= HUM_LIMIT)
          digitalWrite(LED_HUM, HIGH);
        else
          digitalWrite(LED_HUM, LOW);
    }
    delay(2000);
}
