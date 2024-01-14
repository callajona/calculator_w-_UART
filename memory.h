#ifndef _MEMORY_H_
#define _MEMORY_H_ hi

void memory(char symbol);

void inc_shift_pos(void);
void dec_shift_pos(void);
void reset_shift_pos(void);
int read_shift_pos(void);
void reset_all();
void store_previous_ans(float previous_answer);

void display_mem_array(); // TEST CODE

void compute_length();
float calculate();

// Error Check Functions
int multi_symbol_condense(void);
void symbol_at_start(void);
void numerical_error_check(void);
void minus_check(void);
void remove_leading_zeros(void);
void multi_decimal_points(void);
void first_element_symbol_check(void);
void shift_back(int element, int distance);
void error(void);
int check_error_check(int val);

// Array Processing Functions
int concatinate(float array[], int amount);
float decimal_concatinate(float array[], int amount);
int symbol_check(int i);
int seperate_and_concatiate(void);
void merge_symb_numb(int no_numbs);

// Calculation Functions
float maths(float a, float b, char symbol);
float compute(int final_length);

// Password Functions
int password_check(void);

#endif