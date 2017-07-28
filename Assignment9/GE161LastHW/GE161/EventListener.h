#pragma once

#include "Event.h"

namespace GE161
{
	class EventListener
	{
	public:
		EventListener();

		// This method should be overridden by derived classes that
		// want to receive events.
		virtual void onEvent(Event& ev);
	};

}
