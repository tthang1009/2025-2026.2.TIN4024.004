#include <Arduino.h>

#define PIN_LED_RED     23
#define PIN_LED_GREEN   22
#define PIN_LED_YELLOW  21

bool IsReady(unsigned long &uTimer, uint32_t millisecond){
  if (millis() - uTimer < millisecond) return false;
  uTimer = millis();
  return true;
}

void ALLOFF(){
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Traffic LED - No Blink");

  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
}

void loop() {
  static unsigned long timerPhase = 0;
  static int phase = 0;

  ALLOFF(); // đảm bảo chỉ 1 LED sáng

  if (phase == 0) {            // 🔴 ĐỎ – 5s
    digitalWrite(PIN_LED_RED, HIGH);
    if (IsReady(timerPhase, 5000)) {
      Serial.println("RED -> GREEN");
      phase = 1;
    }
  }
  else if (phase == 1) {       // 🟢 XANH – 7s
    digitalWrite(PIN_LED_GREEN, HIGH);
    if (IsReady(timerPhase, 7000)) {
      Serial.println("GREEN -> YELLOW");
      phase = 2;
    }
  }
  else if (phase == 2) {       // 🟡 VÀNG – 3s
    digitalWrite(PIN_LED_YELLOW, HIGH);
    if (IsReady(timerPhase, 3000)) {
      Serial.println("YELLOW -> RED");
      phase = 0;
    }
  }
}
