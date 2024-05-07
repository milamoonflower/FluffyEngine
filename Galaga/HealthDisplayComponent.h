#pragma once
#include "Component.h"
#include "IEventListener.h"
#include <memory>

namespace Fluffy
{
	class Component;
	class GameObject;
	class IEventListener;
	class Event;
	class Text;
}

class HealthDisplayComponent final : public Fluffy::Component, Fluffy::IEventListener
{
public:
	HealthDisplayComponent(Fluffy::GameObject* pOwner, int playerIndex, const std::string& fontPath, int fontSize);
	~HealthDisplayComponent();
	std::string GetTypeName() override { return typeid(*this).name(); }

	void OnNotify(const Fluffy::EventType& eventType, const struct Fluffy::IEventParam* param) override;

private:
	const int m_PlayerIndex;
	Fluffy::Text* m_pText;

	std::string GetLivesString() const;
};
