/*
 ============================================================================
 Name        : action.c
 Author      : Mateusz Kaczmarczyk
 Version     :
 Description :
 ============================================================================
 */
#include "action.h"

trimmer trimInit(void) {
	trimmer tmp;
	tmp.trmTrimSpeed = 1;
	tmp.trmTurnSpeed = 2;
	tmp.trmSharpSpeed = 3;

	tmp.trmTrimDist = 10;
	tmp.trmTurnDist = 10;
	tmp.trmSharpDist = 20;

	tmp.trmSpeedUpSlow = 2;
	tmp.trmSpeedUpFast = 10;

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
void speedUpEasy(uint8_t *rightSpeed, uint8_t *leftSpeed) {
	*rightSpeed += _trmSpeedUpSlow;
	*leftSpeed += _trmSpeedUpSlow;
}

/*************************************************************************
 Function: 	speedUpFast()
 Purpose:	Fast acceleration
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void speedUpFast(uint8_t *rightSpeed, uint8_t *leftSpeed) {
	*rightSpeed += _trmSpeedUpFast;
	*leftSpeed += _trmSpeedUpFast;
}

/*************************************************************************
 Function: 	throttleBack()
 Purpose:	Slow deceleration
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void throttleBack(uint8_t *rightSpeed, uint8_t *leftSpeed) {
	*rightSpeed -= _trmSpeedUpSlow;
	*leftSpeed -= _trmSpeedUpSlow;
}

/*************************************************************************
 Function: 	slowDown()
 Purpose:	Fast deceleration
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void slowDown(uint8_t *rightSpeed, uint8_t *leftSpeed) {
	*rightSpeed -= _trmSpeedUpFast;
	*leftSpeed -= _trmSpeedUpFast;
}


/*************************************************************************
 Function: 	trimRight()
 Purpose:
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void trimRight(uint8_t *rightSpeed, uint8_t *leftSpeed) {
	*rightSpeed += _trmTrimSpeed;
	*leftSpeed -= _trmTrimSpeed;
}

/*************************************************************************
 Function: 	trimLeft()
 Purpose:
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void trimLeft(uint8_t *rightSpeed, uint8_t *leftSpeed) {
	*rightSpeed -= _trmTrimSpeed;
	*leftSpeed += _trmTrimSpeed;
}

/*************************************************************************
 Function: 	turnRight()
 Purpose:
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void turnRight(uint8_t *rightSpeed, uint8_t *leftSpeed) {
	*rightSpeed += _trmTurnSpeed;
	*leftSpeed -= _trmTurnSpeed;
}

/*************************************************************************
 Function: 	turnLeft()
 Purpose:
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void turnLeft(uint8_t *rightSpeed, uint8_t *leftSpeed) {
	*rightSpeed -= _trmTurnSpeed;
	*leftSpeed += _trmTurnSpeed;
}

/*************************************************************************
 Function: 	sharpRight()
 Purpose:
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void sharpRight(uint8_t *rightSpeed, uint8_t *leftSpeed) {
	*rightSpeed += _trmSharpSpeed;
	*leftSpeed -= _trmSharpSpeed;
}

/*************************************************************************
 Function: 	sharpLeft()
 Purpose:
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void sharpLeft(uint8_t *rightSpeed, uint8_t *leftSpeed) {
	*rightSpeed -= _trmSharpSpeed;
	*leftSpeed += _trmSharpSpeed;
}

/*************************************************************************
 Function: 	drive()
 Purpose:
 Input:		Pointers for DC motors speed adjustment variables (scale: percent)
 **************************************************************************/
void drive(distance_s space, uint8_t *R, uint8_t *L) {

	//@brief: Slow down if close to obstacle
	if((space.rightSens < _trmSharpDist) ||			//@brief: If obstacle very close: slow down fast
			(space.leftSens < _trmSharpDist))
	{
		slowDown(R, L);
	}
	else if((space.rightSens < _trmTurnDist) ||		//@brief: If obstacle fairly close: slow down easy
			(space.leftSens < _trmTurnDist))
	{
		throttleBack(R, L);
	}

	//@brief:  Turn in order to avoid obstacle
	if((space.rightSens < _trmSharpDist) && (space.leftSens > (space.rightSens + 5)))  //@brief: In case if very close to obstacle
	{
		sharpLeft(R, L);
	}
	else if((space.rightSens > _trmSharpDist) && (space.leftSens < (space.rightSens + 5)))
	{
		sharpRight(R, L);
	}
	else if((space.rightSens < _trmTurnDist) && (space.leftSens > (space.rightSens + 5))) //@brief: In case if fairly close to obstacle
	{
		turnLeft(R, L);
	}
	else if((space.rightSens > _trmTurnDist) && (space.leftSens < (space.rightSens + 5)))
	{
		turnRight(R, L);
	}
	else if(space.rightSens < space.leftSens + _trmTrimDist)  //@brief: In case if fairly far from obstacle
	{
		trimLeft(R, L);
	}
	else if(space.rightSens > space.leftSens + _trmTrimDist)
	{
		trimRight(R, L);
	}
	else						//@brief: Accelerate if way clear
	{
		speedUpEasy(R, L);
	}

	//TODO: implement this check somewhere else in order to prevent overflowing
	if(*R > 100) {
		*R = 100;
	} else if(*R < 1)  {
		*R = 0;
	}
	if(*L > 100) {
		*L = 100;
	} else if(*L < 1)  {
		*L = 0;
	}
	rightMotorGo(*R);
	leftMotorGo(*L);

}
