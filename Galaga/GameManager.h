#pragma once
#include "Singleton.h"
#include "Level.h"
#include "Event.h"
#include "IEventListener.h"
#include "EnemiesSquadron.h"

namespace Fluffy
{
	struct IEventParam;
	class GameObject;
	class Scene;
}

class GameManager final : public Fluffy::Component, public Fluffy::ComponentSingleton<GameManager>, public Fluffy::IEventListener
{
public:
	GameManager(Fluffy::GameObject* pOwner);
	~GameManager();

	GameManager(const GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	GameManager& operator=(GameManager&&) = delete;

	void StartLevel(const int levelIndex);
	void SkipToNextLevel();
	void Update(const float deltaTime) override;
	void OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* param) override;

private:
	Level m_ActiveLevel{};
	int m_CurrentLevelIndex{ 0 };

	EnemiesSquadron m_EnemiesSquadron{};

	const static float PLAYER_RESPAWN_TIMER_DURATION;
	const static int LEVELS_COUNT;

	float m_PlayerRespawnTimers[2]{ 0.0f };

	int m_ShotsFiredCount{ 0 };
	int m_ShotsHitCount{ 0 };

	void StartPlayerRespawnTimer(const int playerIndex);
	void UpdatePlayerRespawnTimers(const float deltaTime);
	void RespawnPlayer(const int playerIndex);
	void TriggerGameOver();
};
