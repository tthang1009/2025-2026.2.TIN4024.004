#include <Arduino.h>

#define PIN_LED_RED     25
#define PIN_LED_YELLOW  32
#define PIN_LED_GREEN   33


#define TIME_RED     10000
#define TIME_YELLOW  3000
#define TIME_GREEN   7000

enum TrafficState {
  RED,
  YELLOW,
  GREEN
};

TrafficState currentState = RED;
unsigned long lastTime = 0;

void setLights(bool red, bool yellow, bool green) {
  digitalWrite(PIN_LED_RED, red);
  digitalWrite(PIN_LED_YELLOW, yellow);
  digitalWrite(PIN_LED_GREEN, green);
}

void setup() {
  Serial.begin(115200);
  Serial.println("TRAFFIC LIGHT START");

  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);

  setLights(HIGH, LOW, LOW); 
  lastTime = millis();
}

void loop() {
  unsigned long now = millis();

  switch (currentState) {

    case RED:
      if (now - lastTime >= TIME_RED) {
        currentState = GREEN;
        lastTime = now;
        setLights(LOW, LOW, HIGH);
        Serial.println("GREEN ON");
      }
      break;

    case GREEN:
      if (now - lastTime >= TIME_GREEN) {
        currentState = YELLOW;
        lastTime = now;
        setLights(LOW, HIGH, LOW);
        Serial.println("YELLOW ON");
      }
      break;

    case YELLOW:
      if (now - lastTime >= TIME_YELLOW) {
        currentState = RED;
        lastTime = now;
        setLights(HIGH, LOW, LOW);
        Serial.println("RED ON");
      }
      break;
  }
}
