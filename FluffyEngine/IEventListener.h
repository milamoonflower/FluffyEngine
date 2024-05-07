#pragma once
#include "Event.h"
#include "IEventParam.h"

namespace Fluffy
{
	class IEventListener
	{
	public:
		virtual void OnNotify(const EventType& eventType, const IEventParam* pParam = nullptr) = 0;
	};
}

