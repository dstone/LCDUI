#include "InputDevices.h"
#include "WProgram.h"

RotaryEncoder::RotaryEncoder( EncoderPort port, int buttonPin ) {
    _port = port;
    _buttonPin = buttonPin;
    pinMode( buttonPin, INPUT );
    digitalWrite( buttonPin, HIGH );
    initPort();
}

int8_t RotaryEncoder::readNav() {
    static int8_t inc = 0;
    inc += readEncoder();
    if ( inc/4 ) {
        int8_t retVal = inc/4;
        inc = 0;
        return retVal;
    }
    return 0;
}

int8_t RotaryEncoder::click() {
    static int8_t push = 0;

    // click (push and release) has occured if button was pressed last
    // reading and is now released.
    if ( pressed() ) {
        push = 1;
        return 0;
    } else if ( push ) {
        push = 0;
        return 1;
    } else {
        return 0;
    }
}

int8_t RotaryEncoder::pressed() {

    // debounce
    int8_t r1 = digitalRead( _buttonPin );
    delay( 5 );
    if ( r1 != digitalRead( _buttonPin ) ) {
        return 0;
    }

    // button connected to ground
    return r1 == LOW;
}

int8_t RotaryEncoder::readEncoder() {
    int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
    static uint8_t prev_state = 0;

    prev_state <<= 2;
    prev_state |= (readPort() & 0x03);

    uint8_t index = prev_state & 0x0f;
    return enc_states[index];
}

uint8_t RotaryEncoder::readPort() {
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

void RotaryEncoder::initPort() {
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

