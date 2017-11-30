/*
 ============================================================================
 Name        : action.h
 Author      : Mateusz Kaczmarczyk
 Version     : Atmega8! WGM registers vary among uC
 Description :
 ============================================================================
 */
#ifndef ACTION_H
#define ACTION_H

#include "motor.h"
#include "ultrasonic.h"

#if 0
#include <avr/eeprom.h>
#endif

#if 0				// Enable this code if there is space for it and when system will use H bridge L293
//@brief: Definitions for handling directions with H-Bridge L293
#define L293_DDR		DDRC
#define L293_PORT		PORTC
#define L293_1A			(1 << 0)
#define L293_2A			(1 << 1)

#define L_MOTOR_FORWARD_A	L293_PORT &= ~L293_1A
#define L_MOTOR_FORWARD_B	L293_PORT |= L293_2A
#define L_MOTOR_BACKWARD_A 	L293_PORT &= ~L293_2A
#define L_MOTOR_BACKWARD_B 	L293_PORT |= L293_1A
#define L_MOTOR_FAST_STOP 	L293_PORT &= ~L293_1A & ~L293_2A

#define R_MOTOR_FORWARD_A	L293_PORT &= ~L293_3A
#define R_MOTOR_FORWARD_B	L293_PORT |= L293_4A
#define R_MOTOR_BACKWARD_A 	L293_PORT &= ~L293_4A
#define R_MOTOR_BACKWARD_B 	L293_PORT |= L293_3A
#define R_MOTOR_FAST_STOP 	L293_PORT &= ~L293_3A & ~L293_4A


typedef enum {
	L_MOTOR_FORWARD		= (1 << 0),
	L_MOTOR_BACKWARD	= (1 << 1),
	L_FAST_STOP			= (1 << 2),
	R_MOTOR_FORWARD		= (1 << 3),
	R_MOTOR_BACKWARD	= (1 << 4),
	R_FAST_STOP			= (1 << 5),
	ERROR				= (1 << 6),
} motorDir;


void changeMotorDir(motorDir motorWithDir);
#endif

#if 0
void changeMotorDir(motorDir motorWithDir) {
	switch(motorWithDir){
	case L_MOTOR_FORWARD:
		L_MOTOR_FORWARD_A;
		L_MOTOR_FORWARD_B;
	break;

	case L_MOTOR_BACKWARD:
		L_MOTOR_BACKWARD_A;
		L_MOTOR_BACKWARD_B;
	break;

	case R_MOTOR_FORWARD:
		R_MOTOR_FORWARD_A;
		R_MOTOR_FORWARD_B;
	break;

	case R_MOTOR_BACKWARD:
		R_MOTOR_BACKWARD_A;
		R_MOTOR_BACKWARD_B;
	break;

	default:
		motorWithDir = ERROR; //TODO: return error
	}
}
#endif

typedef struct {
uint8_t trmTrimSpeed;
uint8_t trmTurnSpeed;
uint8_t trmSharpSpeed;

uint8_t trmTrimDist;
uint8_t trmTurnDist;
uint8_t trmSharpDist;

uint8_t trmSpeedUpSlow;
uint8_t trmSpeedUpFast;
} trimmer;

//brief: Variables below are local - DO NOT change them outside of trimUpdate
//XXX: For faster speeds store those variables in flash or RAM

uint8_t _trmTrimSpeed;
uint8_t _trmTurnSpeed;
uint8_t _trmSharpSpeed;
uint8_t _trmTrimDist;
uint8_t _trmTurnDist;
uint8_t _trmSharpDist;
uint8_t _trmSpeedUpSlow;
uint8_t _trmSpeedUpFast;
#if 0
extern uint8_t EEMEM _trmTrimSpeed;
extern uint8_t EEMEM _trmTurnSpeed;
extern uint8_t EEMEM _trmSharpSpeed;
extern uint8_t EEMEM _trmTrimDist;
extern uint8_t EEMEM _trmTurnDist;
extern uint8_t EEMEM _trmSharpDist;
extern uint8_t EEMEM _trmSpeedUpSlow;
extern uint8_t EEMEM _trmSpeedUpFast;
#endif
trimmer trimInit(void);

void trimUpdate(trimmer tmp);


/**
 * @brief:
 * @param: Pointers for DC motors speed adjustment variables
 *	 	 	 Scaled  as percent
 */
void speedUpEasy(uint8_t *rightSpeed, uint8_t *leftSpeed);

//@brief: Fast acceleration
/**
 * @brief:
 * @param: Pointers for DC motors speed adjustment variables
 *	 	 	 Scaled  as percent
 */
void speedUpFast(uint8_t *rightSpeed, uint8_t *leftSpeed);

//@brief: Slow deceleration
/**
 * @brief:
 * @param: Pointers for DC motors speed adjustment variables
 *	 	 	 Scaled  as percent
 */
void throttleBack(uint8_t *rightSpeed, uint8_t *leftSpeed);

//@brief: Fast deceleration
/**
 * @brief:
 * @param: Pointers for DC motors speed adjustment variables
 *	 	 	 Scaled  as percent
 */
void slowDown(uint8_t *rightSpeed, uint8_t *leftSpeed);

/**
 * @brief:
 * @param: Pointers for DC motors speed adjustment variables
 *	 	 	 Scaled  as percent
 */
void trimRight(uint8_t *rightSpeed, uint8_t *leftSpeed);

/**
 * @brief:
 * @param: Pointers for DC motors speed adjustment variables
 *	 	 	 Scaled  as percent
 */
void trimLeft(uint8_t *rightSpeed, uint8_t *leftSpeed);

/**
 * @brief:
 * @param: Pointers for DC motors speed adjustment variables
 *	 	 	 Scaled  as percent
 */
void turnRight(uint8_t *rightSpeed, uint8_t *leftSpeed);

/**
 * @brief:
 * @param: Pointers for DC motors speed adjustment variables
 *	 	 	 Scaled  as percent
 */
void turnLeft(uint8_t *rightSpeed, uint8_t *leftSpeed);

/**
 * @brief:
 * @param: Pointers for DC motors speed adjustment variables
 *	 	 	 Scaled  as percent
 */
void sharpRight(uint8_t *rightSpeed, uint8_t *leftSpeed);

/**
 * @brief:
 * @param: Pointers for DC motors speed adjustment variables
 *	 	 	 Scaled  as percent
 */
void sharpLeft(uint8_t *rightSpeed, uint8_t *leftSpeed);

/**
 * @brief:
 * @param: Pointers for DC motors speed adjustment variables
 *	 	 	 Scaled  as percent
 */
void drive(distance_s space, uint8_t *R, uint8_t *L);


#endif
