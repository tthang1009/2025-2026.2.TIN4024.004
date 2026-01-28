#include <Arduino.h>
#include <TM1637Display.h>

// ===== TM1637 =====
#define CLK 18
#define DIO 19
TM1637Display display(CLK, DIO);

// ===== LED =====
#define LED_RED     27
#define LED_YELLOW  26
#define LED_GREEN   25

enum State { RED, GREEN, YELLOW };
State state;

int countdown;
unsigned long lastMillis;

void setState(State s, int timeSec) {
  state = s;
  countdown = timeSec;

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);

  if (state == RED)    digitalWrite(LED_RED, HIGH);
  if (state == GREEN)  digitalWrite(LED_GREEN, HIGH);
  if (state == YELLOW) digitalWrite(LED_YELLOW, HIGH);

  display.showNumberDec(countdown, true);
}

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  display.setBrightness(7);

  setState(RED, 5);   // Bắt đầu đèn đỏ 5s
  lastMillis = millis();
}

void loop() {
  if (millis() - lastMillis >= 1000) {
    lastMillis = millis();

    countdown--;
    display.showNumberDec(countdown, true);

    if (countdown == 0) {
      if (state == RED) {
        setState(GREEN, 7);
      }
      else if (state == GREEN) {
        setState(YELLOW, 3);
      }
      else {
        setState(RED, 5);
      }
    }
  }
}
