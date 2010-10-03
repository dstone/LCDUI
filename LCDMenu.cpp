#include "WProgram.h"
#include <LiquidCrystal.h>
#include "LCDMenu.h"

#define R_ARROW ((char) B01111110)
#define ROWS 2
#define COLS 16

LCDMenu::LCDMenu( LiquidCrystal *lcd, RotaryEncoder *encoder ) {
    _lcd = lcd;
    _encoder = encoder;
}

int LCDMenu::start( char *menuItems[], size_t menuLen ) {
    _menuItems = menuItems;
    _menuLen = menuLen;
    _top = _pos = 0;

    printMenu();

    for (;;) {
        updateMenu();
        if ( (*_encoder).click() ) {
            return _pos;
        }
    }
}

void LCDMenu::updateMenu() {
    int8_t reading = (*_encoder).readNav();
    if ( reading ) {
        _pos = max( 0, _pos + reading );
        _pos = min( _pos, _menuLen-1 );
        Serial.print( "Reading: " );
        Serial.println( reading );
        Serial.print( "Position: " );
        Serial.println( _pos );
        if ( reading > 0 ) {
            // going down
            _top = max( 0, _pos - ROWS + 1 );
        } else {
            _top = min( _pos, _top );
        }
        Serial.print( "Top:" );
        Serial.println( _top );
        printMenu();
    }
}

void LCDMenu::printMenu() {
    (*_lcd).clear();

    int height = min( _menuLen, ROWS );
    int start = _top;
    //int start = max( 0, _pos - ROWS + 1 ); // which menu item to show at the top
    int cursor = _pos - start; // cursor offset from top of screen

    for ( int i = 0; i < height; i++ ) {
        put_s( _menuItems[(start+i)%_menuLen], 1, i );
    }
    put_c( R_ARROW, 0, cursor ); // draw cursor
}

void LCDMenu::put_s( char *str, int col, int row ) {
    (*_lcd).setCursor( col, row );
    (*_lcd).print( str );
}

void LCDMenu::put_c( char c, int col, int row ) {
    (*_lcd).setCursor( col, row );
    (*_lcd).print( c );
}

