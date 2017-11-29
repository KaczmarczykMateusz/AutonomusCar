/*
 ============================================================================
 Name        : 	keyboard.h
 Author      : 	Mateusz Kaczmarczyk
 Version     :	Microcontroller : Atmel AVR Atmega
       			16MHz external crystal resonator
 Description :
 ============================================================================
 */
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

//@brief Buttons masks definitions
#define SELECT_BTN_MASK (1 << 3)
#define UP_BTN_MASK 	(1 << 4)
#define DOWN_BTN_MASK 	(1 << 5)

//@brief	struct holding button values
typedef struct {
	volatile uint8_t *K_PIN;	//@brief PINx of button
	volatile uint8_t *K_DDR;
	volatile uint8_t *K_PORT;
	uint8_t key_mask;		//@brief mask: physical PIN of microcontroller assigned tobutton
	uint8_t PressKeyLock;		//@brief overfloving counter lock of press event
	uint8_t PushupKeyLock;		//@brief overfloving counter lock of push up event
	uint8_t longPressLock;		//@brief overfloving counter lock of long press event
} key;

/**
 * @brief   Single button initialisation
 * 			update of Data Direction and PORT registers
 * 			initialisation of struct with button parameters
 * @param
 * @return	Struct with button parameters
 */
key keyInit(volatile uint8_t * K_DDR, volatile uint8_t * K_PORT, volatile uint8_t *K_PIN, uint8_t keyMask);

/**
 * @brief	Assigning action to key key press event
 * @param	key struct and pointer to void function performing action
 * 			triggered at button press event
 * @return	None
 */
void keyPress(key * btn, void (*action)(void));

/**
 * @brief  Setting time as 24h format by user
 * 	@param  *addKey	:	Struct consisting of add button parameters or NULL
 *  @param  *subtrBtn:	Struct consisting of subtract button parameters or NULLL
 *  @param  *modVal	:	Struct consisting of time to be set or NULL
 *  @param	maxVal	:	Maximum value which can be reached by modVal
 *  					1: enables toggle mode where modVal ALWAYS become (0 or 1)
 *  @return Set if time got changed, and modify time values
 */
uint8_t keyIncrDcr(key *addKey, key *subtKey, uint8_t *modVal, uint8_t maxVal);



#endif /* KEYBOARD_H */
