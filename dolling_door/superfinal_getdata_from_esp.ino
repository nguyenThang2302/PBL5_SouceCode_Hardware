// #include <SoftwareSerial.h> // Thư viện cho cổng nối tiếp mềm
#define ENA_PIN 11
#define RX_PIN 10 // Chân RX của cổng nối tiếp mềm
#define TX_PIN 11 // Chân TX của cổng nối tiếp mềm
#define LED_PIN 8 // Chân kết nối với led
bool ledIsOn = false;
char c = '\\';
int in1=9, in2=3,in3=6,in4=12;
int ctht1=4, ctht2=5;
int nutnhanxuong = 7, nutnhanlen=2;

// SoftwareSerial mySerial(RX_PIN, TX_PIN); // Tạo một đối tượng cổng nối tiếp mềm

void setup() {
  Serial.begin(9600); // Khởi tạo cổng nối tiếp cứng với tốc độ baud là 9600
  // mySerial.begin(9600); // Khởi tạo cổng nối tiếp mềm với tốc độ baud là 9600
  pinMode(ENA_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT); // Đặt chân kết nối với led là chân đầu ra
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(nutnhanlen, INPUT_PULLUP);
  pinMode(nutnhanxuong, INPUT_PULLUP);
  pinMode(ctht1,INPUT);
  pinMode(ctht2,INPUT);
  // Serial.println("Starting...");
}

void loop() {
  int trangthainutlen=digitalRead(nutnhanlen);
  int trangthainutxuong=digitalRead(nutnhanxuong);
  int trangthaict1=digitalRead(ctht1);
  int trangthaict2=digitalRead(ctht2);
  // Serial.print(trangthaict1);
  // Serial.println(trangthaict2);

  if(trangthainutlen==0 && trangthainutxuong!=0 && trangthaict1==1 ){
    lui();
  }
  else if (trangthainutlen!=0 && trangthainutxuong==0 && trangthaict2==1){ 
    tien();
  }
  else {
    dung();
  }
  if (Serial.available() > 0) { // Nếu có dữ liệu từ cổng nối tiếp mềm
    // String received = mySerial.readStringUntil('\n'); // Đọc chuỗi đến ký tự newline

    // int c = Serial.parseInt(); // Chuyển đổi chuỗi thành số nguyên
     String receivedData = Serial.readStringUntil('\n');
     Serial.println(receivedData);
     processData(receivedData);
    // if (c == 1 && trangthaict1 == 1) { // Nếu giá trị là 1
    //     lui();
    // } else if (c == -1 && trangthaict2 == 1) { // Nếu giá trị là 0
    //     tien();
    // } else { // Nếu giá trị khác
    //     dung();
    // }
}

}
void tien(){
  analogWrite(ENA_PIN, 75);
  digitalWrite(in1, HIGH); // Điều chỉnh tốc độ bằng cách thay đổi giá trị từ 0 đến 255
  digitalWrite(in2,LOW);
  delay(100);

}
 void lui(){
  analogWrite(ENA_PIN, 75);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  delay(100);
}
 void dung(){
  analogWrite(ENA_PIN, 0);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  delay(100);
  }
  void turnOnLed(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  }
  void turnOffLed(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  }
void processData(String data) {
  int val = 0;
  int trangthaict1 = digitalRead(ctht1);
  int trangthaict2 = digitalRead(ctht2);

  if (data.startsWith("rolling_door-")) {
    // Extract the integer value from the string
    val = data.substring(13).toInt();
    Serial.print("Received rolling_door: ");
    Serial.println(val);
    
    if (val == 1 && trangthaict1 == 1) {
      lui();
      Serial.println("Tien");
    } else if (val == -1 && trangthaict2 == 1) {
      tien();
      Serial.println("Lui");
    } else {
      dung();
      Serial.println("Dung");
    }
  } else if (data.startsWith("light-")) {
    val = data.substring(6).toInt();
    Serial.print("Received light: ");
    Serial.println(val);
    
    if (val == 1) {
      turnOnLed();
      Serial.println("Turn on led");
    } else {
      turnOffLed();
      Serial.println("Turn off led");
    }
  }
}

