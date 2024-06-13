#include <FirebaseESP8266.h>
#include <FirebaseFS.h>
#include <ESP8266WiFi.h>
#include "addons/TokenHelper.h"

const String name_wifi = "TAP HOA DAU CAU"; 
const String password_wifi = "14091974";

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
int statusMainDoorCurrent;
int statusMainDoorDefault = 0;
int statusMainDoor;

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

//  firebaseConfig.api_key = API_KEY;
//  firebaseConfig.database_url = DATABASE_URL;

//  if(Firebase.signUp(&firebaseConfig, &auth, "", "")){
//    Serial.println("");
//  } else {
//    Serial.println(firebaseConfig.signer.signupError.message.c_str());
//  }
//
//  firebaseConfig.token_status_callback = tokenStatusCallback;
//  
//  Firebase.begin(&firebaseConfig, &auth);
//  Firebase.reconnectWiFi(true);
}.




void loop(){
  if (Firebase.getInt(firebaseData, "/main_door")) {
    if (firebaseData.dataType() == "int") {
        statusMainDoorCurrent = firebaseData.intData();
        if (statusMainDoorCurrent != statusMainDoorDefault) {
          Serial.println(statusMainDoorCurrent);
        }
    }
  }
  statusMainDoorDefault = statusMainDoorCurrent;
}
