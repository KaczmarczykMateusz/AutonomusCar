/*
 ============================================================================
 Name        : main.h
 Author      : Mateusz Kaczmarczyk
 Version     :
 Description : CPU 8MHz
 ============================================================================
 */
#ifndef MAIN_H_
#define MAIN_H_

#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include <util/atomic.h>
#include <avr/eeprom.h>

#include "lcd.h"
#include "ultraSonic.h"
#include "motor.h"
#include "keyboard.h"
#include "action.h"

uint8_t lockMenu;

#define MENU_SET	lockMenu |= (1 << 3)
#define IS_MENU		lockMenu & (1 << 3)
#define MENU_CLEAR	lockMenu &= ~(1 << 3)

uint8_t EEMEM trmTrimSpeedEEMEM = 1;		//TODO: check if and how it works
uint8_t menuIncrStep;

void menuNextStep(void);

#endif
