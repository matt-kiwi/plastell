/*
  PlasTell Emulator by KiwiFil, V1
  Eva Hakansson, April 2025

  This code is quite ugly, but it works! It is script-kiddie coding hacked together from several Arduino examples. Thank you all tutorial authors - you are real heros! 

 The circuit:
 * RX is digital pin 10 (connect to TX of other device) White wire
 * TX is digital pin 11 (connect to RX of other device) Yellow wire

 */
 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX, TX is the yellow wire. 
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

  char message[8][15] = 
{ "0Start",
  "1PLA 1.36",
  "1PLA 2.5",
  "2PETG 1.28",
  "2PET/PETG 0.5",
  "3ABS 0.5",
  "3TPU 0.5"
}; // "Random" messages representing the 'scanned' part. Don't change these - it will affect the rest of the code. 

void displayMessage (byte msgNum) // Function for troubleshooting - prints the message on the serial monitor
{ 
  Serial.println(message[msgNum]);
}

void setup() {

  int calibrationWait = 1; 

   Serial.begin(9600);
  while (!Serial) {
    ; 
  }
  Serial.println("Welcome to the PlasTell Emulator by KiwiFil");
 
  lcd.init();
  delay(100);
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("KiwiFil PlasTell");
  lcd.setCursor(0,1);
  lcd.print("Emulator");
  delay(700);

      digitalWrite(5, HIGH);
      delay(700);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      delay(700);
      digitalWrite(6, LOW);      
      digitalWrite(7, HIGH);
      delay(700);
      digitalWrite(7, LOW);
      delay(700);

  mySerial.begin(9600);

  Serial.println("Calibrating.... please wait.");
   
  lcd.clear(); 
  lcd.setCursor(0,0);
  lcd.print("Calibrating...");
  lcd.setCursor(0,1);
  lcd.print("...please wait ");
  delay(1000);

do 
  {
  lcd.setCursor(15,1);
  lcd.print(calibrationWait);
  Serial.println(calibrationWait);
  calibrationWait++; 
  delay(1000);
   } while (calibrationWait <= 2); // Increase this number if you want the "calibration" to last longer. The real scanner calibrates for 10-15 seconds. 

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(message[0]);

  mySerial.println(message[0]); // Sending the message "0Start" to signal that that scanner is ready. 
  Serial.println(message[0]);

  delay(1000); 

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ready. Press");
  lcd.setCursor(0,1);
  lcd.print("button to 'scan'");
  
  pinMode(4, INPUT_PULLUP); // Button on orange box
  pinMode(12, INPUT_PULLUP); // Button on the scanner dummy
  pinMode(13, OUTPUT); // LED in the dummy button

  digitalWrite(13, LOW); // Make sure the LED in the dummy button is off. 

}

void loop() { 

int buttonVal =(digitalRead(12)) ; // Read the button on the scanner dummy
int buttonVal2 =(digitalRead(4)) ; // Read the button on the orange box

  if ((buttonVal == LOW) || (buttonVal2 == LOW)) { // Reading for any button press
    
    digitalWrite(13, HIGH);

     digitalWrite(5, LOW); // Making sure all LEDs are off
     digitalWrite(6, LOW);
     digitalWrite(7, LOW);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Scanning...");
    delay(1500); // Delay to simulate the time the actual scan takes. 

    long randNumber; 

    lcd.clear();
    randNumber = random(1,7); // Selects a random message from the array. 
    displayMessage(randNumber); 
    mySerial.println(message[randNumber]);
    lcd.print(message[randNumber]);

     pinMode(5, OUTPUT); // Green LED
     pinMode(6, OUTPUT); // Blue LED
     pinMode(7, OUTPUT); // Red LED

if (randNumber == 1){ digitalWrite(5, HIGH);} // Turn on green LED
if (randNumber == 2){ digitalWrite(5, HIGH);} // Turn on green LED
if (randNumber == 3){ digitalWrite(6, HIGH);} // Turn on blue LED
if (randNumber == 4){ digitalWrite(6, HIGH);} // Turn on blue LED
if (randNumber == 5){ digitalWrite(7, HIGH);} // Turn on red LED
if (randNumber == 6){ digitalWrite(7, HIGH);} // Turn on red LED

  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }

    } else {
    digitalWrite(13, LOW);
  }

}
