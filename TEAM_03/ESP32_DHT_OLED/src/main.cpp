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