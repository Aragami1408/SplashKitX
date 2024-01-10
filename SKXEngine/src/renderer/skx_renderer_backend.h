#pragma once

#include "skx_renderer_types.inl"

struct SKXPlatformState;

b8 skx_renderer_backend_create(enum SKXRendererBackendType type,
                               struct SKXPlatformState *plat_state,
                               struct SKXRendererBackend *out_renderer_backend);

void skx_renderer_backend_destroy(struct SKXRendererBackend *renderer_backend);
