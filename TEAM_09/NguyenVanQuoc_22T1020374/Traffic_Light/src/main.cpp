#include <Arduino.h>
#include <TM1637Display.h>

// --- KHAI BÁO CHÂN (GPIO) ---
// Hãy kiểm tra lại diagram.json nếu chân nối khác
#define PIN_CLK 13        // Chân CLK của màn hình
#define PIN_DIO 12        // Chân DIO của màn hình

#define PIN_RED 27        // Đèn Đỏ
#define PIN_YELLOW 26     // Đèn Vàng
#define PIN_GREEN 25      // Đèn Xanh

#define PIN_BTN 33        // Nút bấm (dây xanh lá/dương nối vào đây)
#define PIN_POT 34        // Biến trở (chân giữa nối vào đây)
#define PIN_BLUE_LED 2    // Đèn LED xanh dương (hoặc LED tích hợp trên board)

// --- CẤU HÌNH THỜI GIAN (mặc định) ---
int redTime = 5;
int yellowTime = 2;
int greenTime = 5;

// Khởi tạo đối tượng màn hình
TM1637Display display(PIN_CLK, PIN_DIO);

// Biến trạng thái
enum TrafficState { RED, GREEN, YELLOW };
TrafficState currentState = RED;
int counter = redTime;
unsigned long lastMillis = 0;
bool blueLedState = false;

void setup() {
  Serial.begin(115200);
  
  // Cấu hình chân đèn
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE_LED, OUTPUT);
  
  // Cấu hình nút bấm (INPUT_PULLUP nếu không có điện trở ngoài, 
  // nhưng trong hình Wokwi thường cần INPUT nếu nối VCC/GND cụ thể)
  pinMode(PIN_BTN, INPUT_PULLUP); 

  // Cấu hình độ sáng màn hình (0-7)
  display.setBrightness(5);
  
  Serial.println("HE THONG DEN GIAO THONG KHOI DONG...");
}

void loop() {
  // 1. ĐỌC BIẾN TRỞ ĐỂ CHỈNH TỐC ĐỘ
  // Đọc giá trị analog (0-4095)
  int potValue = analogRead(PIN_POT); 
  // Map ra tốc độ delay (từ 200ms đến 1500ms cho 1 giây đếm)
  int tickSpeed = map(potValue, 0, 4095, 200, 1500);

  // 2. XỬ LÝ NÚT BẤM (BẬT/TẮT ĐÈN XANH DƯƠNG)
  if (digitalRead(PIN_BTN) == LOW) { // Giả sử nút nối xuống đất khi nhấn
    delay(50); // Chống rung phím
    if (digitalRead(PIN_BTN) == LOW) {
      blueLedState = !blueLedState;
      digitalWrite(PIN_BLUE_LED, blueLedState ? HIGH : LOW);
      Serial.println(blueLedState ? "PEDESTRIAN MODE: ON" : "PEDESTRIAN MODE: OFF");
      while(digitalRead(PIN_BTN) == LOW); // Chờ thả nút
    }
  }

  // 3. LOGIC ĐÈN GIAO THÔNG (KHÔNG DÙNG DELAY CHẶN)
  if (millis() - lastMillis >= tickSpeed) {
    lastMillis = millis();
    
    // Hiển thị đếm ngược lên màn hình 7 thanh
    display.showNumberDec(counter, true); // true = hiển thị số 0 đằng trước
    Serial.printf("State: %d | Time: %d \n", currentState, counter);

    counter--;

    if (counter < 0) {
      // Chuyển trạng thái đèn
      switch (currentState) {
        case RED:
          currentState = GREEN;
          counter = greenTime;
          digitalWrite(PIN_RED, LOW);
          digitalWrite(PIN_GREEN, HIGH);
          break;
        case GREEN:
          currentState = YELLOW;
          counter = yellowTime;
          digitalWrite(PIN_GREEN, LOW);
          digitalWrite(PIN_YELLOW, HIGH);
          break;
        case YELLOW:
          currentState = RED;
          counter = redTime;
          digitalWrite(PIN_YELLOW, LOW);
          digitalWrite(PIN_RED, HIGH);
          break;
      }
    }
  }
}