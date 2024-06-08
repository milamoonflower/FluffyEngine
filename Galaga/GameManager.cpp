#include "GameManager.h"
#include "Parser.h"
#include "BulletsManager.h"
#include "CharactersManager.h"
#include "EventParams.h"
#include "Character.h"
#include "Structs.h"
#include "Parser.h"

const float GameManager::PLAYER_RESPAWN_TIMER_DURATION{ 1.0f };

GameManager::GameManager(Fluffy::GameObject* pOwner)
	: Component(pOwner)
{
	RegisterInstance(this);

	CharactersManager::GetInstance().GetOnPlayerKilled().AddListener(this);
	CharactersManager::GetInstance().GetOnEnemyKilled().AddListener(this);
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

	m_ActiveLevel.StartLevel(enemiesData);

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
			const int characterIndex{ deathParam->GetCharacter()->GetPlayerIndex() };
			StartPlayerRespawnTimer(characterIndex);
		}
		break;

	case Fluffy::EventType::OnEnemyKilled:

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
