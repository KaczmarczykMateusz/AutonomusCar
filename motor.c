/*
 ============================================================================
 Name        : mototr.c
 Author      : Mateusz Kaczmarczyk
 Version     :
 Description :	Brush electric mototr control with PWM
		Microcontroller : Atmel AVR Atmega8 8MHz internal osc
 ============================================================================
 */
#include "motor.h"

/*************************************************************************
Function: motorInit()
Purpose:  Initialise PWM for DC motor
**************************************************************************/
void motorInit(void) {
	MOTOR_A_DDR_INIT;
	TIMER1_PWM_NON_INVERTING_MOE;
	TIMER1_FAST_PWM_8_BIT;
	TIMER1_ENABLE;
}

/*************************************************************************
Function: motorGo()
Purpose:  Increase/ decrease speed of motor
Input  : 0 - 255
	   : 0: Constant Low
	   : 255: Constant High
**************************************************************************/
void motorGo(uint32_t motorSpeed) {
	OCR1A = motorSpeed;	//seting duty cycle at PIN OC1A equal to variable button
}
