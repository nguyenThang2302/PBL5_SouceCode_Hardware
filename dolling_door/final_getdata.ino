#include <SoftwareSerial.h>

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
//https://testesp8266-f5f3c-default-rtdb.firebaseio.com/
#define FIREBASE_HOST "smarthome-98045-default-rtdb.firebaseio.com/"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "rjho60yExTX3lcgkw4y7hZRKVcjvuX1ot4gWjpW9" //Your Firebase Database Secret goes here
/* 4, Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* Define the FirebaseConfig data for config data */
FirebaseConfig config;
#define WIFI_SSID "ip"                                               //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "244466666"                                      //Password of your wifi network 
// #include<SoftwareSerial.h>

// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

// Declare global variable to store value
int val=0;
// Khai báo các chân RX và TX cho espsoftwareserial
// #define RX_PIN 4 // D2
// #define TX_PIN 5 // D1

// Tạo một đối tượng espsoftwareserial với tốc độ baud là 9600
// SoftwareSerial mySerial(RX_PIN, TX_PIN);
int i = 1;

void setup() {
  // Khởi tạo cổng nối tiếp phần cứng với tốc độ baud là 115200
  Serial.begin(9600);

  // Khởi tạo cổng nối tiếp phần mềm với tốc độ baud là 9600
  // mySerial.begin(9600);

  // In ra thông báo khởi động
  // Serial.println("ESP8266 UART Communication Example");
  config.database_url = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  // Serial.println("Serial communication started\n\n");  
           
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  // Serial.print("Connecting to ");
  // Serial.print(WIFI_SSID);


  
  while (WiFi.status() != WL_CONNECTED) {
    // Serial.print(".");
    delay(500);
  }

  
  // Serial.println();
  // Serial.print("Connected to ");
  // Serial.println(WIFI_SSID);
  // Serial.print("IP Address is : ");
  // Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(&config, &auth);

  Firebase.reconnectWiFi(true);
  delay(1000);
}
void loop() {
// Firebase Error Handling And Reading Data From Specified Path ************************************************
    readLightValue();
    readRollingDoorValue();
    // readWindowValue();
    // readFanValue();
 }
void readLightValue() {
    if (Firebase.getInt(firebaseData, "/light")) { // On successful Read operation, function returns 1  
       int val = firebaseData.intData();
            
    // Chuyển đổi số nguyên thành chuỗi
    char valStr[10];
    snprintf(valStr, sizeof(valStr), "%d", val);
            
    // Tạo chuỗi kết quả
    char charValue[50];
    snprintf(charValue, sizeof(charValue), "light-%s", valStr);
            
    // Gửi chuỗi kết quả qua mySerial
    Serial.println(charValue);
    } else {
        // Serial.println(firebaseData.errorReason());
    }
}

void readRollingDoorValue(){
  if (Firebase.getInt(firebaseData, "/rolling_door")) {                           // On successful Read operation, function returns 1  
    if (firebaseData.dataType() == "int") {
      int val = firebaseData.intData();
            
    // Chuyển đổi số nguyên thành chuỗi
    char valStr[10];
    snprintf(valStr, sizeof(valStr), "%d", val);
            
    // Tạo chuỗi kết quả
    char charValue[50];
    snprintf(charValue, sizeof(charValue), "rolling_door-%s", valStr);
            
    // Gửi chuỗi kết quả qua mySerial
    Serial.println(charValue);
    }

  } else {
    // Serial.println(firebaseData.errorReason());
  }
}
void readFanValue(){
  if (Firebase.getInt(firebaseData, "/fan")) {                           // On successful Read operation, function returns 1  
    int val = firebaseData.intData();
            
    // Chuyển đổi số nguyên thành chuỗi
    char valStr[10];
    snprintf(valStr, sizeof(valStr), "%d", val);
            
    // Tạo chuỗi kết quả
    char charValue[50];
    snprintf(charValue, sizeof(charValue), "fan-%s", valStr);
            
    // Gửi chuỗi kết quả qua mySerial
    Serial.println(charValue);
  } else {
    // Serial.println(firebaseData.errorReason());
  }
}
void readWindowValue(){
  if (Firebase.getInt(firebaseData, "/window")) {                           // On successful Read operation, function returns 1  
    int val = firebaseData.intData();
            
    // Chuyển đổi số nguyên thành chuỗi
    char valStr[10];
    snprintf(valStr, sizeof(valStr), "%d", val);
            
    // Tạo chuỗi kết quả
    char charValue[50];
    snprintf(charValue, sizeof(charValue), "window-%s", valStr);
            
    // Gửi chuỗi kết quả qua mySerial
    Serial.println(charValue);

  } else {
    // Serial.println(firebaseData.errorReason());
  }
}


