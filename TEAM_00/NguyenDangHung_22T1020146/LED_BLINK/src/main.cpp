#include <Arduino.h>

int ledXanh = 25;
int ledVang = 27;
int ledDo   = 26;

void setup() {
  pinMode(ledXanh, OUTPUT);
  pinMode(ledVang, OUTPUT);
  pinMode(ledDo, OUTPUT);
}

void loop() {
  // ĐÈN XANH - 7 GIÂY
  digitalWrite(ledXanh, HIGH);
  digitalWrite(ledVang, LOW);
  digitalWrite(ledDo, LOW);
  delay(7000);

  // ĐÈN VÀNG - 3 GIÂY
  digitalWrite(ledXanh, LOW);
  digitalWrite(ledVang, HIGH);
  digitalWrite(ledDo, LOW);
  delay(3000);

  // ĐÈN ĐỎ - 10 GIÂY
  digitalWrite(ledXanh, LOW);
  digitalWrite(ledVang, LOW);
  digitalWrite(ledDo, HIGH);
  delay(10000);
}
