#include <Arduino.h>

// Định nghĩa chân đèn
#define RED_LED 23
#define YELLOW_LED 22
#define GREEN_LED 21

void setup() {
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop() {
  // 1. Đèn Đỏ sáng 5 giây
  Serial.println("DUNG LAI (RED)");
  digitalWrite(RED_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  delay(5000);

  // 2. Đèn Vàng sáng 2 giây
  Serial.println("CHUAN BI DI (YELLOW)");
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  delay(2000);

  // 3. Đèn Xanh sáng 5 giây
  Serial.println("DI THOI (GREEN)");
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  delay(5000);
}