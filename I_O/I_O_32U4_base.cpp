#include <avr/io.h>
#include <stdbool.h>

#include "I_O_32U4_base.h"

#define MASK(X) (1ul<<(X))

button_state_machine::button_state_machine()
{
	machine_state = WAIT_FOR_PRESS;
}

_Bool button_state_machine::debounce_state_machine(_Bool input_state)
{
	uint32_t current_time = counter;
	
	switch(machine_state)
	{
		case WAIT_FOR_PRESS:
		if(input_state==1)
		{
			time_entered_state = current_time;

			machine_state = CONFIRM_PUSHED;

		}
		break;
		
		case CONFIRM_PUSHED:

		if(input_state==0)
		{
			machine_state = WAIT_FOR_PRESS;
		}
		else if((time_entered_state-current_time)>=6000000)
		{
			machine_state = WAIT_FOR_RELEASE;
			return 1;
		}
		break;
		
		case WAIT_FOR_RELEASE:
		if(input_state==0)
		{
			machine_state = CONFIRM_RELEASED;
		}
		break;
		
		case CONFIRM_RELEASED:
		if(input_state==1)
		{
			machine_state = WAIT_FOR_RELEASE;
		}
		else if((time_entered_state-current_time)>=6000000)
		{
			machine_state = WAIT_FOR_PRESS;
		}
		break;
		
	}
	counter++;
	return 0;
}

button_base::button_base()
{	
	//config_button();
}

void button_base::config_button()
{
		//DDR &= ~(MASK(PIN));
		//PORT|= MASK(PIN);
}

_Bool button_base::is_pressed()
{
	//return!(PIN_REF & MASK(PIN));	
}

_Bool button_base::is_not_pressed()
{
	return!(is_pressed());
}

_Bool button_base::debounce_press()
{
	//this calls its is_pressed which does nothing, so need to re-define this in the second layer
	return press_state.debounce_state_machine(is_pressed());	
}

output_base::output_base()
{
	config_pin();
}

void output_base::config_pin()
{
	//DDR_set |= MASK(PIN_set);
	set_low();
}

void output_base::set_high()
{
	//PORT_set |= MASK(PIN_set);
}

void output_base::set_low()
{
	//PORT_set &= ~MASK(PIN_set);
}



