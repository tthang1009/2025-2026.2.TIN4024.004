#include <Arduino.h>

#define RED_LED 25
#define YELLOW_LED 33
#define GREEN_LED 32

void setup()
{
  Serial.begin(115200);
  delay(500);

  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop()
{
  // RED
  Serial.println("LED [RED  ] ON => 5 Seconds");
  digitalWrite(RED_LED, HIGH);
  delay(5000);
  digitalWrite(RED_LED, LOW);

  // YELLOW
  Serial.println("LED [YELLOW] ON => 3 Seconds");
  digitalWrite(YELLOW_LED, HIGH);
  delay(3000);
  digitalWrite(YELLOW_LED, LOW);

  // GREEN
  Serial.println("LED [GREEN ] ON => 7 Seconds");
  digitalWrite(GREEN_LED, HIGH);
  delay(7000);
  digitalWrite(GREEN_LED, LOW);
}