#include <Arduino.h>

// Định nghĩa các chân cắm (GPIO)
const int RED_LED = 23;
const int YELLOW_LED = 22;
const int GREEN_LED = 21;

void setup()
{
  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  Serial.println("He thong den giao thong da cap nhat thoi gian!");
}

void loop()
{
  // 1. ĐÈN ĐỎ SÁNG - Chờ 3 giây
  Serial.println("Den Do: 3s");
  digitalWrite(RED_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  delay(3000); // 3000ms = 3s

  // 2. ĐÈN XANH SÁNG - Chờ 5 giây
  Serial.println("Den Xanh: 5s");
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  delay(5000); // 5000ms = 5s

  // 3. ĐÈN VÀNG SÁNG - Chờ 7 giây
  Serial.println("Den Vang: 7s");
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  delay(7000); // 7000ms = 7s
}