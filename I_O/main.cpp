#include "I_O_32U4_second_layer.h"
#include "timer_32U4.h"
#define MASK(X) (1ul<<(X))


int g_counter=1;




int main(void)
{
	button_A button_button_A;
	//button_C button_button_C;
	yellow_led yellow_yellow_led;
	green_led green_green_led;
	red_led red_red_led;

	while (1) 
    {

		
		if(button_button_A.debounce_press())
		{
			g_counter=(g_counter+1)%4;
		}
		else
		{
			
		}
		if(g_counter==1)
		{
			yellow_yellow_led.set_high();
			green_green_led.set_low();
			red_red_led.set_low();			
		}
		else if (g_counter==2)
		{
			yellow_yellow_led.set_low();
			green_green_led.set_high();
			red_red_led.set_low();			
		}
		else if (g_counter==3)
		{
			yellow_yellow_led.set_low();
			green_green_led.set_low();
			red_red_led.set_high();			
		}
		else
		{
			yellow_yellow_led.set_low();
			green_green_led.set_low();
			red_red_led.set_low();
		}
    }
}

