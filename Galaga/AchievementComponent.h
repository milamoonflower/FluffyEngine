#pragma once
#include "Component.h"
#include "IEventListener.h"
#include <string>

class AchievementComponent : public Fluffy::Component, Fluffy::IEventListener
{
	// Inherited via Component

	std::string GetTypeName() override { return typeid(*this).name(); }
};
