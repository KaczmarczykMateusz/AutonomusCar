/*
 ============================================================================
 Name        : keyboard.c
 Author      : Mateusz Kaczmarczyk
 Version     : Microcontroller : Atmel AVR Atmega32
 Description : See header file
 ============================================================================
 */

#include "keyboard.h"
#include <avr/io.h>

/*************************************************************************
 Function: 	keyInit()
 Purpose:	Initialise single button
 Input:		Parameters of button connection; DDR, PORT, PIN adresses and key mask
 Returns:	Returns struct with button parameters
 **************************************************************************/
key keyInit(volatile uint8_t * K_DDR, volatile uint8_t * K_PORT, volatile uint8_t *K_PIN, uint8_t keyMask) {
	key upKey;
//	upKey.K_DDR &= ~keyMask;
//	upKey.K_PORT |= keyMask;
	upKey.K_DDR = K_DDR;
	upKey.K_PORT = K_PORT;
	upKey.K_PIN = K_PIN;
	upKey.key_mask = keyMask;
	upKey.PressKeyLock = 0;
	*upKey.K_DDR &= ~keyMask;
	*upKey.K_PORT |= keyMask;

	return upKey;
}

/*************************************************************************
 Function: 	key_press()
 Purpose:	assigning action to key key press event
 Input:		key struct and pointer to void function performing action
 **************************************************************************/
void keyPress(key * btn, void (*action)(void)) {
 	register uint8_t key_press = (*btn->K_PIN & btn->key_mask);

 	if(!btn->PressKeyLock && !key_press) {
		btn->PressKeyLock = 1;
		if(action) {
			action(); // action for PRESS of button
		}

	} else if(btn->PressKeyLock && key_press) {
		(++btn->PressKeyLock);
	}
 }


/*************************************************************************
 Function: keyIncrDcr()
 Purpose:  Incrementing and/ or decrementing time or value
 Input:    Struct with adding and subtracting buttons parameters
 	 	   Variable to be modified and its maximum allowed value
 Returns:  Set if time got changed
 **************************************************************************/
uint8_t keyIncrDcr(key *addKey, key *subtKey, uint8_t *modVal, uint8_t maxVal) {
	static uint8_t longPress = 0;
	static uint8_t shorterDelay = 0;
	uint8_t opPerformed = 0;


	register uint8_t addPressed = !(*addKey->K_PIN & addKey->key_mask);
	register uint8_t subtPressed = !(*subtKey->K_PIN & subtKey->key_mask);

#if 0
	register uint8_t addPressed;
	addPressed = addKey ? (*addKey->K_PIN & addKey->key_mask) : 1;
	register uint8_t subtPressed;
	subtPressed = subtrBtn ? (*subtrBtn->K_PIN & subtrBtn->key_mask) : 1;
#endif
	if (addPressed || subtPressed) { //TODO: subtracting part of function disabled because of undefined behavior
	// addPressed can override subtracting action without issues but they can't coexist even if you change PIN and port of it
		//	if (addPressed) {
		uint8_t temporaryVal = 1;
		opPerformed = 1;
		if (longPress > 30) {
			temporaryVal += 60;
		} else if (longPress > 15) {
			temporaryVal += 30;
		} else if (longPress > 0) {
			temporaryVal += 3;
		}

		if(modVal && addPressed) {
			*modVal += temporaryVal;
		} else if(modVal && subtPressed) {
			*modVal -= temporaryVal;
		}
		if(maxVal == 1) {			//In case if we use toggle mode
			*modVal = 0;
		} else {
			if(*modVal > maxVal) {
				*modVal = maxVal;
			}
		}


		if(!shorterDelay) {
			_delay_ms(120);
		}
		_delay_ms(120);
		if (addPressed || subtPressed) {
			shorterDelay = 1;
			if (longPress <= 26) {
				longPress++;
			}
		}
#if 0
		INPUT_MODIFIED_SET;
#endif
	} else {
		longPress = 0;
		shorterDelay = 0;
	}

	if(!opPerformed) {
		return 0;
	} else {
		return 1;
	}
}