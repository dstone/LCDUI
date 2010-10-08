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
    while( !(*_encoder).click() );

    return 30;
}

CountdownTimer::CountdownTimer( LiquidCrystal *lcd, RotaryEncoder *encoder ) {
    _encoder = encoder;
    _lcd = lcd;
}

void CountdownTimer::start( int durationInSeconds ) {
    duration = durationInSeconds * 1000;
    Serial.print( "starting timer, duration " );
    Serial.println( duration );
    //duration = 120000; // 120 second duration for testing
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
