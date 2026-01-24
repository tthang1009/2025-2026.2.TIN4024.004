#include <Arduino.h>

// Pin Definitions
#define GREEN_PIN  32
#define YELLOW_PIN 33
#define RED_PIN    25

// Timing Definitions (in milliseconds)
#define RED_TIME    8000
#define YELLOW_TIME 3000
#define GREEN_TIME  7000 

void setup() {
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  
  // Initialize Serial at the standard ESP32 speed
  Serial.begin(115200);
}

void loop() {
  // --- Phase 1: GREEN (7 Seconds total) ---
  Serial.println("LED [GREEN] ON => 7 Seconds");
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
  
  delay(5000); // Solid for 5 seconds
  
  // Blink for the remaining 2 seconds (4 cycles of 450ms ON/450ms OFF)
  Serial.println("LED [GREEN] is blinking...");
  for (int i = 0; i < 4; i++) {
    digitalWrite(GREEN_PIN, LOW);
    delay(450);
    digitalWrite(GREEN_PIN, HIGH);
    delay(450);
  }

  // --- Phase 2: YELLOW ---
  Serial.println("LED [YELLOW] ON => 3 Seconds");
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, HIGH);
  digitalWrite(RED_PIN, LOW);
  delay(YELLOW_TIME);

  // --- Phase 3: RED ---
  Serial.println("LED [RED] ON => 8 Seconds");
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, HIGH);

  delay(6000); // Solid for 6 seconds

  // Blink for the remaining 2 seconds (4 cycles of 450ms ON/450ms OFF)
  Serial.println("LED [RED] is blinking...");
  for (int i = 0; i < 4; i++) {
    digitalWrite(RED_PIN, LOW);
    delay(450);
    digitalWrite(RED_PIN, HIGH);
    delay(450);
  }
}