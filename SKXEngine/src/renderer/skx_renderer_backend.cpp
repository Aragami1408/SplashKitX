#include "skx_renderer_backend.h"

#include <renderer/vulkan/skx_vulkan_backend.h>

b8 skx_renderer_backend_create(
    enum SKXRendererBackendType type, struct SKXPlatformState *plat_state,
    struct SKXRendererBackend *out_renderer_backend) {

  switch (type) {
  case RENDERER_BACKEND_TYPE_VULKAN: {
    out_renderer_backend->initialize = skx_vulkan_renderer_backend_initialize;
    out_renderer_backend->shutdown = skx_vulkan_renderer_backend_shutdown;
    out_renderer_backend->begin_frame = skx_vulkan_renderer_backend_begin_frame;
    out_renderer_backend->end_frame = skx_vulkan_renderer_backend_end_frame;
    out_renderer_backend->resized = skx_vulkan_renderer_backend_resized;
    return TRUE;
  } break;
  case RENDERER_BACKEND_TYPE_OPENGL: {
    return TRUE;
  } break;
  case RENDERER_BACKEND_TYPE_DIRECTX: {
    return TRUE;
  } break;
  }

  return FALSE;
}

void skx_renderer_backend_destroy(struct SKXRendererBackend *renderer_backend) {
  renderer_backend->initialize = 0;
  renderer_backend->shutdown = 0;
  renderer_backend->begin_frame = 0;
  renderer_backend->end_frame = 0;
  renderer_backend->resized = 0;
}
