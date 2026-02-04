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
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// Cấu hình OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
// Khởi tạo OLED với SDA=13, SCL=12 theo diagram.json của bạn
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Cấu hình DHT22
#define DHTPIN 16
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Định nghĩa chân LED theo sơ đồ
#define LED_RED 4
#define LED_YELLOW 2
#define LED_GREEN 15 // Chân led3 (Cyan) dùng làm Green báo hiệu Cold

void setup()
{
  Serial.begin(115200);

  // Cấu hình chân LED
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  // Khởi tạo I2C tùy chỉnh cho OLED (SDA=13, SCL=12)
  Wire.begin(13, 12);

  // Khởi tạo DHT
  dht.begin();

  // Khởi tạo OLED (Địa chỉ 0x3C)
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
  display.println("He thong dang khoi dong...");
  display.display();
  delay(2000);
}

void loop()
{
  // Đọc dữ liệu từ DHT22
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

  // Logic phân loại ngưỡng nhiệt độ
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

  // Hiển thị lên OLED
  display.clearDisplay();

  // Hiển thị Nhiệt độ
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print(t, 1);
  display.print(" C");

  // Hiển thị trạng thái và Icon
  display.setTextSize(1);
  display.setCursor(75, 15);
  display.print(status);

  // Hiển thị Độ ẩm
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(h, 1);
  display.print(" %");

  display.display();

  // Xử lý nhấp nháy LED (trong vòng 2 giây lấy mẫu)
  // Tắt tất cả LED trước
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);

  // Nhấp nháy LED tương ứng 2 lần trong 2 giây
  for (int j = 0; j < 2; j++)
  {
    digitalWrite(activeLED, HIGH);
    delay(500);
    digitalWrite(activeLED, LOW);
    delay(500);
  }
}