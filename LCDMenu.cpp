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

LCDMenu::LCDMenu( LiquidCrystal *lcd, EncoderPort port ) {
    _lcd = lcd;
    _port = port;
    initPort();
}

int LCDMenu::start( char *menuItems[], size_t menuLen ) {
    _menuItems = menuItems;
    _menuLen = menuLen;
    _top = _pos = 0;

    printMenu();

    for (;;) {
        updateMenu();
        /*
        static int8_t inc = 0;
        inc += readEncoder();
        if ( inc/4 ) {
            _pos += inc/4;
            _pos = min( _pos, _menuLen );
            printMenu();
            inc = 0;
        }
        //put_c ( inc+48, 15, 0 );
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
        */
    }
}

void LCDMenu::updateMenu() {
    int8_t reading = readInput();
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

int8_t LCDMenu::readInput() {
    // TODO: decide whether to use buttons or encoder
    static int8_t inc = 0;
    inc += readEncoder();
    if ( inc/4 ) {
        int8_t retVal = inc/4;
        inc = 0;
        return retVal;
    }
    return 0;
}

int8_t LCDMenu::readEncoder() {
    int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
    static uint8_t prev_state = 0;

    prev_state <<= 2;
    prev_state |= (readPort() & 0x03);
    //put_c ( prev_state+48, 15, 0 );

    uint8_t index = prev_state & 0x0f;
    return enc_states[index];
}

uint8_t LCDMenu::readPort() {
    switch ( _port ) {
        case PIN_D:
            return PIND;
        case PIN_B:
            return PINB;
        case PIN_C:
            return PINC;
        default:
            return (uint8_t) 0;
    }
}

void LCDMenu::initPort() {
    int pin_a = 14;
    int pin_b = 15;
    switch ( _port ) {
        case PIN_D:
            // TODO: this:
            break;
        case PIN_B:
            // TODO: this:
            break;
        case PIN_C:
            break;
    }
    pinMode( pin_a, INPUT );
    pinMode( pin_b, INPUT );
    digitalWrite( pin_a, HIGH );
    digitalWrite( pin_b, HIGH );
}

