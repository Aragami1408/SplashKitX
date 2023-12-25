#pragma once

#include <core/skx_application.h>

class SKXGame {
public:
	// The application configuration
	SKXApplicationConfig app_config;

	// Function pointer to game's initialize function.
	b8 (*initialize)(SKXGame *game_inst);

	// Function pointer to game's update function.
	b8 (*update)(SKXGame *game_inst, f32 delta_time);

	// Function pointer to game's render function.
	b8 (*render)(SKXGame *game_inst, f32 delta_time);

	// Function pointer to handle resizes, if applicable
	void (*on_resize)(SKXGame *game_inst, u32 width, u32 height);

	// Game-specific game state. Create and managed by the game
	void *state;
};


