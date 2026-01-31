#include <Arduino.h>
#include <TM1637Display.h>

// ===== LED =====
#define LED_RED     27
#define LED_YELLOW  26
#define LED_GREEN   25
#define LED_BLUE    21

// ===== TM1637 =====
#define CLK 18
#define DIO 19
TM1637Display display(CLK, DIO);

// ===== BUTTON =====
#define BUTTON_PIN 23

volatile bool displayEnabled = true;
volatile bool buttonEvent = false;
volatile unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 200;

// ===== ISR nút nhấn =====
void IRAM_ATTR handleButton() {
  unsigned long now = millis();
  if (now - lastInterruptTime > debounceDelay) {
    displayEnabled = !displayEnabled;
    buttonEvent = true;           // báo có sự kiện nút bấm
    lastInterruptTime = now;
  }
}

// ===== Blink + Countdown =====
void blinkLed(int pin, int times, const char* name) {

  // ===== THÔNG BÁO ĐÈN BẬT =====
  Serial.print("LED[");
  Serial.print(name);
  Serial.print("] ON => ");
  Serial.print(times);
  Serial.println(" seconds");

  for (int i = times; i >= 0; i--) {

    // ===== SERIAL =====
    Serial.print("[");
    Serial.print(name);
    Serial.print("] => ");
    Serial.print(i);
    Serial.println(" seconds");

    // ===== DISPLAY + LED BLUE =====
    if (displayEnabled) {
      display.showNumberDec(i, true);
      digitalWrite(LED_BLUE, HIGH);
    } else {
      display.clear();
      digitalWrite(LED_BLUE, LOW);
    }

    // ===== LED BLINK =====
    if (i > 0) {
      digitalWrite(pin, HIGH);
      delay(500);
      digitalWrite(pin, LOW);
      delay(500);
    } else {
      delay(1000); // giữ số 0
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

  // ===== HIỂN THỊ TRẠNG THÁI NÚT =====
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