/////////////////////////////////////////////////////////////////////
// Project: ATmega328P STUXNET 
/////////////////////////////////////////////////////////////////////
// Author: Kevin Thomas
// E-Mail: ket189@pitt.edu
// Version: 1.0
// Date: 12/27/24
// Target Device: ATmega328P (Arduino Nano)
// Clock Frequency: 16 MHz
// Toolchain: AVR-GCC, AVRDUDE
// License: Apache License 2.0
// Description: This program generates a ~50Hz PWM signal on PB1
//              (Pin 9) to control a servo. The servo sweeps from
//              0° to 180° and back to 0° in 1° steps. Additionally,
//              it controls LEDs on D5 and D6 based on sweep delays.
//              If both SWEEP_DELAY_UP and SWEEP_DELAY_DOWN are 5,
//              it turns off LED at D6 and turns on LED at D5.
//              Otherwise, it turns off LED at D5 and turns on LED at 
//              D6. This program mimics the basic functionality of
//              the reactors at the Natanz Nuclear Facility.
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// INCLUDES
/////////////////////////////////////////////////////////////////////
#include <avr/io.h>
#include <util/delay.h>

/////////////////////////////////////////////////////////////////////
// DEFINES, MACROS, CONSTANTS
/////////////////////////////////////////////////////////////////////
#ifndef F_CPU
#define F_CPU 16000000UL          // define clk freq (16 MHz)
#endif
#define SERVO_MIN 2000            // minimum pulse width (1ms)
#define SERVO_MAX 4000            // maximum pulse width (2ms)
#define SERVO_STEP 11             // step size each degree (11 ticks)
#define SWEEP_DELAY_UP 5          // delay in ms for upward sweep
#define SWEEP_DELAY_DOWN 5        // delay in ms for downward sweep
#define LED_D5 PD5                // Arduino Digital Pin 5
#define LED_D6 PD6                // Arduino Digital Pin 6

/////////////////////////////////////////////////////////////////////
// FUNCTION DECLARATIONS
/////////////////////////////////////////////////////////////////////
static void timer1_init(void);
static void servo_write(uint8_t pos);

/////////////////////////////////////////////////////////////////////
// FUNCTIONS
/////////////////////////////////////////////////////////////////////
int main(void) {
  timer1_init();                  // initialize Timer1 for PWM

  // control LEDs based on sweep delays
  #if (SWEEP_DELAY_UP == 5) && (SWEEP_DELAY_DOWN == 5)
    PORTD &= ~(1 << LED_D5);      // LED off at D5
    PORTD |= (1 << LED_D6);       // LED on at D6
  #else
    PORTD &= ~(1 << LED_D6);      // LED off at D6
    PORTD |= (1 << LED_D5);       // LED on at D5
  #endif

  while (1) {
    // sweep up from 0° to 180°
    for (uint8_t pos = 0; pos <= 180; pos++) {
      servo_write(pos);           // set servo position
      _delay_ms(SWEEP_DELAY_UP);
    }

    // sweep down from 180° to 0°
    for (uint8_t pos = 180; pos > 0; pos--) {
      servo_write(pos);           // set servo position
      _delay_ms(SWEEP_DELAY_DOWN);
    }
  }

  return 0;
}

/////////////////////////////////////////////////////////////////////
// FUNCTION: timer1_init
/////////////////////////////////////////////////////////////////////
// Description: Configures Timer1 for Fast PWM mode with a frequency
//              of ~50Hz and sets PB1 (Pin 9) as the output.
//              Also configures LEDs on D5 and D6 as outputs.
/////////////////////////////////////////////////////////////////////
static void timer1_init(void) {
  // set PB1 (OC1A) as output and set PD5 and PD6 as outputs
  DDRB |= (1 << PB1);           
  DDRD |= (1 << LED_D5) | (1 << LED_D6); 

  // configure Timer1 for Fast PWM, TOP=ICR1, non-inverting mode
  TCCR1A = (1 << COM1A1) | (1 << WGM11); 
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); 

  // set ICR1 to 39999 for 20ms period
  ICR1 = 39999;
}

/////////////////////////////////////////////////////////////////////
// FUNCTION: servo_write
/////////////////////////////////////////////////////////////////////
// Description: Sets the servo position by updating OCR1A with the
//              pulse width corresponding to the position in degrees
//              (0° to 180°).
/////////////////////////////////////////////////////////////////////
static void servo_write(uint8_t pos) {
  // calculate pulse width (ticks) for the given position
  uint16_t pulse = SERVO_MIN + ((uint16_t)pos * SERVO_STEP);
  if (pulse > SERVO_MAX) 
    pulse = SERVO_MAX; 
  OCR1A = pulse; 
}
