#include <Arduino.h>

class KeyCreator
{
private:
 uint8_t PinNum;
 bool Logic ;
 unsigned long debouncTimer = 0;
 uint8_t buttonFlag = 0;

public:

    int DigitalKeyState();
    KeyCreator(uint8_t pinNum, bool logic);
};