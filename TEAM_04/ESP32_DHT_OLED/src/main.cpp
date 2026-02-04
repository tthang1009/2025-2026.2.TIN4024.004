/*
THÔNG TIN NHÓM 04
1. Nguyễn Thành Doanh
2. Lê Ngọc Minh
3. Hồ Ngọc Phúc Thăng
4. Võ Hữu Lộc
5. Nguyễn Bá Quý Đạt
*/

#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup()
{
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop()
{
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}