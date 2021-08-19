### Usage
````


void my_call_back(void* console) {
	*reinterpret_cast<Stream*>(console) << "heartbeat" << etl::endl;
}

Timer heartbeater{HAL_GetTick, my_call_back}; // pass a call_back
Timer no_name_task{HAL_GetTick}; // just init a timer

//...
heartbeater.launch(2000UL, Timer::TIMER_LOOP); // every 2 seconds print a msg
//...
no_name_task.launch(20UL * 1000UL, 1, [](void*){
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0 );
}); //  toggle a pin in 20s once (1)

// main loop:

heartbeater.routine(reinterpret_cast<void*>(&g_console)); // share MCU time and pass a global var
no_name_task.routine(); // just share MCU time (no arg is required)

```
