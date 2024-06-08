#pragma once
#include "Singleton.h"
#include "Level.h"
#include "Event.h"
#include "IEventListener.h"

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
	~GameManager() = default;

	GameManager(const GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	GameManager& operator=(GameManager&&) = delete;

	void CreatePlayerCharacters(Fluffy::Scene* scene);
	void StartLevel1();
	void Update(const float deltaTime) override;
	void OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* param) override;

private:
	Level m_ActiveLevel{};

	const static float PLAYER_RESPAWN_TIMER_DURATION;

	float m_PlayerRespawnTimers[2]{ 0.0f };

	void StartPlayerRespawnTimer(const int playerIndex);
	void UpdatePlayerRespawnTimers(const float deltaTime);
	void RespawnPlayer(const int playerIndex);
};
