#include <Arduino.h>

#define PIN_LED_RED     25
#define PIN_LED_YELLOW  32
#define PIN_LED_GREEN   33

#define TIME_RED     10000
#define TIME_YELLOW  3000
#define TIME_GREEN   7000

#define BLINK_TIME   500   

enum TrafficState {
  RED,
  GREEN,
  YELLOW
};

TrafficState currentState = RED;

unsigned long stateTimer = 0;
unsigned long blinkTimer = 0;
bool ledStatus = false;

void allOff() {
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_LED_GREEN, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);

  stateTimer = millis();
  blinkTimer = millis();
}

void loop() {
  unsigned long now = millis();

  
  if (now - blinkTimer >= BLINK_TIME) {
    blinkTimer = now;
    ledStatus = !ledStatus;

    allOff();

    if (currentState == RED)
      digitalWrite(PIN_LED_RED, ledStatus);

    else if (currentState == GREEN)
      digitalWrite(PIN_LED_GREEN, ledStatus);

    else if (currentState == YELLOW)
      digitalWrite(PIN_LED_YELLOW, ledStatus);
  }
  switch (currentState) {

    case RED:
      if (now - stateTimer >= TIME_RED) {
        currentState = GREEN;
        stateTimer = now;
        Serial.println("CHANGE TO GREEN");
      }
      break;

    case GREEN:
      if (now - stateTimer >= TIME_GREEN) {
        currentState = YELLOW;
        stateTimer = now;
        Serial.println("CHANGE TO YELLOW");
      }
      break;

    case YELLOW:
      if (now - stateTimer >= TIME_YELLOW) {
        currentState = RED;
        stateTimer = now;
        Serial.println("CHANGE TO RED");
      }
      break;
  }
}
