/*
 ============================================================================
 Name        : motor.h
 Author      : Mateusz Kaczmarczyk
 Version     : Atmega8! WGM registers vary among uC
 Description :
 ============================================================================
 */
#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>


//@brief: Motors PINs definitions
#define MOTOR_A_DDR_INIT	DDRB |=	(1 << 1)
#define MOTOR_B_DDR_INIT	DDRB |=	(1 << 2)


//@brief: PWM definitions
#define TIMER1_PWM_NON_INVERTING_MODE_CH_A	TCCR1A |= (1 << COM1A1);				//Non inverting PWM at PIN OC1A
#define TIMER1_PWM_NON_INVERTING_MODE_CH_B	TCCR1A |= (1 << COM1B1);				//Non inverting PWM at PIN OC1B
#define TIMER1_PWM_INVERTING_MODE_CH_A		TCCR1A |= (1 << COM1A1) | (1 << COM1A0);//Inverting PWM at PIN OC1A
#define TIMER1_PWM_INVERTING_MODE_CH_B		TCCR1A |= (1 << COM1B1) | (1 << COM1B0);//Inverting PWM at PIN OC1B

#define TIMER1_FAST_PWM_8_BIT				TCCR1A |= (1 << WGM10) | (1 << WGM12)	// Choose fast PWM 8-bit
#define TIMER1_PHASE_CORRECT_PWM_8_BIT		TCCR1A |= (1 << WGM10)  				// Choose Phase correct PWM 8-bit

#define TIMER1_PRESCALE_8					(1 << CS11)								//clk/8 prescaler
#define TIMER1_PRESCALE_64					(1 << CS11) | (1 << CS10)				//clk/64 prescaler
#define TIMER1_ENABLE						TCCR1B |= TIMER1_PRESCALE_8				//Start Timer1 with prescaler clk/8


/**
* @brief:	Initialise DC motor
* @param:	None
* @return:	None
*/
void motorInit(void);

/**
* @brief:	Increase/ decrease speed speed of right
* 			motor connected to channel A (PIN: OC1A)
* @param:	Value to write to OCR1A as percents
* 			: 0 - 100%
		   	: 0: Constant Low
		    : 100: Constant High
* @return:	None
*/
void rightMotorGo(uint8_t motorSpeed);

/**
* @brief:	Increase/ decrease speed of left
* 			motor connected to channel A (PIN: OC1B)
* @param:	Value to write to OCR1B as percents
* 			: 0 - 100%
		   	: 0: Constant Low
		    : 100: Constant High
* @return:	None
*/
void leftMotorGo(uint8_t motorSpeed);

#endif
