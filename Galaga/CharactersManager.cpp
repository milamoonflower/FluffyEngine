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
#include "Parser.h"
#include <memory>
#include <algorithm>

const float CharactersManager::PLAYER_RESPAWN_TIMER_DURATION{ 1.0f };

CharactersManager::CharactersManager(Fluffy::GameObject* pOwner)
	: Component(pOwner)
{
	RegisterInstance();
}

void CharactersManager::StartLevel1()
{
	std::vector<EnemyEnteringData> data;
	Parser::GetInstance().ParseEnemyLayoutData("D:/Repos/FluffyEngine/Data/Formations/galaga_level_1.csv", data);
	data;

	std::string beeFormationsData{ "Formations/Formation1Bees.txt" };
	std::string butterflyFormationsData{ "Formations/Formation1Butterflies.txt" };
	std::string bossFormationsData{ "Formations/Formation1Boss.txt" };

	std::queue<EnemyEnteringData> enemiesData{};

	BezierPath firstPath{};
	BezierCurve firstCurve{ { -32.0f, -32.0f }, { -32.0f, -32.0f }, { 290.0f, 200.0f }, { 290.0f, 200.0f } };
	firstPath.AddCurve(firstCurve, 1);

	enemiesData.push({ 4.0f, {}, firstPath, EnemyType::Boss });

	BezierPath secondPath{};
	BezierCurve secondCurve{ { 640.0f, -32.0f }, { 640.0f, -32.0f }, { 330.0f, 200.0f }, { 330.0f, 200.0f } };
	secondPath.AddCurve(secondCurve, 1);

	enemiesData.push({ 4.3f, {}, secondPath, EnemyType::Bee });

	m_Level.StartLevel(enemiesData);

	BulletsManager::GetInstance().Initialize();
}

void CharactersManager::Update(const float deltaTime)
{
	PurgeDestroyedCharacters();

	// if the level has started
	m_Level.Update(deltaTime);

	UpdatePlayerRespawnTimers(deltaTime);

	BulletsManager::GetInstance().Update(deltaTime);
}

void CharactersManager::CreatePlayerCharacters(Fluffy::Scene& scene)
{
	std::shared_ptr<Fluffy::GameObject> pPlayer1{ std::make_shared<Fluffy::GameObject>(SCREEN_SIZE.x / 2.0f, SCREEN_SIZE.y - 80.0f) };

	pPlayer1->AddComponent<Fluffy::Sprite>("galaga_player1.png");
	PlayerCharacter* pPlayer1Component{ pPlayer1->AddComponent<PlayerCharacter>(4, int(m_PlayerCharacters.size())) };
	scene.Add(pPlayer1);
	pPlayer1Component->GetOnDeath().AddListener(this);

	m_PlayerCharacters.push_back(pPlayer1Component);
}

EnemyCharacter* CharactersManager::SpawnEnemy(const EnemyEnteringData& data)
{
	std::shared_ptr<Fluffy::GameObject> pEnemy{ std::make_shared<Fluffy::GameObject>(data.path.GetStartPoint()) };
	std::string fileName;

	switch (data.type)
	{
	case EnemyType::Boss:
		fileName = "galaga_boss.png";
		break;
		
	case EnemyType::Butterfly:
		fileName = "galaga_butterfly.png";
		break;

	case EnemyType::Bee:
		fileName = "galaga_bee.png";
		break;
	}

	pEnemy->AddComponent<Fluffy::Sprite>(fileName);
	const float enemySpeed{ 200.0f };
	EnemyCharacter* pEnemyCharacter{ pEnemy->AddComponent<EnemyCharacter>(data.type, enemySpeed) };
	m_pOwner->GetScene()->Add(pEnemy);
	pEnemyCharacter->GetOnDeath().AddListener(this);
	m_Enemies.push_back(pEnemyCharacter);

	return pEnemyCharacter;
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
		if (const CharacterDeathParam* deathParam{ static_cast<const CharacterDeathParam*>(param) })
		{
			const int characterIndex{ deathParam->GetCharacter()->GetPlayerIndex() };

			if (characterIndex != INVALID_PLAYER_INDEX)
				StartPlayerRespawnTimer(characterIndex);
			else
				m_OnEnemyKilled.Invoke(param);
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

void CharactersManager::RegisterInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = this;
}

void CharactersManager::PurgeDestroyedCharacters()
{
	m_PlayerCharacters.erase(std::ranges::remove_if(m_PlayerCharacters, [](const PlayerCharacter* pPlayer)
		{
			return pPlayer->GetGameObject()->IsDestroyed();
		}).begin(), m_PlayerCharacters.end());

	m_Enemies.erase(std::ranges::remove_if(m_Enemies, [](const EnemyCharacter* pEnemy)
		{
			return pEnemy->GetGameObject()->IsDestroyed();
		}).begin(), m_Enemies.end());
}

void CharactersManager::StartPlayerRespawnTimer(const int playerIndex)
{
	m_PlayerRespawnTimers[playerIndex] = PLAYER_RESPAWN_TIMER_DURATION;
}

void CharactersManager::UpdatePlayerRespawnTimers(const float deltaTime)
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

void CharactersManager::RespawnPlayer(const int playerIndex)
{
	m_PlayerCharacters[playerIndex]->Respawn();
}
