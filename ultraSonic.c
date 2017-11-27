/*
 ============================================================================
 Name        : ultrasonic.c
 Author      : Mateusz Kaczmarczyk
 Version     : Ultra sonic sensor hc-sr04
	       Microcontroller : Atmel AVR Atmega8
 Description : CPU 8MHz
 ============================================================================
 */
#include "ultraSonic.h"

/*************************************************************************
Function: distanceInit()
Purpose:  Initialise variables and registers needed for distance measurement
**************************************************************************/
void distanceInit(void) {
	//@brief: Initialise trigger PORTs directions
	TRIG_A_PORT_DIR;
	TRIG_B_PORT_DIR;

	//@brief: Initialise Input Capture PORTs directions
	INT0_PORT_DIR;
	INT1_PORT_DIR;

	currentCount = 0;
	intFlag = 0;
	measureA_B = 0;
}

/*************************************************************************
Function: distanceA()
Purpose:  Measure distance function
**************************************************************************/
uint32_t distanceA(void) {
	measureA_B = MEASURE_A;					// Confirm to comparison interrupt which sensor to read
	GICR |= (1 << INT0); 					// enable external interrupts at INT0
	MCUCR |= (1 << ISC01) | (1 << ISC00);	// choose source of interrupt (INT0) rising edge
	SET_TRIG_A_PORT;

	_delay_us(10);			// delay required by ultrasonic module to start conversion
	CLR_TRIG_A_PORT;
	_delay_ms(65);			//TODO: exchange this with free running mode
	GICR &= ~(1 << INT0);	// disable external interrupts at INT0

	static uint16_t distanceSave = 0;
	if(!intFlag) {
//		err; // TODO: add error code
	}

	uint32_t distance;
	distance = ((uint32_t)currentCount * 10) / 58;	//save counter value in distA with prescaling it dividing by 5.8

	if ((distance >= 400) ||
			(!intFlag)	  ||
			distance < 10) { 							// abandon if echo shows distance longer than maximum range
		distance = distanceSave;
	} else {
		distanceSave = distance;
	}
	currentCount = 0;
	intFlag = 0;

	return distance;
}

/*************************************************************************
Function: distanceB()
Purpose:  Measure distance function
**************************************************************************/
uint32_t distanceB(void) {
	measureA_B = MEASURE_B;					// Confirm to comparison interrupt which sensor to read
	GICR |= (1 << INT1); 					// enable external interrupts at INT1
	MCUCR |= (1 << ISC11) | (1 << ISC10);	// choose source of interrupt (INT1) rising edge
	SET_TRIG_B_PORT;

	_delay_us(10);				// delay required by ultrasonic module to start conversion
	CLR_TRIG_B_PORT;
	_delay_ms(65);
	GICR &= ~(1 << INT1);		// disable external interrupts at INT0

	static uint16_t distanceSave = 0;
	if(!intFlag) {
//		err; // TODO: add error code
	}

	uint32_t distance;
	distance = ((uint32_t)currentCount * 10) / 58;	//save counter value in distA with prescaling it dividing by 5.8

	if ((distance >= 400) ||
			(!intFlag)	  ||
			distance < 9) { 							// abandon if echo shows distance longer than maximum range
		distance = distanceSave;
	} else {
		distanceSave = distance;
	}
	currentCount = 0;
	intFlag = 0;

	return distance;
}

/*************************************************************************
Function: distanceB()
Purpose:  Timer comp a interrupt
**************************************************************************/
ISR(TIMER2_COMP_vect) {
	currentCount++;

	if(currentCount > 23200)	{
		intFlag = 0;
		if(measureA_B == MEASURE_A) {				// Check which sensor we are reading
			MCUCR |= (1 << ISC01) | (1 << ISC00);	// choose source of interrupt (INT0) rising edge
			GICR |= (1 << INT0);					// enable external interrupts at INT0
		} else if(MEASURE_B){
			MCUCR |= (1 << ISC11) | (1 << ISC10);	// choose source of interrupt (INT1) rising edge
			GICR |= (1 << INT1);					// enable external interrupts at INT1
		}
	}
}

ISR(INT0_vect) {
	if (intFlag == 0) {
		GICR &= ~(1 << INT0);	// disable external interrupts

		intFlag = 1;
		TCCR2 |= (1 << WGM21);

		OCR2 = 10;				// set compare match for counter1
		TCNT2 = 0;
		TCCR2 |= (1 << CS21);	//Start timer2
		TIMSK |= (1 << OCIE2);

		MCUCR |= (1 << ISC01);	// ensuring that interrupt (INT0) falling edge
		MCUCR &= ~(1 << ISC00);

		GICR |= (1 << INT0);	// enable external interrupts
	} else {
		TIMSK &= ~(1<<OCIE2);
		TCCR2 &= ~(1<<CS21);	// STOP timer
		GICR &= ~(1<<INT0);		// disable external interrupts at INT0
	}
}

ISR(INT1_vect) {
	if (intFlag == 0) {
		GICR &= ~(1 << INT1);	// disable external interrupts

		intFlag = 1;
		TCCR2 |= (1 << WGM21);

		OCR2 = 10;				// set compare match for counter1
		TCNT2 = 0;
		TCCR2 |= (1 << CS21);	//Start timer2
		TIMSK |= (1 << OCIE2);

		MCUCR |= (1 << ISC11);	// ensuring that interrupt (INT1) falling edge
		MCUCR &= ~(1 << ISC10);

		GICR |= (1 << INT1);	// enable external interrupts
	} else {
		TIMSK &= ~(1<<OCIE2);
		TCCR2 &= ~(1<<CS21);	// STOP timer
		GICR &= ~(1 << INT1);	// disable external interrupts at INT0
	}
}
