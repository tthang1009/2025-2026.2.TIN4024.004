/*
THÔNG TIN NHÓM 04
1. Nguyễn Thành Doanh
2. Lê Ngọc Minh
3. Hồ Ngọc Phúc Thăng
4. Võ Hữu Lộc
5. Nguyễn Bá Quý Đạt
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 16
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define LED_RED 4
#define LED_YELLOW 2
#define LED_GREEN 15

void setup()
{
  Serial.begin(115200);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  Wire.begin(13, 12);

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("He thong dang khoi dong..");
  display.display();
  delay(2000);
}

void loop()
{
 
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Loi doc cam bien DHT!"));
    return;
  }

  String status = "";
  String icon = "";
  int activeLED = -1;

  
  if (t < 13)
  {
    status = "TOO COLD";
    icon = "  COLD  ";
    activeLED = LED_GREEN;
  }
  else if (t >= 13 && t < 20)
  {
    status = "COLD";
    icon = "  RAIN  ";
    activeLED = LED_GREEN;
  }
  else if (t >= 20 && t < 25)
  {
    status = "COOL";
    icon = " CLOUD  ";
    activeLED = LED_YELLOW;
  }
  else if (t >= 25 && t < 30)
  {
    status = "WARM";
    icon = "  SUN   ";
    activeLED = LED_YELLOW;
  }
  else if (t >= 30 && t <= 35)
  {
    status = "HOT";
    icon = " HOT SUN";
    activeLED = LED_RED;
  }
  else
  {
    status = "TOO HOT";
    icon = "  FIRE  ";
    activeLED = LED_RED;
  }


  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print(t, 1);
  display.print(" C");
  display.setTextSize(1);
  display.setCursor(75, 15);
  display.print(status);
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(h, 1);
  display.print(" %");
  display.display();

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);

  for (int j = 0; j < 2; j++)
  {
    digitalWrite(activeLED, HIGH);
    delay(500);
    digitalWrite(activeLED, LOW);
    delay(500);
  }
}