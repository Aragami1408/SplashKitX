#include <containers/skx_darray.h>
#include <core/skx_event.h>
#include <core/skx_memory.h>

struct RegisteredEvent {
  void *listener;
  PFN_on_event callback;
};

struct EventCodeEntry {
  RegisteredEvent *events;
};

// This should be more than enough codes...
#define MAX_MESSAGE_CODES 16384

// State structure
struct EventSystemState {
  // Lookup table for event codes
  EventCodeEntry registered[MAX_MESSAGE_CODES];
};

static b8 is_initialized = FALSE;
static EventSystemState state;

b8 skx_event_initialize() {
  if (is_initialized == TRUE) {
    return FALSE;
  }

  is_initialized = FALSE;
  skx_zero_memory(&state, sizeof(state));

  is_initialized = TRUE;
  return TRUE;
}

void skx_event_shutdown() {
  // Free the events arrays. And objects pointed to should be destroyed on their
  // own.
  for (u16 i = 0; i < MAX_MESSAGE_CODES; ++i) {
    if (state.registered[i].events != 0) {
      skx_darray_destroy(state.registered[i].events);
      state.registered[i].events = 0;
    }
  }
}

b8 skx_event_register(u16 code, void *listener, PFN_on_event on_event) {
  if (is_initialized == FALSE) {
    return FALSE;
  }

  if (state.registered[code].events == 0) {
    state.registered[code].events =
        (RegisteredEvent *)skx_darray_create(RegisteredEvent);
  }

  u64 registered_count = skx_darray_length(state.registered[code].events);
  for (u64 i = 0; i < registered_count; ++i) {
    if (state.registered[code].events[i].listener == listener) {
      // TODO: warn
      return FALSE;
    }
  }

  // If at this point, no duplicate was found. Proceed with registration
  RegisteredEvent event;
  event.listener = listener;
  event.callback = on_event;
  skx_darray_push(state.registered[code].events, event);

  return TRUE;
}

b8 skx_event_unregister(u16 code, void *listener, PFN_on_event on_event) {
  if (is_initialized == FALSE) {
    return FALSE;
  }

  // On nothing is registered for the code, boot out.
  if (state.registered[code].events == 0) {
    // TODO: warn
    return FALSE;
  }

  u64 registered_count = skx_darray_length(state.registered[code].events);
  for (u64 i = 0; i < registered_count; ++i) {
    RegisteredEvent e = state.registered[code].events[i];
    if (e.listener == listener && e.callback == on_event) {
      // Found one, remove it
      RegisteredEvent popped_event;
      skx_darray_pop_at(state.registered[code].events, i, &popped_event);
      return TRUE;
    }
  }

  // Not found.
  return FALSE;
}

b8 skx_event_fire(u16 code, void *sender, struct SKXEventContext context) {
  if (is_initialized == FALSE) {
    return FALSE;
  }

  // If nothing is registered for the code, boot out.
  if (state.registered[code].events == 0) {
    return FALSE;
  }

  u64 registered_count = skx_darray_length(state.registered[code].events);
  for (u64 i = 0; i < registered_count; ++i) {
    RegisteredEvent e = state.registered[code].events[i];
    if (e.callback(code, sender, e.listener, context)) {
      // Message has been handled, do not send to other listeners.
      return TRUE;
    }
  }

  // Not found.
  return FALSE;
}
