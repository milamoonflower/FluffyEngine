#pragma once
#include "Component.h"
#include "IEventListener.h"
#include <memory>

class HealthDisplayComponent final : public Component, IEventListener
{
public:
	HealthDisplayComponent(const std::weak_ptr<class GameObject> pOwner, int playerIndex, const std::string& fontPath, int fontSize);
	~HealthDisplayComponent();
	std::string GetTypeName() override { return typeid(*this).name(); }

	void OnNotify(const EventType& eventType, const struct IEventParam* param) override;

private:
	const int m_PlayerIndex;
	std::shared_ptr<class Text> m_pText;

	std::string GetLivesString() const;
};
