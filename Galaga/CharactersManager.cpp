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
#include "GameEvents.h"
#include <memory>
#include <algorithm>
#include <format>

CharactersManager::CharactersManager()
{
	GameEvents::OnLevelCompleted.AddListener(this);
	GameEvents::OnGameOver.AddListener(this);
}

CharactersManager::~CharactersManager()
{
	GameEvents::OnLevelCompleted.RemoveListener(this);
	GameEvents::OnGameOver.RemoveListener(this);
}

void CharactersManager::CreatePlayerCharacters()
{
	if (!m_PlayerCharacters.empty())
	{
		std::ranges::for_each(m_PlayerCharacters, [](auto& player) { player->Respawn(); });
		return;
	}

	std::shared_ptr<Fluffy::GameObject> pPlayer{ std::make_shared<Fluffy::GameObject>(SCREEN_SIZE.x / 2.0f, SCREEN_SIZE.y - 80.0f) };
	m_pCurrentScene->Add(pPlayer);

	const int playerIndex{ int(m_PlayerCharacters.size()) };
	pPlayer->AddComponent<Fluffy::Sprite>(std::format("galaga_player{}.png", playerIndex + 1));

	PlayerCharacter* pPlayerComponent{ pPlayer->AddComponent<PlayerCharacter>(4, playerIndex) };
	pPlayerComponent->GetOnDeath().AddListener(this);

	m_PlayerCharacters.push_back(pPlayerComponent);
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
				EnemyCharacter* pEnemy{ static_cast<EnemyCharacter*>(deathParam->GetCharacter()) };
				pEnemy->GetOnDeath().RemoveListener(this);

				const auto& it{ std::ranges::find(m_Enemies, pEnemy) };
				if (it != m_Enemies.end())
					m_Enemies.erase(it);

				m_OnEnemyKilled.Invoke(param);
			}
		}
		break;

	case Fluffy::EventType::OnLevelCompleted:
	case Fluffy::EventType::OnGameOver:
		ClearAllCharacters();
		break;
	}
}

PlayerCharacter* CharactersManager::GetPlayer(const int playerIndex)
{
	return playerIndex != INVALID_PLAYER_INDEX && playerIndex < int(m_PlayerCharacters.size()) ?
			m_PlayerCharacters[playerIndex] :
			nullptr;
}

void CharactersManager::ClearAllCharacters()
{
	std::ranges::for_each(m_PlayerCharacters, [](auto& pPlayer)
		{
			pPlayer->GetGameObject()->SetActive(false);
		});

	std::ranges::for_each(m_Enemies, [](auto& pEnemy)
		{
			pEnemy->GetGameObject()->Destroy();
		});

	m_Enemies.clear();
}
