#include <Arduino.h>

/* ====== KHAI BÁO CHÂN ====== */
#define PIN_RED     23
#define PIN_YELLOW  22
#define PIN_GREEN   21

/* ====== TRẠNG THÁI ĐÈN ====== */
enum TrafficState {
  RED,
  GREEN,
  YELLOW
};

/* ====== HÀM NON-BLOCKING ====== */
bool IsReady(unsigned long &timer, uint32_t intervalMs) {
  if (millis() - timer < intervalMs) return false;
  timer = millis();
  return true;
}

/* ====== HÀM BẬT / TẮT ĐÈN ====== */
void setLight(bool red, bool yellow, bool green) {
  digitalWrite(PIN_RED, red);
  digitalWrite(PIN_YELLOW, yellow);
  digitalWrite(PIN_GREEN, green);
}

/* ====== SETUP ====== */
void setup() {
  Serial.begin(115200);
  Serial.println("=== TRAFFIC LIGHT START ===");

  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);

  // Bắt đầu với đèn đỏ
  setLight(HIGH, LOW, LOW);
}

/* ====== LOOP ====== */
void loop() {
  static TrafficState state = RED;
  static unsigned long timer = 0;

  switch (state) {
    case RED:
      setLight(HIGH, LOW, LOW);
      if (IsReady(timer, 5000)) {   // Đỏ 5 giây
        state = GREEN;
        Serial.println("GREEN");
      }
      break;

    case GREEN:
      setLight(LOW, LOW, HIGH);
      if (IsReady(timer, 5000)) {   // Xanh 5 giây
        state = YELLOW;
        Serial.println("YELLOW");
      }
      break;

    case YELLOW:
      setLight(LOW, HIGH, LOW);
      if (IsReady(timer, 2000)) {   // Vàng 2 giây
        state = RED;
        Serial.println("RED");
      }
      break;
  }
}
