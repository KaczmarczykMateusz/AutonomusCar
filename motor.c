/*
 ============================================================================
 Name        : motor.c
 Author      : Mateusz Kaczmarczyk
 Version     :
 Description :	Two brush DC motor control with PWM
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
	TIMER1_PWM_NON_INVERTING_MODE_CH_A
	TIMER1_PWM_NON_INVERTING_MODE_CH_B;
	TIMER1_FAST_PWM_8_BIT;
	TIMER1_START;
	MOTOR_B_DDR_INIT;
}

/*************************************************************************
Function: motorGo()
Purpose:  Increase/ decrease speed of right DC motor at OC1A PIN
Input  : 0 - 100% percent of maximum Voltage
**************************************************************************/
void rightMotorGo(uint8_t motorSpeed) {
	uint16_t tmp = motorSpeed;
	tmp *= 255;		//@brief: convert from percent into 8 bit value
	tmp *= 0.01f;
	OCR1A = tmp;	//seting duty cycle at PIN OC1A equal to variable button
}

/*************************************************************************
Function: motorGo()
Purpose:  Increase/ decrease speed of left DC motor at OC1B PIN
Input  : 0 - 100% percent of maximum Voltage
**************************************************************************/
void leftMotorGo(uint8_t motorSpeed) {
	uint16_t tmp = motorSpeed;
	tmp *= 255;		//@brief: convert from percent into 8 bit value
	tmp *= 0.01f;
	OCR1B = tmp;	//seting duty cycle at PIN OC1A equal to variable button
}
