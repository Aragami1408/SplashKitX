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


