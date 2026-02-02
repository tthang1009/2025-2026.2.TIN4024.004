/*
THÔNG TIN NHÓM 6
1. Nguyễn Hữu Trình
2. Ngô Thời Quang
3. Hồ Sỹ Vinh
4. Nguyễn Đinh Vĩnh Phú
5. Nguyễn Đăng Bảo Toàn
*/

#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}