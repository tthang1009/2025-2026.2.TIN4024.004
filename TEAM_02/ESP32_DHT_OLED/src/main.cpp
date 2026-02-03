/*
THÔNG TIN NHÓM 2
1. Trần Hữu Tôn Hoàng Gia
2. Lê Thành Huy
*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ================= OLED =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ================= PIN ==================
#define DHTPIN 16

#define LED_GREEN  15
#define LED_YELLOW 2
#define LED_RED    4

// ================= BLINK =================
unsigned long previousMillis = 0;
bool ledState = false;
const int blinkInterval = 400;

// ========================================
// ====== ĐỌC DHT22 KHÔNG THƯ VIỆN =========
// ========================================
bool readDHT(float &temp, float &hum)
{
  uint8_t data[5] = {0};

  pinMode(DHTPIN, OUTPUT);
  digitalWrite(DHTPIN, LOW);
  delay(2);
  digitalWrite(DHTPIN, HIGH);
  delayMicroseconds(30);
  pinMode(DHTPIN, INPUT_PULLUP);

  if (!pulseIn(DHTPIN, LOW, 100)) return false;
  if (!pulseIn(DHTPIN, HIGH, 100)) return false;

  for (int i = 0; i < 40; i++)
  {
    pulseIn(DHTPIN, LOW);
    long t = pulseIn(DHTPIN, HIGH);

    data[i/8] <<= 1;
    if (t > 40) data[i/8] |= 1;
  }

  if ((data[0]+data[1]+data[2]+data[3]) != data[4])
    return false;

  hum  = ((data[0] << 8) | data[1]) * 0.1;
  temp = ((data[2] << 8) | data[3]) * 0.1;

  return true;
}

// ========================================
void blinkLed(int pin)
{
  if (millis() - previousMillis >= blinkInterval)
  {
    previousMillis = millis();
    ledState = !ledState;

    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);

    digitalWrite(pin, ledState);
  }
}
// ========================================

void setup()
{
  Serial.begin(115200);

  // 🔥 BẮT BUỘC vì bạn dùng 13/12
  Wire.begin(13, 12);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

// ========================================

void loop()
{
  float temp, hum;

  if (!readDHT(temp, hum)) return;

  String status;
  int ledPin;

  // ===== BẢNG NGƯỠNG =====
  if (temp < 13) {
    status = "TOO COLD";
    ledPin = LED_GREEN;
  }
  else if (temp < 20) {
    status = "COLD";
    ledPin = LED_GREEN;
  }
  else if (temp < 25) {
    status = "COOL";
    ledPin = LED_YELLOW;
  }
  else if (temp < 30) {
    status = "WARM";
    ledPin = LED_YELLOW;
  }
  else if (temp < 35) {
    status = "HOT";
    ledPin = LED_RED;
  }
  else {
    status = "TOO HOT";
    ledPin = LED_RED;
  }

  blinkLed(ledPin);

  // ============ OLED ============
  display.clearDisplay();

  display.setTextColor(WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temp);
  display.println(" C");

  display.setCursor(0, 16);
  display.print("Hum : ");
  display.print(hum);
  display.println(" %");

  display.setTextSize(2);
  display.setCursor(0, 36);
  display.println(status);

  display.display();

  delay(200);
}

