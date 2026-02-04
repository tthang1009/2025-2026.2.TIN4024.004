/*
THÔNG TIN NHÓM 10
1. Lê Nhữ Hoàng
2. Hoàng Anh Quân
3. Trần Nguyễn Phước Kiệt
4. Huỳnh Tấn Sang
5.
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