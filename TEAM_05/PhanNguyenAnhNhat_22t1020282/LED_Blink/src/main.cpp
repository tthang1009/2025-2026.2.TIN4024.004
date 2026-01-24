#include <Arduino.h>
// Định nghĩa các chân LED và các tham số
// 1. Chân LED và số lần nháy tương ứng
const int ledPins[] = {33, 25, 32}; 
const String ledNames[] = {"YELLOW", "RED   ", "GREEN "}; 
const int blinkCounts[] = {3, 5, 7}; 

// 2. Cấu hình tốc độ: 0.5 giây = 500ms
const long interval = 500; 

// Các biến trạng thái
int currentLedIndex = 0;    
int currentBlinkCount = 0;  
bool isLedOn = false;       
unsigned long previousMillis = 0;
bool isNewSequence = true; // Cờ để kiểm soát việc in log

// Hàm mẫu có sẵn
int myFunction(int, int);

void setup() {
  Serial.begin(115200);
  printf("Welcome IOT\n"); // Giữ nguyên header

  // Cấu hình Output
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); 
  }
}

void loop() {
  unsigned long currentMillis = millis();

  // IN LOG: Chỉ in 1 lần ngay khi bắt đầu chuyển sang màu đèn mới
  if (isNewSequence) {
    // Sử dụng Serial.printf để định dạng chuỗi giống hệt trong ảnh
    Serial.printf("LED [%s] ON => %d Seconds\n", ledNames[currentLedIndex].c_str(), blinkCounts[currentLedIndex]);
    isNewSequence = false; // Đã in xong, tắt cờ
  }

  // LOGIC NHẤP NHÁY (Non-blocking)
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; 

    if (!isLedOn) {
      // Bật đèn
      digitalWrite(ledPins[currentLedIndex], HIGH);
      isLedOn = true;
    } else {
      // Tắt đèn -> Tính là hoàn thành 1 lần nháy
      digitalWrite(ledPins[currentLedIndex], LOW);
      isLedOn = false;
      currentBlinkCount++;
      
      // Kiểm tra xem đã đủ số lần nháy của đèn hiện tại chưa
      if (currentBlinkCount >= blinkCounts[currentLedIndex]) {
        currentBlinkCount = 0;      // Reset đếm
        currentLedIndex++;          // Chuyển sang đèn kế tiếp trong mảng
        isNewSequence = true;       // Bật cờ để in log cho đèn mới
        
        // Nếu đã hết đèn cuối cùng (index 2) thì quay lại đèn đầu tiên (index 0)
        if (currentLedIndex > 2) {
          currentLedIndex = 0;
        }
      }
    }
  }
}

int myFunction(int x, int y) {
  return x + y;
}