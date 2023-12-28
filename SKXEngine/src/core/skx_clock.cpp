#include <core/skx_clock.h>

#include <platform/skx_platform.h>

void SKXClock::update() {
	if (this->start_time != 0) {
		this->elapsed = skx_platform_get_absolute_time() - this->start_time;
	}
}

void SKXClock::start() {
	this->start_time = skx_platform_get_absolute_time();
	this->elapsed = 0;
}

void SKXClock::stop() {
	this->start_time = 0;
}
