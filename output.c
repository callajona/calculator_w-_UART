
//----------------------------------------------------------------------------
// Created By: Jon Calladine
// Date: 10/01/2023

//  Description: Code for calculating values

//----------------------------------------------------------------------------

#include "output.h"
#include "math.h"
#include "memory.h"
#include "LCD.h"

int output_array[30]; // Array of output seperated into digits

void output_answer(float answer, int precision) {
	int output_array_length = split_number(answer, precision);
	
	// move cursor to last location
	int shift_amount = 39 - read_shift_pos(); // 39 = final box on second row, 
	shift_Cursor(1,shift_amount);
	
	for (int i = 0; i < output_array_length; i++) {
		// display element
		
		if (output_array[i] == '.') {
			LCD_Write_Char(0x2E); // decimal point symbol
		}
		else if (output_array[i] == '-') {
			LCD_Write_Char(0x2D); // Minus symbol
		}
		else {
			switch (output_array[i]) {
			case 0:
				LCD_Write_Char(0x30);
				break;
			case 1:
				LCD_Write_Char(0x31);
				break;
			case 2:
				LCD_Write_Char(0x32);
				break;
			case 3:
				LCD_Write_Char(0x33);
				break;
			case 4:
				LCD_Write_Char(0x34);
				break;
			case 5:
				LCD_Write_Char(0x35);
				break;
			case 6:
				LCD_Write_Char(0x36);
				break;
			case 7:
				LCD_Write_Char(0x37);
				break;
			case 8:
				LCD_Write_Char(0x38);
				break;
			case 9:
				LCD_Write_Char(0x39);
				break;
			}
		}
		shift_Cursor(0,2); // shift back 2
	}
}

int split_number(float value,int precision) {
  float digit = 0;
  int i = 0;
  int trunc_float = 0;
  int negative_flag = 0;
  
  value = round_dp(value, precision); // round value to specified precision
  
  if (value < 0) {
    negative_flag = 1; // Set negative flag high, so minus symbol can be added at end
    value = value * -1; // make number positive
  }
	
	// Disply zero is answer is equal to zero
	if (value == 0) {
		// include zeros after 
		if (precision > 0) {
			for (int j = 0; j < precision; j++) {
				output_array[i] = 0;
				i++;
			}
		}
		output_array[i] = '.';
		i++;
		output_array[i] = 0;
		i++;
  }
  
  while (value != 0) {
		
    digit = fmod(value,10); // Split first digit from value
    
    if ((i == 0) && (fmod(digit * 10,10) != 0)) {  // Check if first value has a decimal
			for (int j = precision; j > 0; j--) {
				trunc_float = fmod(digit * pow(10,j),10);
				output_array[i] = trunc_float;
				i++;
			}

			output_array[i] = '.'; // Add decimal point
			i++;
    }

    trunc_float = digit; // Remove decimal places
    output_array[i] = trunc_float; // Add value to array
    value = (value - digit) / 10; // Remove digit from value and reduce num
    i++;
  }

  if (negative_flag == 1) {
    output_array[i] = '-'; // add negative symbol if required
    i++;
  }
	
	return i; // i = length
}

float round_dp(float value, int dp) {
  value = value * pow(10,dp);
  value = round(value);
  value = value / pow(10,dp);
  return value;
}