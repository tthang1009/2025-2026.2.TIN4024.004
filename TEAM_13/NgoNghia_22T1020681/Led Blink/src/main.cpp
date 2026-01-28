#include <Arduino.h>

#define PIN_LED_RED     23
#define PIN_LED_GREEN   21
#define PIN_LED_YELLOW  22

// Non-blocking timer
bool IsReady(unsigned long &ulTimer, uint32_t millisecond) {
  if (millis() - ulTimer < millisecond) return false;
  ulTimer = millis();
  return true;
}

enum LedState {
  RED,
  GREEN,
  YELLOW
};

void setup() {
  printf("WELCOME IOT\n");

  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
}

void loop() {
  static LedState state = RED;

  static unsigned long stateTimer = 0;
  static unsigned long blinkTimer = 0;

  static bool ledStatus = false;

  switch (state) {

    case RED:
      if (IsReady(blinkTimer, 500)) {
        ledStatus = !ledStatus;
        digitalWrite(PIN_LED_RED, ledStatus);
        printf("LED [RED] [%s]\n", ledStatus ? "ON" : "OFF");
      }

      digitalWrite(PIN_LED_GREEN, LOW);
      digitalWrite(PIN_LED_YELLOW, LOW);

      if (IsReady(stateTimer, 5000)) {
        state = GREEN;
        ledStatus = false;
        printf("RED -> GREEN\n");
      }
      break;

    case GREEN:
      if (IsReady(blinkTimer, 500)) {
        ledStatus = !ledStatus;
        digitalWrite(PIN_LED_GREEN, ledStatus);
        printf("LED [GREEN] [%s]\n", ledStatus ? "ON" : "OFF");
      }

      digitalWrite(PIN_LED_RED, LOW);
      digitalWrite(PIN_LED_YELLOW, LOW);

      if (IsReady(stateTimer, 7000)) {
        state = YELLOW;
        ledStatus = false;
        printf("GREEN -> YELLOW\n");
      }
      break;

    case YELLOW:
      if (IsReady(blinkTimer, 300)) {
        ledStatus = !ledStatus;
        digitalWrite(PIN_LED_YELLOW, ledStatus);
        printf("LED [YELLOW] [%s]\n", ledStatus ? "ON" : "OFF");
      }

      digitalWrite(PIN_LED_RED, LOW);
      digitalWrite(PIN_LED_GREEN, LOW);

      if (IsReady(stateTimer, 3000)) {
        state = RED;
        ledStatus = false;
        printf("YELLOW -> RED\n");
      }
      break;
  }
}
