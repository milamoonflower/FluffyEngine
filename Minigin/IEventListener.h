#pragma once
#include "Event.h"
#include "IEventParam.h"

class IEventListener
{
public:
	virtual void OnNotify(const EventType& eventType, const IEventParam* param = nullptr) = 0;
};

