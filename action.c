/*
 ============================================================================
 Name        : action.c
 Author      : Mateusz Kaczmarczyk
 Version     :
 Description :
 ============================================================================
 */
#include "action.h"

#if 0
uint8_t EEMEM _trmTrimSpeed = 1;
uint8_t EEMEM _trmTurnSpeed = 2;
uint8_t EEMEM _trmSharpSpeed = 3;
uint8_t EEMEM _trmTrimDist = 30;
uint8_t EEMEM _trmTurnDist = 20;
uint8_t EEMEM _trmSharpDist = 10;
uint8_t EEMEM _trmSpeedUpSlow = 2;
uint8_t EEMEM _trmSpeedUpFast = 3;
#endif

#if 0
void trimUpdate(trimmer tmp) {
	eeprom_update_byte(&_trmTrimSpeed, tmp.trmTrimSpeed);
	eeprom_update_byte(&_trmTurnSpeed, tmp.trmTurnSpeed);
	eeprom_update_byte(&_trmSharpSpeed, tmp.trmSharpSpeed);

	eeprom_update_byte(&_trmTrimDist, tmp.trmTrimDist);
	eeprom_update_byte(&_trmTurnDist, tmp.trmTurnDist);
	eeprom_update_byte(&_trmSharpDist, tmp.trmSharpDist);

	eeprom_update_byte(&_trmSpeedUpSlow, tmp.trmSpeedUpSlow);
	eeprom_update_byte(&_trmSpeedUpFast, tmp.trmSpeedUpFast);
}
#endif

trimmer trimInit(void) {
	trimmer tmp;
	tmp.trmTrimSpeed = 1;
	tmp.trmTurnSpeed = 2;
	tmp.trmSharpSpeed = 3;

	tmp.trmTrimDist = 30;
	tmp.trmTurnDist = 20;
	tmp.trmSharpDist = 10;

	tmp.trmSpeedUpSlow = 2;
	tmp.trmSpeedUpFast = 3;

	trimUpdate(tmp);

	return tmp;
}

void trimUpdate(trimmer tmp) {
	_trmTrimSpeed = tmp.trmTrimSpeed;
	_trmTurnSpeed = tmp.trmTurnSpeed;
	_trmSharpSpeed = tmp.trmSharpSpeed;

	_trmTrimDist = tmp.trmTrimDist;
	_trmTurnDist = tmp.trmTurnDist;
	_trmSharpDist = tmp.trmSharpDist;

	_trmSpeedUpSlow = tmp.trmSpeedUpSlow;
	_trmSpeedUpFast = tmp.trmSpeedUpFast;
}

/*************************************************************************
 Function: 	speedUpEasy()
 Purpose:	Slow acceleration
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void speedUpEasy(uint8_t *leftSpeed, uint8_t *rightSpeed) {
	*rightSpeed += _trmSpeedUpSlow;
	*leftSpeed += _trmSpeedUpSlow;
}

/*************************************************************************
 Function: 	speedUpFast()
 Purpose:	Fast acceleration
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void speedUpFast(uint8_t *leftSpeed, uint8_t *rightSpeed) {
	*rightSpeed += _trmSpeedUpFast;
	*leftSpeed += _trmSpeedUpFast;
}

/*************************************************************************
 Function: 	throttleBack()
 Purpose:	Slow deceleration
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void throttleBack(uint8_t *leftSpeed, uint8_t *rightSpeed) {
	*rightSpeed -= _trmSpeedUpSlow;
	*leftSpeed -= _trmSpeedUpSlow;
}

/*************************************************************************
 Function: 	slowDown()
 Purpose:	Fast deceleration
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void slowDown(uint8_t *leftSpeed, uint8_t *rightSpeed) {
	*rightSpeed -= _trmSpeedUpFast;
	*leftSpeed -= _trmSpeedUpFast;
}


/*************************************************************************
 Function: 	trimRight()
 Purpose:
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void trimRight(uint8_t *leftSpeed, uint8_t *rightSpeed) {
	*rightSpeed -= _trmTrimSpeed;
	*leftSpeed += _trmTrimSpeed;
}

/*************************************************************************
 Function: 	trimLeft()
 Purpose:
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void trimLeft(uint8_t *leftSpeed, uint8_t *rightSpeed) {
	*rightSpeed += _trmTrimSpeed;
	*leftSpeed -= _trmTrimSpeed;
}

/*************************************************************************
 Function: 	turnRight()
 Purpose:
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void turnRight(uint8_t *leftSpeed, uint8_t *rightSpeed) {
	*rightSpeed -= _trmTurnSpeed;
	*leftSpeed += _trmTurnSpeed;
}

/*************************************************************************
 Function: 	turnLeft()
 Purpose:
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void turnLeft(uint8_t *leftSpeed, uint8_t *rightSpeed) {
	*rightSpeed += _trmTurnSpeed;
	*leftSpeed -= _trmTurnSpeed;
}

/*************************************************************************
 Function: 	sharpRight()
 Purpose:
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void sharpRight(uint8_t *leftSpeed, uint8_t *rightSpeed) {
	*rightSpeed -= _trmSharpSpeed;
	*leftSpeed += _trmSharpSpeed;
}

/*************************************************************************
 Function: 	sharpLeft()
 Purpose:
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void sharpLeft(uint8_t *leftSpeed, uint8_t *rightSpeed) {
	*rightSpeed += _trmSharpSpeed;
	*leftSpeed -= _trmSharpSpeed;
}

/*************************************************************************
 Function: 	drive()
 Purpose:
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void drive(distance_s space, uint8_t *Left, uint8_t *Right) {
#if 0 // TODO: Consider enabling code for slowing down from below in version with bi-directional motor control
	//@brief: Slow down if close to obstacle
	if((space.rightSens < eeprom_read_byte(&_trmSharpDist)) ||			//@brief: If obstacle very close: slow down fast
			(space.leftSens < eeprom_read_byte(&_trmSharpDist)))
	{
		slowDown(&L, &R);
	}
	else if((space.rightSens < eeprom_read_byte(&_trmTurnDist)) ||		//@brief: If obstacle fairly close: slow down easy
			(space.leftSens < eeprom_read_byte(&_trmTurnDist)))
	{
		throttleBack(&L, &R);
	}
#endif

	uint8_t R = 100; //@brief: Temporary variable for motor speed subtraction and add
	uint8_t L = 100; //@brief: Temporary variable for motor speed subtraction and add

	//@brief:  Turn in order to avoid obstacle
	if((space.rightSens < _trmSharpDist) && (space.leftSens > (space.rightSens + 5)))  //@brief: In case if very close to obstacle
	{
		sharpLeft(&L, &R);
	}
	else if((space.leftSens < _trmSharpDist) && (space.rightSens > (space.leftSens + 5)))
	{
		sharpRight(&L, &R);
	}
	else if((space.rightSens < _trmTurnDist) && (space.leftSens > (space.rightSens + 5))) //@brief: In case if fairly close to obstacle
	{
		turnLeft(&L, &R);
	}
	else if((space.leftSens < _trmTurnDist) && (space.rightSens > (space.leftSens + 5)))
	{
		turnRight(&L, &R);
	}
	else if(space.rightSens < space.leftSens + _trmTrimDist)  //@brief: In case if fairly far from obstacle
	{
		trimLeft(&L, &R);
	}
	else if(space.rightSens > space.leftSens + _trmTrimDist)
	{
		trimRight(&L, &R);
	}
	else						//@brief: Accelerate if way clear
	{
		speedUpEasy(&L, &R);
	}

	//@brief: prevent overflowing
	if(R < 100) {
		if((R + *Right) > 100) {
			*Right = (*Right + 100) - (100 - R);
		} else {
			*Right = 0;
		}
	} else {
		*Right += (R - 100);
		if(*Right > 100) {
			*Right = 100;
		}
	}

	if(L < 100) {
		if((L + *Left) > 100) {
			*Left = (*Left + 100) - (100 - L);
		} else {
			*Left = 0;
		}
	} else {
		*Left += (L - 100);
		if(*Left > 100) {
			*Left = 100;
		}
	}

	rightMotorGo(*Right);
	leftMotorGo(*Left);

}
