#pragma once

#include <queue>
#include <vector>
#include <utility>
#include "Game.h"
#include "Event.h"

namespace GE161
{
	class EventQueue
	{
		friend class Game;

	public:
		EventQueue();
		~EventQueue();

	private:
		void getSDLEvents();

		void registerAsListener(int eventType, EventListener* listener);

		void callEventListeners();

		void insertEvent(Event* event);      /// hw 8

		std::queue<Event*> eventQueue_;

		std::vector<std::pair<int, EventListener*>> eventListenerList_;

	};

}

