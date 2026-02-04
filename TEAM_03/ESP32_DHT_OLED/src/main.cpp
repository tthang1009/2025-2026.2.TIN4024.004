 /*
THÔNG TIN NHÓM 3
1. Nguyễn Đình Tuấn
2. 
3. 
4. 
5.
*/

#include <DHT.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 16
#define DHTTYPE DHT22

#define LED_RED 4
#define LED_YELLOW 2
#define LED_GREEN 15

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

unsigned long lastDhtRead = 0;
unsigned long lastBlink = 0;

const unsigned long dhtInterval = 2000;   // đọc DHT mỗi 2s
const unsigned long blinkInterval = 500;  // LED nhấp nháy 0.5s

bool ledState = false;

float temperature = 0;
float humidity = 0;
String statusText = "";
uint8_t activeLed = 0; // 0-none, 1-green, 2-yellow, 3-red

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  Wire.begin(13, 12); // SDA, SCL (theo diagram)
  dht.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}