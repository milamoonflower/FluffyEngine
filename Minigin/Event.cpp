#pragma once
#include "IEventListener.h"
#include "IEventParam.h"
#include "Event.h"
#include <algorithm>

Event::Event(EventType eventType)
	: m_EventType{ eventType }
{
}

void Event::Invoke(const IEventParam* param)
{
	for (auto& listener : m_Listeners)
		listener->OnNotify(m_EventType, param);
}

void Event::RemoveListener(class IEventListener* pListener)
{
	const auto& it{ std::ranges::find(m_Listeners, pListener) };

	if (it != m_Listeners.end())
	{
		m_Listeners.erase(it);
	}
}
