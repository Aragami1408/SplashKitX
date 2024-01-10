#pragma once

#include <skx_defines.h>

enum SKXRendererBackendType {
  RENDERER_BACKEND_TYPE_VULKAN,
  RENDERER_BACKEND_TYPE_OPENGL,
  RENDERER_BACKEND_TYPE_DIRECTX,
};

struct SKXRendererBackend {
  struct SKXPlatformState *plat_state;
  u64 frame_number;

  b8 (*initialize)(struct SKXRendererBackend *backend,
                   const char *application_name,
                   struct SKXPlatformState *plat_state);

  void (*shutdown)(struct SKXRendererBackend *backend);

  void (*resized)(struct SKXRendererBackend *backend, u16 width, u16 height);

  b8 (*begin_frame)(struct SKXRendererBackend *backend, f32 delta_time);
  b8 (*end_frame)(struct SKXRendererBackend *backend, f32 delta_time);
};

struct SKXRenderPacket {
  f32 delta_time;
};
