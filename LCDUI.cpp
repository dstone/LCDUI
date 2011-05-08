#include "LCDUI.h"

LCDUI::LCDUI( LiquidCrystal *lcd, RotaryEncoder *encoder ) {
    _lcd = lcd;
    _encoder = encoder;
}

LiquidCrystal* LCDUI::getLcd() {
    return _lcd;
}

RotaryEncoder* LCDUI::getEncoder() {
    return _encoder;
}

int LCDUI::getInt( char* pattern, int maxVal, int col, int row, int wrap ) {
    _lcd->cursor();
    int num = 0;
    char buffer[33];
    while ( !click() ) {
        int reading = (*_encoder).readNav();
        num += reading;
        if ( wrap ) {
            if ( num < 0 ) {
                num = maxVal;
            } else if ( num > maxVal ) {
                num = 0;
            }
        } else {
            num = max( 0, min( maxVal, num ) );
        }
        _lcd->setCursor( col, row );
        int len = sprintf( buffer, pattern, num );
        _lcd->print( buffer );
        _lcd->setCursor( col+len-1, row );
    }
    _lcd->cursor();
    return num;
}

int LCDUI::cursorMenu( int locs[][2], int count, int pos ) {
    _lcd->cursor();
    _lcd->blink();

    while ( !click() ) {
        _lcd->setCursor( locs[pos][0], locs[pos][1] );
        int8_t reading = (*_encoder).readNav();
        if ( reading ) {
            pos += reading;
            if ( pos < 0 ) {
                pos = count - 1;
            } else if ( pos >= count ) {
                pos = 0;
            }
        }
    }

    _lcd->noCursor();
    _lcd->noBlink();

    return pos;
}

int LCDUI::stringMenu( char *menuItems[], size_t menuLen ) {
    int top = 0;
    int pos = 0;

    printMenu( menuItems, menuLen, top, pos );

    for (;;) {
        int reading = _encoder->readNav();
        if ( reading ) {
            pos = max( 0, pos + reading );
            pos = min( pos, menuLen-1 );
            if ( reading > 0 ) {
                top = max( 0, pos - ROWS + 1 );
            } else {
                top = min( pos, top );
            }
            printMenu( menuItems, menuLen, top, pos );
        }
        if ( _encoder->click() ) {
            return pos;
        }
    }
}

int LCDUI::getTime() {
    _lcd->clear();
    
    // print time input
    _lcd->setCursor(0,0);
    _lcd->print( "00:00:00" );

    // print menu
    _lcd->setCursor(0,1);
    _lcd->print( " OK      Cancel" );
    _lcd->cursor();

    // cursor menu locations
    int locs[5][2] = {
        {1,0}, // hours
        {4,0}, // minutes
        {7,0}, // seconds
        {1,1}, // OK
        {9,1}  // Cancel
    };

    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    int menuSel = 0;
    for (;;) {
        // user selects which field to modify or completion action
        menuSel = cursorMenu( locs, 5, menuSel );
        // now get input for appropriate field, or return value or cancel
        switch ( menuSel ) {
            case 0:
                hours = getInt( "%02d", 59, 0, 0 );
                break;
            case 1:
                minutes = getInt( "%02d", 59, 3, 0 );
                break;
            case 2:
                seconds = getInt( "%02d", 59, 6, 0 );
                break;
            case 3:
                return hours * 3600 + minutes * 60 + seconds;
            default:
                return 0;
        }
    }
}

int LCDUI::click() {
    return (*_encoder).click();
}

void LCDUI::printMenu( char *menuItems[], size_t menuLen, int top, int pos ) {
    _lcd->clear();

    int height = min( menuLen, ROWS );
    int start = top;
    int cursor = pos - start; // cursor offset from top of screen

    for ( int i = 0; i < height; i++ ) {
        put_s( menuItems[(start+i)%menuLen], 1, i );
    }
    put_c( R_ARROW, 0, cursor ); // draw cursor
}

void LCDUI::put_s( char *str, int col, int row ) {
    _lcd->setCursor( col, row );
    _lcd->print( str );
}

void LCDUI::put_c( char c, int col, int row ) {
    _lcd->setCursor( col, row );
    _lcd->print( c );
}
