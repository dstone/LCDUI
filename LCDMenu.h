/*
 * LCDMenu.h - Library for basic menu navigation on 16x2 character LCD.
 */
#ifndef LCDMenu_h
#define LCDMenu_h

#include "WProgram.h"
#include <LiquidCrystal.h>

class LCDMenu {
    public:
        enum EncoderPort { PIN_D, PIN_B, PIN_C };
        LCDMenu( LiquidCrystal *lcd, int navPin, int selPin );
        LCDMenu( LiquidCrystal *lcd, EncoderPort port );
        int start( char *menuItems[], size_t menuLen );
    private:
        LiquidCrystal *_lcd;
        int _navPin, _selPin;
        int _top, _pos;
        char **_menuItems;
        size_t _menuLen;
        EncoderPort _port;

        void printMenu();
        void put_s( char *str, int col, int row );
        void put_c( char c, int col, int row );
        int8_t readInput();
        void updateMenu();
        int8_t readEncoder();
        uint8_t readPort();
        void initPort();
};

#endif
