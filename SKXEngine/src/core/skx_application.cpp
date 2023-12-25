#include "skx_application.h"
#include "skx_game_types.h"

#include <core/skx_logger.h>
#include <platform/skx_platform.h>
#include <core/skx_memory.h>

struct ApplicationState {
	SKXGame *game_inst;
	b8 is_running;
	b8 is_suspended;
	SKXPlatformState platform;
	i16 width;
	i16 height;
	f64 last_time;
};

static b8 initialized = FALSE;
static ApplicationState app_state;

b8 skx_application_create(SKXGame *game_inst) {
	if (initialized) {
		SKX_ERROR("create() called more than once.");
		return FALSE;
	}

	app_state.game_inst = game_inst;

	// Initialize subsystems.
	skx_initialize_logging();

	// TODO: Remove this
    SKX_FATAL("A test message: %f", 3.14f);
    SKX_ERROR("A test message: %f", 3.14f);
    SKX_WARN("A test message: %f", 3.14f);
    SKX_INFO("A test message: %f", 3.14f);
    SKX_DEBUG("A test message: %f", 3.14f);
    SKX_TRACE("A test message: %f", 3.14f);

	app_state.is_running = TRUE;
	app_state.is_suspended = FALSE;

	SKXPlatformState platform = app_state.platform;

	if (!platform.startup(
				game_inst->app_config.name,
				game_inst->app_config.start_pos_x,
				game_inst->app_config.start_pos_y,
				game_inst->app_config.start_width,
				game_inst->app_config.start_height)) {

		return FALSE;
	}
	
	// Initialize the game
	if(!app_state.game_inst->initialize(app_state.game_inst)) {
		SKX_FATAL("Game failed to initialize");
		return FALSE;
	}

	app_state.game_inst->on_resize(app_state.game_inst, app_state.width, app_state.height);

	initialized = TRUE;

	return TRUE;
}

b8 skx_application_run() {
	SKX_INFO(skx_get_memory_usage_str());
	SKXPlatformState platform = app_state.platform;
	while (app_state.is_running) {
		if (!platform.pump_messages()) {
			app_state.is_running = FALSE;
		}

		if (!app_state.is_suspended) {
			if (!app_state.game_inst->update(app_state.game_inst, (f32)0)) {
				SKX_FATAL("Game update failed, shutting down");
				app_state.is_running = FALSE;
				break;
			}

			// Call the game's render routine
			if (!app_state.game_inst->render(app_state.game_inst, (f32)0)) {
				SKX_FATAL("Game render failed, shutting down");
				app_state.is_running = FALSE;
				break;
			}
		}
	}

	app_state.is_running = FALSE;

    platform.shutdown();

	return TRUE;
}
