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
public:
	void CreatePlayerCharacters(Fluffy::Scene* pScene);
	class EnemyCharacter* SpawnEnemy(const EnemyEnteringData& data);
	void KillEnemy(const int killerIndex);
	void RespawnPlayer(const int playerIndex);
	void OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* param) override;

	class PlayerCharacter* GetPlayer(const int playerIndex);
	inline Fluffy::Event& GetOnPlayerKilled() { return m_OnPlayerKilled; }
	inline Fluffy::Event& GetOnEnemyKilled() { return m_OnEnemyKilled; }

private:
	Fluffy::Event m_OnPlayerKilled{ Fluffy::EventType::OnPlayerKilled };
	Fluffy::Event m_OnEnemyKilled{ Fluffy::EventType::OnEnemyKilled };

	std::vector<class PlayerCharacter*> m_PlayerCharacters{};
	std::vector<class EnemyCharacter*> m_Enemies{};

	Fluffy::Scene* m_pCurrentScene{};
};
