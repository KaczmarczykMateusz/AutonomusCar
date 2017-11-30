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

#include "lcd.h"
#include "ultraSonic.h"
#include "motor.h"
#include "keyboard.h"
#include "action.h"

uint8_t lockMenu;

#define MENU_SET	lockMenu |= (1 << 3)
#define IS_MENU		lockMenu & (1 << 3)
#define MENU_CLEAR	lockMenu &= ~(1 << 3)

uint8_t menuIncrStep;

#if 0
#include <avr/eeprom.h>

extern const char EEMEM displaySpeedR[16];
extern const char EEMEM displaySpeedL[];
extern const char EEMEM setTurnSpeed[];
extern const char EEMEM setDistTrim[] ;
extern const char EEMEM setSpeedChange[];

extern const char EEMEM dispSlowSpeed[];
extern const char EEMEM dispMiddleSpeed[];
extern const char EEMEM dispFastSpeed[];

extern const char EEMEM dispLongDist[];
extern const char EEMEM dispMiddleDist[];
extern const char EEMEM dispShortDist[];

extern const char EEMEM dispSlowSpeedChange[];
extern const char EEMEM dispFastSpeedChange[];
#endif

void menuNextStep(void);

#endif
