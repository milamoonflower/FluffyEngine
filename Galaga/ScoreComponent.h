#pragma once
#include "Component.h"
#include "IEventListener.h"
#include <memory>

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
	ScoreComponent(Fluffy::GameObject* pOwner, int playerIndex, const std::shared_ptr<class Font>& pFont);
	ScoreComponent(Fluffy::GameObject* pOwner, int playerIndex, const std::string& fontPath, int fontSize);
	~ScoreComponent();

	void OnNotify(const Fluffy::EventType& eventType, const struct Fluffy::IEventParam* pParam) override;

private:
	const int m_PlayerIndex;
	int m_Score{ 0 };
	class Fluffy::Text* m_pText;

	int m_IdleBeeKillScore{ 50 };
	int m_MovingBeeKillScore{ 100 };
	int m_IdleButterflyKillScore{ 80 };
	int m_MovingButterflyKillScore{ 160 };
	int m_IdleBossKillScore{ 150 };
	int m_MovingBossKillScore{ 400 };

	std::string GetScoreString() const;
	int CalculateScore(const class EnemyCharacter* pEnemy) const;
};

