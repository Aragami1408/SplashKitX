#include <skx_entry.h>
#include <core/skx_memory.h>

#include "game.h"


b8 skx_create_game(SKXGame *out_game) {
	// Application configuration.
	out_game->app_config.start_pos_x = 100;
	out_game->app_config.start_pos_y = 100;
	out_game->app_config.start_width = 1280;
	out_game->app_config.start_height = 720;
	out_game->app_config.name = "SplashKitX Game Window";

    out_game->update = game_update;
    out_game->render = game_render;
    out_game->initialize = game_initialize;
    out_game->on_resize = game_on_resize;

    // Create the game state
    out_game->state = skx_allocate_memory(sizeof(GameState), SKXMemoryTag::MEMORY_TAG_GAME);

    return TRUE;
}
