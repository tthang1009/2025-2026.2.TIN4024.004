#include <Arduino.h>
void setup() {
  printf("welcome to LED Blink\n");
}

void loop() {
  printf("loop running\n");
  delay(1000);
  // put your main code here, to run repeatedly:
}
//Non-blocking LED Blink
void loop(){
  static unsigned long uLastMillis = 0;
  static bool ledStatus = false;
}

