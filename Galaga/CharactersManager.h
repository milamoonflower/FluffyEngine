#pragma once
#include "Singleton.h"
#include "Event.h"
#include "IEventListener.h"
#include <memory>
#include <vector>
#include <queue>
#include "Structs.h"
#include "Level.h"

namespace Fluffy
{
	struct IEventParam;
	class Scene;
	class GameObject;
}

class CharactersManager final : public Fluffy::Component, public Fluffy::ComponentSingleton<CharactersManager>, public Fluffy::IEventListener
{
public:
	CharactersManager(Fluffy::GameObject* pOwner);
	~CharactersManager() = default;

	CharactersManager(const CharactersManager&) = delete;
	CharactersManager(CharactersManager&&) = delete;
	CharactersManager& operator=(const CharactersManager&) = delete;
	CharactersManager& operator=(CharactersManager&&) = delete;

	void StartLevel1();

	void Update(const float deltaTime) override;

	void CreatePlayerCharacters(class Fluffy::Scene& scene);
	class EnemyCharacter* SpawnEnemy(const EnemyEnteringData& data);
	void KillEnemy(int killerIndex);
	void OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* param) override;

	class PlayerCharacter* GetPlayer(const int playerIndex);
	inline Fluffy::Event& GetOnPlayerKilled() { return m_OnPlayerKilled; }
	inline Fluffy::Event& GetOnEnemyKilled() { return m_OnEnemyKilled; }

protected:
	void RegisterInstance() override;

private:
	Level m_Level{};
	Fluffy::Event m_OnPlayerKilled{ Fluffy::EventType::OnPlayerKilled };
	Fluffy::Event m_OnEnemyKilled{ Fluffy::EventType::OnEnemyKilled };

	std::vector<class PlayerCharacter*> m_PlayerCharacters{};
	std::vector<class EnemyCharacter*> m_Enemies{};

	const static float PLAYER_RESPAWN_TIMER_DURATION;

	float m_PlayerRespawnTimers[2]{ 0.0f };

	void PurgeDestroyedCharacters();
	void StartPlayerRespawnTimer(const int playerIndex);
	void UpdatePlayerRespawnTimers(const float deltaTime);
	void RespawnPlayer(const int playerIndex);
};
