/*
 ============================================================================
 Name        : main.c
 Author      : Mateusz Kaczmarczyk
 Version     :
 Description :
 ============================================================================
 */

#include "main.h"


// TODO: often result wrong is 7-8 or more than 300, check it,
//			emphasizing division between both measurements (measureA_B), error occurs ONLY while both sensors working
//			Consider taking 3-5 measurements and skipping 1-2 extreme different

int main(void) {
	lockMenu = 0;
	menuIncrStep = 0;
	char buf[16];
	char buf2[16];
	uint8_t byteFromEEPROM = eeprom_read_byte(&trmTrimSpeedEEMEM);
	//uint8_t byteFromEEPROM =  = eeprom_read_byte (( uint8_t *) 0); // TODO: use this scheme if another is not working

	LCD_Init();
	distInit();
	delayInit();
	motorInit();

	key selectKey = keyInit(&DDRC, &PORTC, &PINC, SELECT_BTN_MASK);
	key upKey = keyInit(&DDRC, &PORTC, &PINC, UP_BTN_MASK);
	key dwnKey = keyInit(&DDRC, &PORTC, &PINC, DOWN_BTN_MASK);

	trimmer trim;
	trim = trimInit();
	sei();
	distance_s dist;

	//@brief: Right motor speed as percentage of maximum voltage
	uint8_t rightSpeed = 40;

	//@brief: Left motor speed as percentage of maximum voltage
	uint8_t leftSpeed = 40;

	while(1) {
		if((mainDelay > 1)) {							// TODO: this condition is enabled only during debugging
			distMeasure(&dist);
			mainDelay = 0;
			sprintf(buf, "R: %d speed: %d", dist.rightSens, rightSpeed);
			LCD_Clear();
			LCD_WriteText(buf);
			sprintf(buf, "L: %d speed: %d", dist.leftSens, leftSpeed);
			LCD_GoTo(0, 1);
			LCD_WriteText(buf);

			drive(dist, &rightSpeed, &leftSpeed);

		}

		//	****************** TRIMMING MENU ******************	//
		keyPress(&selectKey, menuNextStep);

		switch(menuIncrStep) {
		case 1:
			//MENU_SET;
			//eeprom_update_byte (( uint8_t *)0, 666);	// TODO: use this scheme if another is not working
//				trmTrimSpeedEEMEM = 123;
			keyIncrDcr(&upKey, &dwnKey, &trim.trmTrimSpeed, 100);
			sprintf(buf, "Set turn speed");
			sprintf(buf2, "Slow: %d%%", trim.trmTrimSpeed );
			LCD_writeScreen(buf, buf2);
		break;

		case 2:
			keyIncrDcr(&upKey, &dwnKey, &trim.trmTurnSpeed, 100);
			sprintf(buf, "Set turn speed");
			LCD_writeScreen(buf, buf2);
		break;
#if 0	//XXX: Lack of Program memory at atmega8
		case 3:
			keyIncrDcr(&upKey, &dwnKey, &trim.trmSharpSpeed, 100);
			sprintf(buf, "Set turn speed");
			sprintf(buf2, "Fast: %d%%", trim.trmSharpSpeed );
			LCD_writeScreen(buf, buf2);
		break;

		case 4:
			keyIncrDcr(&upKey, &dwnKey, &trim.trmTrimDist, 100);
			sprintf(buf, "Set dist trimmer");
			sprintf(buf2, "Long: %d[cm]", trim.trmTrimDist );
			LCD_writeScreen(buf, buf2);
		break;

		case 5:
			keyIncrDcr(&upKey, &dwnKey, &trim.trmTurnDist, 100);
			sprintf(buf, "Set dist trimmer");
			sprintf(buf2, "Middle: %d[cm]", trim.trmTurnDist );
			LCD_writeScreen(buf, buf2);
		break;

		case 6:
			keyIncrDcr(&upKey, &dwnKey, &trim.trmSharpDist, 100);
			sprintf(buf, "Set dist trimmer");
			sprintf(buf2, "Short: %d[cm]", trim.trmSharpDist );
			LCD_writeScreen(buf, buf2);
		break;

		case 7:
			keyIncrDcr(&upKey, &dwnKey, &trim.trmSpeedUpSlow, 100);
			sprintf(buf, "Set speed change");
			sprintf(buf2, "Slow: %d%%", trim.trmSpeedUpSlow);
			LCD_writeScreen(buf, buf2);
		break;

		case 8:
			keyIncrDcr(&upKey, &dwnKey, &trim.trmSpeedUpFast, 100);
			sprintf(buf, "Set trimmer");
			sprintf(buf2, "Fast: %d%%", trim.trmSpeedUpFast );
			LCD_writeScreen(buf, buf2);
			trimUpdate(trim);
		//	MENU_CLEAR;
		break;
#endif
		default:
			menuIncrStep = 0;
		}
	}
}
//TODO: if motor.c included in this file is working properly, then replace other
//version in other folders(double timer (motor and time) with current one



void menuNextStep(void) {
	menuIncrStep++;
}
