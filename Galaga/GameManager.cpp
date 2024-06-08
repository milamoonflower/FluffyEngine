#define ALTERNATE_SPAWN_SIDES

#include "GameManager.h"
#include "Parser.h"
#include "BulletsManager.h"
#include "Bullet.h"
#include "CharactersManager.h"
#include "EventParams.h"
#include "Character.h"
#include "PlayerCharacter.h"
#include "Structs.h"
#include "Parser.h"
#include "GameEvents.h"
#include <format>

const float GameManager::PLAYER_RESPAWN_TIMER_DURATION{ 2.0f };
const int GameManager::LEVELS_COUNT{ 3 };

GameManager::GameManager(Fluffy::GameObject* pOwner)
	: Component(pOwner)
{
	RegisterInstance(this);

	CharactersManager::GetInstance().GetOnPlayerKilled().AddListener(this);
	CharactersManager::GetInstance().GetOnEnemyKilled().AddListener(this);

	GameEvents::OnPlayerShoot.AddListener(this);
	GameEvents::OnBulletHit.AddListener(this);
}

GameManager::~GameManager()
{
	RegisterInstance(nullptr);

	CharactersManager::GetInstance().GetOnPlayerKilled().RemoveListener(this);
	CharactersManager::GetInstance().GetOnEnemyKilled().RemoveListener(this);

	GameEvents::OnPlayerShoot.RemoveListener(this);
	GameEvents::OnBulletHit.RemoveListener(this);
}

void GameManager::StartLevel(const int levelIndex)
{
	m_CurrentLevelIndex = levelIndex;

	CharactersManager::GetInstance().CreatePlayerCharacters();

	std::vector<EnemyEnteringData> enemiesData;
	Parser::GetInstance().ParseEnemyLayoutData(std::format("D:/Repos/FluffyEngine/Data/Formations/galaga_level_{}.csv", levelIndex), enemiesData);
	std::ranges::sort(enemiesData, [](const auto& a, const auto& b) { return a.time < b.time; });

#ifdef ALTERNATE_SPAWN_SIDES
	const glm::vec2 spawnPosLeft{ -40.0f, -40.0f };
	const glm::vec2 spawnPosRight{ SCREEN_SIZE.x + 40.0f, -40.0f };
#else
	const glm::vec2 spawnPos{ SCREEN_SIZE.x / 2.0f, -40.0f };
#endif

	for (auto& data : enemiesData)
	{
#ifdef ALTERNATE_SPAWN_SIDES
		const glm::vec2& spawnPos{ int(data.time) % 2 == 0 ? spawnPosLeft : spawnPosRight };
#endif
		data.path.AddCurve({ spawnPos, spawnPos, data.position, data.position }, 1);
	}

	std::queue<EnemyEnteringData> enemiesQueue{ };
	std::ranges::for_each(enemiesData, [&enemiesQueue](const auto& data) { enemiesQueue.push(data); });

	m_ActiveLevel.StartLevel(enemiesQueue);
	const LevelStartParam param{ levelIndex };
	GameEvents::OnLevelStart.Invoke(&param);

	BulletsManager::GetInstance().Initialize();
}

void GameManager::Update(const float deltaTime)
{
	// if the level has started
	m_ActiveLevel.Update(deltaTime);

	UpdatePlayerRespawnTimers(deltaTime);

	BulletsManager::GetInstance().Update(deltaTime);
}

void GameManager::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* param)
{
	switch (eventType)
	{
	case Fluffy::EventType::OnPlayerKilled:
		if (const CharacterDeathParam* deathParam{ static_cast<const CharacterDeathParam*>(param) })
		{
			const int playerIndex{ deathParam->GetCharacter()->GetPlayerIndex() };

			if (CharactersManager::GetInstance().GetPlayer(playerIndex)->GetLivesCount() > 0)
			{
				StartPlayerRespawnTimer(playerIndex);
			}
			else
			{
				TriggerGameOver();
			}
		}
		break;

	case Fluffy::EventType::OnEnemyKilled:
		if (CharactersManager::GetInstance().AreAllEnemiesDead())
		{
			if (++m_CurrentLevelIndex <= LEVELS_COUNT)
			{
				GameEvents::OnLevelCompleted.Invoke();
				StartLevel(m_CurrentLevelIndex);
			}
			else
			{
				TriggerGameOver();
			}
		}
		break;

	case Fluffy::EventType::OnPlayerShoot:
		++m_ShotsFiredCount;
		break;

	case Fluffy::EventType::OnBulletHit:
		if (const BulletHitParam* bulletHitParam{ static_cast<const BulletHitParam*>(param) })
		{
			if (bulletHitParam->GetBullet()->GetOwnerIndex() != INVALID_PLAYER_INDEX)
				++m_ShotsHitCount;
		}
		break;
	}
}

void GameManager::StartPlayerRespawnTimer(const int playerIndex)
{
	m_PlayerRespawnTimers[playerIndex] = PLAYER_RESPAWN_TIMER_DURATION;
}

void GameManager::UpdatePlayerRespawnTimers(const float deltaTime)
{
	for (int i = 0; i < 2; ++i)
	{
		if (m_PlayerRespawnTimers[i] <= 0.0f)
			continue;

		m_PlayerRespawnTimers[i] -= deltaTime;
		if (m_PlayerRespawnTimers[i] <= 0.0f)
			RespawnPlayer(i);
	}
}

void GameManager::RespawnPlayer(const int playerIndex)
{
	CharactersManager::GetInstance().RespawnPlayer(playerIndex);
}

void GameManager::TriggerGameOver()
{
	const GameOverParam gameOverParam{ m_ShotsFiredCount, m_ShotsHitCount };
	GameEvents::OnGameOver.Invoke(&gameOverParam);
}
