#include <avr/io.h>
#include <avr/delay.h>
#include "Headers/display.h"

int size = DISPLAY_SIZE - 1; // Since the digits used to represent 0-100% are three out of four

const uint8_t digits[] = {
	0x03, //:0
	0x9F, //:1
	0x25, //:2
	0x0D, //:3
	0x99, //:4
	0x49, //:5
	0x41, //:6
	0x1F, //:7
	0x01, //:8
	0x09  //:9
};

const uint8_t channel[] = {
	0x08, //DIG4;
	0x04, //DIG3;
	0x02, //DIG2;
	//0x01  //DIG1;
};


void init_shift_register()
{
	DDRB = (1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB4); //Set as output
	PORTB &= ~(1<<PORTB4); //Enable Output of shift registers as first init
}

void disable_output_register(){
	// !OE, is active-LOW
	PORTB |= (1<<PORTB4);
}

void enable_output_register()
{
	PORTB &= ~(1<<PORTB4);
}

void shift_out(uint8_t data, uint8_t byte_lenght, char *direction)
{
	/*
		This function simply shifts one or more byte of data on a shift register (i.e. SH74HC595N)
		if direction == 1 LSBFIRST
		if direction == 0 MSBFIRST
	*/
	
	int8_t position;
	
	if(!strcmp(direction,"LSBFIRST")){
		
		LATCH_LOW;
		for(position = 0; position<byte_lenght; position++){
			CLK_LOW;
			if((data & (1<<position)) != 0){
				SHIFT_H;
			} else{
				SHIFT_L;
			}
			CLK_HIGH;
		}
		LATCH_HIGH;
	
	} else if(!strcmp(direction,"MSBFIRST")){
		
			LATCH_LOW;
			for(position=byte_lenght - 1; position > -1; position--){
				CLK_LOW;
				if((data & (1<<position)) != 0){
					SHIFT_H;
					} else{
					SHIFT_L;
				}
				CLK_HIGH;
			}
			LATCH_HIGH;
	}
}


void display_number(uint8_t number, uint8_t *num_digits)
{
	int j = 0;
	
	for (int i=number;i>0;i=i/10)
	{
		num_digits[(size) - j] = i % 10;
		j++;
	}

	for (int i=0;i<=size;i++)
	{
		disable_output_register();
		shift_out(channel[i],BYTE_LENGHT,"LSBFIRST");
		shift_out(digits[num_digits[size-i]],BYTE_LENGHT,"MSBFIRST");
		enable_output_register();
		num_digits[size-i] = 0;
		_delay_ms(5);
	}
}