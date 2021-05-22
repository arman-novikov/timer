#include "meta_timer.h"

/*!
 * @brief simple ctor
 */
MetaTimer::MetaTimer(MetaTimer::tick_counter_t tick_counter):
	_tick_counter(tick_counter),
	_offsetMS(0), _start_time(0), _is_running(false)
{}

/*!
* @brief launches the timer
* @param [in] offsetMS offset in mlseconds after
*		which the isTimeOut() method returns true
*/
void MetaTimer::launch(const unsigned long &offsetMS)
{
	_offsetMS = offsetMS;
	_is_running = true;
	_start_time = this->_tick_counter();
}

/*!
* @brief checks if the _offsetMS mlseconds have already passed
* @return bool : true if _offsetMS mlseconds have passed and false vice versa
*/
bool MetaTimer::is_time_out()
{
  if (!this->_is_running)
    return false;

  bool is_expired = this->_tick_counter() - _start_time > _offsetMS;
  if  (is_expired)
    _is_running = false;

	return is_expired;
}

/*!
 * @brief getter for field _is_launched
 * @return true if is launched and the time is not expired
 *    otherwise false
 */
 bool MetaTimer::is_running() const
 {
	 return this->_is_running;
 }
