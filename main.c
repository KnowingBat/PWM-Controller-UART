/*
 * Author : Davide D'Angelo
 * LinkedIn:
 * GitHub: 
 *
 * Micro controller: Atmega328p
 * Purposes of this program is to get able to control the speed of a DC motor
 * through pulse width modulation (PWM), using the USART interface in order to
 * increase or decrease its speed. Therefore, writing "u"("d") on terminal window 
 * increases(decreases) the motor's speed of 1%. The percentage level of the speed 
 * is displayed on a 4 digit 7 segments display, multiplexed by two shift registers
 * (SN74HC595N) connected in series. 
 *
 */

#define F_CPU	16000000UL
#define BAUD	9600 //Set the baud rate for UART comm
#define CLEAR	0X00UL
#define USER_TOP	255

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>
#include <math.h>
#include "Headers/display.h"

int main(void);
void timer1_config(void); 
void USART_config(void);

volatile unsigned char top = (unsigned char) USER_TOP;
unsigned char data;
uint8_t number = 0;

uint8_t num_digits[] = {0,0,0};

int main(){
	
	init_shift_register();
	timer1_config();
	USART_config();
	
	while(1)
	{
		display_number(number,num_digits);
	}
}

void timer1_config(){
	/*
		This function is meant to configure timer0 functionality,
		in order to control the PWM signal
	*/
	
	// Set PD5 (Timer 0 Output PIN) as output: this would be the output of the PWM signal
	DDRD |= (1<<DDD5);
	//Configuring timer function mode (Fast PWM), see data sheet for more
	TCCR0A = ((1<<COM0B1)|(1<<WGM01)|(1<<WGM00));
	TCCR0B = ((1<<WGM02)|(1<<CS02)|(1<<CS00));
	OCR0A = top;
	OCR0B = CLEAR; //This configuration results in a 0% duty cycle
	//Modifying this value will change the duty cycle of PWM signal  
}

void USART_config()
{
	/*
		This function performs the USART configuration declaring function mode,
		baud rate, data standard for communications (RX)
	 */
	//Baud rate declaration from setbaud.h
	UBRR0 = UBRR_VALUE;
	//Enable transmit unit and receive complete interrupt
	UCSR0B = (1<<RXEN0)|(1<<RXCIE0);
	//Enabling asynchronous 8-bit mode (data sheet for more info)
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	
	//Enable global interrupts
	sei();
}

//Interrupt Service Routines

ISR(USART_RX_vect)
{
	data = UDR0; //Pick data from received data register
	
	if(data == 'u')
	{
		if(number>=0 && number<=99)
		{
			number++;
		}
	} else if(data == 'd')
	{
		if(number>=1 && number<=100)
		{
			number--;
		}
	}
	
	OCR0B = ceil(number*(top / 100)); //Set the new duty cycle value
	// DUTY_CYCLE_MAX : 100% = X : number
}

