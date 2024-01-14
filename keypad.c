
// ----------------------------------------------------------------------------
// Created By: Jon Calladine
// Date: 03/12/2023

//  Description: Code for Keypad functions

//  PortD = Columns
// 	PortE = Rows (require PDR)

// ----------------------------------------------------------------------------

#include "keypad.h"
#include "Init.h"
#include "PLL.h"
#include "LCD.h"
#include "Buzzer.h"
#include "memory.h"

// Global Variables
char shift_state = 0;
volatile char press_state = 0;
volatile char first_press = 1;

char read_keypad(void) {
	// This function reads the key pad and returns a value between 1 and 16 that represents each key
	// Function returns a 0 if no value is pressed
	
	//  KEYPAD				 VALUE
	// 1  2  3  A		 1  2  3  4
	// 4  5  6  B	   5  6  7  8
	// 7  8  9  C  	 9  10 11 12
	// *  0  #  D		 13 14 15 16
		
	int press_val = 0;  // value of key press
	int return_value = 0;
	
	// Read Row 1
	int search_val = 1; // reset search value
	GPIO_PORTE_DATA_R = 0x01; // Set Row one input high
	
	for(int i = 1; i < 5; i++) {
		if (GPIO_PORTD_DATA_R & search_val) {
			press_val = i;
		}
		search_val = search_val * 2;
	}	
	
	// Read Row 2
	search_val = 1;
	GPIO_PORTE_DATA_R = 0x02; // Set Row two input high
	
	for(int i = 5; i < 9; i++) {
		if (GPIO_PORTD_DATA_R & search_val) {
			press_val = i;
		}
		search_val = search_val * 2;
	}	
	
	// Read Row 3
	search_val = 1;
	GPIO_PORTE_DATA_R = 0x04; // Set Row three input high
	
	for(int i = 9; i < 13; i++) {
		if (GPIO_PORTD_DATA_R & search_val) {
			press_val = i;
		}
		search_val = search_val * 2;
	}	
	
	// Read Row 4
	search_val = 1;
	GPIO_PORTE_DATA_R = 0x08; // Set Row four input high
	
	for(int i = 13; i < 17; i++) {
		if (GPIO_PORTD_DATA_R & search_val) {
			press_val = i;
		}
		search_val = search_val * 2;
	}	
	
	SysTick_Wait_ms(50); // 	50ms delay to avoid switch bounce
	
	
	
	// Functions to only receive one keypress
	
	if (press_val >= 1 && press_val <= 16) {
		press_state = 1; // button pressed so set state high
	}
	else if (press_val == 0) {
		press_state = 0; // Button not pressed so state is low
	}
	
	if (press_state == 1) {
		if (first_press == 1) {
			first_press = 0; // No longer the first press
			return_value = press_val;
		}
		else {
			return_value = 0;
		}
	}
	else if (press_state == 0) {
		press_state = 0; // reset press state
		first_press = 1; // reset first press 
		return_value = 0;
	}
	return return_value;
}

char decode_key_press(int value) {
	char symbol;
	
	// Shifted Values
	if (shift_state == 1) {
		switch (value) {
			case 0:
				symbol = 'N'; // N for null
				break;				
			case 1:
				symbol = 1;
				LCD_Write_Char(0x31);
				shift_state = 0; // Un-press Shift
				break;
			case 2:
				symbol = 2;
				LCD_Write_Char(0x32);
				shift_state = 0; // Un-press Shift
				break;
			case 3:
				symbol = 3;
				LCD_Write_Char(0x33);
				shift_state = 0; // Un-press Shift
				break;
			case 4:
				// Clear all
				clear_LCD();
				shift_state = 0; // Un-press Shift
				break;
			case 5:
				symbol = 4;
				LCD_Write_Char(0x34);
				shift_state = 0; // Un-press Shift
				break;
			case 6:
				symbol = 5;
				LCD_Write_Char(0x35);
				shift_state = 0; // Un-press Shift
				break;
			case 7:
				symbol = 6;
				LCD_Write_Char(0x36);
				shift_state = 0; // Un-press Shift
				break;
			case 8:
				symbol = 'x'; // Multiply 
				LCD_Write_Char(0xB7);
				shift_state = 0; // Un-press Shift
				break;
			case 9:
				symbol = 7;
				LCD_Write_Char(0x37);
				shift_state = 0; // Un-press Shift
				break;
			case 10:
				symbol = 8;
				LCD_Write_Char(0x38);
				shift_state = 0; // Un-press Shift
				break;
			case 11:
				symbol = 9;
				LCD_Write_Char(0x39);
				shift_state = 0; // Un-press Shift
				break;
			case 12:
				symbol = '/'; // Divide
				LCD_Write_Char(0xB8);
				shift_state = 0; // Un-press Shift
				break;
			case 13:
				shift_state = 0; // Un-press Shift
				break;
			case 14:
				symbol = 0;
				LCD_Write_Char(0x30);
				shift_state = 0; // Un-press Shift
				break;
			case 15:
				symbol = 'A'; // Ans
				// Write "A"
				LCD_Write_Char(0x41);
				shift_state = 0; // Un-press Shift
				break;
			case 16:
				symbol = '=';
				LCD_Write_Char(0x3D);
				shift_state = 0; // Un-press Shift
				break;		
		}
	}
	
	// Un-Shifted Values
	else {
		switch (value) {
			case 0:
				symbol = 'N'; // N for null
				break;
			case 1:
				symbol = 1;
				LCD_Write_Char(0x31);
				break;
			case 2:
				symbol = 2;
				LCD_Write_Char(0x32);
				break;
			case 3:
				symbol = 3;
				LCD_Write_Char(0x33);
				break;
			case 4:
				if (read_shift_pos() > 0) { // Stops cursor going past first digits
					symbol = 'd'; // Delete Last
					shift_Cursor(0,1); // Shift left one
					LCD_Write_Char(0x20); // Blank Digit
					shift_Cursor(0,1); // Shift left one
				}
				break;
			case 5:
				symbol = 4;
				LCD_Write_Char(0x34);
				break;
			case 6:
				symbol = 5;
				LCD_Write_Char(0x35);
				break;
			case 7:
				symbol = 6;
				LCD_Write_Char(0x36);
				break;
			case 8:
				symbol = '+'; // Add 
				LCD_Write_Char(0x2B);
				break;
			case 9:
				symbol = 7;
				LCD_Write_Char(0x37);
				break;
			case 10:
				symbol = 8;
				LCD_Write_Char(0x38);
				break;
			case 11:
				symbol = 9;
				LCD_Write_Char(0x39);
				break;
			case 12:
				symbol = '-'; // Minus
				LCD_Write_Char(0x2D);
				break;
			case 13:
				shift_state = 1; // Press Shift
				break;
			case 14:
				symbol = 0;
				LCD_Write_Char(0x30);
				break;
			case 15:
				symbol = '.'; // Decimal Point
				LCD_Write_Char(0x2E);
				break;
			case 16:
				symbol = '=';
				LCD_Write_Char(0x3D);
				break;
		}
	}
	
	return symbol;
}

void keypad_LED(int value) {
	
	// COLOUR   LED(s) PortF
	// dark     ---    0
	// red      R--    0x02
	// blue     --B    0x04
	// green    -G-    0x08
	// yellow   RG-    0x0A
	// sky blue -GB    0x0C
	// white    RGB    0x0E
	// pink     R-B    0x06

	switch (value) {
		case 1:
			GPIO_PORTF_DATA_R = 0x02; // Red
			break;
		case 2:
			GPIO_PORTF_DATA_R = 0x04; //blue
			break;
		case 3:
			GPIO_PORTF_DATA_R = 0x08; // green
			break;
		case 4:
			GPIO_PORTF_DATA_R = 0x0A; // yelow
			break;
		case 5:
			GPIO_PORTF_DATA_R = 0x0C; // Sky blue
			break;
		case 6:
			GPIO_PORTF_DATA_R = 0x06; // Pink
			break;
		case 7:
			GPIO_PORTF_DATA_R = 0x0E; // White
			break;
		case 8:
			GPIO_PORTF_DATA_R = 0x02; // Red
			break;
		case 9:
			GPIO_PORTF_DATA_R = 0x04; // Blue
			break;
		case 10:
			GPIO_PORTF_DATA_R = 0x08; // green
			break;
		case 11:
			GPIO_PORTF_DATA_R = 0x0A; // Yellow
			break;
		case 12:
			GPIO_PORTF_DATA_R = 0x0C; // Sky Blue
			break;
		case 13:
			GPIO_PORTF_DATA_R = 0x06; // Pink
			break;
		case 14:
			GPIO_PORTF_DATA_R = 0x0E; // White
			break;
		case 15:
			GPIO_PORTF_DATA_R = 0x02; // Red
			break;
		case 16:
			GPIO_PORTF_DATA_R = 0x04; // Blue
			break;
		default:
			GPIO_PORTF_DATA_R = 0x00; // Dark
	}
}
void keypad_Notes(int value) {
	
	// COLOUR   LED(s) PortF
	// dark     ---    0
	// red      R--    0x02
	// blue     --B    0x04
	// green    -G-    0x08
	// yellow   RG-    0x0A
	// sky blue -GB    0x0C
	// white    RGB    0x0E
	// pink     R-B    0x06
	float duration = 0.2;
	
	switch (value) {
		case 1:
			play_notes(0xA6,duration);
			break;
		case 2:
			play_notes(0xB6,duration);
			break;
		case 3:
			play_notes(0xC7,duration);
			break;
		case 4:
			break;
		case 5:
			play_notes(0xD7,duration);
			break;
		case 6:
			play_notes(0xE7,duration);
			break;
		case 7:
			play_notes(0xF7,duration);
			break;
		case 8:
			break;
		case 9:
			play_notes(0x07,duration);
			break;
		case 10:
			play_notes(0xA7,duration);
			break;
		case 11:
			play_notes(0xB7,duration);
			break;
		case 12:
			break;
		case 13:
			play_the_Lick(2);
			break;
		case 14:
			play_notes(0xC8,duration);
			break;
		case 15:
			break;
		case 16:
			break;
	}
}