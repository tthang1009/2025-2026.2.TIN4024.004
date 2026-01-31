#include <Arduino.h>
#include <TM1637Display.h>

#define LED_RED     27
#define LED_YELLOW  26
#define LED_GREEN   25
#define LED_BLUE    21

#define CLK 18
#define DIO 19
TM1637Display display(CLK, DIO);

#define BUTTON_PIN 23

volatile bool displayEnabled = true;
volatile bool buttonEvent = false;
volatile unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 200;

void IRAM_ATTR handleButton() {
  unsigned long now = millis();
  if (now - lastInterruptTime > debounceDelay) {
    displayEnabled = !displayEnabled;
    buttonEvent = true;
    lastInterruptTime = now;
  }
}

void blinkLed(int pin, int times, const char* name) {

  Serial.print("LED[");
  Serial.print(name);
  Serial.print("] ON => ");
  Serial.print(times);
  Serial.println(" seconds");

  for (int i = times; i >= 0; i--) {

    Serial.print("[");
    Serial.print(name);
    Serial.print("] => ");
    Serial.print(i);
    Serial.println(" seconds");

    if (displayEnabled) {
      display.showNumberDec(i, true);
      digitalWrite(LED_BLUE, HIGH);
    } else {
      display.clear();
      digitalWrite(LED_BLUE, LOW);
    }

    if (i > 0) {
      digitalWrite(pin, HIGH);
      delay(500);
      digitalWrite(pin, LOW);
      delay(500);
    } else {
      delay(1000);
    }
  }

  display.clear();
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  display.setBrightness(0x0f);
  display.clear();

  attachInterrupt(
    digitalPinToInterrupt(BUTTON_PIN),
    handleButton,
    FALLING
  );

  digitalWrite(LED_BLUE, HIGH);

  Serial.println("SYSTEM READY");
  Serial.println("DISPLAY: ON");
}

void loop() {

  if (buttonEvent) {
    if (displayEnabled) {
      Serial.println("DISPLAY: ON");
    } else {
      Serial.println("DISPLAY: OFF");
    }
    buttonEvent = false;
  }

  blinkLed(LED_RED, 5, "RED");
  delay(1000);

  blinkLed(LED_YELLOW, 3, "YELLOW");
  delay(1000);

  blinkLed(LED_GREEN, 7, "GREEN");
  delay(2000);
}