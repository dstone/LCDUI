#ifndef Inputs_h
#define Inputs_h
#include "WProgram.h"

class RotaryEncoder {
    public:
        enum EncoderPort { PIN_D, PIN_B, PIN_C };
        RotaryEncoder( EncoderPort port, int buttonPin );

        int8_t readNav();
        int8_t click();
        int8_t pressed();

    private:
        EncoderPort _port;
        int _buttonPin;

        int8_t readEncoder();
        uint8_t readPort();
        void initPort();
};

#endif
