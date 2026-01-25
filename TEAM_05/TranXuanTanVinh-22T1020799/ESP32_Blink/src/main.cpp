#include <Arduino.h>

// Định nghĩa chân cắm
const int RED_LED = 23;
const int YELLOW_LED = 22;
const int GREEN_LED = 21;

void setup() {
  // Thiết lập các chân là Output
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop() {
  // 1. Đèn Xanh sáng (Ví dụ: 3 giây)
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  delay(3000);

  // 2. Đèn Vàng sáng (Ví dụ: 1 giây)
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  delay(1000);

  // 3. Đèn Đỏ sáng (Ví dụ: 3 giây)
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  delay(3000);
}