// ----------------------------------------------------------------------------------
// Created By: Jon Calladine
// Date: 26/11/2023

//  Description: This File is used to ititialise ports A,B,D and E

// ----------------------------------------------------------------------------------

#include "Init.h"
#include "PLL.h"

// 3) Subroutines Section
void Init_portA(void){ 
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000001;		// Active Clock for PortA
	delay = SYSCTL_RCGC2_R;					// Delay to allow clk to establish
	GPIO_PORTA_LOCK_R = 0x4C4F434B; // Unlock CR Register for PORTA
	GPIO_PORTA_CR_R = 0x1C; 				// Allow changes to PA2-4
	GPIO_PORTA_DIR_R = 0x1C; 				// PA2-4 = Output (0001.1100)
	GPIO_PORTA_AMSEL_R = 0x00;			// Disable Analouge function on PortA
	GPIO_PORTA_AFSEL_R = 0x00;			// Disable Alternate function on PortA
	GPIO_PORTA_PCTL_R = 0x00000000; // Clear PCTL Regster
	GPIO_PORTA_PUR_R = 0x00; 				// No PUR set on PortA pins
	GPIO_PORTA_DEN_R = 0x1C; 				// Enable digital I/0 on PA2-4
	
}
void Init_portB(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000002;		// Active Clock for PortB
	delay = SYSCTL_RCGC2_R;					// Delay to allow clk to establish
	GPIO_PORTB_LOCK_R = 0x4C4F434B; // Unlock CR Register for PORTB
	GPIO_PORTB_CR_R = 0x0F; 				// Allow changes to PB0-3
	GPIO_PORTB_DIR_R = 0x0F; 				// PB0-3 = Outputs
	GPIO_PORTB_AMSEL_R = 0x00;			// Disable Analouge function on PortB
	GPIO_PORTB_AFSEL_R = 0x00;			// Disable Alternate function on PortB
	GPIO_PORTB_PCTL_R = 0x00000000; // Clear PCTL Regster
	GPIO_PORTB_PUR_R = 0x00; 				// No PUR set on PortB pins
	GPIO_PORTB_DEN_R = 0x0F; 				// Enable digital I/0 on PB0-3
}
void Init_portD(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000008;		// Active Clock for PortD
	delay = SYSCTL_RCGC2_R;					// Delay to allow clk to establish
	GPIO_PORTD_LOCK_R = 0x4C4F434B; // Unlock CR Register for PORTD
	GPIO_PORTD_CR_R = 0x0F; 				// Allow changes to PD0-3
	GPIO_PORTD_DIR_R = 0x00; 				// PD0-3 = inputs
	GPIO_PORTD_AMSEL_R = 0x00;			// Disable Analouge function on PortD
	GPIO_PORTD_AFSEL_R = 0x00;			// Disable Alternate function on PortD
	GPIO_PORTD_PCTL_R = 0x00000000; // Clear PCTL Regster
	GPIO_PORTD_PUR_R = 0x00; 				// No PUR set on PortD pins
	GPIO_PORTD_DEN_R = 0x0F; 				// Enable digital I/0 on PD0-3
}
void Init_portE(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000010;		// Active Clock for PortE
	delay = SYSCTL_RCGC2_R;					// Delay to allow clk to establish
	GPIO_PORTE_LOCK_R = 0x4C4F434B; // Unlock CR Register for PORTE
	GPIO_PORTE_CR_R = 0x0F; 				// Allow changes to PE0-3
	GPIO_PORTE_DIR_R = 0x0F; 				// PE0-3 = output
	GPIO_PORTE_AMSEL_R = 0x00;			// Disable Analouge function on PortE
	GPIO_PORTE_AFSEL_R = 0x00;			// Disable Alternate function on PortE
	GPIO_PORTE_PCTL_R = 0x00000000; // Clear PCTL Regster
	GPIO_PORTE_PDR_R = 0x0F; 				// Set Pull-Down Resistors on PE0-3
	GPIO_PORTE_DEN_R = 0x0F; 				// Enable digital I/0 on PE0-3
}
void Init_portF(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000020;		// Active Clock for PortE
	delay = SYSCTL_RCGC2_R;					// Delay to allow clk to establish
	GPIO_PORTF_LOCK_R = 0x4C4F434B; // Unlock CR Register for PORTF
	GPIO_PORTF_CR_R = 0x0E; 				// Allow changes to PF3-1
	GPIO_PORTF_DIR_R = 0x0E; 				// PF1-3 = outputs
	GPIO_PORTF_AMSEL_R = 0x00;			// Disable Analouge function on PortF
	GPIO_PORTF_AFSEL_R = 0x00;			// Disable Alternate function on PortF
	GPIO_PORTF_PCTL_R = 0x00000000; // Clear PCTL Regster
	GPIO_PORTF_PUR_R = 0x0E; 				// Set pull down resistors on PF1-3
	GPIO_PORTF_DEN_R = 0x0E; 				// Enable digital I/0 on PF1-3
}