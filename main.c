
#include "stdio.h"   // standard C library 
#include "UART.h"    // functions to implment input/output

#include "Init.h"
#include "PLL.h"
#include "LCD.h"
#include "keypad.h"
#include "Buzzer.h"
#include "output.h"
#include "memory.h"
#include "TExaS.h"

// Prototype for Functions in main
void welcome_screen(void);
void password();
int silent_mode_sel(void);
int precision_sel(void);
void calculator_screen(int silent_sel, int precision);

int main(void){    
	// Initialuse PLL and SysTick
	PLL_Init();
	SysTick_Init();
	
	// Run all Init Functions
	Init_portA();
	Init_portB();
	Init_portD();
	Init_portE();
	Init_portF();
	
	// Initialise LCD
	InitLCD();
	
	UART_Init();    																						// initialize UART for printing
  printf("\nCalculator Program Test\n");
	
	// Menu System
	welcome_screen();
	password();
	int silent_sel = silent_mode_sel();
	int precision = precision_sel();
	calculator_screen(silent_sel,precision);
}

void welcome_screen() {
	clear_LCD();
	LCD_Write_8_bit_command(0x0C); // Turn Cursor off
	shift_Cursor(1,6); // Shift cursor across by 5 to move word to centre
	
	// Write WELCOME
	int delay = 50;
	SysTick_Wait_ms(delay);
	LCD_Write_Char(0x57);	// Write W
	SysTick_Wait_ms(delay);
	LCD_Write_Char(0x45); // Write E
	SysTick_Wait_ms(delay);
	LCD_Write_Char(0x4C); // Write L
	SysTick_Wait_ms(delay);
	LCD_Write_Char(0x43); // Write C
	SysTick_Wait_ms(delay);
	LCD_Write_Char(0x4F); // Write O
	SysTick_Wait_ms(delay);
	LCD_Write_Char(0x4D); // Write M
	SysTick_Wait_ms(delay);
	LCD_Write_Char(0x45); // Write E
	
	// Play Opening Jingle
	play_the_Lick(3);
	
	// 1 Second Delay
	SysTick_Wait_sec(1);
}

void password() {
	
	clear_LCD();
	write_password();
	
	LCD_Write_8_bit_command(0x0F); // Turn Cursor On
	while (password_check() == 0) {} // Loop untill password is correct
	LCD_Write_8_bit_command(0x0C); // Turn Cursor off
	
	clear_LCD();
	reset_all();
}

int silent_mode_sel(void) {
	
	// Variables
	int value;
	int check = 0;
	
	clear_LCD();
	
	// Display) 1: Silent 
	LCD_Write_Char(0x31); // Write 1
	LCD_Write_Char(0x3A); // Write :
	LCD_Write_Char(0x20); // Write 
	LCD_Write_Char(0x53); // Write S
	LCD_Write_Char(0x69); // Write i
	LCD_Write_Char(0x6C); // Write l
	LCD_Write_Char(0x65); // Write e
	LCD_Write_Char(0x6E); // Write n
	LCD_Write_Char(0x74); // Write t
	
	shift_Cursor(1,11); // Shift cursor across by 1 to move next word to new line
	
	// Display) 2: Musical
	LCD_Write_Char(0x32); // Write 2
	LCD_Write_Char(0x3A); // Write :
	LCD_Write_Char(0x20); // Write 
	LCD_Write_Char(0x4D); // Write M
	LCD_Write_Char(0x75); // Write u
	LCD_Write_Char(0x73); // Write s
	LCD_Write_Char(0x69); // Write i
	LCD_Write_Char(0x63); // Write c
	LCD_Write_Char(0x61); // Write a
	LCD_Write_Char(0x6C); // Write l
	
	// Poll keypad unitl key pressed
	while (check == 0) {
		value = read_keypad(); // Read keypad
		if (value == 1) {
			check = 1; // Stop While loop
		}
		else if (value == 2) {
			check = 1; // Stop While loop	
		}
	}
	
	return value;
}

int precision_sel(void) {
	int precision = 0;
	int check = 0;
	int value;

	clear_LCD();
	
	// Write Select Precision
	shift_Cursor(1,2); // Shift text to centre
	LCD_Write_Char(0x53); // Write S
	LCD_Write_Char(0x65); // Write e
	LCD_Write_Char(0x6C); // Write l
	LCD_Write_Char(0x65); // Write e
	LCD_Write_Char(0x63); // Write c
	LCD_Write_Char(0x74); // Write t
	LCD_Write_Char(0x20); // Write 
	
	LCD_Write_Char(0x50); // Write P
	LCD_Write_Char(0x72); // Write r
	LCD_Write_Char(0x65); // Write e
	LCD_Write_Char(0x63); // Write c
	LCD_Write_Char(0x69); // Write i
	LCD_Write_Char(0x73); // Write s
	LCD_Write_Char(0x69); // Write i
	LCD_Write_Char(0x6F); // Write o
	LCD_Write_Char(0x6E); // Write n
	
	// Write "(1-9): "
	shift_Cursor(1,2); // Shift cursor across to new line
	LCD_Write_Char(0x28); // Write (
	LCD_Write_Char(0x31); // Write 1
	LCD_Write_Char(0x2D); // Write -
	LCD_Write_Char(0x39); // Write 9
	LCD_Write_Char(0x29); // Write )
	LCD_Write_Char(0x3A); // Write :
	
	// Poll keypad unitl key pressed
	while (check == 0) {
		value = read_keypad(); // Read keypad
			if (value%4 != 0 && value != 15 && value != 13) { // value not equal to special function
			precision = decode_key_press(value); // Decode
			if (precision >= 0 && precision <= 9) {
				check = 1; // Stop While loop
			}
		}
	}
	
	clear_LCD();
	
	return precision;
}

void calculator_screen(int silent_sel, int precision) {
	// Declair Variables
	int value = 0;
	char symbol = 0;
	
	LCD_Write_8_bit_command(0x0F); // Turn Cursor On
	
	// Main Loop
	while(1) {
		value = read_keypad();
		symbol = decode_key_press(value);

		if (value != 0 && value != 13 && value != 4 && symbol != 'd') { // null value
			// Only write when keypressed and symbol is not delete
			memory(symbol); // Add value to memory
			//printf("\nSymbol: %d",symbol); 	 												// Test code
			//printf("\nValue: %d",value); 	 			  									// Test code
		}
		
		// Only Play tone if calculator is not in silent
		if (silent_sel == 2) {
			keypad_Notes(value);
		}
		keypad_LED(value);	// LEDs on board
		
		// Equals Key Pressed
		if (value == 16) {	
			// calculate answer, reset system, output answer
			LCD_Write_8_bit_command(0x0C); // Turn Cursor off
			float answer = calculate();
			
			if (silent_sel == 2) {
				if (check_error_check(2) == 0) { // If not an error
					play_Mario_Lick(5);
				}
				if (check_error_check(2) == 1) { // If  an error
					play_error_jingle(10);
				}
			}
			
			if (check_error_check(2) == 0) { // If  not an error
				output_answer(answer,precision); // Output answer
			}
			
			store_previous_ans(answer); // Store previous answer
			while (read_keypad() == 0){} // Wait for key to be pressed and reset the system
			clear_LCD(); // Clear LCD
			reset_all(); // Reset memory elements
			LCD_Write_8_bit_command(0x0F); // Turn Cursor On
		}
	}
} 