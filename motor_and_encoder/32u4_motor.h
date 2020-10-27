#pragma once

class motor
{
	public:
	motor();
	
	void set_right_speed(int16_t right_speed);
	void set_left_speed(int16_t _left_speed);
	void set_both_speed(int16_t right_speed, int16_t left_speed);
	
	//change pin state
	void reverse_right();
	void reverse_left();
	void reverse_both();
	
	void forward_right();
	void forward_left();
	void forward_both();
	
	void stop_left();
	void stop_right();
	void stop_both();
	
	void start_after_stop_left();
	void start_after_stop_right();
	void start_after_stop_both();
	
	private:
	uint16_t max_speed = 400;
	
	void config_motor_IO();
	void config_motor_timers();	
};