
// ----------------------------------------------------------------------------------
// Created By: Jon Calladine
// Date: 03/12/2023

//  Description: This is the header file containing the macros and function prototypes for
//   the initialisation of ports A,B,D and E

// ----------------------------------------------------------------------------------


#ifndef _INIT_H_
#define _INIT_H_

	// Clock Register
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
	
	// Port A
#define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *)0x40004520))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define RS								      (*((volatile unsigned long *)0x40004020))
#define EN							       	(*((volatile unsigned long *)0x40004010))
	
	// Port B
#define GPIO_PORTB_LOCK_R       (*((volatile unsigned long *)0x40005520))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))

// Port D
#define GPIO_PORTD_LOCK_R       (*((volatile unsigned long *)0x40007520))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *)0x40007524))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))
#define GPIO_PORTD_PUR_R        (*((volatile unsigned long *)0x40007510))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))

	// Port E
#define GPIO_PORTE_LOCK_R       (*((volatile unsigned long *)0x40024520))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
#define GPIO_PORTE_PDR_R        (*((volatile unsigned long *)0x40024514))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))

// Port F
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))

	// Funtction Protoypes
// Init Functions
void Init_portA(void);
void Init_portB(void);
void Init_portD(void);
void Init_portE(void);
void Init_portF(void);

// Other functions

#endif