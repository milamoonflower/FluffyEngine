#pragma once
#include "Component.h"
#include "IEventListener.h"
#include <memory>

namespace Fluffy
{
	class Component;
	class GameObject;
	class Sprite;
	class IEventListener;
	class Event;
	class Text;
}

class HealthDisplayComponent final : public Fluffy::Component, Fluffy::IEventListener
{
public:
	HealthDisplayComponent(Fluffy::GameObject* pOwner, int playerIndex);
	~HealthDisplayComponent();

	void OnNotify(const Fluffy::EventType& eventType, const struct Fluffy::IEventParam* param) override;

private:
	const int m_PlayerIndex;

	std::vector<Fluffy::Sprite*> m_Lives;

	std::string GetLivesString() const;
};
