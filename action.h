/*
 ============================================================================
 Name        : action.h
 Author      : Mateusz Kaczmarczyk
 Version     : Atmega8! WGM registers vary among uC
 Description :
 ============================================================================
 */
#ifndef MOTOR_H
#define MOTOR_H

#include "motor.h"
#include "ultrasonic.h"

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
uint8_t _trmTrimSpeed;
uint8_t _trmTurnSpeed;
uint8_t _trmSharpSpeed;
uint8_t _trmTrimDist;
uint8_t _trmTurnDist;
uint8_t _trmSharpDist;
uint8_t _trmSpeedUpSlow;
uint8_t _trmSpeedUpFast;

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
