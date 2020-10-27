#include <avr/io.h>
#include <stdint.h>

#include "32u4_motor.h"

#define MASK(X) (1ul<<(X))

//OC1B output comnpare and PEM output B for timer1
#define LEFT_MOTOR_PWM PB6
#define LEFT_MOTOR_DIRECTION PB2

//OC1A output compare and PWM ouptu A for timer1
#define RIGHT_MOTOR_PWM PB5
#define RIGHT_MOTOR_DIRECTION PB1

#define MAX_SPEED 400
#define MIN_SPEED 0
motor::motor()
{
	config_motor_timers();
	config_motor_IO();
	forward_both();
}

void motor::config_motor_timers()
{
		//we are in Phase and Frequency Correct mode
		//this cleares the OCR registers on counting up and sets them on counting down compare match 
		TCCR1A |= MASK(COM1A1)|MASK(COM1B1);
		//WGM13 PWM, Phase and Frequency Correct
		//CS10 is setting the prescaller, no prescaller
		TCCR1B |= MASK(WGM13)|MASK(CS10);
		
		/*ICR1 acts as the new maximum that the counter can count to*/
		/*this allows the OCR1A to not act as the value to be counting to */
		/*OCR1A now acts as a PWM*/
		
		//input compare register
		ICR1 = 400;
		//output compare registers
		OCR1A=0;
		OCR1B=0;
}

void motor::config_motor_IO()
{
	DDRB |= MASK(LEFT_MOTOR_PWM)|MASK(LEFT_MOTOR_DIRECTION)|MASK(RIGHT_MOTOR_PWM)|MASK(RIGHT_MOTOR_DIRECTION);
}

void motor::set_right_speed(int16_t right_speed)
{
	if(right_speed<MIN_SPEED)
	{
		right_speed = MIN_SPEED;
	}
	else if(right_speed>MAX_SPEED)
	{
		right_speed = MAX_SPEED;
	}
	OCR1A=right_speed;
}

void motor::set_left_speed(int16_t left_speed)
{
	if(left_speed<MIN_SPEED)
	{
		left_speed = MIN_SPEED;
	}
	else if(left_speed>MAX_SPEED)
	{
		left_speed = MAX_SPEED;
	}
	OCR1B=left_speed;	
}

void motor::set_both_speed(int16_t right_speed, int16_t left_speed)
{
	set_left_speed(left_speed);
	set_right_speed(right_speed);
}

void motor::reverse_right()
{
	PORTB &= ~MASK(RIGHT_MOTOR_DIRECTION);
}

void motor::reverse_left()
{
	PORTB &= ~MASK(LEFT_MOTOR_DIRECTION);
}

void motor::reverse_both()
{
	reverse_left();
	reverse_right();
}

void motor::forward_right()
{
	PORTB|= MASK(RIGHT_MOTOR_DIRECTION);
}

void motor::forward_left()
{
	PORTB|= MASK(LEFT_MOTOR_DIRECTION);
}

void motor::forward_both()
{
	forward_left();
	forward_right();
}

void motor::stop_left()
{
	DDRB &= ~(MASK(LEFT_MOTOR_PWM));
}

void motor::stop_right()
{
	DDRB &= ~(MASK(RIGHT_MOTOR_PWM));	
}

void motor::stop_both()
{
	stop_left();
	stop_right();
}

void motor::start_after_stop_left()
{
	DDRB |= MASK(LEFT_MOTOR_PWM);	
}

void motor::start_after_stop_right()
{
	DDRB |= MASK(RIGHT_MOTOR_PWM);	
}

void motor::start_after_stop_both()
{
	start_after_stop_left();
	start_after_stop_right();
}