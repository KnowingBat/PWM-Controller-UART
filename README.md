## PWM Controller using UART interface - Atmega328p 
# Overview 

The main purpose of this project is to learn how to interface an user through UART interface to the PWM module driving a DC Motor.
The program is able to show the motor's speed in terms of percentage of Vmax.

## Components
- 330 Ohm resistors (x4);
- Shift registers (i.e. SH74HC595N) (x2);
- DC Motor (x1);
- Motor driver (i.e. L293D) (x1);
- 4-digits-7-segments display (i.e. );
- Power supply or battery (x1);

## Schematics
Check all the schematics in this folder: 

## File description 
> *display.c*
 
In this file you can find all the functions needed in order to display the speed percentage, controlling the shift registers logic.

> *main.c*
 
This file contains the main function, in which several operations are done as following: 
- Set PINs for data registers, latch clock, shift register clock, output enable signal and the timer0' output;
- Set the UART interface and its function mode;
- Set Timer0 in Fast-PWM mode;
- UART Interrupt handling for receive operations;
