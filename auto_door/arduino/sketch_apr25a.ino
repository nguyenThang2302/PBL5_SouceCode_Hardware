#include <Arduino.h>

// Define the pins
#define Ena 3
#define In1 9
#define In2 10
#define BUTTON_CLOSE 12
#define BUTTON_OPEN 11
#define BUTTON_HT_CLOSE_1 2
#define BUTTON_HT_CLOSE_2 4

// Define variables for PWM
int pwm_a = 0;
int pwm_b = 0;
int valueClose = 0;
bool statusClose = false; // CHưa được nhấn
bool statusOpen = false; // CHưa được nhấn
int statusMainDoor = 0;
int statusFirebase;
int statusMainDoorDefault = 0;

void setup() {
  Serial.begin(9600);
  // Set pin modes
  pinMode(Ena, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(BUTTON_CLOSE, INPUT_PULLUP);
  pinMode(BUTTON_OPEN, INPUT_PULLUP);

  pinMode(BUTTON_HT_CLOSE_1, INPUT);
  pinMode(BUTTON_HT_CLOSE_2, INPUT);

  // Initialize PWM
  pwm_a = 0;
  pwm_b = 0;
}

void loop() {
  int CloseStatus = digitalRead(BUTTON_CLOSE);
  int OpenStatus = digitalRead(BUTTON_OPEN);
  int HTStatus1 = digitalRead(BUTTON_HT_CLOSE_1);
  int HTStatus2 = digitalRead(BUTTON_HT_CLOSE_2);

  // Serial.println("--------");
  // Serial.println(CloseStatus);
  // Serial.println(OpenStatus);
  // Serial.println(HTStatus1); // Close
  // Serial.println(HTStatus2); // Open
  // Serial.println("--------");

  if (Serial.available() == 0) {
    if (CloseStatus == 0 && OpenStatus != 0 && HTStatus1 == 0) {
      openDoor();
    } else if (OpenStatus == 0 && CloseStatus != 0 && HTStatus2 == 0) {
      closeDoor();
    } else {
      cancelActiveDoor();
    }
  }

  // Lấy giá trị ESP8266 lấy từ Firebase truyền sang
  if (Serial.available() > 0) { 
    statusMainDoor = Serial.parseInt(); 
    statusFirebase = statusMainDoor;
    if (statusFirebase == 1 && OpenStatus != 0 && HTStatus1 != 0) { // Yêu cầu cửa mở từ Firebase
      closeDoor();
      delay(500);
    } else if (statusFirebase == 0 && CloseStatus != 0 && HTStatus2 != 0) { // Yêu cầu cửa đóng từ Firebase
      openDoor();
      delay(300);
    } 
  }
}

void closeDoor() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  analogWrite(Ena, 150);
}

void openDoor() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  analogWrite(Ena, 150);
}

void cancelActiveDoor() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  analogWrite(Ena, 0);
}
