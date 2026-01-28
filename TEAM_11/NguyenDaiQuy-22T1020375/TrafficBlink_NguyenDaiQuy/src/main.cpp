#include <Arduino.h>
#include <TM1637Display.h>

// --- 1. CẤU HÌNH CHÂN ---
#define RED_LED 23
#define YELLOW_LED 22
#define GREEN_LED 21
#define STREET_LED 5    
#define BTN_PIN 27      
#define LDR_PIN 34      

#define CLK 18
#define DIO 19

TM1637Display display(CLK, DIO);

// --- 2. CÁC BIẾN QUẢN LÝ ---
enum TrafficState { STATE_RED, STATE_GREEN, STATE_YELLOW };
TrafficState currentState = STATE_RED;

// Thời gian cài đặt (ms)
const long TIME_RED = 5000;
const long TIME_GREEN = 5000;
const long TIME_YELLOW = 3000;

unsigned long previousMillis = 0; 
long currentInterval = TIME_RED;  

// Biến trạng thái
bool isDisplayOn = true;         
bool lastBtnState = HIGH;       
bool lastStreetLightState = false;

// *** BIẾN MỚI ĐỂ SỬA LỖI LAG ***
int lastShownSecond = -1; // Lưu số giây vừa hiển thị để so sánh

void setup() {
  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(STREET_LED, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LDR_PIN, INPUT);

  display.setBrightness(7);
  
  Serial.println(">>> DA FIX LOI CHAM THOI GIAN <<<");
  Serial.println("🔴 DEN DO: DUNG LAI (5s)");
  digitalWrite(RED_LED, HIGH);
}

void turnOffTrafficLeds() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}

void loop() {
  unsigned long currentMillis = millis();

  // --- NHIỆM VỤ A: ĐÈN ĐƯỜNG ---
  // (Đã tối ưu: Chỉ đọc cảm biến mỗi 200ms để đỡ lag)
  static unsigned long lastLdrCheck = 0;
  if (currentMillis - lastLdrCheck > 200) { 
    lastLdrCheck = currentMillis;
    int lightValue = analogRead(LDR_PIN);
    bool isDark = (lightValue > 2000); 

    if (isDark != lastStreetLightState) {
      if (isDark) {
        digitalWrite(STREET_LED, HIGH);
        Serial.println("🌌 TROI TOI: Bat den duong");
      } else {
        digitalWrite(STREET_LED, LOW);
        Serial.println("☀️ TROI SANG: Tat den duong");
      }
      lastStreetLightState = isDark;
    }
  }

  // --- NHIỆM VỤ B: NÚT BẤM ---
  int btnState = digitalRead(BTN_PIN);
  if (btnState == LOW && lastBtnState == HIGH) {
    isDisplayOn = !isDisplayOn; 
    
    if (isDisplayOn) {
      Serial.println("📺 MAN HINH: ON");
      lastShownSecond = -1; // Reset để cập nhật lại ngay
    } else {
      display.clear(); 
      Serial.println("📴 MAN HINH: OFF");
    }
    delay(50); 
  }
  lastBtnState = btnState;

  // --- NHIỆM VỤ C: ĐÈN GIAO THÔNG ---
  unsigned long timePassed = currentMillis - previousMillis;
  long remainingSeconds = (currentInterval - timePassed) / 1000;
  if (remainingSeconds < 0) remainingSeconds = 0;
  
  // *** KEY FIX: CHỈ CẬP NHẬT MÀN HÌNH KHI SỐ THAY ĐỔI ***
  if (isDisplayOn) {
    if (remainingSeconds != lastShownSecond) {
      display.showNumberDec(remainingSeconds);
      lastShownSecond = remainingSeconds; // Lưu lại số vừa hiện
    }
  }

  // Kiểm tra chuyển đèn
  if (timePassed >= currentInterval) {
    previousMillis = currentMillis;
    turnOffTrafficLeds();
    lastShownSecond = -1; // Reset số hiển thị khi chuyển đèn

    switch (currentState) {
      case STATE_RED:
        currentState = STATE_GREEN;
        digitalWrite(GREEN_LED, HIGH);
        currentInterval = TIME_GREEN;
        Serial.println("🟢 DEN XANH (5s)");
        break;

      case STATE_GREEN:
        currentState = STATE_YELLOW;
        digitalWrite(YELLOW_LED, HIGH);
        currentInterval = TIME_YELLOW;
        Serial.println("🟡 DEN VANG (3s)");
        break;

      case STATE_YELLOW:
        currentState = STATE_RED;
        digitalWrite(RED_LED, HIGH);
        currentInterval = TIME_RED;
        Serial.println("🔴 DEN DO (5s)");
        break;
    }
  }
}