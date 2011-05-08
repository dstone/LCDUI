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
         *               If false, no wrapping. Default is true (wrapping enabled).
         */
        int getInt( char* format, int maxVal, int col, int row, int wrap=true );

        /**
         * Displays a single-screen "menu"--using the nav controls causes the 
         * cursor to move to the next in a set of column/row points on the 
         * screen. By activating the action button, a point is selected and the
         * method returns the index of the selected point.
         * \param locs  An array of column/row locations on the LCD.
         * \param count The size of the locs array.
         * \param pos   The index of a location in the locs array to be used as 
         *              the initial location of the cursor.
         */
        int cursorMenu( int locs[][2], int count, int pos=0 );

        /**
         * Displays a vertical-scrolling menu. Selection is indicated by a 
         * right arrow. Nav controls are used to move the arrow up and down.
         * The action control causes the method to return the index of the
         * currently-selected menu item.
         * \param menuItems An array of char* representing the menu contents to
         *                  be displayed.
         * \param menuLen   The length of the menuItems array.
         */
        int stringMenu( char *menuItems[], size_t menuLen );

        int getTime();

        LiquidCrystal* getLcd();

        RotaryEncoder* getEncoder();

    private:
        LiquidCrystal *_lcd;
        RotaryEncoder *_encoder;

        void printMenu( char *menuItems[], size_t menuLen, int top, int pos );
        void put_s( char *str, int col, int row );
        void put_c( char c, int col, int row );

        int click();

};

#endif
