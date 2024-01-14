
// ----------------------------------------------------------------------------------
// Created By: Jon Calladine
// Date: 03/12/2023

//  Description: This is the header file containing the function prototypes for the keypad

// ----------------------------------------------------------------------------------

#ifndef _KEYPAD_H_
#define _KEYPAD_H_

// Funtion Prototypes
char read_keypad(void);
char decode_key_press(int);
void keypad_LED(int value);
void keypad_Notes(int value);

#endif