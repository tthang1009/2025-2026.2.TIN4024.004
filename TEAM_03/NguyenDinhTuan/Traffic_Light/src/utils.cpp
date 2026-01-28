#include "utils.h"

//----- class BUTTON --------------------
BUTTON::BUTTON()
{
    _pin = -1;
    _prevValue = HIGH; // Default HIGH because we use PullUp
}
BUTTON::~BUTTON()
{
}
void BUTTON::setup(int pin)
{
    _pin = pin;
    _prevValue = HIGH;
    // Diagram connects button to GND, so we need Internal Pullup
    pinMode(_pin, INPUT_PULLUP); 
}

void BUTTON::processPressed()
{
    static unsigned long ulTimer = 0;

    // Debounce check (10ms)
    if (!IsReady(ulTimer, 10))
        return;

    int newValue = digitalRead(_pin);
    if (newValue == _prevValue)
        return;
    _prevValue = newValue;
}

bool BUTTON::isPressed()
{
    // Diagram connects to GND, so LOW means Pressed
    return (_prevValue == LOW);
}

//----- class LED --------------------
LED::LED()
{
    _pin = -1;
    _name = "UNKNOWN";
    _status = false;
}
LED::~LED() {}

const char *LED::getName()
{
    return _name.c_str();
}

void LED::setup(int pin, const char *name)
{
    _pin = pin;
    if (name && name[0] != 0)
        _name = name;

    _status = false;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void LED::setStatus(bool bON)
{
    _status = bON;
    digitalWrite(_pin, bON ? HIGH : LOW);
}

void LED::blink()
{
    static unsigned long ulTimer = 0;
    if (!IsReady(ulTimer, 500))
        return;
    _status = !_status;
    digitalWrite(_pin, _status ? HIGH : LOW);
}

//----- class Traffic_Blink --------------------
#define INDEX_LED_GREEN 0
#define INDEX_LED_YELLOW 1
#define INDEX_LED_RED 2

Traffic_Blink::Traffic_Blink()
{
    _idxLED = INDEX_LED_GREEN;
    _waitTime[INDEX_LED_GREEN] = 7 * 1000;
    _waitTime[INDEX_LED_YELLOW] = 3 * 1000;
    _waitTime[INDEX_LED_RED] = 5 * 1000;
    _secondCount = 0;
}

Traffic_Blink::~Traffic_Blink()
{
}

void Traffic_Blink::setup_Pin(int pinRed, int pinYellow, int pinGreen)
{
    // Mapping internal array index to physical LED objects
    _leds[INDEX_LED_GREEN].setup(pinGreen, "GREEN");
    _leds[INDEX_LED_YELLOW].setup(pinYellow, "YELLOW");
    _leds[INDEX_LED_RED].setup(pinRed, "RED");
}

void Traffic_Blink::setup_WaitTime(int redTimer, int yellowTimer, int greenTimer)
{
    _idxLED = INDEX_LED_GREEN;
    _waitTime[INDEX_LED_GREEN] = greenTimer * 1000;
    _waitTime[INDEX_LED_YELLOW] = yellowTimer * 1000;
    _waitTime[INDEX_LED_RED] = redTimer * 1000;
    _secondCount = 0;
}

void Traffic_Blink::blink(bool showLogger)
{
    static unsigned long ulTimer = 0;
    static uint32_t count = _waitTime[_idxLED];
    static bool ledStatus = false;

    // Run logic every 500ms
    if (!IsReady(ulTimer, 500))
        return;

    // Check if we just entered a new state or simply toggling
    if (count == _waitTime[_idxLED])
    {
        _secondCount = (count / 1000) - 1;
        ledStatus = true; // Force ON at start of cycle
        
        for (size_t i = 0; i < 3; i++)
        {
            if (i == _idxLED)
            {
                _leds[i].setStatus(true);
                if (showLogger)
                    printf("LED [%-6s] ON => %d Seconds\n", _leds[i].getName(), count / 1000);
            }
            else
            {
                _leds[i].setStatus(false);
            }
        }
    }
    else
    {
        // Blink logic: toggle status every 500ms
        ledStatus = !ledStatus;
        _leds[_idxLED].setStatus(ledStatus);
    }

    // Logic for counting down seconds
    if (ledStatus)
    {
        if (showLogger)
            printf(" [%s] => seconds: %d \n", _leds[_idxLED].getName(), _secondCount);
        if (_secondCount > 0) _secondCount--;
    }

    count -= 500;
    
    // If timer runs out, move to next light
    if (count > 0)
        return;

    _idxLED = (_idxLED + 1) % 3; // Cycle: 0->1->2->0...
    count = _waitTime[_idxLED];
}

int Traffic_Blink::getCount()
{
    return _secondCount + 1;
}

//----- Helper Functions --------------------
bool IsReady(unsigned long &ulTimer, uint32_t millisecond)
{
    if (millis() - ulTimer < millisecond)
        return false;
    ulTimer = millis();
    return true;
}

String StringFormat(const char *fmt, ...)
{
    va_list vaArgs;
    va_start(vaArgs, fmt);
    va_list vaArgsCopy;
    va_copy(vaArgsCopy, vaArgs);
    const int iLen = vsnprintf(NULL, 0, fmt, vaArgsCopy);
    va_end(vaArgsCopy);
    int iSize = iLen + 1;
    char *buff = (char *)malloc(iSize);
    vsnprintf(buff, iSize, fmt, vaArgs);
    va_end(vaArgs);
    String s = buff;
    free(buff);
    return String(s);
}