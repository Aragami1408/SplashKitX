#pragma once
#include <skx_defines.h>

struct SKXClock {
	f64 start_time;
	f64 elapsed;

	// Updates the clock. Should be called just before checking elapsed time.
	// Has no effect on non-started clocks.
	void update();

	// Starts the clock. Resets elapsed time.
	void start();

	// Stops the clock. Does not reset elapsed time.
	void stop();
};


