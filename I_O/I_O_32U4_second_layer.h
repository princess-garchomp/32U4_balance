#include <avr/io.h>
#include "I_O_32U4_base.h"

#define MASK(X) (1ul<<(X))

class button_A : public button_base
{
	public:
	button_A()
	{
		//the constructor for the base class will not use the correct config_button()
		//so need to do it here
		config_button();
	}
	void config_button()
	{
		DDRB &= ~(MASK(PB3));
		PORTB|= MASK(PB3);
	}
	_Bool is_pressed()
	{
		return!(PINB & MASK(PB3));
	}
	_Bool debounce_press()
	{
		return press_state.debounce_state_machine(is_pressed());
	}

};



class yellow_led:public output_base
{
	
	public:
		yellow_led()
		{
			config_pin();
		}
		void config_pin()
		{
			DDRC |= MASK(PC7);
		}

		void set_high()
		{
			PORTC |= MASK(PC7);
		}
		void set_low()
		{
			PORTC &= ~MASK(PC7);
		}
};

class green_led:public output_base
{
	
	public:
	green_led()
	{
		config_pin();
	}
	void config_pin()
	{
		DDRD |= MASK(PD5);
	}

	void set_high()
	{
		//pin is sinking current, so the led pin needs to be configured as gnd to make the led light up
		PORTD &= ~MASK(PD5);
	}
	void set_low()
	{
		PORTD |= MASK(PD5);
	}
};


class red_led:public output_base
{
	
	public:
	red_led()
	{
		config_pin();
	}
	void config_pin()
	{
		DDRB |= MASK(PB0);
	}

	void set_high()
	{
		//pin is sinking current, so the led pin needs to be configured as gnd to make the led light up
		PORTB &= ~MASK(PB0);
	}
	void set_low()
	{
		PORTB |= MASK(PB0);
	}
};

/*
class button_C : public button_base
{
	public:
	button_C()
	{
		//the constructor for the base class will not use the correct config_button()
		//so need to do it here
		config_button();
	}
	void config_button()
	{
		DDRB &= ~(MASK(PB0));
		PORTB|= MASK(PB0);
	}
	_Bool is_pressed()
	{
		return!(PINB & MASK(PB0));
	}
	_Bool debounce_press()
	{
		return press_state.debounce_state_machine(is_pressed());
	}

};
*/