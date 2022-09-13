#include <Arduino.h>
#include <KeyCreator.h>

KeyCreator::KeyCreator(uint8_t pinNum, bool logic)
{
    PinNum = pinNum;
    Logic = logic;
    pinMode(pinNum, INPUT);
}

int KeyCreator::DigitalKeyState()
{
    static unsigned long debouncTimer = 0;
    static uint8_t buttonFlag = 0;

    if (digitalRead(PinNum) != Logic)
    {
        debouncTimer = millis();
    }
    if (digitalRead(PinNum) == Logic && debouncTimer > 50 && buttonFlag == 0)
    {
        buttonFlag = 1;
        return 1;
    }
    if (digitalRead(PinNum) != Logic&&buttonFlag == 1)
    {
        buttonFlag = 0;
    }
    return 0;
}
