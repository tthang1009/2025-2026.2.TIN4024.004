#include <Arduino.h>

#define LED_RED    25
#define LED_YELLOW 26
#define LED_GREEN  27

void setup() {
  Serial.begin(115200);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  Serial.println("=== ESP32 3 LED Blink Simulation ===");
}

void loop() {
  Serial.println("LED [RED] ON => 5 Seconds");
  digitalWrite(LED_RED, HIGH);
  delay(5000);
  digitalWrite(LED_RED, LOW);

  Serial.println("LED [YELLOW] ON => 3 Seconds");
  digitalWrite(LED_YELLOW, HIGH);
  delay(3000);
  digitalWrite(LED_YELLOW, LOW);

  Serial.println("LED [GREEN] ON => 7 Seconds");
  digitalWrite(LED_GREEN, HIGH);
  delay(7000);
  digitalWrite(LED_GREEN, LOW);

  Serial.println("-----------------------------");
}
