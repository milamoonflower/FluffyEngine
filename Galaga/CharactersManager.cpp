#include "CharactersManager.h"
#include "Character.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "Scene.h"
#include "GameObject.h"
#include "Sprite.h"
#include "SpriteColliderComponent.h"
#include "CollidersHandler.h"
#include "EnemyStates.h"
#include "EventParams.h"
#include "BulletsManager.h"
#include "Structs.h"
#include <memory>
#include <algorithm>

void CharactersManager::CreatePlayerCharacters(Fluffy::Scene* pScene)
{
	std::shared_ptr<Fluffy::GameObject> pPlayer1{ std::make_shared<Fluffy::GameObject>(SCREEN_SIZE.x / 2.0f, SCREEN_SIZE.y - 80.0f) };

	pPlayer1->AddComponent<Fluffy::Sprite>("galaga_player1.png");
	PlayerCharacter* pPlayer1Component{ pPlayer1->AddComponent<PlayerCharacter>(4, int(m_PlayerCharacters.size())) };
	pScene->Add(pPlayer1);
	pPlayer1Component->GetOnDeath().AddListener(this);

	m_PlayerCharacters.push_back(pPlayer1Component);

	m_pCurrentScene = pScene;
}

EnemyCharacter* CharactersManager::SpawnEnemy(const EnemyEnteringData& data)
{
	std::shared_ptr<Fluffy::GameObject> pEnemy{ std::make_shared<Fluffy::GameObject>(data.path.GetStartPoint()) };
	std::string fileName;

	switch (data.type)
	{
	case EnemyType::Boss:
		fileName = "galaga_boss_green.png";
		break;
		
	case EnemyType::Butterfly:
		fileName = "galaga_butterfly.png";
		break;

	case EnemyType::Bee:
		fileName = "galaga_bee.png";
		break;
	}

	pEnemy->AddComponent<Fluffy::Sprite>(fileName, 2, 1, 2.0f);

	const float enemySpeed{ 200.0f };
	EnemyCharacter* pEnemyCharacter{ pEnemy->AddComponent<EnemyCharacter>(data.type, enemySpeed) };
	m_pCurrentScene->Add(pEnemy);
	pEnemyCharacter->GetOnDeath().AddListener(this);
	m_Enemies.push_back(pEnemyCharacter);

	return pEnemyCharacter;
}

void CharactersManager::RespawnPlayer(const int playerIndex)
{
	m_PlayerCharacters[playerIndex]->Respawn();
}

void CharactersManager::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* param)
{
	switch (eventType)
	{
	case Fluffy::EventType::OnCharacterDeath:
		if (const CharacterDeathParam* deathParam{ static_cast<const CharacterDeathParam*>(param) })
		{
			const int characterIndex{ deathParam->GetCharacter()->GetPlayerIndex() };

			if (characterIndex != INVALID_PLAYER_INDEX)
			{
				m_OnPlayerKilled.Invoke(param);
			}
			else
			{
				m_OnEnemyKilled.Invoke(param);

				const EnemyCharacter* pEnemy{ static_cast<EnemyCharacter*>(deathParam->GetCharacter()) };

				const auto& it{ std::ranges::find(m_Enemies, pEnemy) };
				if (it != m_Enemies.end())
					m_Enemies.erase(it);
			}
		}
		break;
	}
}

PlayerCharacter* CharactersManager::GetPlayer(const int playerIndex)
{
	return playerIndex != INVALID_PLAYER_INDEX && playerIndex < int(m_PlayerCharacters.size()) ?
			m_PlayerCharacters[playerIndex] :
			nullptr;
}
