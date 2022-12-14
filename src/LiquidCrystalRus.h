//
// based on LiquidCrystal library from ArduinoIDE, see http://arduino.cc
//  modified 27 Jul 2011
// by Ilya V. Danilov http://mk90.ru/
//

#ifndef LiquidCrystalRus_h
#define LiquidCrystalRus_h

#include <inttypes.h>
#include "Print.h"
#include <Wire.h>
// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En B00000100  // Enable bit
#define Rw B00000010  // Read/Write bit
#define Rs B00000001  // Register select bit
// enum for
#define LCD_DRAM_Normal 0x00
#define LCD_DRAM_WH1601 0x01

#define printIIC(args) Wire.write(args)

class LiquidCrystalRus : public Print
{
public:
  LiquidCrystalRus(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);

  void init();

  void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

  void clear();
  void home();

  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void leftToRight();
  void rightToLeft();
  void autoscroll();
  void noAutoscroll();

  void createChar(uint8_t, uint8_t[]);
  void setCursor(uint8_t, uint8_t);

#if defined(ARDUINO) && ARDUINO >= 100
  virtual size_t write(uint8_t);
  using Print::write;
#else
  virtual void write(uint8_t);
#endif

  void command(uint8_t);

  void setDRAMModel(uint8_t);

private:
  void send(uint8_t, uint8_t);
  void write4bits(uint8_t);
  // uint8_t recv(uint8_t);
  void expanderWrite(uint8_t);
  void pulseEnable(uint8_t);

  uint8_t _Addr;
  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;
  uint8_t _numlines;
  bool _oled = false;
  uint8_t _cols;
  uint8_t _rows;
  uint8_t _backlightval;

  uint8_t _initialized;

  uint8_t _currline;

  uint8_t _dram_model;
  uint8_t utf_hi_char; // UTF-8 high part
};

#endif
