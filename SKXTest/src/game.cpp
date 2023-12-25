#include "game.h"

#include <core/skx_logger.h>

b8 game_initialize(SKXGame *game_inst) {
    SKX_DEBUG("game_initialize() called!");
    return TRUE;
}
b8 game_update(SKXGame *game_inst, f32 delta_time) {
    SKX_DEBUG("game_update() called!");
    return TRUE;
}
b8 game_render(SKXGame *game_inst, f32 delta_time) {
    SKX_DEBUG("game_render() called!");
    return TRUE;
}
void game_on_resize(SKXGame *game_inst, u32 width, u32 height) {
    SKX_DEBUG("game_on_resize() called!");
}
