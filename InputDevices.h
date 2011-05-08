#ifndef InputDevices_h
#define InputDevices_h
#include "WProgram.h"

class NavInput {
    public:
        //virtual ~NavInput() {}
        virtual int8_t readNav() {
            return 0;
        }
        virtual int8_t click() {
            return 0;
        }
        virtual int8_t pressed() {
            return 0;
        }
};

class RotaryEncoder : public NavInput {
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
