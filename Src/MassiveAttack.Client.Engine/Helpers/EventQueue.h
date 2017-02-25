#ifndef __EVENT_QUEUE__
#define __EVENT_QUEUE__

#include "../Main.h"
#include <queue>

enum EVENTTYPES
{
	AUDIO_PLAY_SOUND,
	AUDIO_LOAD_SOUND,
	LEVEL_LOAD
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

		void AddEvents(queue<EVENT> events)
		{
			while (!events.empty())
			{
				m_events.push(events.front());

				events.pop();
			}
		}

		ReturnSet<EVENT> GetEvent()
		{
			try {
				if (m_events.empty())
				{
					throw exception("empty queue");
				}

				auto temp = m_events.front();

				m_events.pop();

				return ReturnSet<EVENT>(temp);
			}
			catch (exception ex) {
				return ReturnSet<EVENT>(ex);
			}
		}

		bool IsEmpty() const
		{
			return m_events.empty();
		}

		queue<EVENT> GetEvents() const
		{
			return m_events;
		}
	private:
		queue<EVENT> m_events;
};

#endif