#include <Arduino.h>

// Định nghĩa các chân nối đèn theo đúng diagram.json của bạn
#define LED_GREEN 32
#define LED_YELLOW 33
#define LED_RED 25

void setup() {
  // Khởi động Serial Monitor để in thông báo ra màn hình (như trong ảnh)
  Serial.begin(115200);

  // Cấu hình các chân đèn là OUTPUT (đầu ra)
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

void loop() {
  // --- PHA 1: ĐÈN ĐỎ SÁNG (5 Giây) ---
  digitalWrite(LED_RED, HIGH);    // Bật đèn Đỏ
  digitalWrite(LED_YELLOW, LOW);  // Tắt đèn Vàng
  digitalWrite(LED_GREEN, LOW);   // Tắt đèn Xanh
  
  Serial.println("LED [RED   ] ON => 5 Seconds"); // In thông báo
  delay(5000); // Chờ 5000ms = 5 giây


  // --- PHA 2: ĐÈN VÀNG SÁNG (3 Giây) ---
  digitalWrite(LED_RED, LOW);     
  digitalWrite(LED_YELLOW, HIGH); // Bật đèn Vàng
  digitalWrite(LED_GREEN, LOW);
  
  Serial.println("LED [YELLOW] ON => 3 Seconds");
  delay(3000); // Chờ 3000ms = 3 giây


  // --- PHA 3: ĐÈN XANH SÁNG (7 Giây) ---
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, HIGH);  // Bật đèn Xanh
  
  Serial.println("LED [GREEN ] ON => 7 Seconds");
  delay(7000); // Chờ 7000ms = 7 giây
}