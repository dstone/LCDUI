#include <stdio.h>
#include "Controls.h"

TimeChooser::TimeChooser( LiquidCrystal *lcd, RotaryEncoder *encoder ) {
    _encoder = encoder;
    _lcd = lcd;
}

int TimeChooser::getTime() {
    (*_lcd).clear();
    // print time input
    (*_lcd).setCursor(0,0);
    (*_lcd).print( "00:00:00" );

    // print menu
    (*_lcd).setCursor(0,1);
    (*_lcd).print( " OK      Cancel" );
    (*_lcd).cursor();
    int8_t locs[5][2] = {
        {1,0},
        {4,0},
        {7,0},
        {1,1},
        {9,1}
    };
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    int8_t menuSel = 0;
    for (;;) {
        menuSel = cursorSelect( locs, 5, menuSel );
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
                Serial.print( "Hours: " );
                Serial.println( hours );
                Serial.print( "minutes: " );
                Serial.println( minutes );
                Serial.println( "seconds: " );
                Serial.println( seconds );
                Serial.println( hours * 3600 + minutes * 60 + seconds );
                return hours * 3600 + minutes * 60 + seconds;
            default:
                return 0;

        }
    }
}

int8_t TimeChooser::cursorSelect( int8_t locs[][2], int8_t count, int8_t pos ) {
    (*_lcd).cursor();
    (*_lcd).blink();

    while ( !(*_encoder).click() ) {
        (*_lcd).setCursor( locs[pos][0], locs[pos][1] );
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

    (*_lcd).noCursor();
    (*_lcd).noBlink();

    return pos;
}

int TimeChooser::getInt( char* pattern, int maxVal, int col, int row ) {
    (*_lcd).cursor();
    int num = 0;
    char buffer[17];
    while ( !(*_encoder).click() ) {
        int reading = (*_encoder).readNav();
        num += reading;
        if ( num < 0 ) {
            num = maxVal;
        } else if ( num > maxVal ) {
            num = 0;
        }
        (*_lcd).setCursor( col, row );
        sprintf( buffer, pattern, num );
        (*_lcd).print( buffer );
        (*_lcd).setCursor( col, row );
    }
    (*_lcd).noCursor();
    return num;
}

CountdownTimer::CountdownTimer( LiquidCrystal *lcd, RotaryEncoder *encoder ) {
    _encoder = encoder;
    _lcd = lcd;
}

void CountdownTimer::start( int durationInSeconds ) {
    duration = ((long)durationInSeconds) * 1000;
    Serial.print( "starting timer, duration " );
    Serial.println( duration );
    (*_lcd).clear();
    startTime = millis();

    (*_lcd).setCursor( 0,0 );
    (*_lcd).print( "Time: " );
    (*_lcd).setCursor( 0,1 );
    (*_lcd).print( "Stop" );
    for (;;) {
        if ( timeLeft() <= 0 ) {
            (*_lcd).clear();
            Serial.println( "Ending timer" );
            return;
        }
        printTime();
        if ( (*_encoder).click() ) {
            duration = timeLeft();
            (*_lcd).setCursor( 0,1 );
            (*_lcd).print( "Start" );
            while ( !(*_encoder).click() ) { }
            startTime = millis();
            (*_lcd).setCursor( 0,1 );
            (*_lcd).print( "Stop " );
        }
            
    }

}

long CountdownTimer::timeLeft() {
    return max( 0, duration - ( millis() - startTime ) );
}

void CountdownTimer::printTime() {
    long time = timeLeft();
    int seconds = (time / 1000) % 60;
    int minutes = (time / 60000);
    char buffer[17];
    sprintf( buffer, "Time: %02d:%02d", minutes, seconds );
    (*_lcd).setCursor( 0,0 );
    (*_lcd).print( buffer );
    (*_lcd).setCursor( 0, 1 );
    (*_lcd).print( "Stop" );

}
