
//----------------------------------------------------------------------------
// Created By: Jon Calladine
// Date: 18/12/2023

//  Description: Memory of device

//----------------------------------------------------------------------------

#include "stdio.h" // NEW
#include "memory.h"
#include "math.h"
#include "LCD.h"
#include "keypad.h"
#include "Buzzer.h"
#include "PLL.h"

// Global Varibles

volatile int cursor_position;
volatile int mem_array[20];
volatile int length;

int pos = 0;
int array_sel = 0;
volatile int error_check = 0;
volatile float previous_answer = 0;

float hold_array[20];
int symb_array[20];
float numb_array[20];
float total_array[20];

														// Memory Functions
void memory(char symbol) {
	if (symbol == 'd') {
		mem_array[cursor_position] = ' '; // Clear element in the array
	}
	mem_array[cursor_position] = symbol;
}
int read_shift_pos(void) {
	return cursor_position;
}
void inc_shift_pos(void) {
	cursor_position++;
}
void dec_shift_pos(void) {
	cursor_position--;
}
void reset_shift_pos(void) {
	cursor_position = 0;
}
void reset_all() {
	reset_shift_pos();
	length = 0;
	pos = 0;
	array_sel = 0;	
	check_error_check(0);
}
void store_previous_ans(float value) {
	previous_answer = value;
}
																							// Main Calculation Function 
float calculate() {
	
	compute_length();
	shift_back(1,1); // Remove erroneous starting value
	length = length + 1; // Add 1 back to length after removing erroneous start value

	// Error Check - Loop incrementally through them, when error detected, stop looping
  int i = 1;
	float answer = 0; // define answer
	
  while (check_error_check(2) == 0) {
    if (i == 1) {
      multi_decimal_points();
    } 
    else if (i == 2) {
			first_element_symbol_check();
    }
    else if (i == 3) {
			symbol_at_start();
    }
    else if (i == 4) {
      //remove_leading_zeros();
			minus_check();
    }
		else if (i == 5) {
			while (multi_symbol_condense() == 0) {}
		}
    else if (i == 6) {
			display_mem_array();
    }
    else if (i == 7) {
      //numerical_error_check();
    }
		else if (i == 8) {
      break; 
    }
    i++; // Increment i
  }
  
	printf("\n\nPost error check: \n");
	display_mem_array();
	
  if (check_error_check(2) == 0){
    // Calculation
    int no_numbs = seperate_and_concatiate();
    merge_symb_numb(no_numbs);
    int final_length = (no_numbs * 2) - 1;
		
		printf("\n\nTotal Array:");
		for (int i = 0; i < final_length; i++) {
			printf("\n%f", total_array[i]);
		}
		
		numerical_error_check(); // Check for divide by zero
		
		if (check_error_check(2) == 0) {
			answer = compute(final_length);
    printf("\n\nAnswer = %f\n",answer);
		}
  }
	
	return answer;
}
														// Calculation Functions
void compute_length() {
	length = cursor_position - 1;
}
void shift_back(int element, int distance) {
  // Shift array back by distance
  // Pos = first element to be shifted back
  // Distance = number of elements to be shifted back
	// max length of array is 20
  for (int i = element; i < 20; i++) {
    mem_array[i - distance] = mem_array[i];
  }
  length = length - distance;
}
int seperate_and_concatiate(void) {
  int decimal_flag = 0;

  for (int i = 0; i <= length; i++) {
    if (symbol_check(i) == 2) {
      decimal_flag = 1; // set decimal flag high
    }

    if ((symbol_check(i) != 0) || (i == length)) {
      float array[pos]; // Create new array that is the same length as the no. of variables
      for (int i = 0; i <= pos; i++) { 
        array[i] = hold_array[i];
        // put values into the new array that is the correct size - this is necessary for the concatination to wrok properly
      }

      if (decimal_flag == 0) {
        numb_array[array_sel] = concatinate(array, pos); // concatinate values, put into values array
      }
      else if (decimal_flag == 1) {
        numb_array[array_sel] = concatinate(array, pos); // concatinate values, put into values array
        decimal_flag = 2;
      }
      else if (decimal_flag == 2) {
        array_sel--; // Decrease value as decimal added to previous value
        numb_array[array_sel] = numb_array[array_sel] + decimal_concatinate(array, pos); // concatinate and add to previous value
        decimal_flag = 0; // reset decimal flag
      }

      // Add symbols to symbol array
      if ((symbol_check(i) == 1)) {
          symb_array[array_sel] = mem_array[i];
      }

      pos = 0; // Reset position variable
      array_sel++; // increment array select
    }
    else {
      hold_array[pos] = mem_array[i];
      pos++; // Increment function
    } 
  }
  return array_sel; // Return the number of numbers in the array 
}

void merge_symb_numb(int no_numbs) {
  int numb_array_index = 0;
  int symb_array_index = 0;

  for (int i = 0; i < (no_numbs * 2) - 1; i++) {
    if (i % 2 == 0) {
      // If i is even, add number to total array
      if (numb_array[numb_array_index] == 'A') {
        total_array[i] = previous_answer;
				numb_array_index++;
      } 
      else {
        total_array[i] = numb_array[numb_array_index];
        numb_array_index++;
      }
    } 
    else if (i % 2 == 1) {
      // If i is odd, add symbol to total array
      total_array[i] = symb_array[symb_array_index];
      symb_array_index++;
    }
  }
}
int symbol_check(int i) {
  int output;

  if (mem_array[i] == '+' || mem_array[i] == '-' || mem_array[i] == '/' || mem_array[i] == 'x') {
    output = 1;
  } 
  else if (mem_array[i] == '.') {
    output = 2; // Special case when symbol is decimal point
  }
  else {
    output = 0;
  }
  return output;
}

int concatinate(float array[], int amount) {
  int value = 0;
  int j = amount - 1;
  for (int i = 0; i < amount; i++) {
    value = value + (array[i] * pow(10,j));
    j--;
  }
  return value;
}

float decimal_concatinate(float array[], int amount) {
  float value = 0;
  for (int i = 0; i < amount; i++) {
    value = value + (array[i] * (1/pow(10,i+1)));
  }
  return value;
}

float compute(int final_length) {
  int flag = 0;
  float answer = 0;

  if (final_length == 1) {
    answer = total_array[0];
  }

  while (final_length >= 1) {

    if (flag == 1) {
      // search memory for + and -
      for (int i = 0; i < final_length; i++) {
        if (total_array[i] == '+' || total_array[i] == '-') {
            total_array[i-1] = maths(total_array[i-1], total_array[i+1], total_array[i]); // Calculated value and place in array
          for (int j = 0; j < final_length - i - 2; j++) {
            // Loop to shift remaining values backwards
              total_array[i+j] = total_array[i+j+2];
          }
          i = final_length; // End search loop
        }
      }
    }
    else if (flag == 0) {
      flag = 1; // Set flag high. Will remain high if no divide is found
      // Search memory for x and /
      for (int i = 0; i < final_length; i++) {
        if (total_array[i] == '/' || total_array[i] == 'x') {
          flag = 0; // set flag back low as divide has been found
            total_array[i-1] = maths(total_array[i-1], total_array[i+1], total_array[i]); // Calculated value and place in array
          for (int j = 0; j < final_length - i - 2; j++) {
            // Loop to shift remaining values backwards
              total_array[i+j] = total_array[i+j+2];
          }
          i = final_length; // End search loop
        }
      }
      if (flag == 1) {
        // Ensure memory length stays the same as no calculation conducted
          final_length = final_length + 2;
      }
    }
      final_length = final_length - 2;
  }
  answer = total_array[0];
  return answer;
}

float maths(float a, float b, char symbol) {
  float output;

  if (symbol == '+') {output = a + b; }
  else if (symbol == '-') {output = a - b; }
  else if (symbol == '/') {output = a / b; }
  else if (symbol == 'x') {output = a * b; }

  return output;
}

																			// Error Check Code
void minus_check(void) {
  // If divide or plus, then minus symbol:
  // Remove minus and add minus symbol to next number
  // e.g. 4,/,-,3,5,+,2 --> 4,/,-3,-5,+2

  for (int i = 0; i < length; i++) {
    if (symbol_check(i) == 1 && mem_array[i + 1] == '-') {
      int j = i + 2;
      while (symbol_check(j) != 1) { // While next element not a symbol
        if (symbol_check(j) == 2) {
          j++; // if element = decimal point, skip
        }
        else {
          mem_array[j] = 0 - mem_array[j]; // Make number negative and move back
          j++;
        }
        
        if (j == length) {
          break; // stop if end of array reached
        } 
      }
      shift_back(i+2,1); // shift back by 1 at end of process
    }
  }

  if (mem_array[0] == '-') {
    // First element is a minus, so remove it and add minuses to next numbers
    int j = 1;
    while (symbol_check(j) != 1) { // While next element not a symbol
      if (symbol_check(j) == 2) {
        j++; // if element = decimal point, skip
      }
      else {
        mem_array[j] = 0 - mem_array[j]; // Make number negative and move back
        j++;
      }
    }
    shift_back(1,1); // shift back by 1 at end of process
  }
}
void symbol_at_start(void) {
  if (mem_array[0] == '+') {
    shift_back(1,1);
    // Remove plus sign
  }
  // Start with divide or multiply is an error
  else if (mem_array[0] == '/') {
    error();
  }
  else if (mem_array[0] == 'x') {
    error();
  }
  // start with minus delt with in minus_check() function
  
}
int multi_symbol_condense() {
  int check = 1; // Ensures function loops until all symbols are condensed
  // Set high here, and set low if condense found 

  for (int i = 0; i < length; i++) {
    if (symbol_check(i) == 1 && mem_array[i + 1] == '/') {
      error();
      i = length; // End Search
    } 
    else if (symbol_check(i) == 1 && mem_array[i + 1] == 'x') {
      error();
      i = length; // End search
    } 
    else if (symbol_check(i) == 1 && mem_array[i + 1] == '+') {
      // Remove Plus
      shift_back(i + 2, 1); // shift elements left to delete add
      check = 0;
    } 
    else if (mem_array[i] == '-' && mem_array[i + 1] == '-') {
      // Remove second minus, replace first with a plus
      mem_array[i] = '+';
      shift_back(i + 2, 1); // shift elements left
      check = 0;
    } 
    else if (mem_array[i] == '+' && mem_array[i + 1] == '-') {
      // Remove plus
      shift_back(i + 1, 1); // shift elements left to delete add
      check = 0;
    }
  }
  return check;
}

void numerical_error_check() {
  for (int i = 0; i < length; i++) {
    // Divide By zero check
    if (total_array[i] == '/' && total_array[i + 1] == 0) {
      // Error
      error();
    }
  }
}

void remove_leading_zeros(void) {
  for (int i = 0; i < length; i++) {
    if (mem_array[i] == 0) {
      if (mem_array[i-1] > 0 && mem_array[i-1] < 10) {
        // Trailing zeros, therefore increase i to next symbol
        while (symbol_check(i) != 1) { 
          i++;
          if (i == length) {break;}
        }
      }
			// Dont remove zeros after decimal point
      else if (symbol_check(i-1) == 2) {
        while (symbol_check(i) != 1) {
          i++;
          if (i == length) {
            break;
          }
        }
      }
      else {
        // Leading zero, therefore remove it
        shift_back(i + 1,1);
        i--; // Decrease i to check location again now array has shifted
      }
    }
  }
}

void multi_decimal_points(void) {
  for (int i = 0; i < length; i++) { // Search array
    if (symbol_check(i) == 2) { // if element = decimal point
      while(symbol_check(i) != 1) { // Loop until next symbol
        if (symbol_check(i+1) == 2) { 
          error();
          break;
        }
        i++;

        if (i == length) {break;} // stop if end of array reached
      }
    }
  }
}

void first_element_symbol_check(void) {
  // If length == 1 and not a number == error;
	
	printf("Length = %d\n",length);
	printf("Symbol = %d\n",mem_array[0]);
  if (length == 1 && symbol_check(0) > 0) {
    error();
  }
}

void error() {
  // Error
  check_error_check(1);
	
	clear_LCD();
	
	shift_Cursor(1,6); // Shift to right by 6 to display error message in the middle
	LCD_Write_Char(0x45); // Write E
	LCD_Write_Char(0x72); // Write r
	LCD_Write_Char(0x72); // Write r
	LCD_Write_Char(0x6F); // Write o
	LCD_Write_Char(0x72); // Write r
	
}

int check_error_check(int val) {
	if (val == 0) {
		error_check = 0;
	}
	else if (val == 1) {
		error_check = 1;
	}
	return error_check;
}

																							// PassWord Code
int password_check() {
	int val;
	int sym;
	int password_check_val = 2;
	
	// int password[] = {0,4,5,6,7,5,3,4}; // password == 4567534
	int password[] = {0,5,5,3}; // password == 553
	
	while (password_check_val == 2) {
		
		// Loop to ensure cursor position cannot go beyond the second row
		while(cursor_position < 20) {shift_Cursor(1,1);}
		
		val = read_keypad();
		
		if (val != 0 && val != 8 && val != 12 && val != 13 && val != 15 && val != 16) {
			// Check Symbol if not special value (except for delete)
			sym = decode_key_press(val);
			if (val != 4) {
				// write to memory if value is a number
				memory(sym); // Add value to memory
				printf("Smybol = %d\n", sym);
				keypad_Notes(val);
			}
		}

		// Equals key pressed
		if (val == 16) {
			compute_length();
			for (int i = 21; i < length + 2; i++) { // offset of 20 introduced to display the word password
				if (password[i-20] != mem_array[i]) {
					// if value incorrect set check to false:
					password_check_val = 0;
				}
			}
			printf("length = %d", length);
			if (length >= 20) { // stops check if nothing entered
				if (password_check_val == 0) {
					// Play error noise
					play_notes(0x06,0.125);
					play_notes(0xC6,0.25);
					clear_LCD();
					reset_all();
					write_password();
				}
				else if (password_check_val != 0) {
					// if not flase, then true
					password_check_val = 1;
					
					// Play correct noise
					play_notes(0x06,0.125);
					play_notes(0xC7,0.25);
				}
			}
		}
	}
	return password_check_val;
}

																							// UART display Code
void display_mem_array() {
	// Start from 1 as there is a leading zero for some reason?
	for (int i = 0; i < length; i++) {
		printf("\n%d", mem_array[i]);
	}
	//printf("\nCursour Position: %d",cursor_position );
	//compute_length();
	//printf("\nLength: %d",length);
	//test??
}
