#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <Servo.h>

#define SERVO_PIN 8

Servo gServo;

//L298N-DC config
// Motor A connections
int enA = 3;
int in1 = 9;
int in2 = 10;
// Motor B connections
int enB = 6;
int in3 = 11;
int in4 = 12;

//Sensor config
const int digitalPin = 4;
const int analogPin = A0;
int digitalValue = 0;
int analogValue = 0;

//Led config
const int ledsPin[] = { 5, 7};

// Alarm config
const int alarmPin = 13;

//Button push config
const int interruptPin = 2;
unsigned long alarmStartTime = 0;

bool isDoorOpened = false;
bool alarmActive = false;
bool status = true;

LiquidCrystal_I2C lcd(0x27, 16, 2);

String data = "";
int pos = 0;
int statusWindow = 0;
int statusWindowFirebase;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(interruptPin, INPUT_PULLUP);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(alarmPin, OUTPUT);
  pinMode(ledsPin[1], OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), pressButton, FALLING);

  gServo.attach(SERVO_PIN);                
}

void loop() {

  digitalValue = digitalRead(digitalPin);
  analogValue = analogRead(analogPin);

  outSerial();
  outLed();
  outLcd();

  if (!digitalValue) {
    digitalWrite(ledsPin[1],HIGH);
  } else {
    digitalWrite(ledsPin[1],LOW);
  }

  Serial.println(analogValue);
  
  if (status && analogValue > 115) {
    alarm();
    activeWindow(pos);
    activeFan();
    statusWindow = 1;
  }

  if (Serial.available() > 0) {
    statusWindowFirebase = Serial.parseInt();
    if (statusWindowFirebase != statusWindow) {
      if (statusWindowFirebase == 1) {
        activeWindow(pos);
        statusWindow = 1;
      } else if (statusWindowFirebase == 0) {
        closeWindow(pos);
        statusWindow = 0;
      }
    }
    statusWindow = statusWindowFirebase;
  }

  delay(1000);
}


void outLcd() {
  lcd.clear();
  lcd.setCursor(0, 1);

  if (status){
    lcd.print("ACTIVE SYSTEM");
  }else{
    lcd.print("DEACTIVE SYSTEM");
  }
}

void pressButton(){
  status = !status;
}

void outLed() {
  analogWrite(ledsPin[0], constrain(analogValue/10, 0, 255));
}

void outSerial(){
  String data = String(analogValue) + "_" + String(status);
}

int toneVal;

void alarm() {
  for (int i = 0; i < 180; i++) {
    toneVal = 2000 + (int(sin(i * (3.1412 / 180)) * 1000));
    tone(alarmPin, toneVal);
    delay(2);
  }
  noTone(alarmPin); 
}

void activeWindow(int pos) {
  pos = 180;
  gServo.write(pos);
}

void closeWindow(int pos) {
  pos = -90;
  gServo.write(pos);
}

void activeFan() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}


