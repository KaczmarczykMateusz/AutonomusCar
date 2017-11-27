/*
 ============================================================================
 Name        : ultrasonic.h
 Author      : Mateusz Kaczmarczyk
 Version     :
 Description : CPU 8MHz
 ============================================================================
 */
#ifndef USONIC_H
#define ULTRASONIC_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define MEASURE_A	0
#define MEASURE_B	1
volatile uint8_t measureA_B;


#define TRIG_A_PORT_DIR		DDRC  |=  (1 << 0)
#define SET_TRIG_A_PORT		PORTC |=  (1 << 0)
#define CLR_TRIG_A_PORT		PORTC &= ~(1 << 0)

#define TRIG_B_PORT_DIR		DDRC  |=  (1 << 1)
#define SET_TRIG_B_PORT		PORTC |=  (1 << 1)
#define CLR_TRIG_B_PORT		PORTC &= ~(1 << 1)

#define INT0_PORT_DIR		DDRD  &= ~(1 << 2)
#define INT1_PORT_DIR		DDRD  &= ~(1 << 3)


volatile uint16_t currentCount;
volatile uint8_t intFlag;

void distanceInit(void);

uint32_t distanceA (void);
uint32_t distanceB (void);

#endif
