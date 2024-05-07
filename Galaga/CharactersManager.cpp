#include "CharactersManager.h"
#include "Character.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "Scene.h"
#include "GameObject.h"
#include "Sprite.h"
#include "SpriteColliderComponent.h"
#include "CollidersHandler.h"
#include <memory>

void CharactersManager::CreatePlayerCharacters(Fluffy::Scene& scene)
{
	std::shared_ptr<Fluffy::GameObject> pPlayer1{ std::make_shared<Fluffy::GameObject>(270.0f, 350.0f) };
	//pPlayer1->AddComponent<Fluffy::Sprite>("galaga_player1.png");

	Fluffy::Sprite* pSprite1{ pPlayer1->AddComponent<Fluffy::Sprite>("galaga_player1.png") };
	PlayerCharacter* pPlayer1Component{ pPlayer1->AddComponent<PlayerCharacter>(3, 1) };
	SpriteColliderComponent* pCollider1{ pPlayer1->AddComponent<SpriteColliderComponent>(pSprite1->GetTextureSize()) };
	pCollider1->GetOnCollision().AddListener(this);
	CollidersHandler::GetInstance().AddColliderComponent(pCollider1);
	scene.Add(pPlayer1);

	m_PlayerCharacters.push_back(pPlayer1Component);

	/*std::shared_ptr<Fluffy::GameObject> pPlayer2{ std::make_shared<Fluffy::GameObject>(330.0f, 350.0f) };
	pPlayer2->AddComponent<Fluffy::Sprite>("galaga_player2.png");

	PlayerCharacter* pPlayer2Component{ pPlayer2->AddComponent<PlayerCharacter>(3, 2) };
	scene.Add(pPlayer2);

	m_PlayerCharacters.push_back(pPlayer2Component);*/
}

void CharactersManager::SpawnEnemies(Fluffy::Scene& scene)
{
	std::shared_ptr<Fluffy::GameObject> pEnemy{ std::make_shared<Fluffy::GameObject>(290.0f, 60.0f) };
	pEnemy->AddComponent<Fluffy::Sprite>("galaga_blue_enemy.png");

	EnemyCharacter* pEnemyCharacter{ pEnemy->AddComponent<EnemyCharacter>() };
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

void CharactersManager::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* param)
{
	switch (eventType)
	{
	case Fluffy::EventType::OnCharacterDeath:
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
