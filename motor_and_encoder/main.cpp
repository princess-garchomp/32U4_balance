#include <stdint.h>

#include "32u4_motor.h"
#include "32u4_encoder.h"

typedef enum {forward,backard,stop} direction;
	direction state = forward;

int main(void)
{
motor motor_stuff;
encoder encoder_stuff;
    while (1) 
    {
		/*
		//what follows is tests of all of the motor functionsd
		uint32_t i;
		//motor_stuff.set_left_speed(100);
		//motor_stuff.set_right_speed(100);
		//motor_stuff.set_both_speed(100,100);
		
		while(i<600000)
		{
			i++;
		}
		motor_stuff.set_both_speed(60,60);
		while(i<600000)
		{
			i++;
		}		
		motor_stuff.reverse_right();
		while(1);
		
		motor_stuff.set_left_speed(60);
		motor_stuff.set_right_speed(60);
		motor_stuff.reverse_right();
		motor_stuff.reverse_left();
		motor_stuff.forward_right();
		motor_stuff.forward_left();

		//motor_stuff.forward_both();
		//motor_stuff.reverse_right();
		//motor_stuff.reverse_left();
		*/
		//what follows is testing the encoder with the motor
// 		motor_stuff.set_both_speed(60,60);
// 		if(encoder_stuff.get_left_count()>3000)
// 		{
// 			motor_stuff.reverse_left();
// 		}
// 		motor_stuff.set_both_speed(60,60);
// 		if(encoder_stuff.get_right_count()>3000)
// 		{
// 			motor_stuff.reverse_right();
// 		}
		
// 		motor_stuff.set_both_speed(60,60);
// 		if(encoder_stuff.get_left_count()>600)
// 		{
// 			motor_stuff.reverse_both();
// 			while(1);
// 		}	

// 		motor_stuff.set_both_speed(60,60);
// 		//encoder_stuff.reset_left_counter();
// 		if(encoder_stuff.reset_and_get_right_count()>30)
// 		{
// 			motor_stuff.reverse_both();
// 			while(1);
// 		}				switch(state)		{			case(forward):				motor_stuff.set_both_speed(70,70);								if(encoder_stuff.get_right_count()==1000)				{					encoder_stuff.reset_right_counter();					state=backard;				}			break;			case(backard):				motor_stuff.reverse_both();				if(encoder_stuff.get_right_count()==(-1000))				{					state=stop;				}							break;			case(stop):				motor_stuff.stop_both();			break;					}
		
	}
}

