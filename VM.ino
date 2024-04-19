#include <ESP8266WiFi.h>

const int m1Pin = 0; // motors pin 1
const int m2Pin = 2;  //motors pin 2

//Initializing IC 74HC595
const int DATA_Pin = 0;   // IC 595 data pin
const int CLK_Pin = 14;   // IC clock pin
const int LATCH_Pin = 15;  //IC latch pin

//Initializing IC 74HC165
const int DATA_Pin = 9;   // IC 595 data pin
const int CLK_Pin = 14;   // IC clock pin
const int LATCH_Pin = 0;  //IC latch pin

//Initializing millis function
const unsigned long d1 = 5000;
const unsigned long d2 = 5000;

// aassign values to the function
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

// State of Motor
bool motor1Running = false;
bool motor2Running = false;

const int button1Pin = 4; // buttons pins
const int button2Pin = 5;  //buttons pins

void setup() {
//Initializing Serial baud rate
  Serial.begin(115200);
//IC 595 pin state
  pinMode(DATA_Pin, OUTPUT); // set data pin as output
  pinMode(CLK_Pin, OUTPUT);  // set clock pin as output
  pinMode(LATCH_Pin, OUTPUT); // set latch pin as output

//IC 165 pin state
  pinMode(DATA_Pin, INPUT); // set data pin as input
  pinMode(CLK_Pin, OUTPUT);// set clock pin as output
  pinMode(LATCH_Pin, OUTPUT);// set latch pin as output

  // Motors pin state
  pinMode(m1Pin, OUTPUT);
  pinMode(m2Pin, OUTPUT);

  // buttons pins state
  pinMode(button1Pin, INPUT_PULLUP); 
  pinMode(button2Pin, INPUT_PULLUP); 
  
}

void loop() {
  currentMillis = millis();


  if (digitalRead(button1Pin) == LOW && !motor1Running) {

    startMotor1();
  }

 
  if (digitalRead(button2Pin) == LOW && !motor2Running) {

    startMotor2();
  }


  if (motor1Running && (currentMillis - previousMillis >= d1)) {

    stopMotor1();
  }

  
  if (motor2Running && (currentMillis - previousMillis >= d2)) {

    stopMotor2();

  }
}

void startMotor1() {
  shiftOut(DATA_Pin, LATCH_Pin, MSBFIRST, B00000001); 
  digitalWrite(CLK_Pin, HIGH); 
  digitalWrite(CLK_Pin, LOW);
  digitalWrite(m1Pin, HIGH);
  Serial.println("Motor 1 Start");

  motor1Running = true;
  previousMillis = currentMillis;

}

void stopMotor1() {
  shiftOut(DATA_Pin, LATCH_Pin, MSBFIRST, B00000000); 
  digitalWrite(CLK_Pin, HIGH); 
  digitalWrite(CLK_Pin, LOW);
  digitalWrite(m1Pin, LOW);
  Serial.println("Motor 1 Stop");
  delay(1000);    

  motor1Running = false;

}

void startMotor2() {

  shiftOut(DATA_Pin, LATCH_Pin, MSBFIRST, B00000010); 
  digitalWrite(CLK_Pin, HIGH); 
  digitalWrite(CLK_Pin, LOW);
  digitalWrite(m2Pin, HIGH);
  Serial.println("Motor 2 Start");

  motor2Running = true;
  previousMillis = currentMillis;

}

void stopMotor2() {

  shiftOut(DATA_Pin, LATCH_Pin, MSBFIRST, B00000000); 
  digitalWrite(CLK_Pin, HIGH); 
  digitalWrite(CLK_Pin, LOW);
  digitalWrite(m2Pin, LOW);
  Serial.println("Motor 2 Stop");
  delay(1000);

  motor2Running = false;

}
