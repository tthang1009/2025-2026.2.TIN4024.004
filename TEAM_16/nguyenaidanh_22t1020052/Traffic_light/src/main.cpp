#include <TM1637Display.h>

// ====== CHÂN KẾT NỐI ======
#define CLK 2
#define DIO 3

#define GREEN_PIN 8
#define YELLOW_PIN 9
#define RED_PIN 10

#define BUTTON_PIN 7   // nút bật/tắt hệ thống
#define LDR_PIN A0     // cảm biến ngày/đêm

TM1637Display display(CLK, DIO);

// ====== BIẾN HỆ THỐNG ======
bool systemOn = true;
bool isNight = false;
bool lastNight = false;

int state = 0;     // 0: xanh, 1: vàng, 2: đỏ
int timer = 7;

unsigned long lastTick = 0;

// ====== SETUP ======
void setup() {
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  display.setBrightness(7);
  display.clear();
}

// ====== LOOP ======
void loop() {
  // Đọc nút bật/tắt
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(200);
    systemOn = !systemOn;
    display.clear();
  }

  // Xác định ngày / đêm
  int lightValue = analogRead(LDR_PIN);
  isNight = lightValue < 500;   // chỉnh nếu cần

  // Reset khi đổi ngày ↔ đêm
  if (isNight != lastNight) {
    state = 0;
    timer = 7;
    lastTick = millis();
    display.clear();
  }
  lastNight = isNight;

  if (!systemOn) {
    allOff();
    return;
  }

  if (isNight) {
    handleNightMode();
  } else {
    handleDayMode();
  }
}

// ====== CHẾ ĐỘ BAN NGÀY ======
void handleDayMode() {
  if (millis() - lastTick >= 1000) {
    lastTick = millis();
    timer--;

    if (timer <= 0) {
      state = (state + 1) % 3;
      if (state == 0) timer = 7;
      else if (state == 1) timer = 3;
      else timer = 10;
    }

    digitalWrite(GREEN_PIN, state == 0);
    digitalWrite(YELLOW_PIN, state == 1);
    digitalWrite(RED_PIN, state == 2);

    // Hiển thị 2 số bên phải
    display.showNumberDec(timer, false, 2, 2);

    // Xóa 2 số bên trái
    uint8_t blank[] = {0, 0};
    display.setSegments(blank, 2, 0);
  }
}

// ====== CHẾ ĐỘ BAN ĐÊM ======
void handleNightMode() {
  static unsigned long lastBlink = 0;
  static bool yellowState = LOW;

  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(RED_PIN, LOW);

  if (millis() - lastBlink >= 500) {
    lastBlink = millis();
    yellowState = !yellowState;
    digitalWrite(YELLOW_PIN, yellowState);
  }

  // Hiện -- bên phải
  const uint8_t dash[] = {0x40, 0x40};
  display.setSegments(dash, 2, 2);

  uint8_t blank[] = {0, 0};
  display.setSegments(blank, 2, 0);
}

// ====== TẮT TẤT CẢ ======
void allOff() {
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
}
