#ifndef Controls_h
#define Controls_h
#include "WProgram.h"
#include "Inputs.h"
#include <LiquidCrystal.h>

class TimeChooser {
    public:
        TimeChooser( LiquidCrystal *lcd, RotaryEncoder *encoder );
        int getTime();
    private:
        LiquidCrystal *_lcd;
        RotaryEncoder *_encoder;
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
