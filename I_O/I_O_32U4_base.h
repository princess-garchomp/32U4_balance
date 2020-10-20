#pragma once

#include <stdbool.h>
#include <stdint.h>

class button_state_machine
{
	public:
		//constructor for inital machine state
		button_state_machine();
		
		_Bool debounce_state_machine(_Bool input_state);
	private:
		enum {WAIT_FOR_PRESS, CONFIRM_PUSHED, WAIT_FOR_RELEASE, CONFIRM_RELEASED}
			machine_state;	
		uint32_t time_entered_state;
		uint32_t counter;
};

class button_base
{
	public:
		//constructor for using a target pin as an input
		button_base();
		
		_Bool is_pressed();
		_Bool is_not_pressed();
		_Bool debounce_press();
				void config_button();
button_state_machine press_state;
	private:

		//_Bool is_configed;
		//gonna try calling config on construction
		
		//this needs to be public for the second_layer to be able to use it
		//button_state_machine press_state;
};

class output_base
{
	public:
		output_base();
		void set_high();
		void set_low();
		
				void config_pin();
	private:

};
/*
#define PORTB                _SFR_IO8(0x18)


#define _SFR_IO8(io_addr) _MMIO_BYTE((io_addr) + __SFR_OFFSET)

#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define __SFR_OFFSET 0x20

 (*(volatile uint8_t *)((0x18) + 0x20)) = 0x55;

PORTB is a pointer to a volatile uint8_t pointer

	
	//DDRC |= MASK(PC7);
	0x27 |= MASK(PC7);
	//#define DDRC _SFR_IO8(0x07)
	//(*(volatile uint8_t *)((0x07) + 0x20)) |= MASK(PC7);
	// (*(volatile uint8_t *)(0x27)) |= MASK(PC7);
	//the two lines of code are equivelent this is the maro expansion of DDRC


*/