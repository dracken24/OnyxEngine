/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 29-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	      event.cpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "deMemory.hpp"
#include "core/event.hpp"
#include "core/logger.hpp"
#include "container/myArray.hpp"

typedef struct	registeredEvent
{
	void			*listener;
	EventPointer	callback;
}	registeredEvent;

typedef struct	eventCodeEntry
{
	registeredEvent	*events;
}	eventCodeEntry;

// This should be more than enough codes...
#define DE_MAX_MESSAGE_CODES 16384

// State structure.
typedef struct	eventSystemState
{
	// Lookup table for event codes.
	eventCodeEntry registered[DE_MAX_MESSAGE_CODES];
}	eventSystemState;

//
static bl8				is_initialized = false;
static eventSystemState	state;

bl8		EventInit(void)
{
	DE_DEBUG("EventInit: Initializing event system.");
	if (is_initialized == true)
	{
		return false;
	}

	is_initialized = false;
	DE_MemSet(&state, sizeof(state));

	is_initialized = true;

	return true;
}

void EventShutdown(void)
{
	// DE_DEBUG("EventShutdown: Shutting down event system.");
	// Free the events arrays. And objects pointed to should be destroyed on their own.
	for (uint16 i = 0; i < DE_MAX_MESSAGE_CODES; ++i)
	{
		if (state.registered[i].events != 0)
		{
			MyArrayDestroy(state.registered[i].events);
			state.registered[i].events = 0;
		}
	}
}

bl8 EventRegister(uint16 code, void *listener, EventPointer on_event)
{
	DE_DEBUG("EventRegister1: Registering event for code %d", code);
	if (is_initialized == false)
	{
		return false;
	}
	DE_DEBUG("EventRegister2: Registering event for code %d", code);

	if (state.registered[code].events == 0)
	{
		state.registered[code].events = (registeredEvent *)MyArrayCreate(registeredEvent);
	}
	DE_DEBUG("EventRegister3: Registering event for code %d", code);

	uint64 registeredCount = MyArrayLength(state.registered[code].events);
	for (uint64 i = 0; i < registeredCount; ++i)
	{
		if (state.registered[code].events[i].listener == listener)
		{
			DE_DEBUG("EventRegister4: Registering event for code %d", code);
			// TODO: warn
			return false;
		}
	}
	DE_DEBUG("EventRegister5: Registering event for code %d", code);

	// If at this point, no duplicate was found. Proceed with registration.
	registeredEvent event;
	event.listener = listener;
	event.callback = on_event;
	DE_WARNING("EventRegister8: Registering event for code %d", code);
	MyArrayPushEvent(state.registered[code].events, event);
	DE_WARNING("EventRegister7: Registering event for code %d", code);

	return true;
}

bl8 EventUnregister(uint16 code, void *listener, EventPointer pntEvent)
{
	// DE_DEBUG("EventUnregister: Unregistering event for code %d", code);
	if (is_initialized == false)
	{
		return false;
	}

	// On nothing is registered for the code, boot out.
	if (state.registered[code].events == 0)
	{
		// TODO: warn
		return false;
	}

	uint64 registeredCount = MyArrayLength(state.registered[code].events);
	for (uint64 i = 0; i < registeredCount; ++i)
	{
		registeredEvent ev = state.registered[code].events[i];
		if (ev.listener == listener && ev.callback == pntEvent)
		{
			// Found one, remove it
			registeredEvent popped_event;
			MyArrayPopAt(state.registered[code].events, i, &popped_event);
			return true;
		}
	}

	// Not found.
	return false;
}

bl8 EventFire(uint16 code, void *sender, eventContext context)
{
	if (is_initialized == false)
	{
		return false;
	}
	// If nothing is registered for the code, boot out.
	if (state.registered[code].events == 0)
	{
		return false;
	}

	uint64 registered_count = MyArrayLength(state.registered[code].events);
	for (uint64 i = 0; i < registered_count; ++i)
	{
		registeredEvent ev = state.registered[code].events[i];
		if (ev.callback(code, sender, ev.listener, context))
		{
			// Message has been handled, do not send to other listeners.
			return true;
		}
	}

	// Not found.
	return false;
}