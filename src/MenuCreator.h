#include <Arduino.h>
#include "LiquidCrystalRus.h"

#define DEFAULT_MENU_HANDLER 0xff

#ifndef MAX_MENU_COUNT

#define MAX_MENU_COUNT 10

#endif



class MenuCreator
{
private:
    uint8_t _countMenu = 0;
    uint8_t _crs = 0;
    uint8_t _frame[2] = {0, 1};
    uint8_t handler = DEFAULT_MENU_HANDLER;
    const char *menuNames[MAX_MENU_COUNT] = {};
    LiquidCrystalRus *_lcd = nullptr;
    void (*_handlFunc[MAX_MENU_COUNT])(uint8_t *handl) = {};
    void _menu(const char *name, uint8_t id);

public:
    // MenuCreator *subMenu = nullptr;
    bool isCreated = false;
    enum Cursor
    {
        CURSOR_UP,
        CURSOR_DOWN,
        CURSOR_OK
    };
    void createMenu(const char *MenuName, void (*func)(uint8_t *handl));
    void show();
    void moveCursor(Cursor crs);
    void clerMenu();
    void backMenu();
    void clearDisplay();
    void backMenu(uint8_t *handl);
    MenuCreator(LiquidCrystalRus *lcd);
    ~MenuCreator();
};