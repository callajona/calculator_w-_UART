// ----------------------------------------------------------------------------------
// Created By: Jon Calladine
// Date: 26/11/2023

//  Description: This File is used to ititialise the PLL clock and systick timer
//   and contains the systick wait funciton

// ----------------------------------------------------------------------------------

#include "PLL.h"

// 3) Subroutines Section
void PLL_Init(void){
  SYSCTL_RCC2_R |=  0x80000000;  // Use RCC2
  SYSCTL_RCC2_R |=  0x00000800;  // Bypass while initialising
  SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)   // clear XTAL field
                 + 0x00000540;   // Configure for 16 MHz crystal
  SYSCTL_RCC2_R &= ~0x00000070;  // Configure for main oscillator source
  SYSCTL_RCC2_R &= ~0x00002000;  // Activate PLL by clearing PWRDN
  SYSCTL_RCC2_R |= 0x40000000;   // Use 400 MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000)  // Clear system clock divider
                  + (4<<22);      // configure for 80 MHz clock 
  while((SYSCTL_RIS_R&0x00000040)==0){};  // Wait for PLLRIS bit (bit toggles high when clk @ correct frequency)
  SYSCTL_RCC2_R &= ~0x00000800; // Enable PLL (by Clearing BYPASS)
}

void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // Disable SysTick during setup
  NVIC_ST_RELOAD_R = 0x00FFFFFF;        // Set RELOAD to max value
  NVIC_ST_CURRENT_R = 0;                // Write to CURRENT register to clear it            
  NVIC_ST_CTRL_R = 0x00000005;          // Enable SysTick with core clock
}

void SysTick_Wait(unsigned long delay){
  NVIC_ST_RELOAD_R = delay-1;  							// Set the number of clk cycles to wait for
  NVIC_ST_CURRENT_R = 0;       							// Write to CURRENT register to clear it
  while((NVIC_ST_CTRL_R&0x00010000) == 0){  // Wait for flag
		// Bit 16 goes high when count reaches 0
  }
}

void SysTick_Wait_ms(unsigned long multiple) {
	multiple = multiple * 80000; // Converts ms time delay to systic value
	SysTick_Wait(multiple);	
	// NB 209ms = max delay
}

void SysTick_Wait_sec(int seconds) {
	for (int j = 0; j < seconds; j++) {
		// Repeat j number of times for specified delay
		for (int i = 0; i < 5; i++) {
			// Repet 5 times for one second
			SysTick_Wait_ms(200);
		}
	}
}