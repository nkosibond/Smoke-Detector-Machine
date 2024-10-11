// C++ code
//
/*

  The circuit:
  * LCD RS pin to digital pin 12
  * LCD Enable pin to digital pin 11
  * LCD D4 pin to digital pin 5
  * LCD D5 pin to digital pin 4
  * LCD D6 pin to digital pin 3
  * LCD D7 pin to digital pin 2
  * LCD R/W pin to ground
  * LCD VSS pin to ground
  * LCD VCC pin to 5V
  * 10K resistor:
  * ends to +5V and ground
  * wiper to LCD VO pin (pin 3)

*/

#include <LiquidCrystal.h>
int seconds = 0;

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);
const int gas_input = A0;
int gas = 0;
const int RedLed = 13;       
const int buzzer = 9;
const int buttonpin = 8;   
int buttonState = 0;
bool alarmSilenced = false; 

void setup()
{
  lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.
  pinMode(RedLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(buttonpin, INPUT_PULLUP);  

  
  
  lcd_1.print("IOT Project");

  Serial.begin(9600);

  // Print a message to the LCD.
  lcd_1.setCursor(1, 1);
  lcd_1.print("System Ready");
  delay(3000);
}

void loop()
{
  Serial.begin(9600);
  //Serial.println(gas);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting
  // begins with 0):
  lcd_1.setCursor(0, 1);
  // print the gas values:
  lcd_1.print("Gas Value: ");
  
  lcd_1.print(gas);
  delay(1000); // Wait for 1000 millisecond(s)
  
  gas = analogRead(gas_input);
   Serial.println(gas);

   buttonState = digitalRead(buttonpin);

 

   if (buttonState == LOW) {
      alarmSilenced = true;
      noTone(buzzer);
      digitalWrite(RedLed, LOW);   
      lcd_1.clear();
      lcd_1.print("System Silenced");
      delay(1000);
   }
   else if
	 (gas > 30 && !alarmSilenced) {  
      int led_out = map(gas, 80, 400, 0, 255); 
      digitalWrite(RedLed, HIGH); 
      tone(buzzer, led_out, 100);
      delay(1000);
      tone(buzzer, led_out, 9000);
      delay(250); 
      lcd_1.clear();
      lcd_1.print("Alert: Smoke!!!");
     lcd_1.setCursor(0, 1);
     lcd_1.print("Gas Value: ");
  	lcd_1.print(gas);
     delay(2000);
     lcd_1.clear();
     lcd_1.print("Button to mute");
    }

 

    if (gas <= 30) {
      alarmSilenced = false;
      lcd_1.clear();
      lcd_1.print("System Ready");
      digitalWrite(RedLed, LOW);
   }
  
  	if (buttonState == LOW) {
      alarmSilenced = true;
      noTone(buzzer);
      digitalWrite(RedLed, LOW);   
      lcd_1.clear();
      lcd_1.print("System Silenced");
      delay(1000);
   }
}