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

const float GameManager::PLAYER_RESPAWN_TIMER_DURATION{ 1.0f };

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

void GameManager::CreatePlayerCharacters(Fluffy::Scene* scene)
{
	CharactersManager::GetInstance().CreatePlayerCharacters(scene);
}

void GameManager::StartLevel1()
{
	/*std::vector<EnemyEnteringData> data;
	Parser::GetInstance().ParseEnemyLayoutData("D:/Repos/FluffyEngine/Data/Formations/galaga_level_1.csv", data);*/

	std::queue<EnemyEnteringData> enemiesData{};

	BezierPath firstPath{};
	BezierCurve firstCurve{ { -32.0f, -32.0f }, { -32.0f, -32.0f }, { 290.0f, 200.0f }, { 290.0f, 200.0f } };
	firstPath.AddCurve(firstCurve, 1);

	enemiesData.push({ 4.0f, {}, firstPath, EnemyType::Boss });

	BezierPath secondPath{};
	BezierCurve secondCurve{ { 640.0f, -32.0f }, { 640.0f, -32.0f }, { 330.0f, 200.0f }, { 330.0f, 200.0f } };
	secondPath.AddCurve(secondCurve, 1);

	enemiesData.push({ 4.3f, {}, secondPath, EnemyType::Bee });

	m_ShotsFiredCount = 0;
	m_ShotsHitCount = 0;

	m_ActiveLevel.StartLevel(enemiesData);
	const LevelStartParam param{ 1 };
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
				const GameOverParam gameOverParam{ m_ShotsFiredCount, m_ShotsHitCount };
				GameEvents::OnGameOver.Invoke(&gameOverParam);
			}
		}
		break;

	case Fluffy::EventType::OnEnemyKilled:
		if (CharactersManager::GetInstance().AreAllEnemiesDead())
		{
			const GameOverParam gameOverParam{ m_ShotsFiredCount, m_ShotsHitCount };
			GameEvents::OnLevelCompleted.Invoke(&gameOverParam);
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
