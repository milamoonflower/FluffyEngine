#pragma once
#include "Singleton.h"
#include "Event.h"
#include "IEventListener.h"
#include "Structs.h"
#include <memory>
#include <vector>
#include <queue>

namespace Fluffy
{
	struct IEventParam;
	class Scene;
}

class CharactersManager final : public Fluffy::Singleton<CharactersManager>, public Fluffy::IEventListener
{
	friend Fluffy::Singleton<CharactersManager>;

public:
	~CharactersManager();

	inline void SetScene(Fluffy::Scene* pScene) { m_pCurrentScene = pScene; }
	void CreatePlayerCharacters();
	class EnemyCharacter* SpawnEnemy(const EnemyEnteringData& data);
	void RespawnPlayer(const int playerIndex);
	void OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* param) override;

	class PlayerCharacter* GetPlayer(const int playerIndex);
	inline bool AreAllEnemiesDead() const { return m_Enemies.empty(); }

	inline Fluffy::Event& GetOnPlayerKilled() { return m_OnPlayerKilled; }
	inline Fluffy::Event& GetOnEnemyKilled() { return m_OnEnemyKilled; }

private:
	CharactersManager();
	void ClearAllCharacters();

	Fluffy::Event m_OnPlayerKilled{ Fluffy::EventType::OnPlayerKilled };
	Fluffy::Event m_OnEnemyKilled{ Fluffy::EventType::OnEnemyKilled };

	std::vector<class PlayerCharacter*> m_PlayerCharacters{};
	std::vector<class EnemyCharacter*> m_Enemies{};

	Fluffy::Scene* m_pCurrentScene{};
};
