#include <Arduino.h>

// 1. Định nghĩa các chân cắm (GPIO) dựa trên diagram.json của bạn
const int RED_LED = 23;    // Đèn Đỏ nối chân 23
const int YELLOW_LED = 22; // Đèn Vàng nối chân 22
const int GREEN_LED = 21;  // Đèn Xanh nối chân 21

void setup() {
  // Khởi tạo Serial để theo dõi trên màn hình máy tính
  Serial.begin(115200);

  // Cấu hình các chân LED là đầu ra (OUTPUT)
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  Serial.println("He thong den giao thong dang khoi dong...");
}

void loop() {
  // --- CHU KỲ ĐÈN GIAO THÔNG ---

  // 1. ĐÈN ĐỎ SÁNG (Dừng lại)
  Serial.println("Trang thai: DEN DO - Dung lai (3s)");
  digitalWrite(RED_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  delay(3000); // Chờ 3 giây

  // 2. ĐÈN XANH SÁNG (Được đi)
  Serial.println("Trang thai: DEN XANH - Duoc di (5s)");
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  delay(5000); // Chờ 5 giây

  // 3. ĐÈN VÀNG SÁNG (Chậm lại/Chuẩn bị dừng)
  Serial.println("Trang thai: DEN VANG - Cham lai (2s)");
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  delay(2000); // Chờ 2 giây (Thực tế đèn vàng thường ngắn hơn)
}