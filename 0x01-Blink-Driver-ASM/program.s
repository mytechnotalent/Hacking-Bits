; ===================================================================
; Project: ATmega328P Blink Driver
; ===================================================================
; Author: Kevin Thomas
; E-Mail: ket189@pitt.edu
; Version: 1.0
; Date: 12/26/24
; Target Device: ATmega328P (Arduino Nano)
; Clock Frequency: 16 MHz
; Toolchain: AVR-AS, AVRDUDE
; License: Apache License 2.0
; Description: This program toggles the onboard LED connected to PB5 
;              (Pin 13) on the Arduino Nano at 1-second intervals 
;              using pure AVR Assembly. The delay is implemented 
;              using nested loops calibrated for a 16 MHz 
;              clock frequency.
; ===================================================================

; ===================================================================
; SYMBOLIC DEFINITIONS
; ===================================================================
.equ     DDRB, 0x04               ; Data Direction Register for PORTB
.equ     PORTB, 0x05              ; PORTB Data Register
.equ     PB5, 5                   ; Pin 5 of PORTB (D13 on Nano)

; ===================================================================
; PROGRAM ENTRY POINT
; ===================================================================
.global  program                  ; global label; make avail external
.section .text                    ; start of the .text (code) section

; ===================================================================
; PROGRAM LOOP
; ===================================================================
; Description: Main program loop which executes all subroutines and 
;              then repeads indefinately.
; -------------------------------------------------------------------
; Instructions: AVR Instruction Set Manual
;               6.87 RCALL – Relative Call to Subroutine
;               6.90 RJMP – Relative Jump
; ===================================================================
program:
  rcall  config_pins              ; config pins
program_loop:
  rcall  led_on                   ; turn LED on
  rcall  delay_1s                 ; wait 1 second
  rcall  led_off                  ; turn LED off
  rcall  delay_1s                 ; wait 1 second
  rjmp   program_loop             ; infinite loop

; ===================================================================
; SUBROUTINE: config_pins
; ===================================================================
; Description: Main configuration of pins on the ATmega128P Arduino 
;              Nano.
; -------------------------------------------------------------------
; Instructions: AVR Instruction Set Manual
;               6.95 SBI – Set Bit in I/O Register
;               6.88 RET – Return from Subroutine
; ===================================================================
config_pins:
  sbi    DDRB, PB5                ; set PB5 as output
  ret                             ; return from subroutine

; ===================================================================
; SUBROUTINE: led_on
; ===================================================================
; Description: Sets PB5 high to turn on the LED.
; -------------------------------------------------------------------
; Instructions: AVR Instruction Set Manual
;               6.95 SBI – Set Bit in I/O Register
;               6.88 RET – Return from Subroutine
; ===================================================================
led_on:
  sbi    PORTB, PB5               ; set PB5 high
  ret                             ; return from subroutine

; ===================================================================
; SUBROUTINE: led_off
; ===================================================================
; Description: Clears PB5 to turn off the LED.
; -------------------------------------------------------------------
; Instructions: AVR Instruction Set Manual
;               6.33 CBI – Clear Bit in I/O Register
;               6.88 RET – Return from Subroutine
; ===================================================================
led_off:
  cbi    PORTB, PB5               ; set PB5 low
  ret                             ; return from subroutine

; ===================================================================
; SUBROUTINE: delay_1s
; ===================================================================
; Description: A one-second delay.
;              - CPU Clock: 16 MHz
;              - 1 clock cycle = 62.5 ns
;              - total cycles for 1 second = 16,000,000
;              - nested loops create approximate 1-second delay
; -------------------------------------------------------------------
; Instructions: AVR Instruction Set Manual
;               6.69 LDI – Load Immediate
;               6.81 NOP – No Operation
;               6.49 DEC – Decrement
;               6.23 BRNE – Branch if Not Equal
;               6.88 RET – Return from Subroutine
; ===================================================================
delay_1s:
  ldi    r16, 250                 ; outer loop counter
.outer_loop:
  ldi    r17, 250                 ; middle loop counter
.middle_loop:
  ldi    r18, 64                  ; inner loop counter
.inner_loop:
  nop                             ; 1 cycle delay
  dec    r18                      ; decrement inner loop counter
  brne   .inner_loop              ; repeat if not zero else 2 cycles
  dec    r17                      ; decrement middle loop counter
  brne   .middle_loop             ; repeat if not zero
  dec    r16                      ; decrement outer loop counter
  brne   .outer_loop              ; repeat if not zero
  ret                             ; return from subroutine
