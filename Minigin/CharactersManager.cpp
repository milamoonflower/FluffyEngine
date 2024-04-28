#include "CharactersManager.h"
#include "Character.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "Scene.h"
#include "GameObject.h"
#include "Sprite.h"
#include <memory>

void CharactersManager::CreatePlayerCharacters(Scene& scene)
{
	std::shared_ptr<GameObject> pPlayer1{ std::make_shared<GameObject>(270.0f, 350.0f) };
	pPlayer1->AddComponent<Sprite>(std::make_unique<Sprite>(pPlayer1.get(), "galaga_player1.png"));
	
	PlayerCharacter* pPlayer1Component{ pPlayer1->AddComponent<PlayerCharacter>(std::make_unique<PlayerCharacter>(pPlayer1.get(), 3, 1)) };
	scene.Add(pPlayer1);

	m_PlayerCharacters.push_back(pPlayer1Component);


	std::shared_ptr<GameObject> pPlayer2{ std::make_shared<GameObject>(330.0f, 350.0f) };
	pPlayer2->AddComponent<Sprite>(std::make_unique<Sprite>(pPlayer2.get(), "galaga_player2.png"));

	PlayerCharacter* pPlayer2Component{ pPlayer2->AddComponent<PlayerCharacter>(std::make_unique<PlayerCharacter>(pPlayer2.get(), 3, 2)) };
	scene.Add(pPlayer2);

	m_PlayerCharacters.push_back(pPlayer2Component);
}

void CharactersManager::SpawnEnemies(Scene& scene)
{
	std::shared_ptr<GameObject> pEnemy{ std::make_shared<GameObject>(290.0f, 60.0f) };
	pEnemy->AddComponent<Sprite>(std::make_unique<Sprite>(pEnemy.get(), "galaga_blue_enemy.png"));

	EnemyCharacter* pEnemyCharacter{ pEnemy->AddComponent<EnemyCharacter>(std::make_unique<EnemyCharacter>(pEnemy.get())) };
	scene.Add(pEnemy);

	pEnemyCharacter->GetOnDeath().AddListener(this);

	m_Enemies.push_back(pEnemyCharacter);
}

void CharactersManager::KillEnemy(int killerIndex)
{
	if (!m_Enemies.empty())
	{
		m_Enemies.back()->Kill(killerIndex);
		m_Enemies.back()->GetGameObject()->Destroy();
		m_Enemies.pop_back();
	}
}

void CharactersManager::OnNotify(const EventType& eventType, const IEventParam* param)
{
	switch (eventType)
	{
	case EventType::OnCharacterDeath:
		m_OnEnemyKilled.Invoke(param);
		break;
	}
}

PlayerCharacter* CharactersManager::GetPlayer(int playerIndex)
{
	return playerIndex > 0 && playerIndex <= int(m_PlayerCharacters.size()) ?
			m_PlayerCharacters[playerIndex - 1] :
			nullptr;
}
