
//----------------------------------------------------------------------------
// Created By: Jon Calladine
// Date: 26/11/2023

//  Description: Code for LCD functions (inlc. initilaisation and operation)

//  RS = PA3 (0x08)
//  EN = PA2 (0x04)
// DB4 = PB0
// DB5 = PB1 
// DB6 = PB2 
// DB7 = PB3 
//----------------------------------------------------------------------------

#include "Init.h"
#include "PLL.h"
#include "LCD.h"
#include "memory.h"

void EN_pulse(void) {
	EN = 0x04; // Set enable pin high
	SysTick_Wait(40); // 0.5us Delay
	EN = 0x00; // Set enable pin low
	SysTick_Wait(40); // 0.5us Delay
}

void InitLCD(void) {
	// Initilaisation
	
	RS = 0x00; // Writing command
	SysTick_Wait_ms(15); // wait 15ms after power on
	LCD_Write_Nibble(0x3); 
	SysTick_Wait_ms(10); // Wait 10ms after instruction
	LCD_Write_Nibble(0x3); 
	SysTick_Wait_ms(2); // Wait 2ms after instruction
	LCD_Write_Nibble(0x3); 	
	SysTick_Wait_ms(10); // Wait 10ms after instruction
	
	// Set interface to 4-bits length
	LCD_Write_Nibble(0x2); 
	SysTick_Wait_ms(2); // Wait 2ms after instruction
	
	// Select Display line and character font
	// DL = 0, N = 1, F = 0: 4-bit, 2-line, 5x8 font: 0010 1000 = 0x28
	LCD_Write_8_bit_command(0x28); 
	SysTick_Wait_ms(2); // Wait 2ms after instruction

	// Display on
	LCD_Write_8_bit_command(0x0F);
	SysTick_Wait_ms(2); // Wait 2ms after instruction
	
	// Clear Display
	clear_LCD();
	
	// Increase address by one
	LCD_Write_8_bit_command(0x06); 
	SysTick_Wait_ms(2); // Wait 2ms after instruction
}

void LCD_Write_Nibble(char nibble){
	GPIO_PORTB_DATA_R = nibble; // Write Nibble
	EN_pulse(); // Latch the comand
	SysTick_Wait_ms(1); // 1ms Delay after command
}

void LCD_Write_8_bit_command(char data){
	char upperNibble = ((data & 0xF0) >> 4); // Take only the 4 Most significant bits (upper 4 bits)
	char lowerNibble = (data & 0x0F); 			 // Take only the 4 Least significant bits (lower 4 bits)
	
	RS = 0x00; // Writing command
	SysTick_Wait(80); // 1us Delay
	
	LCD_Write_Nibble(upperNibble);
	LCD_Write_Nibble(lowerNibble);
}

void LCD_Write_8_bit_data(char data){
	char upperNibble = ((data & 0xF0) >> 4); // Take only the 4 Most significant bits (upper 4 bits)
	char lowerNibble = (data & 0x0F); 			 // Take only the 4 Least significant bits (lower 4 bits)
	
	RS = 0x08; // Writing data
	SysTick_Wait(80); // 1us Delay
	
	LCD_Write_Nibble(upperNibble); // Write Upper Nibble
	LCD_Write_Nibble(lowerNibble); // Write Lower Nibble
}
void LCD_Write_Char(char data){
	LCD_Write_8_bit_data(data); // Write Letter
	LCD_Write_8_bit_command(0x06);  // Increase address by one
	inc_shift_pos(); // Increase cursor position by one
}
void clear_LCD(void){
	LCD_Write_8_bit_command(0x01); 
	reset_shift_pos();
	SysTick_Wait_ms(10); // Wait 10ms after instruction
}

void shift_Cursor(char L_R, int num){
	
	// For Loop repeasts instrucion for each shift required
	for (int i = 0; i < num; i++){
		// L_R = 0, Shift Left
		if (L_R == 0) {
			LCD_Write_8_bit_command(0x10); // 0001 0000 - Dont display shift
			dec_shift_pos(); // Decrease cursor position by one
		}
		else {
			LCD_Write_8_bit_command(0x14); // 0001 0100 - Dont display shift
			inc_shift_pos(); // Increase cursor position by one
		}
	}
}
void write_password() {
		// Write Enter Password: 
	LCD_Write_Char(0x45); // Write E
	LCD_Write_Char(0x6E); // Write n	
	LCD_Write_Char(0x74); // Write t
	LCD_Write_Char(0x65); // Write e
	LCD_Write_Char(0x72); // Write r
	LCD_Write_Char(0x20); // Write 
	LCD_Write_Char(0x50); // Write P
	LCD_Write_Char(0x61); // Write a
	LCD_Write_Char(0x73); // Write s
	LCD_Write_Char(0x73); // Write s
	LCD_Write_Char(0x77); // Write w
	LCD_Write_Char(0x6F); // Write o
	LCD_Write_Char(0x72); // Write r
	LCD_Write_Char(0x64); // Write d
	LCD_Write_Char(0x3A); // Write :
	shift_Cursor(1,5);
	
}
void LCD_Test(void){	
	// Display the word calculator in the centre of the screen
	
	shift_Cursor(1,4); // Shift cursor across by 5 to move word to centre
	
	// Write C
	LCD_Write_8_bit_data(0x43); // Write Letter
	LCD_Write_8_bit_command(0x06);  // Increase address by one
	
	// Write A
	LCD_Write_8_bit_data(0x41);
	LCD_Write_8_bit_command(0x06); 
	
	// Write L
	LCD_Write_8_bit_data(0x4C);
	LCD_Write_8_bit_command(0x06); 
	
	// Write C
	LCD_Write_8_bit_data(0x43);
	LCD_Write_8_bit_command(0x06); 
	
	// Write U
	LCD_Write_8_bit_data(0x55);
	LCD_Write_8_bit_command(0x06); 
	
	// Write L
	LCD_Write_8_bit_data(0x4C);
	LCD_Write_8_bit_command(0x06); 
	
	// Write A
	LCD_Write_8_bit_data(0x41);
	LCD_Write_8_bit_command(0x06); 
	
	// Write T
	LCD_Write_8_bit_data(0x54);
	LCD_Write_8_bit_command(0x06); 
	
	// Write O
	LCD_Write_8_bit_data(0x4F);
	LCD_Write_8_bit_command(0x06); 
	
	// Write R
	LCD_Write_8_bit_data(0x52);
	LCD_Write_8_bit_command(0x06); 
}