#include "main.h"

// Define Pins based on Wokwi diagram.json
#define PIN_LED_RED     25
#define PIN_LED_YELLOW  33
#define PIN_LED_GREEN   32

// TM1637 Connection Pins
#define CLK 15
#define DIO 2

// Interaction Pins
#define PIN_BUTTON_DISPLAY 23
#define PIN_LED_BLUE    21

// Initialize Objects
TM1637Display display(CLK, DIO);
BUTTON btnBlue;
LED ledBlue;
Traffic_Blink traffic;

// --- GLOBAL STATE ---
// Initialized to true so the system is ON by default
bool displayMode = true; 

/**
 * Handles button logic for Toggling Display Mode.
 */
void ProcessButtonPressed()
{
  static int prevSecond = -1;
  static bool lastButtonState = false; 

  // 1. Read Hardware State
  btnBlue.processPressed();
  bool currentButtonState = btnBlue.isPressed();

  // 2. Edge Detection: Check if button went from NOT PRESSED to PRESSED
  if (currentButtonState == true && lastButtonState == false)
  {
      displayMode = !displayMode; // Toggle the logical mode

      // Handle feedback (LEDs and Serial Log)
      if (displayMode) 
      {
          ledBlue.setStatus(true);
          printf("*** DISPLAY ON ***\n");
      } 
      else 
      {
          ledBlue.setStatus(false);
          display.clear(); // Clear display immediately
          printf("*** DISPLAY OFF ***\n");
      }
  }
  
  lastButtonState = currentButtonState;

  // 3. Update 7-Segment Display if Mode is Active
  if (displayMode)
  {
    int secondCount = traffic.getCount();
    
    if (prevSecond != secondCount)
    {
      prevSecond = secondCount;
      display.showNumberDec(secondCount);
    }
  }
}

void setup()
{
  Serial.begin(115200);

  // Setup Hardware
  btnBlue.setup(PIN_BUTTON_DISPLAY);
  ledBlue.setup(PIN_LED_BLUE, "BLUE");
  
  // Setup Display
  display.setBrightness(0x0a);
  display.clear();

  // Setup Traffic Logic
  traffic.setup_Pin(PIN_LED_RED, PIN_LED_YELLOW, PIN_LED_GREEN);
  traffic.setup_WaitTime(5, 3, 7); 

  // --- SET INITIAL STATE ---
  displayMode = true;        // Ensure logical state is TRUE
  ledBlue.setStatus(true);   // Turn on Blue indicator LED
  printf("*** SYSTEM STARTED: DISPLAY ON ***\n");
}

void loop()
{
  ProcessButtonPressed();

  // Run traffic blink logic
  // Pass 'displayMode' so the Serial Logger only prints when mode is ON
  traffic.blink(displayMode);
}