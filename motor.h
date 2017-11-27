/*
 ============================================================================
 Name        : motor.h
 Author      : Mateusz Kaczmarczyk
 Version     :
 Description :
 ============================================================================
 */
#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/interrupt.h>
#include <util/delay.h>  
#include <avr/io.h>
#include <stdint.h>

void motorInit(void);
void motorGo(uint32_t motorSpeed);
void motorOff(void);

#endif