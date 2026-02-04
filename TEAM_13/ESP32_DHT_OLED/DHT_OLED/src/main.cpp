/*
  THÔNG TIN NHÓM 13
1. Trần Tuấn Long
2. Nguyễn Thị Huyền Trân
3. Nguyễn Thị Thùy Ngân
4.Ngô Nghĩa
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