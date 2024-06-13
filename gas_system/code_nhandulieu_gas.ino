#include <FirebaseESP8266.h>
#include <FirebaseFS.h>
#include <ESP8266WiFi.h>
#include "addons/TokenHelper.h"

const String name_wifi = "Vantai-Vando"; 
const String password_wifi = "18012102";

//#define API_KEY "AIzaSyCxzL7reZyKc3KAiFPv1izlZnVOTkU9Q74"
//#define DATABASE_URL "https://smarthome-98045-default-rtdb.firebaseio.com/"

#define FIREBASE_HOST "smarthome-98045-default-rtdb.firebaseio.com/"                 
#define FIREBASE_AUTH "rjho60yExTX3lcgkw4y7hZRKVcjvuX1ot4gWjpW9"
FirebaseData firebaseData;
FirebaseJson json;
FirebaseAuth auth;
FirebaseConfig firebaseConfig;

String data;
bool dataReady = false;
float t = 30.56;
bool historyIsActive;
int gasValue;
int statusWindowDefault = 0;
int statusWindowFirebase;

void setup(){
  Serial.begin(9600);
  WiFi.begin(name_wifi, password_wifi);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  firebaseConfig.database_url = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&firebaseConfig, &auth);

  Firebase.reconnectWiFi(true);
  delay(1000);
}


void loop(){
  if (Serial.available() > 0) {
    gasValue = Serial.parseInt();
  }
  Firebase.setInt(firebaseData, "/gas", gasValue);

  if (Firebase.getInt(firebaseData, "/bed-room/window")) {
    if (firebaseData.dataType() == "int") {
        statusWindowFirebase = firebaseData.intData();
        if (statusWindowFirebase != statusWindowDefault) {
          Serial.println(statusWindowFirebase);
        }
    }
  }
  statusWindowDefault = statusWindowFirebase;
}
