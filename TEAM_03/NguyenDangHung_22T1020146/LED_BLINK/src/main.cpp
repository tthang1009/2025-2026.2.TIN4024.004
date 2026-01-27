#include <Arduino.h>

const int ledPin = 23;
const int buttonPin = 14;

bool ledState = false;        // trạng thái LED (ban đầu tắt)
bool lastButtonState = HIGH; // vì dùng INPUT_PULLUP

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  // Phát hiện cạnh nhấn (từ HIGH -> LOW)
  if (lastButtonState == HIGH && buttonState == LOW) {
    ledState = !ledState;   // đảo trạng thái LED
    delay(200);             // chống dội nút
  }

  digitalWrite(ledPin, ledState);
  lastButtonState = buttonState;
}

