/*
 ============================================================================
 Name        : main.c
 Author      : Mateusz Kaczmarczyk
 Version     : Simple with only forward running motors
 Description : Project not developed further mostly because
 	 	 	 	 of uC (Atmega8)limitations. There is no space mostly for
 	 	 	 	 user adjustment functions etc, so it is possible
 	 	 	 	 to improve project basis much, much more, even without
 	 	 	 	 changing of uC and putting a lot of efforts.
 ============================================================================
 */

#include "main.h"

//#include <avr/pgmspace.h>
#define PERCENTAGE 100

// XXX: often result wrong is 7-8 or more than 300, check it,
//			emphasizing division between both measurements (measureA_B), error occurs ONLY while both sensors working
//			Consider taking 3-5 measurements and skipping 1-2 extreme different
#if 0
	const char EEMEM displaySpeedR[16] = "R: %d speed: %d";
	const char EEMEM displaySpeedL[] = "L: %d speed: %d";
	const char EEMEM setTurnSpeed[] = "Set turn speed";
	const char EEMEM setDistTrim[] = "Set dist trimmer";
	const char EEMEM setSpeedChange[] = "Set speed change";

	const char EEMEM dispSlowSpeed[] = "Slow: %d%%";
	const char EEMEM dispMiddleSpeed[] = "Middle: %d%%";
	const char EEMEM dispFastSpeed[] = "Fast: %d%%";

	const char EEMEM dispLongDist[] = "Long: %d[cm]";
	const char EEMEM dispMiddleDist[] = "Middle: %d[cm]";
	const char EEMEM dispShortDist[] = "Short: %d[cm]";

	const char EEMEM dispSlowSpeedChange[] = "Slow: %d%%";
	const char EEMEM dispFastSpeedChange[] = "Fast: %d%%";
#endif

int main(void) {
#if 0
	key selectKey = keyInit(&DDRC, &PORTC, &PINC, SELECT_BTN_MASK);
	key upKey = keyInit(&DDRC, &PORTC, &PINC, UP_BTN_MASK);
	key dwnKey = keyInit(&DDRC, &PORTC, &PINC, DOWN_BTN_MASK);
#endif

	lockMenu = 0;
	menuIncrStep = 0;
	char LCD_buff[16]; // TODO: check if we shouldn't exceed size to 17

	LCD_Init();
	distInit();
	delayInit();
	motorInit();

	trimmer trim;
	trim = trimInit();
	sei();
	distance_s dist;

	//@brief: Right motor speed as percentage of maximum voltage
	uint8_t rightSpeed = 40;

	//@brief: Left motor speed as percentage of maximum voltage
	uint8_t leftSpeed = 40;

	while(1) {
		if((mainDelay > 0)) {
			distMeasure(&dist);
			mainDelay = 0;
#if DEBUGGING
			sprintf(LCD_buff, "R: %d speed: %d", dist.rightSens, rightSpeed);
			LCD_Clear();
			LCD_WriteText(LCD_buff);
			sprintf(LCD_buff, "L: %d speed: %d", dist.leftSens, leftSpeed);
			LCD_GoTo(0, 1);
			LCD_WriteText(LCD_buff);
#endif
			drive(dist, &leftSpeed, &rightSpeed);
		}

		//	****************** TRIMMING MENU ******************	//
#if 0	//XXX: Lack of Program memory at atmega8
		keyPress(&selectKey, menuNextStep);

		switch(menuIncrStep) {
		case 1:
			MENU_SET;
			keyIncrDcr(&upKey, &dwnKey, &trim.trmTrimSpeed, PERCENTAGE);
			sprintf(LCD_buff, PSTR(dispSlowSpeed), trim.trmTrimSpeed );
			LCD_writeScreen(PSTR(setTurnSpeed), LCD_buff);
		break;

		case 2:
			keyIncrDcr(&upKey, &dwnKey, &trim.trmTurnSpeed, PERCENTAGE);
			sprintf(buf2, PSTR(dispMiddleSpeed), trim.trmSharpSpeed );
			LCD_writeScreen(PSTR(setTurnSpeed), LCD_buff);
		break;

		case 3:
			keyIncrDcr(&upKey, &dwnKey, &trim.trmSharpSpeed, PERCENTAGE);
			sprintf(LCD_buff, PSTR(dispFastSpeed), trim.trmSharpSpeed );
			LCD_writeScreen(PSTR(setTurnSpeed), LCD_buff);
		break;
		case 4:
			keyIncrDcr(&upKey, &dwnKey, &trim.trmTrimDist, PERCENTAGE);
			sprintf(LCD_buff, PSTR(dispLongDist), trim.trmTrimDist );
			LCD_writeScreen(PSTR(setDistTrim), LCD_buff);
		break;
		case 5:
			keyIncrDcr(&upKey, &dwnKey, &trim.trmTurnDist, PERCENTAGE);
			sprintf(LCD_buff, PSTR(dispMiddleDist), trim.trmTurnDist );
			LCD_writeScreen(PSTR(setDistTrim), LCD_buff);
		break;
		case 6:
			keyIncrDcr(&upKey, &dwnKey, &trim.trmSharpDist, PERCENTAGE);
			sprintf(LCD_buff, PSTR(dispShortDist), trim.trmSharpDist );
			LCD_writeScreen(PSTR(setDistTrim), LCD_buff);
		break;
		case 7:
			keyIncrDcr(&upKey, &dwnKey, &trim.trmSpeedUpSlow, PERCENTAGE);
			sprintf(LCD_buff, PSTR(dispSlowSpeedChange), trim.trmSpeedUpSlow);
			LCD_writeScreen(PSTR(setSpeedChange), LCD_buff);
		break;
		case 8:
			keyIncrDcr(&upKey, &dwnKey, &trim.trmSpeedUpFast, PERCENTAGE);
			sprintf(LCD_buff, PSTR(dispFastSpeedChange), trim.trmSpeedUpFast );
			LCD_writeScreen(PSTR(setSpeedChange), LCD_buff);
			trimUpdate(trim);
			MENU_CLEAR;
		break;

		default:
			menuIncrStep = 0;
		}
#endif
	}
}


void menuNextStep(void) {
	menuIncrStep++;
}
