#include "EventQueue.h"
#include "GE161int.h"


GE161::EventQueue::EventQueue()
{
}


GE161::EventQueue::~EventQueue()
{
}

void GE161::EventQueue::getSDLEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		eventQueue_.push(new GE161::Event(e));
	}
}

void GE161::EventQueue::registerAsListener(int eventType, EventListener* listener)
{
	std::pair<int, EventListener*> p(eventType, listener);
	eventListenerList_.push_back(p);
}

void GE161::EventQueue::callEventListeners()
{
	// for each event in the queue
	while (!eventQueue_.empty())
	{
		Event* e = eventQueue_.front();

		// for each listener
		for (auto p : eventListenerList_)
		{
			int listenedForEventType = p.first;
			EventListener* listener = p.second;
			// if there is a match between this event type and the listener's event type
			if (listenedForEventType == e->type)
			{
				// call the listener's onEvent()
				listener->onEvent(*e);
			}
		}
		// and now we have handled that event
		eventQueue_.pop();
	}

}

void GE161::EventQueue::insertEvent(Event* event)      /// hw 8
{
	eventQueue_.push(event);
}
