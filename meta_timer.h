#pragma once

/*
* @class MetaTimer
* @brief a simple timer
* @example
*	MetaTimer *myTimer = new MetaTimer();
*	...
*	myTimer->launch(100500);
*	...
*	if (myTimer->isTimeOut()) {
*		sayHello();
*	}
*/
class MetaTimer
{
public:
	typedef unsigned long (*tick_counter_t)(void);
	MetaTimer(tick_counter_t tick_counter);
	void launch(const unsigned long &offsetMS);
	bool is_time_out();
	virtual bool is_running() const;

	virtual ~MetaTimer() = default;
protected:
	tick_counter_t _tick_counter;
	unsigned long _offsetMS;
	unsigned long _start_time;
	bool _is_running;
};
