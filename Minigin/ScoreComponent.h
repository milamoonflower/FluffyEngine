#pragma once
#include "Component.h"
#include "IEventListener.h"

class ScoreComponent final: public Component, IEventListener
{
public:
	ScoreComponent(const std::weak_ptr<class GameObject> pOwner, int playerIndex, const std::string& fontPath, int fontSize);
	~ScoreComponent();
	std::string GetTypeName() override { return typeid(*this).name(); }

	void OnNotify(const EventType& eventType, const struct IEventParam* param) override;

private:
	const int m_PlayerIndex;
	int m_Score{ 0 };
	std::shared_ptr<class Text> m_pText;

	std::string GetScoreString() const;
};

