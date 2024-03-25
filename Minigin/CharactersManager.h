#pragma once
#include "Singleton.h"
#include "Event.h"
#include "IEventListener.h"
#include <memory>
#include <vector>

class CharactersManager : public Singleton<CharactersManager>, IEventListener
{
public:
	void CreatePlayerCharacters(class Scene& scene);
	void SpawnEnemies(class Scene& scene);
	void KillEnemy(int killerIndex);
	void OnNotify(const EventType& eventType, const IEventParam* param) override;
	std::shared_ptr<class PlayerCharacter> GetPlayer(int playerIndex);
	inline Event& GetOnEnemyKilled() { return m_OnEnemyKilled; }

private:
	Event m_OnEnemyKilled{ EventType::OnEnemyKilled };

	std::vector<std::shared_ptr<class PlayerCharacter>> m_PlayerCharacters{};
	std::vector<std::shared_ptr<class EnemyCharacter>> m_Enemies{};
};
