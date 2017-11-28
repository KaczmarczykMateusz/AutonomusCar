/*
 ============================================================================
 Name        : ultrasonic.h
 Author      : Mateusz Kaczmarczyk
 Version     :
 Description : CPU 8MHz
 ============================================================================
 */
#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

typedef struct {
	uint16_t sensINT0;
	uint16_t sensINT1;
} distance_s;

//@brief: Count compare matches of counter2 in order to measure time between sensing pulse and receiving echo
volatile uint16_t currentCount;

//@brief: Flag switching between phases of interrupt
volatile uint8_t intFlag;

//@brief: Increment this value during overflow of counter0 interrupt event
volatile uint8_t countDelayA;

//@brief: Increment this value during overflow of counter0 interrupt event
volatile uint8_t countDelayB;

//@brief: Increment this value during overflow of counter0 interrupt event
volatile uint8_t mainDelay;

//@brief: define whether measurement triggered or operation completed
uint8_t measureStep;

//@brief: Switch between sensor connected to INT0 and INT1
#define NEXT_STEP_CLR		measureStep &= ~(1 << 0)
#define NEXT_STEP_SET		measureStep |= (1 << 0)
#define IS_NEXT_STEP_SET	measureStep & (1 << 0)

//@brief: Confirm whether results processed or not
#define STEP_PROCESSED_CLR	measureStep &= ~(1 << 1)
#define STEP_PROCESSED_SET	measureStep |= (1 << 1)
#define IS_STEP_PROCESSED	measureStep & (1 << 1)

//@brief:
#define NEXT_STEP_WAIT_CLR	measureStep &= ~(1 << 2)
#define NEXT_STEP_WAIT_SET	measureStep |= (1 << 2)
#define IS_NEXT_STEP_WAIT	measureStep & (1 << 2)

//@brief:
#define F_STEP_WAIT_CLR	measureStep &= ~(1 << 3)
#define F_STEP_WAIT_SET	measureStep |= (1 << 3)
#define IS_F_STEP_WAIT	measureStep & (1 << 3)

//@brief:
#define CHECK_CLR	measureStep &= ~(1 << 4)
#define CHECK_SET	measureStep |= (1 << 4)
#define IS_CHECK	measureStep & (1 << 4)

//@brief:
#define LOCK_CLR	measureStep &= ~(1 << 5)
#define LOCK_SET	measureStep |= (1 << 5)
#define LOCK_CHECK	measureStep & (1 << 5)

//@brief: PORTs definitions
#define TRIG_A_PORT_DIR		DDRC  |=  (1 << 0)
#define SET_TRIG_A_PORT		PORTC |=  (1 << 0)
#define CLR_TRIG_A_PORT		PORTC &= ~(1 << 0)

#define TRIG_B_PORT_DIR		DDRC  |=  (1 << 1)
#define SET_TRIG_B_PORT		PORTC |=  (1 << 1)
#define CLR_TRIG_B_PORT		PORTC &= ~(1 << 1)

#define INT0_PORT_DIR		DDRD  &= ~(1 << 2)
#define INT1_PORT_DIR		DDRD  &= ~(1 << 3)


//@brief: Operations at registers
#define ENABLE_INT0			GICR |= (1 << INT0)						// enable external interrupts at INT0
#define DISABLE_INT0		GICR &= ~(1 << INT0)					// disable external interrupts at INT0
#define INT0_RISING_EDGE	MCUCR |= (1 << ISC01) | (1 << ISC00)	// choose source of interrupt (INT0) rising edge

#define ENABLE_INT1			GICR |= (1 << INT1)						// enable external interrupts at INT1
#define DISABLE_INT1		GICR &= ~(1 << INT1)					// disable external interrupts at INT1
#define INT1_RISING_EDGE	MCUCR |= (1 << ISC11) | (1 << ISC10)	// choose source of interrupt (INT1) rising edge

#define TIMER2_ENABLE					TCCR2 |= (1 << CS21)		//Start Timer2 with CLK/8 prescaler
#define TIMER2_DISABLE					TCCR2 &= ~(1<<CS21)			//STOP Timer2 with CLK/8 prescaler
#define TIMER2_OC_INTERRUPT_ENABLE		TIMSK |= (1 << OCIE2)		//Enable Output Compare Match (with OCR2) interrupt for timer2
#define TIMER2_OC_INTERRUPT_DISABLE		TIMSK &= ~(1 << OCIE2)		//Disable Output Compare Match (with OCR2) interrupt for timer2
#define TIMER2_CTC_MODE					TCCR2 |= (1 << WGM21)		//Choose Clear Timer on Compare (CTC) mode

#define TIMER0_ENABLE					TCCR0 |= (1 << CS00) | (1 << CS02)	//Start Timer0 with clk/1024 prescaler
#define TIMER0_OVF_INTERRUPT_ENABLE		TIMSK |= (1 << TOIE0);				//Enable overflow interrupt

uint8_t measureA_B;
#define  MEASURE_A 1
#define  MEASURE_B 0

/**
 * @brief:	Initialise variables and registers needed for distance measurement
 * @param:	None
 * @return:	None
 */
void distanceInit(void);

/**
 * @brief:	Initialise Clock0 to count time for marking delays
 * 			between triggering ultrasonic sensors
 * @param:	None
 * @return:	None
 */
void delayInit(void);

/**
 * @brief:	Measure distance using two ultrasonic sensors
 * @param:	Structure with both sensors to save value in it
 * @return:	0: Wait
 * 			1: Value save to structure
 */
uint8_t distance(distance_s *tmp);

#endif
