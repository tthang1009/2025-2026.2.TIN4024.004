#include <Arduino.h> // <--- QUAN TRỌNG: Phải có dòng này trong file .cpp

// Định nghĩa chân kết nối
const int PIN_RED = 25;
const int PIN_YELLOW = 33;
const int PIN_GREEN = 32;

void setup() {
  // Khởi động Serial Monitor
  Serial.begin(115200);

  // Cấu hình các chân là OUTPUT
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
}

void loop() {
  // --- GIAI ĐOẠN ĐÈN ĐỎ ---
  digitalWrite(PIN_RED, HIGH);   
  Serial.println("LED [RED   ] ON => 5 Seconds");
  delay(5000);                   
  digitalWrite(PIN_RED, LOW);    

  // --- GIAI ĐOẠN ĐÈN VÀNG ---
  digitalWrite(PIN_YELLOW, HIGH); 
  Serial.println("LED [YELLOW] ON => 3 Seconds");
  delay(3000);                    
  digitalWrite(PIN_YELLOW, LOW);  

  // --- GIAI ĐOẠN ĐÈN XANH ---
  digitalWrite(PIN_GREEN, HIGH);  
  Serial.println("LED [GREEN ] ON => 7 Seconds");
  delay(7000);                    
  digitalWrite(PIN_GREEN, LOW);   
}