/*
 ============================================================================
 Name        : mototr.c
 Author      : Mateusz Kaczmarczyk
 Version     :
 Description :	Brush electric mototr control with PWM
		Microcontroller : Atmel AVR Atmega8
 ============================================================================
 */
#include "motor.h"

/*************************************************************************
Function: motorInit()
Purpose:  
**************************************************************************/
void motorInit(void) {
	//DDRB |= (1<<DDB1);
	DDRB |= (1 << 1);
	PORTB |= (1 << 1);
	TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
	TCCR1A |= (1 << WGM10);
	TIMSK |= (1 << OCIE1A);
}

/*************************************************************************
Function: motorGo()
Purpose:  
**************************************************************************/			
void motorGo(uint32_t motorSpeed) {
	TCCR1B |= (1 << CS11);
	OCR1A = motorSpeed;	//seting duty cycle at PIN OC1A equal to variable button
}

/*************************************************************************
Function: motorOff()
Purpose:  
**************************************************************************/
void motorOff(void) {
	TCCR1B &= ~(1 << CS11);
}
   
