#include <Arduino.h>
// #include <SoftwareSerial.h>

// Defines
#define PIN_LED_YELLOW 5 
#define PIN_LED_GREEN 13
#define PIN_LED_RED 2
#define PIN_SW_SERIAL_RX 10
#define PIN_SW_SERIAL_TX 11

// Public vars / objects
uint8_t lineBuffer[30];

// Serial ports, console for messages & serailInput from the orange box
Serial_ console = Serial;
// SoftwareSerial serialInput(PIN_SW_SERIAL_RX, PIN_SW_SERIAL_TX);
Serial_ serialInput = Serial;

// Forward declarations
void allLeds( bool led_state );
void plasticTypePLA();
void plasticTypePETG();
void plasticTypeUknown();

void setup() {
  console.begin(9600);
  serialInput.begin(9600);
  pinMode(PIN_LED_GREEN,OUTPUT);
  pinMode(PIN_LED_RED,OUTPUT);
  pinMode(PIN_LED_YELLOW,OUTPUT);
  allLeds(HIGH);
  delay(1000);
  allLeds(LOW);
  console.println("Interpreter starting");
}

void loop() {
  uint8_t firstDigit;
  delay(1000); // Reasonable time for string to arrive
  memset(lineBuffer,0, sizeof(lineBuffer) );
  if( serialInput.readBytesUntil('\n', lineBuffer, sizeof(lineBuffer) ) == 0 ){
    return; // Buffer empty do nothing
  }
  firstDigit = lineBuffer[0] - '0';
  allLeds(LOW);
  switch( firstDigit ){
    case 0:
      console.println("Got start message.");
      break;
    case 1:
      digitalWrite( PIN_LED_GREEN, HIGH);
      plasticTypePLA();
      break;
    case 2:
      digitalWrite( PIN_LED_YELLOW, HIGH);
      plasticTypePETG();
      break;
    default:
      digitalWrite( PIN_LED_RED, HIGH);
      plasticTypeUknown();
  }
}

// Utility functions
void allLeds( bool led_state ){
  digitalWrite(PIN_LED_GREEN,led_state);
  digitalWrite(PIN_LED_YELLOW,led_state);
  digitalWrite(PIN_LED_RED,led_state);
}

void plasticTypePLA(){
  console.println("PLA Plastic");
  // Write your integration here
}

void plasticTypePETG(){
  console.println("PETG Plastic");
  // Write your integration here
}

void plasticTypeUknown(){
  console.println("Unkown Plastic");
  // Write your integration here
}
