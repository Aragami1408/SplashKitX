#pragma once

#include <skx_defines.h>
#include <skx_game_types.h>

struct GameState {
	f32 delta_time;
};

b8 game_initialize(SKXGame *game_inst);
b8 game_update(SKXGame *game_inst, f32 delta_time);
b8 game_render(SKXGame *game_inst, f32 delta_time);
void game_on_resize(SKXGame *game_inst, u32 width, u32 height);
