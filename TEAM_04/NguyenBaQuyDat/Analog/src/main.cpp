#include <TM1637Display.h>
#include <esp32-hal.h>
#include <HardwareSerial.h>

// Pins
#define CLK 15
#define DIO 2
#define RED_LED 25
#define YELLOW_LED 33
#define GREEN_LED 32
#define LDR_PIN 34

TM1637Display display(CLK, DIO);

const float GAMMA = 0.7;
const float RL10 = 50;

void setup()
{
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  display.setBrightness(0x0f);
}

float getLux()
{
  int analogValue = analogRead(LDR_PIN);
  // ESP32 ADC is 12-bit (4096) and 3.3V
  float voltage = analogValue / 4095. * 3.3;
  float resistance = 2000 * voltage / (1 - voltage / 3.3);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
  return lux;
}

void nightMode()
{
  digitalWrite(RED_LED, LOW);
  delay(500);
  digitalWrite(GREEN_LED, LOW);
  delay(500);
  // Nhấp nháy đèn vàng
  digitalWrite(YELLOW_LED, HIGH);
  delay(500);
  digitalWrite(YELLOW_LED, LOW);
  delay(500);
  display.showNumberDec(0); // Hiển thị số 0 hoặc thông báo đêm
}

void dayMode()
{
  // Chu kỳ đèn giao thông đơn giản
  // Đỏ
  digitalWrite(RED_LED, HIGH);
  for (int i = 5; i > 0; i--)
  {
    display.showNumberDec(i);
    if (getLux() < 10)
      return; // Kiểm tra nhanh nếu trời tối đột ngột
    delay(1000);
  }
  digitalWrite(RED_LED, LOW);

  // Xanh
  digitalWrite(GREEN_LED, HIGH);
  for (int i = 5; i > 0; i--)
  {
    display.showNumberDec(i);
    if (getLux() < 10)
      return;
    delay(1000);
  }
  digitalWrite(GREEN_LED, LOW);

  // Vàng
  digitalWrite(YELLOW_LED, HIGH);
  for (int i = 3; i > 0; i--)
  {
    display.showNumberDec(i);
    if (getLux() < 10)
      return;
    delay(1000);
  }
  digitalWrite(YELLOW_LED, LOW);
}

void loop()
{
  float currentLux = getLux();
  Serial.print("Lux: ");
  Serial.println(currentLux);

  if (currentLux < 10)
  {
    nightMode();
  }
  else
  {
    dayMode();
  }
}