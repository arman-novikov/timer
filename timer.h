#pragma once
#include "meta_timer.h"

/*!
 * @brief class TaskManager for handling with delayed works
 */
class Timer: protected MetaTimer
{
public:
  Timer(tick_counter_t tick_counter, void(*on_time_out)(void*) = nullptr);
  void set_call_back(void(*on_time_out)(void*));
  void set_offset(const unsigned long &offset);
  void launch(const unsigned long &offset, const int &times,
    void(*on_time_out)(void*) = nullptr);
  void pause();
  void resume();
  bool is_done(int *times_remained = nullptr) const;
  bool is_paused() const;
  bool is_running() const override;
  void routine(void *param = nullptr);

  static const int TIMER_LOOP;
  static constexpr int RECURSIVE_RELAUNCH = 2;

  virtual ~Timer() = default;

  Timer(const Timer&) = delete;
  Timer(Timer&&) = delete;
  Timer& operator=(const Timer&)= delete;
  Timer& operator=(Timer&&) = delete;

private:
  void (*_call_back)(void*);
  bool _is_paused;
  int _times;
};
