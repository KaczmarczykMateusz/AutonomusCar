/*
 ============================================================================
 Name        : main.c
 Author      : Mateusz Kaczmarczyk
 Version     :
 Description :
 ============================================================================
 */
#include "main.h"


uint8_t motorSpeed;		// variable for setting duty cycle

char buf[16];


// TODO: often result wrong is 7-8 or more than 300, check it,
//			emphasizing division between both measurements (measureA_B), error occurs ONLY while both sensors working
//			Consider taking 3-5 measurements and skipping 1-2 extreme different

int main(void) {
	sei();
	LCD_Initalize();
	distanceInit();
	uint32_t resultA = 0;
	uint32_t resultB = 0;
//TODO: get rid of collision between distance measure and PWM for motor speed control
//	motorInit();
	while (1) {
		if (intFlag == 0) {
			resultA = distanceA();
			resultB = distanceB();
			sprintf(buf, "%ld", resultA);
			LCD_Clear();
			LCD_WriteText(buf);		// send counter value to display
			sprintf(buf, "%ld", resultB);
			LCD_GoTo(0, 1);
			LCD_WriteText(buf);		// send counter value to display
		}
		//motorGo(100);
	}
}

//TODO: if motor.c included in this file is working properly, then replace other version in other folders(double timer (motor and time) with current one
