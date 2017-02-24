#ifndef __EVENT_QUEUE__
#define __EVENT_QUEUE__

#include "../Main.h"
#include <queue>

enum EVENTTYPES
{
	AUDIO_PLAY_SOUND,
	AUDIO_LOAD_SOUND
};

struct EVENT
{
	EVENTTYPES EventType;
	string argument;
};

class EventQueue
{
	public:
		EventQueue()
		{
			m_events = queue<EVENT>();
		}

		void AddEvent(EVENTTYPES eventType, string argument)
		{
			auto event = EVENT();

			event.EventType = eventType;
			event.argument = argument;

			m_events.push(event);
		}

		EVENT GetEvent()
		{
			auto temp = m_events.front();

			m_events.pop();

			return temp;
		}

		bool IsEmpty() const
		{
			return m_events.empty();
		}
	private:
		queue<EVENT> m_events;
};

#endif