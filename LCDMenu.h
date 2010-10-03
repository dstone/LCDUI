/*
 * LCDMenu.h - Library for basic menu navigation on 16x2 character LCD.
 */
#ifndef LCDMenu_h
#define LCDMenu_h

#include "WProgram.h"
#include <LiquidCrystal.h>
#include "Inputs.h"

class LCDMenu {
    public:
        LCDMenu( LiquidCrystal *lcd, RotaryEncoder *encoder );
        int start( char *menuItems[], size_t menuLen );
    private:
        LiquidCrystal *_lcd;
        RotaryEncoder *_encoder;
        int _top, _pos;
        char **_menuItems;
        size_t _menuLen;

        void printMenu();
        void put_s( char *str, int col, int row );
        void put_c( char c, int col, int row );
        int8_t readInput();
        void updateMenu();
};

#endif
