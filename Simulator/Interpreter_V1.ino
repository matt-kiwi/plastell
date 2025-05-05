/*
  PlasTell Interpreter by KiwiFil, V1
  Eva Hakansson, 2025 

  This code is very ugly, but it works! It is script-kiddie coding hacked together from several Arduino examples. Feel free to make it pretty. 
  Thank you all tutorial authors - you are real heros! 
 

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Welcome to the PlasTell Interpreter by KiwiFil!"); 

  mySerial.begin(9600);  // set the data rate for the SoftwareSerial port
  //mySerial.println("Hello, Eva?");
}
/*
void loop() { // We don't need this data because we are talking back and forth betweeen the "simulator" and the "interpreter".
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

*/


void loop() {
    recvWithEndMarker();
    showNewData();

}

void recvWithEndMarker() {

        
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (mySerial.available() > 0 && newData == false) {
        rc = mySerial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void showNewData() {

  char leadingNumber = "u"; 
  leadingNumber = receivedChars[0];
  pinMode(5, OUTPUT); // Green LED
  pinMode(6, OUTPUT); // Blue LED
  pinMode(7, OUTPUT); // Red LED

    if (newData == true) { // This section is from an Arduino tutorial. I just left all the code in here. 
        Serial.print("This just came in ... ");
        Serial.println(receivedChars);
        Serial.println("The leading number is...");
        Serial.println(leadingNumber);
        int intLeadingNumber = 0; 
        intLeadingNumber = leadingNumber - 48; // Changing the char into an integer to make further processing simpler. 
        Serial.println("Leading number as int is....");
        Serial.println(intLeadingNumber);

        
switch (intLeadingNumber) { // Turning on the corresponding LED. Green = PLA, Blue = PETG, Red = Other. 
  case 1:
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    
    break;
  case 2:
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    break;
  case 3:
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    break;

  default:
    // if nothing else matches, do the default
    // default is optional
    break;
}


        newData = false;
    }
}




