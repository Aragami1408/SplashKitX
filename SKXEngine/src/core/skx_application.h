#pragma once

#include <skx_defines.h>

struct SKXGame;

// Application configuration
struct SKXApplicationConfig {
public:
	// Window starting position x-axis, if applicable
	i16 start_pos_x;

	// Window starting position y-axis, if applicable
	i16 start_pos_y;

	// Window starting width, if applicable
	i16 start_width;

	// Window starting height, if applicable
	i16 start_height;

	// The application name used in windowing, if applicable
	char *name;

};

SKX_API b8 skx_application_create(SKXGame *game_inst);
SKX_API b8 skx_application_run();
