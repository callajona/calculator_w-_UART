#ifndef _LCD_H_
#define _LCD_H_

// ----------------------------------------------------------------------------------
// Created By: Jon Calladine
// Date: 03/12/2023

//  Description: This is the header file containing the function prototypes for the LCD

// ----------------------------------------------------------------------------------

void EN_pulse(void);
void InitLCD(void);
void LCD_Write_Nibble(char);
void LCD_Write_8_bit_command(char);  
void LCD_Write_8_bit_data(char);
void LCD_Write_Char(char data);
void LCD_Test(void);
void clear_LCD(void); // Function to clear LCD Screen
void write_password(void);
void shift_Cursor(char L_R, int no); // Shift cursor along, char = L/R Shift (0 = L, 1 = R). Int = no. moves

#endif