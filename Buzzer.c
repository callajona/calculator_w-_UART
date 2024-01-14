
//----------------------------------------------------------------------------
// Created By: Jon Calladine
// Date: 17/12/2023

//  Description: Code for Buzzer

//----------------------------------------------------------------------------

#include "Buzzer.h"
#include "Init.h"
#include "PLL.h"

void play_tone(float frequency, float duration) {
	float period = 1 / frequency;
	float delay_const = (period / 2) * 80000000; // Times by clock frequency
	
	// Play tone for 0.1 seconds - create value for no. of loops required to reach duration
	int repeats = duration / period;
	
	for (int i = 0; i < repeats; i++) {
		GPIO_PORTA_DATA_R |= 0x10; // PA4 High
		SysTick_Wait(delay_const); // Delay
		GPIO_PORTA_DATA_R &= ~0x10; // PA4 Low
		SysTick_Wait(delay_const); // Delay
	}
}

void play_notes(char note, float duration) {
	// NB 0 represets the note G
	
	// 1 = Ab / G#
	// 2 = Bb / A#
	// 3 = Db / C#
	// 4 = Eb / D#
	// 5 = Gb / F#
	
	if (note == 0x00) {
		play_tone(0,duration); // REST
	}
	if (note == 0xB5) {
		play_tone(987.8,duration); // B6
	}
	else if (note == 0xC6) {
		play_tone(1046.5,duration); // C6
	}
	else if (note == 0xD6) {
		play_tone(1174.66,duration); // D6
	}
	else if (note == 0xE6) {
		play_tone(1318.5,duration); // E6
	}
	else if (note == 0xF6) {
		play_tone(1396.9,duration); // F6
	}
	else if (note == 0x06) {
		play_tone(1568,duration); // G6
	}
	else if (note == 0x16) {
		play_tone(1661.2,duration); // Ab6
	}
	else if (note == 0xA6) {
		play_tone(1760,duration); // A6
	}
	else if (note == 0x26) {
		play_tone(1864.7,duration); // Bb6
	}
	else if (note == 0xB6) {
		play_tone(1975.5,duration); // B6
	}
	else if (note == 0xC7) {
		play_tone(2093,duration); // C7
	}
	else if (note == 0xD7) {
		play_tone(2349,duration); // D7
	}
	else if (note == 0x47) {
		play_tone(2489,duration); // Eb7
	}
	else if (note == 0xE7) {
		play_tone(2637,duration); // E7
	}
	else if (note == 0xF7) {
		play_tone(2793.8,duration); // F7
	}
	else if (note == 0x07) {
		play_tone(3136,duration); // G7
	}
	else if (note == 0xA7) {
		play_tone(3520,duration); // A7
	}
	else if (note == 0xB7) {
		play_tone(3951.1,duration); // B7
	}
	else if (note == 0xC8) {
		play_tone(4186,duration); // C8
	}
}

void play_the_Lick(float speed) {
	// Input is a variable that increases or decreases the speed
	
	speed = 1 / speed; // Invert the vaiable such that a value greater than 1 increases the speed and a value less than 1 decreases the speed
	
	play_notes(0xD7,0.25*speed);
	play_notes(0xE7,0.25*speed);
	play_notes(0xF7,0.25*speed);
	play_notes(0x07,0.25*speed);
	play_notes(0xE7,0.5*speed);
	play_notes(0xC7,0.25*speed);
	play_notes(0xD7,0.75*speed);
}

void play_Mario_Lick(float speed) {
	// G7, F7, Eb7, D7, C7, B6, C7, Eb7, C7, Ab6, F6, D7, C7, Bb6, A6, G6, C6, B5, C6, G6, Bb6, A6, G6, Ab6, Bb6, C7, Eb7, D7, F7. E7, D7, Eb7, C7
	
	speed = 1 / speed;
	
	play_notes(0x07,1 * speed); // G7
	play_notes(0xF7,0.5*speed); // F7
	play_notes(0x47,0.5*speed); // Eb7
	play_notes(0xD7,0.5*speed); // D7
	play_notes(0xC7,0.5*speed); // C7
	play_notes(0xB6,0.5*speed); // B6
	play_notes(0xC7,0.5*speed); // C7
	play_notes(0x47,0.5*speed); // Eb7
	play_notes(0xC7,0.5*speed); // C7
	play_notes(0x16,0.5*speed); // Ab6
	play_notes(0xF6,0.5*speed); // F6
	play_notes(0xD7,0.5*speed); // D7
	play_notes(0xC7,0.5*speed); // C7
	play_notes(0x26,0.5*speed); // Bb6
	play_notes(0xA6,0.5*speed); // A6
	play_notes(0x06,0.5*speed); // G6
	play_notes(0xC6,0.5*speed); // C6
	play_notes(0xB5,0.5*speed); // B5
	play_notes(0xC6,0.5*speed); // C6
	play_notes(0x06,0.5*speed); // G6
	play_notes(0x26,0.5*speed); // Bb6
	play_notes(0xA6,0.5*speed); // A6
	play_notes(0x06,0.5*speed); // G6
	play_notes(0x16,0.5*speed); // Ab6
	play_notes(0x26,0.5*speed); // Bb6
	play_notes(0xC7,0.5*speed); // C7
	play_notes(0x47,0.5*speed); // Eb7
	play_notes(0xD7,0.5*speed); // D7
	play_notes(0xF7,0.5*speed); // F7
	play_notes(0xE7,0.5*speed); // E7
	play_notes(0xD7,0.5*speed); // D7
	play_notes(0x47,0.5*speed); // Eb7
	play_notes(0xC7,0.5*speed); // C7
}
void play_error_jingle(float speed) {
	speed = 1 / speed;

	play_notes(0xC7,4.5*speed);
	play_notes(0x06,4.5*speed);
	play_notes(0xE6,3*speed);
	
	play_notes(0xA6,2*speed);
	play_notes(0xB6,2*speed);
	play_notes(0xA6,2*speed);
	
	play_notes(0x16,2*speed);
	play_notes(0x26,2*speed);
	play_notes(0x16,2*speed);
	
	play_notes(0x06,2*speed);
	play_notes(0xF6,2*speed);
	play_notes(0x06,5*speed);
	
}