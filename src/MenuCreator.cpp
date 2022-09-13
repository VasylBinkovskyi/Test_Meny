#include <Arduino.h>
#include <MenuCreator.h>
// #include <LiquidCrystalRus.h>

#define DEFAULT_MENU_HANDLER 0xff

#define MAX_MENU 2

/**
 * @brief Функція для створення меню
 * @param *lcd приймає екземпляр класу LiquidCrystal_I2C, передавати потрібно адресу. Наприклад MenuCreator test(&lcd);
 *
 * */
MenuCreator::MenuCreator(LiquidCrystalRus *lcd)
{
    _lcd = lcd;
}

/**
 * @brief
 * Функція для переходу в попередній пункт меню.
 * Приклад:
 *
 * void menu1(uint8_t *handl){
 * MenuCreator::backMenu(handl);
 * }
 * @param *handl  потрібно передати обробник з попереднього пункту меню
 * @return none
 * @example test
 * */
void MenuCreator::backMenu(uint8_t *handl)
{
    if (MenuCreator::handler != DEFAULT_MENU_HANDLER)
    {
        return;
    }
    *handl = DEFAULT_MENU_HANDLER;
}

void MenuCreator::clerMenu()
{
    isCreated = false;
    _countMenu = 0;
}

/**
 * @brief
 * Виклик функції перейде в меню на якому знаходиться курсор.
 * */

void MenuCreator::clearDisplay()
{
    _lcd->setCursor(0, 0);
    _lcd->print("                ");
    _lcd->setCursor(0, 1);
    _lcd->print("                ");
}

/**
 * @brief
 * Функція для пересування курсору на екрані.
 * @param Cursor  приймає значення  MenuCreator::Cursor  CURSOR_UP або CURSOR_DOWN
 * */
void MenuCreator::moveCursor(MenuCreator::Cursor c)
{
    if (MenuCreator::handler != DEFAULT_MENU_HANDLER)
    {
        return;
    }

    if (c == CURSOR_UP)
    {
        if (MenuCreator::_crs == 0)
        {
            if (MenuCreator::_countMenu > MAX_MENU)
            {
                MenuCreator::clearDisplay();
            }
            MenuCreator::_crs = _countMenu - 1;
            MenuCreator::_frame[0] = _countMenu > MAX_MENU ? _countMenu - 1 : 0;
            MenuCreator::_frame[1] = _countMenu;
        }
        else
        {
            if (_crs == _frame[0])
            {
                if (_countMenu > MAX_MENU)
                {
                    MenuCreator::clearDisplay();
                }
                if (_frame[0] - MAX_MENU >= 0)
                {
                    _frame[0] -= MAX_MENU;
                    _frame[1] -= MAX_MENU;
                }
                else
                {
                    _frame[0] = 0;
                    _frame[1] = MAX_MENU - 1;
                }
            }
            _crs--;
        }
    }
    else if (c == CURSOR_DOWN)
    {
        if (_crs >= _countMenu - 1)
        {
            _crs = 0;
            _frame[0] = 0;
            _frame[1] = MAX_MENU - 1;
            if (_countMenu > MAX_MENU)
                MenuCreator::clearDisplay();
        }
        else
        {
            if (_crs == _frame[1])
            {
                _frame[0] += MAX_MENU;
                _frame[1] += MAX_MENU;
                if (_countMenu > MAX_MENU)
                    MenuCreator::clearDisplay();
            }
            _crs++;
        }
    }
    else if (c == CURSOR_OK)
    {
        MenuCreator::handler = _crs;
    }
}

void MenuCreator::_menu(const char *name, uint8_t id)
{
    if ((MenuCreator::_countMenu != 0) && (id >= MenuCreator::_frame[0] && id <= MenuCreator::_frame[1]))
    {
        static uint8_t y = 0;
        y = (uint8_t)(id % 2 != 0);
        _lcd->setCursor(0, y);
        (MenuCreator::_crs == id) ? _lcd->print(">") : _lcd->print(" ");
        _lcd->print(name);
    }
}

/**
 * @brief
 * Функція для відображення меню на екрані.
 * */
void MenuCreator::show()
{
    if (handler != DEFAULT_MENU_HANDLER)
    {
        (*_handlFunc[handler])(&handler);
    }
    else
    {
        for (size_t i = 0; i < MenuCreator::_countMenu; i++)
        {
            MenuCreator::_menu(MenuCreator::menuNames[i], i);
        }
    }
}


/**
 * @brief Функція для створення меню
 * @param MenuName назва пункту меню
 * @param (*func) Обробник меню. Функція обробника меню обовязково повина приймати параметр типу uint8_t
 * */
void MenuCreator::createMenu(const char *MenuName, void (*func)(uint8_t *handl))
{
    if (_countMenu == MAX_MENU_COUNT - 1)
        return;

    menuNames[_countMenu] = MenuName;
    _handlFunc[_countMenu] = func;
    _countMenu++;
    isCreated = true;
}

/**
 * @brief Деструктор класа, зануляються посилання на функції обробників, пункти меню та посилання на диспей.
 *
 * */
MenuCreator::~MenuCreator()
{
    for (size_t i = 0; i < 10; i++)
    {
        _handlFunc[i] = nullptr;
    }
    // subMenu = nullptr;
    _countMenu = 0;
    _lcd = nullptr;
}
