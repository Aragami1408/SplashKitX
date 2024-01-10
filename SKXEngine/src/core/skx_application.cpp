#include "skx_application.h"
#include "skx_game_types.h"

#include <core/skx_clock.h>
#include <core/skx_event.h>
#include <core/skx_input.h>
#include <core/skx_logger.h>
#include <core/skx_memory.h>

#include <platform/skx_platform.h>

#include <renderer/skx_renderer_frontend.h>

struct ApplicationState {
  SKXGame *game_inst;
  b8 is_running;
  b8 is_suspended;
  SKXPlatformState platform;
  i16 width;
  i16 height;
  SKXClock clock;
  f64 last_time;
};

static b8 initialized = FALSE;
ApplicationState app_state;

b8 application_on_event(u16 code, void *sender, void *listener_inst,
                        SKXEventContext context) {
  switch (code) {
  case EVENT_CODE_APPLICATION_QUIT: {
    SKX_INFO("EVENT_CODE_APPLICATION_QUIT received, shutting down.\n");
    app_state.is_running = FALSE;
    return TRUE;
  } break;
  }

  return FALSE;
}
b8 application_on_key(u16 code, void *sender, void *listener_inst,
                      SKXEventContext context) {
  if (code == EVENT_CODE_KEY_PRESSED) {
    u16 key_code = context.data.u16[0];
    if (key_code == KEY_ESCAPE) {
      // NOTE: Technically firing an event to itself, but there may be other
      // listeners
      SKXEventContext data = {};
      skx_event_fire(EVENT_CODE_APPLICATION_QUIT, 0, data);

      // Block anything else from processing this.
      return TRUE;
    } else if (key_code == KEY_A) {
      // Example on checking for a key
      SKX_DEBUG("Explicit - A key pressed!");
    } else {
      SKX_DEBUG("'%c' key pressed in window.", key_code);
    }
  } else if (code == EVENT_CODE_KEY_RELEASED) {
    u16 key_code = context.data.u16[0];
    if (key_code == KEY_B) {
      // Example on checking for a key
      SKX_DEBUG("Explicit - B key released!");
    } else {
      SKX_DEBUG("'%c' key released in window.", key_code);
    }
  }

  return FALSE;
}

b8 skx_application_create(SKXGame *game_inst) {
  if (initialized) {
    SKX_ERROR("create() called more than once.");
    return FALSE;
  }

  app_state.game_inst = game_inst;

  // Initialize subsystems.
  skx_initialize_logging();
  skx_input_initialize();

  // TODO: Remove this
  SKX_FATAL("A test message: %f", 3.14f);
  SKX_ERROR("A test message: %f", 3.14f);
  SKX_WARN("A test message: %f", 3.14f);
  SKX_INFO("A test message: %f", 3.14f);
  SKX_DEBUG("A test message: %f", 3.14f);
  SKX_TRACE("A test message: %f", 3.14f);

  app_state.is_running = TRUE;
  app_state.is_suspended = FALSE;

  if (!skx_event_initialize()) {
    SKX_ERROR(
        "Event system failed initialization. Application cannot continue.");
    return FALSE;
  }

  skx_event_register(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
  skx_event_register(EVENT_CODE_KEY_PRESSED, 0, application_on_key);
  skx_event_register(EVENT_CODE_KEY_RELEASED, 0, application_on_key);

  if (!app_state.platform.startup(
          game_inst->app_config.name, game_inst->app_config.start_pos_x,
          game_inst->app_config.start_pos_y, game_inst->app_config.start_width,
          game_inst->app_config.start_height)) {

    return FALSE;
  }

  if (!skx_renderer_initialize(game_inst->app_config.name,
                               &app_state.platform)) {
    SKX_FATAL("Failed to initialize renderer. Aborting application.");
    return FALSE;
  }

  // Initialize the game
  if (!app_state.game_inst->initialize(app_state.game_inst)) {
    SKX_FATAL("Game failed to initialize");
    return FALSE;
  }

  app_state.game_inst->on_resize(app_state.game_inst, app_state.width,
                                 app_state.height);

  initialized = TRUE;

  return TRUE;
}

b8 skx_application_run() {
  app_state.clock.start();
  app_state.clock.update();
  app_state.last_time = app_state.clock.elapsed;
  f64 running_time = 0;
  u8 frame_count = 0;
  f64 target_frame_seconds = 1.0f / 60;

  SKX_INFO(skx_get_memory_usage_str());

  while (app_state.is_running) {
    if (!app_state.platform.pump_messages()) {
      app_state.is_running = FALSE;
    }

    if (!app_state.is_suspended) {
      // Update clock and get delta time.
      app_state.clock.update();
      f64 current_time = app_state.clock.elapsed;
      f64 delta = (current_time - app_state.last_time);
      f64 frame_start_time = skx_platform_get_absolute_time();

      if (!app_state.game_inst->update(app_state.game_inst, (f32)delta)) {
        SKX_FATAL("Game update failed, shutting down");
        app_state.is_running = FALSE;
        break;
      }

      // Call the game's render routine
      if (!app_state.game_inst->render(app_state.game_inst, (f32)delta)) {
        SKX_FATAL("Game render failed, shutting down");
        app_state.is_running = FALSE;
        break;
      }

      // TODO: refactor packet creation
      SKXRenderPacket packet;
      packet.delta_time = delta;
      skx_renderer_draw_frame(&packet);

      // Figure out how long the frame took and, if below
      f64 frame_end_time = skx_platform_get_absolute_time();
      f64 frame_elapsed_time = frame_end_time - frame_start_time;
      running_time += frame_elapsed_time;
      f64 remaining_seconds = target_frame_seconds - frame_elapsed_time;

      if (remaining_seconds > 0) {
        u64 remaining_ms = (remaining_seconds * 1000);

        // If there is time left, give it back to the OS
        b8 limit_frames = FALSE;
        if (remaining_ms > 0 && limit_frames) {
          skx_platform_sleep(remaining_ms - 1);
        }

        frame_count++;
      }

      // NOTE: Input update/state copying should always be handled
      // after any input should be recorded; I.E. before this line.
      // As a safety, input is the last thing to be updated before
      // this frame ends.
      skx_input_update(delta);

      // Update last time
      app_state.last_time = current_time;
    }
  }

  app_state.is_running = FALSE;

  skx_event_unregister(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
  skx_event_unregister(EVENT_CODE_KEY_PRESSED, 0, application_on_key);
  skx_event_unregister(EVENT_CODE_KEY_RELEASED, 0, application_on_key);

  skx_event_shutdown();
  skx_input_shutdown();

  skx_renderer_shutdown();

  app_state.platform.shutdown();

  return TRUE;
}
