#include <Arduino.h>

#define GREEN_PIN  32
#define YELLOW_PIN 33
#define RED_PIN    25

void setup() {
  // Initialize the pins as outputs
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("Traffic Light Sequence Started");
}

void loop() {
  // --- Phase 1: GO (Green) ---
  Serial.println("Light is GREEN");
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
  delay(5000); 

  // --- Phase 1.5: GO (Green Blinking) ---
  Serial.println("Light is GREEN (Blinking)");
  // Blink 3 times
  for (int i = 0; i < 3; i++) {
    digitalWrite(GREEN_PIN, LOW);  // Off
    delay(550);
    digitalWrite(GREEN_PIN, HIGH); // On
    delay(550);
  }

  // --- Phase 2: CAUTION (Yellow) ---
  Serial.println("Light is YELLOW");
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, HIGH);
  digitalWrite(RED_PIN, LOW);
  delay(2000); 

  // --- Phase 3: STOP (Red) ---
  Serial.println("Light is RED");
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, HIGH);
  delay(7000); 

  // --- Phase 3.5: STOP (Red Blinking) ---
  Serial.println("Light is RED (Blinking)");
  // Blink 3 times
  for (int i = 0; i < 3; i++) {
    digitalWrite(RED_PIN, LOW);  // Off
    delay(550);
    digitalWrite(RED_PIN, HIGH); // On
    delay(550);
  }
}