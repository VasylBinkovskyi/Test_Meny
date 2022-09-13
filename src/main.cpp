#include <Arduino.h>
#include <MenuCreator.h>
#include <KeyCreator.h>
// #include <LiquidCrystalRus.h>
// #define MAX_MENU_COUNT 20

#define ADRESS 0x27
#define MAX_MENU 20
#define UP 8
#define DOWN 7
#define OK 9
#define BACK 10
#define DEFAULT_HANDLER 0xff

LiquidCrystalRus lcd(ADRESS, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
// uint8_t count_menu = 0;
// uint8_t frame[2] = {0, 1};
// uint8_t i = 0, crs = 0, count = 1;

int DigitalKeyMonitor(int pinNumber)
{
  static unsigned long debouncTimer = 0;
  static int isPressFlag = 0;
  static bool initFlag = false;
  static const long longPressLimit = 2000;
  static const int debouncLimit = 20;

  if (true)
  {
    pinMode(pinNumber, INPUT);
    initFlag = true;
  }
  bool bootonState = digitalRead(pinNumber);
  if (!bootonState)
  {
    debouncTimer = millis();
    if (isPressFlag == 1)
    {
      isPressFlag = 0;
      return 2;
    }
    if (isPressFlag == 2)
    {
      isPressFlag = 0;
      return 4;
    }
  }
  else if (millis() - debouncTimer > debouncLimit && millis() - debouncTimer < (debouncLimit + 10))
  {
    isPressFlag = 1;
  }
  else if (millis() - debouncTimer > longPressLimit)
  {
    isPressFlag = 2;
    return 3;
  }
  else if (isPressFlag == 1)
  {
    return 1;
  }
  return 0;
}

void RelaySettings(uint8_t *id)
{
  static MenuCreator menuTree(&lcd);
  if (!menuTree.isCreated)
  {
    menuTree.createMenu("Налаштування реле", RelaySettings);
    // menuTree.createMenu("Time_1", STime);
    // menuTree.createMenu("Inputs_1", SInputs);
  }
  else
  {
    menuTree.show();
  }
  menuTree.backMenu(id);
}
void RelayDosSettings(uint8_t *id)
{
}
void LightSettings(uint8_t *id)
{
}
void ButtonSettings(uint8_t *id)
{
}
void EqipmentSettings(uint8_t *id)
{
}
void QereEqipmentSettings(uint8_t *id)
{
}
void WorkingSettings(uint8_t *id)
{

  static MenuCreator menuTree(&lcd);
  static KeyCreator DownKey(DOWN, true);
  static KeyCreator UpKey(UP, true);
  static KeyCreator OkKey(OK, true);
  static KeyCreator BackKey(BACK, true);
  if (!menuTree.isCreated)
  {
    menuTree.createMenu("Налашт. реле", RelaySettings);
    menuTree.createMenu("Налашт. реле доз", RelayDosSettings);
    menuTree.createMenu("Налашт. пiдсв кнопок", LightSettings);
    menuTree.createMenu("Налашт. кнопок", ButtonSettings);
    menuTree.createMenu("Налашт. приладiв", EqipmentSettings);
    menuTree.createMenu("Налашт. черги приладiв", QereEqipmentSettings);
  }
  else
  {
    menuTree.show();
  }

  if (DownKey.DigitalKeyState())
  {
    lcd.clear();
    menuTree.moveCursor(menuTree.CURSOR_DOWN);
  }
  if (UpKey.DigitalKeyState())
  {
    lcd.clear();
    menuTree.moveCursor(menuTree.CURSOR_UP);
  }
  if (OkKey.DigitalKeyState())
  {
    lcd.clear();
    menuTree.moveCursor(menuTree.CURSOR_OK);
  }
  if (BackKey.DigitalKeyState())
  {
    menuTree.backMenu(id);
  }
}
void ResetSettings(uint8_t *id)
{
}
void ResetTimers(uint8_t *id)
{
}
void AdditionalSettings(uint8_t *id)
{
  static MenuCreator menuTree(&lcd);
  static KeyCreator DownKey(DOWN, true);
  static KeyCreator UpKey(UP, true);
  static KeyCreator OkKey(OK, true);
  static KeyCreator BackKey(BACK, true);
  if (!menuTree.isCreated)
  {
    menuTree.createMenu("Скидання налаштувань", ResetSettings);
    menuTree.createMenu("Скидання лічильників", ResetTimers);
  }
  else
  {
    menuTree.show();
  }

  if (DownKey.DigitalKeyState())
  {
    lcd.clear();
    menuTree.moveCursor(menuTree.CURSOR_DOWN);
  }
  if (UpKey.DigitalKeyState())
  {
    lcd.clear();
    menuTree.moveCursor(menuTree.CURSOR_UP);
  }
  if (OkKey.DigitalKeyState())
  {
    lcd.clear();
    menuTree.moveCursor(menuTree.CURSOR_OK);
  }
  if (BackKey.DigitalKeyState())
  {
    menuTree.backMenu(id);
  }
}

void PriceSettings(uint8_t *id)
{
}
void DoseSettings(uint8_t *id)
{
}
void TimeSettings(uint8_t *id)
{
}
void VEND_Settings(uint8_t *id)
{
}
void ADD_Settings(uint8_t *id)
{
}
void CardSettings(uint8_t *id)
{
}
void TimersSettings(uint8_t *id)
{
}

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  // pinMode(UP, INPUT);
  // pinMode(DOWN, INPUT);
  // pinMode(OK, INPUT);
  Serial.println("--------------------------------Start----------------------------------------");
  lcd.command(0b101010);
  lcd.clear();
}

void loop()
{
  // Serial.print(DownKey.DigitalKeyState());
  static MenuCreator menuTree(&lcd);
  static KeyCreator DownKey(DOWN, false);
  static KeyCreator UpKey(UP, false);
  static KeyCreator OkKey(OK, false);
  static KeyCreator BackKey(BACK, false);
  Serial.print("DownKey :");
  Serial.println(DownKey.DigitalKeyState());
  Serial.print("UpKey   :");
  Serial.println(UpKey.DigitalKeyState());
  Serial.print("OkKey   :");
  Serial.println(OkKey.DigitalKeyState());
  Serial.print("BackKey :");
  Serial.println(BackKey.DigitalKeyState());
  if (!menuTree.isCreated)
  {
    menuTree.createMenu("Налашт. роботи", WorkingSettings);
    menuTree.createMenu("Додатковi налашт.", AdditionalSettings);
    menuTree.createMenu("Налашт. цiни", PriceSettings);
    menuTree.createMenu("Налашт. дозацiї", DoseSettings);
    menuTree.createMenu("Налашт. часу", TimeSettings);
    menuTree.createMenu("Налашт. Венд", VEND_Settings);
    menuTree.createMenu("Налашт. доп", ADD_Settings);
    menuTree.createMenu("Налашт. карток", CardSettings);
    menuTree.createMenu("Лiчильники", TimersSettings);
  }
  else
  {
    menuTree.show();
  }
  if (DownKey.DigitalKeyState())
  {
    //lcd.clear();
    menuTree.moveCursor(menuTree.CURSOR_DOWN);
  }
  if (UpKey.DigitalKeyState())
  {
    //lcd.clear();
    menuTree.moveCursor(menuTree.CURSOR_UP);
  }
  if (OkKey.DigitalKeyState())
  {
    //lcd.clear();
    menuTree.moveCursor(menuTree.CURSOR_OK);
  }
}
