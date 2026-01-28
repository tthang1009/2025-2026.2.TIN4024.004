#include <Arduino.h>
#include <TM1637Display.h>

// LED giao thông
#define LED_GREEN   25
#define LED_YELLOW  26
#define LED_RED     27

// LED xanh dương + nút
#define LED_BLUE    21
#define BUTTON_PIN  23

// LDR
#define LDR_PIN     13

// TM1637
#define CLK_PIN     18
#define DIO_PIN     19

TM1637Display display(CLK_PIN, DIO_PIN);

// LED xanh dương mắc ngược → LOW = ON
bool blueLedState = false;

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  pinMode(LED_BLUE, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // LED xanh dương tắt ban đầu
  digitalWrite(LED_BLUE, HIGH);

  display.setBrightness(7);
  display.showNumberDec(0, true);

  Serial.begin(115200);
}

void loop() {
  int lightValue = analogRead(LDR_PIN);

  // Hiển thị LDR
  display.showNumberDec(lightValue, true);

  // LED giao thông theo ánh sáng
  if (lightValue < 1500) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
  } else if (lightValue < 3000) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
  } else {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
  }

  // ===== XỬ LÝ NÚT BẤM (ỔN ĐỊNH) =====
  if (digitalRead(BUTTON_PIN) == LOW) {
    blueLedState = !blueLedState;
    digitalWrite(LED_BLUE, blueLedState ? LOW : HIGH);

    Serial.println("Button pressed");

    // CHỜ NHẢ NÚT
    while (digitalRead(BUTTON_PIN) == LOW) {
      delay(10);
    }

    delay(200); // chống dội
  }

  delay(100);
}
