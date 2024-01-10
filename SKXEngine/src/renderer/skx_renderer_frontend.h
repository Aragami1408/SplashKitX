#pragma once

#include "skx_renderer_types.inl"

struct SKXStaticMeshData;
struct SKXPlatformState;

b8 skx_renderer_initialize(const char *application_name,
                           struct SKXPlatformState *plat_state);
void skx_renderer_shutdown();

void skx_renderer_on_resized(u16 width, u16 height);

b8 skx_renderer_draw_frame(SKXRenderPacket *packet);
