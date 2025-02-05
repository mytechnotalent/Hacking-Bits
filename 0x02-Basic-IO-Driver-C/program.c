/////////////////////////////////////////////////////////////////////
// Project: ATmega328P Basic IO Driver
/////////////////////////////////////////////////////////////////////
// Author: Kevin Thomas
// E-Mail: ket189@pitt.edu
// Version: 1.0
// Date: 12/27/24
// Target Device: ATmega328P (Arduino Nano)
// Clock Frequency: 16 MHz
// Toolchain: AVR-GCC, AVRDUDE
// License: Apache License 2.0
// Description: This program uses a button connected to PD2 to ctrl
//              an external LED connected to PD5. When the button is
//              pressed, the LED illuminates; otherwise, it remains
//              off.
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// INCLUDES
/////////////////////////////////////////////////////////////////////
#include <avr/io.h>

/////////////////////////////////////////////////////////////////////
// DEFINES, MACROS, CONSTANTS
/////////////////////////////////////////////////////////////////////
#ifndef F_CPU
#define F_CPU 16000000UL          // define clk freq (16 MHz)
#endif

/////////////////////////////////////////////////////////////////////
// FUNCTIONS
/////////////////////////////////////////////////////////////////////
int main(void) {
  DDRD &= ~(1 << PD2);            // set PD2 (D1) as input 
  PORTD |= (1 << PD2);            // enable pull-up resistor on PD2
  DDRD |= (1 << PD5);             // set PD5 (D5) as output

  while (1) {
    if (!(PIND & (1 << PD2))) {   // if button pressed (PD2 low)
      PORTD |= (1 << PD5);        // LED on
    } else {                      // if button not pressed (PD2 high)
      PORTD &= ~(1 << PD5);       // LED off
    }
  }

  return 0;
}
