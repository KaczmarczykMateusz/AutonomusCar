/*
 ============================================================================
 Name        : ultrasonic.c
 Author      : Mateusz Kaczmarczyk
 Version     : Ultra sonic sensor hc-sr04
	       Microcontroller : Atmel AVR Atmega8
 Description : CPU 8MHz, use of timer0, timer2, and both interrupt PINs
 ============================================================================
 */
#include "ultraSonic.h"
#include "lcd.h"

/*************************************************************************
Function: Timer2 comparison interrupt()
Purpose:  Called every 10 clock cycles in order to count time from
			sending sound till detecting it as echo
**************************************************************************/
ISR(TIMER2_COMP_vect) {
	currentCount++;

	if(currentCount > 2320)	{			//If 23200us (400cm) means it's more than maximum sensor range
		TIMER2_OC_INTERRUPT_DISABLE;
		TIMER2_DISABLE;
		DISABLE_INT0;
		currentCount = 0;				//Clear counter in order to present error
	}
}

/*************************************************************************
Function: PIN INT0 interrupt service routine()
Purpose:  Called when sensor at INT0 detected it's echo
**************************************************************************/
ISR(INT0_vect) {
	if (intFlag == 0) {
		TIMER2_ENABLE;

		DISABLE_INT0;
		intFlag = 1;

		MCUCR |= (1 << ISC01);	//Change interrupt trigger at INT0 to falling edge
		MCUCR &= ~(1 << ISC00);

		TIMER2_OC_INTERRUPT_ENABLE;
		ENABLE_INT0;
	} else {
		TIMER2_OC_INTERRUPT_DISABLE;
		TIMER2_DISABLE;
		DISABLE_INT0;
	}
}

/*************************************************************************
Function: PIN INT1 interrupt service routine()
Purpose:  Called when sensor at INT1 detected it's echo
**************************************************************************/
ISR(INT1_vect) {
	if (intFlag == 0) {
		TIMER2_ENABLE;

		DISABLE_INT1;
		intFlag = 1;

		MCUCR |= (1 << ISC11);	//Change interrupt trigger at INT1 to falling edge
		MCUCR &= ~(1 << ISC10);

		TIMER2_OC_INTERRUPT_ENABLE;
		ENABLE_INT1;
	} else {
		TIMER2_OC_INTERRUPT_DISABLE;
		TIMER2_DISABLE;
		DISABLE_INT1;
	}
}

//
/*************************************************************************
Function: TIMER0 overflow interrupt service routine()
Purpose:  Called whenever TCNT0 overflows, counts every 32,64ms
**************************************************************************/
ISR(TIMER0_OVF_vect) {
	countDelayA++;
	countDelayB++;
	mainDelay++;
}


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
	measureStep = 0;
}

/*************************************************************************
Function: distance()
Purpose:  Measure distance function
Input:	  Structure with both sensors to save value in it
Return:	  Value changed or not
**************************************************************************/
uint8_t distance(distance_s *tmp) {
	if(!(IS_F_STEP_WAIT) && !(IS_NEXT_STEP_SET) && !(IS_CHECK)) {
		TIMER2_CTC_MODE;
		OCR2 = 10;						//Set compare match for counter2
		TCNT2 = 0;

		F_STEP_WAIT_SET;

		ENABLE_INT0;
		INT0_RISING_EDGE;

		SET_TRIG_A_PORT;
		_delay_us(10);			//Delay required by ultrasonic module to start conversion
		CLR_TRIG_A_PORT;

		TCNT0 = 0;
		countDelayA = 1;
	} else if((IS_NEXT_STEP_SET)) {
		TIMER2_CTC_MODE;
		OCR2 = 10;						//Set compare match for counter2
		TCNT2 = 0;

		NEXT_STEP_WAIT_SET;

		ENABLE_INT1;
		INT1_RISING_EDGE;

		SET_TRIG_B_PORT;
		_delay_us(10);		//Delay required by ultrasonic module to start conversion
		CLR_TRIG_B_PORT;

		TCNT0 = 0;
		countDelayB = 1;		//Drive delay counter back to value: 2


	}
	if((countDelayA <= 1) && (IS_F_STEP_WAIT)) {
		return 0;
	} else if(IS_F_STEP_WAIT) {
		F_STEP_WAIT_CLR;
		STEP_PROCESSED_SET;
		NEXT_STEP_SET;
	} else if((IS_NEXT_STEP_SET) && (countDelayB <= 1)) {

		NEXT_STEP_CLR;
		CHECK_SET;
		return 0;
	} else if((IS_CHECK) && (countDelayB > 1)) {
		CHECK_CLR;
		NEXT_STEP_CLR;
	}

	TIMER2_OC_INTERRUPT_DISABLE;
	TIMER2_DISABLE;

	uint32_t dist = 0;
	dist = ((uint32_t)currentCount * 10) / 58;	//Save counter value in distA with prescaling it dividing by 5.8

	if(!dist) {
		//		err; // TODO: add error code
	}

	if(IS_STEP_PROCESSED) {
		static uint16_t distanceSaveA = 0;
		if(!dist || dist == 7) {			//XXX: Error of read often shows 7,
			dist = (uint32_t)distanceSaveA;		// after excluding it everything works fine
		} else {
			distanceSaveA = (uint16_t)dist;
			NEXT_STEP_WAIT_CLR;
		}
		tmp->sensINT0 = distanceSaveA;

		STEP_PROCESSED_CLR;
		currentCount = 0;
		intFlag = 0;
	} else {
		static uint16_t distanceSaveB = 0;
		if(!dist) {
			dist = (uint32_t)distanceSaveB;
		} else {
			distanceSaveB = (uint16_t)dist;
			NEXT_STEP_WAIT_CLR;
		}
		tmp->sensINT1 = distanceSaveB;
		currentCount = 0;
		intFlag = 0;
	}
	return 1;
}

/*************************************************************************
Function: delayInit()
Purpose:  Initialise Clock0 to count time for marking delays
			between triggering ultrasonic sensors
**************************************************************************/
void delayInit(void) {
	TIMER0_ENABLE;
	TIMER0_OVF_INTERRUPT_ENABLE;
    TCNT0 = 0; 			//Initialise Timer0 counter
}
