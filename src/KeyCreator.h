#include <Arduino.h>

class KeyCreator
{
private:
 uint8_t PinNum;
 bool Logic ;

public:

    int DigitalKeyState();
    KeyCreator(uint8_t pinNum, bool logic);
};