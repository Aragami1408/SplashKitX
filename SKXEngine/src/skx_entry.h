#pragma once

#include <core/skx_application.h>
#include <core/skx_logger.h>
#include <core/skx_memory.h>

#include "skx_game_types.h"

// Externally-defined function to create a game.
extern b8 skx_create_game(SKXGame *out_game);

int main(void) {
	skx_initialize_memory();
    // Request the game instance from the application.
    SKXGame game_inst;
    if (!skx_create_game(&game_inst)) {
        SKX_FATAL("Could not create game!")
        return -1;
    }

	// Ensure the function pointers exist
	if (!game_inst.render || !game_inst.update || !game_inst.initialize || !game_inst.on_resize) {
		SKX_FATAL("The game's function pointers must be assigned!");
		return -2;
	}

	// Initialization
    if(!skx_application_create(&game_inst)) {
		SKX_FATAL("Application failed to create!");
		return 1;
	}

	// Begin the game loop
    if(!skx_application_run()) {
		SKX_FATAL("Application did not shutdown gracefully");
		return 2;
	}

	skx_shutdown_memory();

    return 0;
}
