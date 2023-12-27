#include <core/skx_input.h>
#include <core/skx_event.h>
#include <core/skx_memory.h>
#include <core/skx_logger.h>

struct KeyboardState {
	b8 keys[256];
};

struct MouseState {
	i16 x;
	i16 y;
	u8 buttons[BUTTON_MAX_BUTTONS];
};

struct InputState {
	KeyboardState keyboard_current;
	KeyboardState keyboard_previous;
	MouseState mouse_current;
	MouseState mouse_previous;
};

// Internal input state
static b8 initialized = FALSE;
static InputState state = {};

void skx_input_initialize() {
	skx_zero_memory(&state, sizeof(InputState));
	initialized = TRUE;
	SKX_INFO("Input subsystem initialized");
}

void skx_input_shutdown() {
	// TODO: ADd shutdown routines when needed
	initialized = FALSE;
}

void skx_input_update(f64 delta_time) {
	if (!initialized)
		return;

	// Copy current states to prev states
	skx_copy_memory(&state.keyboard_previous, &state.keyboard_current, sizeof(KeyboardState));
	skx_copy_memory(&state.mouse_previous, &state.mouse_current, sizeof(MouseState));
}

void skx_input_process_key(SKXKeys key, b8 pressed) {
	// Only handle this if the state actually changed
	if (state.keyboard_current.keys[key] != pressed) {
		// Update internal state
		state.keyboard_current.keys[key] = pressed;

		// Fire off an event for immediate processing.
		SKXEventContext context;
		context.data.u16[0] = key;
		skx_event_fire(pressed ? EVENT_CODE_KEY_PRESSED : EVENT_CODE_KEY_RELEASED, 0, context);
	}
}

void skx_input_process_button(SKXButtons button, b8 pressed) {

	if (state.mouse_current.buttons[button] != pressed) {
		// Update internal state
		state.mouse_current.buttons[button] = pressed;

		// Fire off an event for immediate processing.
		SKXEventContext context;
		context.data.u16[0] = button;
		skx_event_fire(pressed ? EVENT_CODE_BUTTON_PRESSED : EVENT_CODE_BUTTON_RELEASED, 0, context);
	}
}

void skx_input_process_mouse_move(i16 x, i16 y) {
	// Only process if actually different
	if (state.mouse_current.x != x || state.mouse_current.y != y) {
		// NOTE: Enable this if debugging
		SKX_DEBUG("Mouse pos: %i, %i!", x, y);

		// Update internal state.
		state.mouse_current.x = x;
		state.mouse_current.y = y;

		// Fire the event
			SKXEventContext context;
			context.data.u16[0] = x;
			context.data.u16[1] = y;
			skx_event_fire(EVENT_CODE_MOUSE_MOVED, 0, context);

	}
}

void skx_input_process_mouse_wheel(i8 z_delta) {
	// NOTE: no internal state to update

	// Fire the event
	SKXEventContext context;
	context.data.u8[0] = z_delta;
	skx_event_fire(EVENT_CODE_MOUSE_WHEEL, 0, context);
}

// keyboard input
b8 skx_input_is_key_down(SKXKeys key) {
    if (!initialized) {
        return FALSE;
    }
    return state.keyboard_current.keys[key] == TRUE;
}

b8 skx_input_is_key_up(SKXKeys key) {
    if (!initialized) {
        return TRUE;
    }
    return state.keyboard_current.keys[key] == FALSE;
}

b8 skx_input_was_key_down(SKXKeys key) {
    if (!initialized) {
        return FALSE;
    }
    return state.keyboard_previous.keys[key] == TRUE;
}

b8 skx_input_was_key_up(SKXKeys key) {
    if (!initialized) {
        return TRUE;
    }
    return state.keyboard_previous.keys[key] == FALSE;
}

// mouse input
b8 skx_input_is_button_down(SKXButtons button) {
    if (!initialized) {
        return FALSE;
    }
    return state.mouse_current.buttons[button] == TRUE;
}

b8 skx_input_is_button_up(SKXButtons button) {
    if (!initialized) {
        return TRUE;
    }
    return state.mouse_current.buttons[button] == FALSE;
}

b8 skx_input_was_button_down(SKXButtons button) {
    if (!initialized) {
        return FALSE;
    }
    return state.mouse_previous.buttons[button] == TRUE;
}

b8 skx_input_was_button_up(SKXButtons button) {
    if (!initialized) {
        return TRUE;
    }
    return state.mouse_previous.buttons[button] == FALSE;
}

void skx_input_get_mouse_position(i32* x, i32* y) {
    if (!initialized) {
        *x = 0;
        *y = 0;
        return;
    }
    *x = state.mouse_current.x;
    *y = state.mouse_current.y;
}

void skx_input_get_previous_mouse_position(i32* x, i32* y) {
    if (!initialized) {
        *x = 0;
        *y = 0;
        return;
    }
    *x = state.mouse_previous.x;
    *y = state.mouse_previous.y;
}

