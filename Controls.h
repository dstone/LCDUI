#ifndef Controls_h
#define Controls_h
#include "WProgram.h"
#include "InputDevices.h"
#include <LiquidCrystal.h>

class TimeChooser {
    public:
        TimeChooser( LiquidCrystal *lcd, RotaryEncoder *encoder );
        int getTime();
    private:
        LiquidCrystal *_lcd;
        RotaryEncoder *_encoder;
        int8_t cursorSelect( int8_t locs[][2], int8_t count, int8_t pos=0 );
        int getInt( char* pattern, int maxCal, int col, int row );
};

class CountdownTimer {
    public:
        CountdownTimer( LiquidCrystal *lcd, RotaryEncoder *encoder );
        void start( int durationInSeconds );

    private:
        RotaryEncoder *_encoder;
        LiquidCrystal *_lcd;
        long startTime;
        long duration;

        long timeLeft();
        void printTime();
};

#endif
