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
	LCD_Initalize();
	distanceInit();
	delayInit();
	motorInit();

	sei();
	distance_s dist;
	while (1) {
		if(mainDelay > 1) {							// TODO: this condition is enabled only during debugging
			distance(&dist);
			mainDelay = 0;
			sprintf(buf, "L: %d", dist.sensINT0);
			LCD_Clear();
			LCD_WriteText(buf);
			sprintf(buf, "R: %d", dist.sensINT1);
			LCD_GoTo(0, 1);
			LCD_WriteText(buf);

			motorGo(dist.sensINT0);
		}
	}
}
//TODO: if motor.c included in this file is working properly, then replace other
//version in other folders(double timer (motor and time) with current one
