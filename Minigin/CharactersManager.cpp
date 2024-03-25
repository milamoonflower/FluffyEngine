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
	std::shared_ptr<Sprite> pPlayer1Sprite{ std::make_shared<Sprite>(pPlayer1, "galaga_player1.png") };
	pPlayer1->AddComponent<Sprite>(pPlayer1Sprite);
	std::shared_ptr<PlayerCharacter> pPlayer1Component{ std::make_shared<PlayerCharacter>(pPlayer1, 3, 1) };
	pPlayer1->AddComponent<PlayerCharacter>(pPlayer1Component);
	scene.Add(pPlayer1);

	m_PlayerCharacters.push_back(pPlayer1Component);

	std::shared_ptr<GameObject> pPlayer2{ std::make_shared<GameObject>(330.0f, 350.0f) };
	std::shared_ptr<Sprite> pPlayer2Sprite{ std::make_shared<Sprite>(pPlayer2, "galaga_player2.png") };
	std::shared_ptr<PlayerCharacter> pPlayer2Component{ std::make_shared<PlayerCharacter>(pPlayer2, 3, 2) };
	pPlayer2->AddComponent<Sprite>(pPlayer2Sprite);
	scene.Add(pPlayer2);

	m_PlayerCharacters.push_back(pPlayer2Component);
}

void CharactersManager::SpawnEnemies(Scene& scene)
{
	std::shared_ptr<GameObject> enemy{ std::make_shared<GameObject>(290.0f, 60.0f) };
	std::shared_ptr<Sprite> enemySprite{ std::make_shared<Sprite>(enemy, "galaga_blue_enemy.png")};
	std::shared_ptr<EnemyCharacter> enemyCharacter{ std::make_shared<EnemyCharacter>(enemy) };
	enemy->AddComponent<Sprite>(enemySprite);
	enemy->AddComponent<EnemyCharacter>(enemyCharacter);
	scene.Add(enemy);

	enemyCharacter->GetOnDeath().AddListener(this);

	m_Enemies.push_back(enemyCharacter);
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

std::shared_ptr<PlayerCharacter> CharactersManager::GetPlayer(int playerIndex)
{
	return playerIndex > 0 && playerIndex <= int(m_PlayerCharacters.size()) ?
			m_PlayerCharacters[playerIndex - 1] :
			nullptr;
}
