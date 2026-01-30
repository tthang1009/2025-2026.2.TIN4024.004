#include <Arduino.h>
#include <TM1637Display.h>

// ===== PIN MAP THEO MẠCH =====
#define LED_GREEN   25
#define LED_YELLOW  26
#define LED_RED     27
#define LED_BLUE    21
#define BUTTON_PIN  23

#define CLK 18
#define DIO 19

TM1637Display display(CLK, DIO);

#define RED_TIME     4
#define YELLOW_TIME  2
#define GREEN_TIME   6

int state = 0; 
int remainSeconds = GREEN_TIME;
bool blinkState = true;

bool displayOn = false;
bool lastButton = HIGH;

unsigned long last500ms = 0;
unsigned long lastButtonRead = 0;

void setLight(int s) {
  digitalWrite(LED_GREEN, s == 0 ? blinkState : LOW);
  digitalWrite(LED_YELLOW, s == 1 ? blinkState : LOW);
  digitalWrite(LED_RED, s == 2 ? blinkState : LOW);
}

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  display.setBrightness(0x0f);
  display.clear();

  remainSeconds = GREEN_TIME;
}

void loop() {
  // ===== ĐỌC NÚT NHẤN =====
  if (millis() - lastButtonRead > 30) {
    lastButtonRead = millis();
    bool btn = digitalRead(BUTTON_PIN);

    if (btn == LOW && lastButton == HIGH) {
      displayOn = !displayOn;
      digitalWrite(LED_BLUE, displayOn);

      if (!displayOn) {
        display.clear();
      }
    }
    lastButton = btn;
  }

  // ===== NHẤP NHÁY 0.5s =====
  if (millis() - last500ms >= 500) {
    last500ms = millis();
    blinkState = !blinkState;

    static int halfCount = 0;
    halfCount++;

    if (halfCount >= 2) {
      halfCount = 0;
      remainSeconds--;

      if (remainSeconds < 0) {
        state = (state + 1) % 3;

        if (state == 0) remainSeconds = GREEN_TIME;
        if (state == 1) remainSeconds = YELLOW_TIME;
        if (state == 2) remainSeconds = RED_TIME;
      }
    }

    setLight(state);

    if (displayOn) {
      display.showNumberDec(remainSeconds, true);
    }
  }
}
