#include <ESP8266WiFi.h>

const int m1Pin = 0;
const int m2Pin = 2;

const int DATA_Pin = 0; 
const int CLK_Pin = 14; 
const int LATCH_Pin = 15; 

const unsigned long d1 = 5000;
const unsigned long d2 = 5000;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
bool motor1Running = false;
bool motor2Running = false;

void setup() {
  Serial.begin(115200);
  pinMode(DATA_Pin, OUTPUT);
  pinMode(CLK_Pin, OUTPUT);
  pinMode(LATCH_Pin, OUTPUT);

   pinMode(m1Pin, OUTPUT);
  pinMode(m2Pin, OUTPUT);
}

void loop() {
  currentMillis = millis();

  if (!motor1Running) {
    shiftOut(DATA_Pin, LATCH_Pin, MSBFIRST, B00000001); 
    digitalWrite(CLK_Pin, HIGH); 
    digitalWrite(CLK_Pin, LOW);
    digitalWrite(m1Pin, HIGH);
    Serial.println("Motor 1 Start");
    motor1Running = true;
    previousMillis = currentMillis;
  }

  if (motor1Running && (currentMillis - previousMillis >= d1)) {
    shiftOut(DATA_Pin, LATCH_Pin, MSBFIRST, B00000000); 
    digitalWrite(CLK_Pin, HIGH); 
    digitalWrite(CLK_Pin, LOW);
     digitalWrite(m1Pin, HIGH);
    Serial.println("Motor 1 Stop");
    delay(1000);
    motor1Running = false;
  }

  if (!motor2Running && !motor1Running) {
    shiftOut(DATA_Pin, LATCH_Pin, MSBFIRST, B00000010); 
    digitalWrite(CLK_Pin, HIGH); 
    digitalWrite(CLK_Pin, LOW);
     digitalWrite(m2Pin, HIGH);
    Serial.println("Motor 2 start");
    motor2Running = true;
    previousMillis = currentMillis;
  }

  if (motor2Running && (currentMillis - previousMillis >= d2)) {
    shiftOut(DATA_Pin, LATCH_Pin, MSBFIRST, B00000000); 
    digitalWrite(CLK_Pin, HIGH); 
    digitalWrite(CLK_Pin, LOW);
     digitalWrite(m2Pin, LOW);
    Serial.println("Motor 2 stop");
    delay(1000);
    motor2Running = false;
  }
}
