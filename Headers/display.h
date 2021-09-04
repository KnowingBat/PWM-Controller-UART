#include <avr/io.h>

#ifndef DISPLAY_H
#define DISPLAY_H
#define F_CPU 16000000UL
#define DISPLAY_SIZE 3
#define BYTE_LENGHT 8

#define CLK_LOW (PORTB &= ~(1<<PORTB1)) //SRCLK (Shift register clock)
#define CLK_HIGH (PORTB |= (1<<PORTB1))

#define LATCH_LOW (PORTB &= ~(1<<PORTB2)) //SCLK (Storage Clock)
#define LATCH_HIGH (PORTB |= (1<<PORTB2))

#define SHIFT_H (PORTB |= (1<<PORTB0)) //SER data
#define SHIFT_L (PORTB &= ~(1<<PORTB0))

void init_shift_register(void);
void shift_out(uint8_t, uint8_t, char*);
void enable_output_register(void);
void disable_output_register(void);
void display_number(uint8_t, uint8_t *);

#endif