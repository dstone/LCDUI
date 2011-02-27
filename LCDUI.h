/*
 * LCDUI.h 
 */

#ifndef LCDUI_h
#define LCDUI_h

#include "WProgram.h"
#include <LiquidCrystal.h>
#include "InputDevices.h"
#define R_ARROW ((char) B01111110)
#define ROWS (2)

class LCDUI {
    public:
        LCDUI( LiquidCrystal *lcd, RotaryEncoder *encoder );

        /**
         * Prompts the user to enter a positive integer and returns the result.
         * \param format Standard printf format string used to format inputted
         *               integer.
         * \param maxVal Maximum allowable integer.
         * \param col    Starting column to display value.
         * \param row    Row to display value.
         * \param wrap   Boolean value. If true, values will wrap between 0 and maxVal.
         *               If false, no wrapping.
         */
        int getInt( char* format, int maxVal, int col, int row, int wrap=true );

        int cursorMenu( int locs[][2], int count, int pos=0 );

        int stringMenu( char *menuItems[], size_t menuLen );

        int getTime();

    private:
        LiquidCrystal *_lcd;
        RotaryEncoder *_encoder;

        void printMenu( char *menuItems[], size_t menuLen, int top, int pos );
        void put_s( char *str, int col, int row );
        void put_c( char c, int col, int row );

        int click();

};

#endif
