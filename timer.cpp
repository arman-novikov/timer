#include "timer.h"

/*!
 * @brief simple ctor
 * @param [in] on_time_out call_back to be yielded
 *  when time is out
 */
Timer::Timer(MetaTimer::tick_counter_t tick_counter,
		void(*on_time_out)(void*)):
	MetaTimer(tick_counter),
	_call_back(on_time_out), _is_paused(true), _times(0) {}

/*!
 * @brief a procedure to be called in loop
 * @param [in] a parameter for _call_back
 */
void Timer::routine(void *param)
{
  if (this->_is_paused || !Timer::is_time_out())
    return;

  if (this->_times == 0)
    return;

  if (this->_call_back)
    this->_call_back(param);

  if (this->_times > 0)
    --this->_times;

  if (this->_times == 0)
    return;

  MetaTimer::launch(MetaTimer::_offsetMS);
}

/*!
 * @brief simple setter for _call_back
 */
void Timer::set_call_back(void(*on_time_out)(void*))
{
  _call_back = on_time_out;
}

/*
* @brief (re)launching of the timer
* @param [in] offset in ms
* @param [in] times how many times to call on_time_out
* @param [in] on_time_out new callback to carry out if necessary
*/
void Timer::launch(const unsigned long &offset, const int &times,
  void(*on_time_out)(void*))
{
  if (on_time_out)
    _call_back = on_time_out;
  this->_is_paused = false;
  this->_times = times;
  MetaTimer::launch(offset);
}

/*!
 * @brief prevents TaskManager from doing its job
 */
void Timer::pause()
{
  this->_is_paused = true;
}

/*!
 * @brief make TaskManager do its job
 */
void Timer::resume()
{
  this->_is_paused = false;
  MetaTimer::launch(Timer::_offsetMS);
}

/*!
 * @brief interface for checking the current job status
 * @return true if the job is done otherwise false
 * @param [out] times_remained how many times remianed to do the task
 */
bool Timer::is_done(int *times_remained) const
{
  if (times_remained)
    *times_remained = this->_times;
  return this->_times == 0;
}

/*!
 * @brief simple getter for _is_paused
 * @return true if paused otherwise false
 */
bool Timer::is_paused() const
{
  return this->_is_paused;
}

/*!
 * @brief simple setter for Timer::_offsetMS
 * @param [in] offset offset in ms
 * @detail useful for changing offset after launching and during executing
 */
void Timer::set_offset(const unsigned long &offset)
{
  Timer::_offsetMS = offset;
}

/*!
 * @brief simple setter for Timer::_offsetMS
 * @return true if it is running atm othervise false
 */
bool Timer::is_running() const
{
  return !Timer::is_done() && !Timer::is_paused();
}

const int Timer::TIMER_LOOP = -1;
