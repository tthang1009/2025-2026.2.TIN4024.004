#include <Arduino.h>
#include <TM1637Display.h>

#define PIN_LED_RED     25
#define PIN_LED_YELLOW  32
#define PIN_LED_GREEN   33
#define PIN_LED_BLUE    21 
#define PIN_BUTTON      23 
#define CLK             18
#define DIO             19

#define TIME_RED        10000
#define TIME_YELLOW     3000
#define TIME_GREEN      7000
#define BLINK_INTERVAL  500  

enum TrafficState { RED, GREEN, YELLOW };
TrafficState currentState = RED;

unsigned long stateTimer = 0;
unsigned long blinkTimer = 0;
unsigned long displayTimer = 0;
bool isPedestrianWaiting = false;
bool ledStatus = false;
bool lastButtonState = HIGH;

TM1637Display display(CLK, DIO);

void allOff() {
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_LED_GREEN, LOW);
}

void setup() {
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  display.setBrightness(0x0f);
  display.clear();
  stateTimer = millis();
  blinkTimer = millis();
}

void loop() {
  unsigned long now = millis();
  
  bool currentButtonState = digitalRead(PIN_BUTTON);
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    isPedestrianWaiting = !isPedestrianWaiting;
    if (!isPedestrianWaiting) {
      display.clear();
      digitalWrite(PIN_LED_BLUE, LOW);
    }
    delay(50);
  }
  lastButtonState = currentButtonState;

  if (now - blinkTimer >= BLINK_INTERVAL) {
    blinkTimer = now;
    ledStatus = !ledStatus;

    allOff();
    if (currentState == RED) digitalWrite(PIN_LED_RED, ledStatus);
    else if (currentState == GREEN) digitalWrite(PIN_LED_GREEN, ledStatus);
    else if (currentState == YELLOW) digitalWrite(PIN_LED_YELLOW, ledStatus);

    if (isPedestrianWaiting) digitalWrite(PIN_LED_BLUE, ledStatus);
    else digitalWrite(PIN_LED_BLUE, LOW);
  }

  unsigned long elapsed = now - stateTimer;
  unsigned long currentMaxTime = (currentState == RED) ? TIME_RED : (currentState == GREEN ? TIME_GREEN : TIME_YELLOW);

  if (elapsed >= currentMaxTime) {
    stateTimer = now;
    if (currentState == RED) currentState = GREEN;
    else if (currentState == GREEN) currentState = YELLOW;
    else if (currentState == YELLOW) currentState = RED;
  }

  if (isPedestrianWaiting) {
    if (now - displayTimer >= 250) {
      displayTimer = now;
      int remaining = (currentMaxTime - elapsed) / 1000;
      if (remaining < 0) remaining = 0;
      display.showNumberDec(remaining);
    }
  }
}