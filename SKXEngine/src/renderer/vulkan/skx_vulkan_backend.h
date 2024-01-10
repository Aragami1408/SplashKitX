#pragma once

#include <renderer/skx_renderer_backend.h>

b8 skx_vulkan_renderer_backend_initialize(struct SKXRendererBackend *backend,
                                          const char *application_name,
                                          struct SKXPlatformState *plat_state);

void skx_vulkan_renderer_backend_shutdown(struct SKXRendererBackend *backend);

void skx_vulkan_renderer_backend_resized(struct SKXRendererBackend *backend,
                                         u16 width, u16 height);

b8 skx_vulkan_renderer_backend_begin_frame(struct SKXRendererBackend *backend,
                                           f32 delta_time);
b8 skx_vulkan_renderer_backend_end_frame(struct SKXRendererBackend *backend,
                                         f32 delta_time);
