#include <Arduino.h>

#define PIN_LED_RED     25
#define PIN_LED_YELLOW  33
#define PIN_LED_GREEN   32

#define BLINK_INTERVAL 500  // 1 giây = 1 lần nhấp nháy

#define RED_BLINKS     5
#define YELLOW_BLINKS  3
#define GREEN_BLINKS   7

enum LedState {
  LED_RED,
  LED_YELLOW,
  LED_GREEN
};

bool IsReady(unsigned long &timer, uint32_t interval) {
  if (millis() - timer < interval) return false;
  timer = millis();
  return true;
}

void allOff() {
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_LED_GREEN, LOW);
}

void setup() {
  Serial.begin(115200);
  Serial.println("START");

  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
}

void loop() {
  static unsigned long timer = 0;
  static LedState state = LED_RED;
  static bool ledOn = false;
  static int blinkCount = 0;

  if (!IsReady(timer, BLINK_INTERVAL)) return;

  ledOn = !ledOn;
  allOff();

  switch (state) {

    case LED_RED:
      digitalWrite(PIN_LED_RED, ledOn);
      Serial.print("RED   : ");
      Serial.println(ledOn ? "ON" : "OFF");

      if (!ledOn && ++blinkCount >= RED_BLINKS) {
        blinkCount = 0;
        state = LED_YELLOW;
      }
      break;

    case LED_YELLOW:
      digitalWrite(PIN_LED_YELLOW, ledOn);
      Serial.print("YELLOW: ");
      Serial.println(ledOn ? "ON" : "OFF");

      if (!ledOn && ++blinkCount >= YELLOW_BLINKS) {
        blinkCount = 0;
        state = LED_GREEN;
      }
      break;

    case LED_GREEN:
      digitalWrite(PIN_LED_GREEN, ledOn);
      Serial.print("GREEN : ");
      Serial.println(ledOn ? "ON" : "OFF");

      if (!ledOn && ++blinkCount >= GREEN_BLINKS) {
        blinkCount = 0;
        state = LED_RED;
      }
      break;
  }
}
