#include <Arduino.h>

const int ledXanh = 25;
const int ledVang = 27;
const int ledDo = 26;

void setup() {
  pinMode(ledXanh, OUTPUT);
  pinMode(ledVang, OUTPUT);
  pinMode(ledDo, OUTPUT);

  Serial.begin(115200);
  Serial.println("--- HE THONG DEN GIAO THONG ---");
}

void loop() {
  // --- PHA 1: ĐÈN XANH (7 giây) ---
  Serial.println("XANH: Di chuyen (7s)");
  digitalWrite(ledXanh, HIGH);
  digitalWrite(ledVang, LOW);
  digitalWrite(ledDo, LOW);
  delay(7000); 

  // --- PHA 2: ĐÈN VÀNG (3 giây) ---
  Serial.println("VANG: Cham lai (3s)");
  digitalWrite(ledXanh, LOW);
  digitalWrite(ledVang, HIGH);
  digitalWrite(ledDo, LOW);
  delay(3000);

  // --- PHA 3: ĐÈN ĐỎ (10 giây) ---
  Serial.println("DO: Dung lai (10s)");
  digitalWrite(ledXanh, LOW);
  digitalWrite(ledVang, LOW);
  digitalWrite(ledDo, HIGH);
  delay(10000);
}
//BLOCKING
// void loop() {
//   // put your main code here, to run repeatedly:
//   // static int i = 0;
//   // printf("Loop running ...%d\n",++i);
//   // delay(1000);

//   digitalWrite(PIN_LED_RED, HIGH); // Turn LED ON
//   delay(500); // Wait for 500ms
//   digitalWrite(PIN_LED_RED, LOW); // Turn LED OFF
//   delay(500); // Wait for 500ms  
// }

