#include <Wire.h> 
#include <LiquidCrystal_PCF8574.h>
#include <Keypad.h>

#define PASSWORD_LENGTH 7 

int relayPin = 12;

const char password[PASSWORD_LENGTH+1] = "135*246"; 
char input[PASSWORD_LENGTH+1]; 
byte input_length = 0;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_PCF8574 lcd(0x20);  

void setup(){
    lcd.begin(16, 2);
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}

void loop(){
  char key;

  lcd.setCursor(0,0);
  lcd.print("Enter Password:");

  key = customKeypad.getKey();
  if (key){
    input[input_length] = key; 
    lcd.setCursor(input_length,1); 
    lcd.print(input[input_length]); 
    input_length++; 
  }

  if(input_length == PASSWORD_LENGTH){
    lcd.clear();

    if(!strcmp(input, password)){
      lcd.print("Correct!");
      digitalWrite(relayPin, HIGH); 
      delay(5000);
      digitalWrite(relayPin, LOW);
      }
    else{
      lcd.print("Wrong password!");
      delay(1000);
      }
    
    lcd.clear();
    input_length = 0;  
  }
}
