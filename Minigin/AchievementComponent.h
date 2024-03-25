#pragma once
#include "Component.h"
#include "IEventListener.h"

class AchievementComponent : public Component, IEventListener
{
	// Inherited via Component

	std::string GetTypeName() override { return typeid(*this).name(); }
};
