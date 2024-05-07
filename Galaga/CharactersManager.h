#pragma once
#include "Singleton.h"
#include "Event.h"
#include "IEventListener.h"
#include <memory>
#include <vector>

namespace Fluffy
{
	struct IEventParam;
	class Scene;
}

class CharactersManager : public Fluffy::Singleton<CharactersManager>, Fluffy::IEventListener
{
public:
	void CreatePlayerCharacters(class Fluffy::Scene& scene);
	void SpawnEnemies(class Fluffy::Scene& scene);
	void KillEnemy(int killerIndex);
	void OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* param) override;
	class PlayerCharacter* GetPlayer(int playerIndex);
	inline Fluffy::Event& GetOnEnemyKilled() { return m_OnEnemyKilled; }

private:
	Fluffy::Event m_OnEnemyKilled{ Fluffy::EventType::OnEnemyKilled };

	std::vector<class PlayerCharacter*> m_PlayerCharacters{};
	std::vector<class EnemyCharacter*> m_Enemies{};
};
