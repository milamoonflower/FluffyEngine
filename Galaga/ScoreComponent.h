#pragma once
#include "Component.h"
#include "IEventListener.h"

namespace Fluffy
{
	class Component;
	class GameObject;
	class IEventListener;
	struct IEventParam;
	class Event;
	class Text;
}

class ScoreComponent final: public Fluffy::Component, Fluffy::IEventListener
{
public:
	ScoreComponent(Fluffy::GameObject* pOwner, int playerIndex, const std::string& fontPath, int fontSize);
	~ScoreComponent();

	void OnNotify(const Fluffy::EventType& eventType, const struct Fluffy::IEventParam* pParam) override;

private:
	const int m_PlayerIndex;
	int m_Score{ 0 };
	class Fluffy::Text* m_pText;

	std::string GetScoreString() const;
};

