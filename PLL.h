// ----------------------------------------------------------------------------------
// Created By: Jon Calladine
// Date: 03/12/2023

//  Description: This is the header file containing the macros and function prototypes for
//   - the initialisation of the PLL clock and systick timer
//   - the systick wait funciton

// ----------------------------------------------------------------------------------


#ifndef _PLL_H_
#define _PLL_H_

// 1) Pre-processor Directives Section
//PLL related Defines
#define SYSCTL_RIS_R          (*((volatile unsigned long *)0x400FE050))	
#define SYSCTL_RCC_R          (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RCC2_R         (*((volatile unsigned long *)0x400FE070))	

//SysTick related Defines	
#define NVIC_ST_CTRL_R        (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R      (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R     (*((volatile unsigned long *)0xE000E018))

// 2) Declarations Section
//   Function Prototypes
void PLL_Init(void);
void SysTick_Init(void);
void SysTick_Wait(unsigned long delay);
void SysTick_Wait_ms(unsigned long multiple);
void SysTick_Wait_sec(int seconds);

#endif