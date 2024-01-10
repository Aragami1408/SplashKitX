#include "skx_renderer_frontend.h"
#include "renderer/skx_renderer_types.inl"
#include "skx_renderer_backend.h"

#include <core/skx_logger.h>
#include <core/skx_memory.h>

// Backend render context
static SKXRendererBackend *backend = 0;

b8 skx_renderer_initialize(const char *application_name,
                           struct SKXPlatformState *plat_state) {

  backend = (SKXRendererBackend *)skx_allocate_memory(
      sizeof(SKXRendererBackend), SKXMemoryTag::MEMORY_TAG_RENDERER);

  // TODO: make this configurable
  skx_renderer_backend_create(RENDERER_BACKEND_TYPE_VULKAN, plat_state,
                              backend);

  if (!backend->initialize(backend, application_name, plat_state)) {
    SKX_ERROR("Renderer backend failed to initialize. Shutting down.");
    return FALSE;
  }

  return TRUE;
}

void skx_renderer_shutdown() {
  backend->shutdown(backend);
  skx_free_memory(backend, sizeof(SKXRendererBackend),
                  SKXMemoryTag::MEMORY_TAG_RENDERER);
}

void skx_renderer_on_resized(u16 width, u16 height) {}

b8 render_begin_frame(f32 delta_time) {
  return backend->begin_frame(backend, delta_time);
}

b8 render_end_frame(f32 delta_time) {
  b8 result = backend->end_frame(backend, delta_time);
  backend->frame_number++;
  return result;
}

b8 skx_renderer_draw_frame(SKXRenderPacket *packet) {
  // If the begin frame returned successfully, mid-frame operations may
  // continue.
  if (render_begin_frame(packet->delta_time)) {
    // End the frame if this fails, it is likely unrecoverable.
    b8 result = render_end_frame(packet->delta_time);

    if (!result) {
      SKX_ERROR("skx_renderer_end_frame failed. Shutting down.");
      return FALSE;
    }
  }

  return TRUE;
}
