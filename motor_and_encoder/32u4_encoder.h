#pragma once
#include <stdbool.h>
class encoder
{
	public:
		encoder();
		
		int16_t get_right_count();
		int16_t get_left_count();
		
		void reset_left_counter();
		void reset_right_counter();
		
		int16_t reset_and_get_right_count();
		int16_t reset_and_get_left_count();
		
	private:	
		void config_encoder_IO();
		void config_XOR_interrupts();
		
		

};

//the logic to configure these pins an inputs is done on creaing an object of class encoder
//thses will only be called by the ISR, which is enabled on creating of an encoder object
//there is no way for these function to be called without the IO being configured
static _Bool check_XOR_left();
static _Bool check_XOR_right();
static _Bool check_B_left();
static _Bool check_B_right();