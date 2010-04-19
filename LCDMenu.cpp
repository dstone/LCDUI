#include "WProgram.h"
#include <LiquidCrystal.h>
#include "LCDMenu.h"

#define R_ARROW ((char) B01111110)
#define ROWS 2
#define COLS 16

LCDMenu::LCDMenu( LiquidCrystal *lcd, int navPin, int selPin ) {
    _lcd = lcd;
    _navPin = navPin;
    _selPin = selPin;
}

int LCDMenu::start( char *menuItems[], size_t menuLen ) {
    _menuItems = menuItems;
    _menuLen = menuLen;
    _pos = 0;

    printMenu();

    for (;;) {
        if ( digitalRead( _navPin ) ) {
            _pos = (_pos+1) % _menuLen;
            printMenu();
            while ( digitalRead( _navPin ) );
        }
        if ( digitalRead( _selPin ) ) {
            while ( digitalRead( _selPin ) );
            return _pos;
        }
        delay( 50 );
    }
}

void LCDMenu::printMenu() {
    (*_lcd).clear();

    int height = ROWS;
    int start = _pos;
    int cursor = 0;
    if ( _menuLen <= ROWS ) {
        height = _menuLen;
        start = 0;
        cursor = _pos;
    }

    for ( int i = 0; i < height; i++ ) {
        put_s( _menuItems[(start+i)%_menuLen], 1, i );
    }
    put_c( R_ARROW, 0, cursor );
}

void LCDMenu::put_s( char *str, int col, int row ) {
    (*_lcd).setCursor( col, row );
    (*_lcd).print( str );
}

void LCDMenu::put_c( char c, int col, int row ) {
    (*_lcd).setCursor( col, row );
    (*_lcd).print( c );
}

