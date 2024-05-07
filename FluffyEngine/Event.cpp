#pragma once
#include "IEventListener.h"
#include "IEventParam.h"
#include "Event.h"
#include <algorithm>

namespace Fluffy
{
	Event::Event(EventType eventType)
		: m_EventType{ eventType }
	{
	}

	void Event::Invoke(const IEventParam* pParam)
	{
		for (auto& listener : m_Listeners)
			listener->OnNotify(m_EventType, pParam);
	}

	void Event::RemoveListener(class IEventListener* pListener)
	{
		const auto& it{ std::ranges::find(m_Listeners, pListener) };

		if (it != m_Listeners.end())
		{
			m_Listeners.erase(it);
		}
	}
}
