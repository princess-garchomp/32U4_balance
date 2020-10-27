#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

#include "32u4_encoder.h"

#define MASK(X) (1ul<<(X))

#define XOR_LEFT PB4
	//pin change interrupt PCINT4
#define XOR_Right PE6
	//pin change itnerrupt  INT6?
#define LEFT_B PE2
#define RIGHT_B PF0

//we are using a ISR in this header file to update the encoder counts
//so these need to be volatile so the compiler does not optimise them out
 
//also can not put these variables in the encoder class because the ISR can not be incorporated a class
//the encoder class is is created in the main file, so these variables cannot be part of the class 
 
static volatile bool last_left_A;
static volatile bool last_left_B;
static volatile bool last_right_A;
static volatile bool last_right_B;

static volatile int16_t encouder_count_left=0;
static volatile int16_t encouder_count_right=0;

encoder::encoder()
{
	config_encoder_IO();
	cli();
	config_XOR_interrupts();
	sei();
}

void encoder::config_encoder_IO()
{
	DDRB &= ~(MASK(XOR_LEFT));
	PORTB|= MASK(XOR_LEFT);
	
	DDRE &= ~(MASK(XOR_Right)) & ~(MASK(LEFT_B));
	PORTE|= MASK(XOR_Right)|MASK(LEFT_B);
	
	DDRF &= ~(MASK(RIGHT_B));
	PORTF |= MASK(RIGHT_B);
}

void encoder::config_XOR_interrupts()
{
	//enable XOR_left interrupt
	
	//enable intterupts
    PCICR = MASK(PCIE0);
	//enable interrupt on the correct pin
    PCMSK0 = MASK(PCINT4);
	//clear the itnerrut flap by writting one to it
    PCIFR = MASK(PCIF0);
	
	//enable XOR_right interrupt
	
	//interruopt triggered on state change of INT6
	EICRB=MASK(ISC60);
	//enable the interrpt
	EIMSK=MASK(INT6);
	//clear the interrupt flag by writting one to it
	EIFR=MASK(INTF6);
}

int16_t encoder::get_right_count()
{
	cli();
	int16_t count= encouder_count_right;
	sei();
	return count;
}

int16_t encoder::get_left_count()
{
	cli();
	int16_t count= encouder_count_left;
	sei();
	return count;	
}

void encoder::reset_left_counter()
{
	encouder_count_left=0;
}

void encoder::reset_right_counter()
{
	 encouder_count_right=0;	
}

int16_t encoder::reset_and_get_right_count()
{

	int16_t count = get_right_count();
	reset_right_counter();
	return count;	
}

int16_t encoder::reset_and_get_left_count()
{
	int16_t count = get_left_count();
	reset_left_counter();
	return count;	
}

static _Bool check_XOR_left()
{
	return!(PINB & MASK(XOR_LEFT));
}
static _Bool check_XOR_right()
{
	return!(PINE & MASK(XOR_Right));
}
static _Bool check_B_left()
{
	return!(PINE & MASK(LEFT_B));
}
static _Bool check_B_right()
{
	return!(PINF & MASK(RIGHT_B));
}

ISR(PCINT0_vect)
{
	//this is the ISR for the XOR_left
    _Bool new_left_B =check_B_left();
    _Bool new_left_A = (check_XOR_left() ^ new_left_B);

    encouder_count_left = encouder_count_left + (last_left_A ^ new_left_B) - (new_left_A ^ last_left_B);

    last_left_A = new_left_A;
    last_left_B = new_left_B;
}

ISR(INT6_vect)
{
	//this is the ISR for XOR_right
    _Bool new_right_B = check_B_right();
    _Bool new_right_A = (check_XOR_right() ^ new_right_B);

    encouder_count_right = encouder_count_right + (last_right_A ^ new_right_B) - (new_right_A ^ last_right_B);
	
    last_right_A = new_right_A;
    last_right_B = new_right_B;
}