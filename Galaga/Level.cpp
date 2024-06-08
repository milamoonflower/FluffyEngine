#include "Level.h"
#include "EnemyStates.h"
#include "EnemyCharacter.h"
#include "CharactersManager.h"
#include "Event.h"
#include "EventParams.h"
#include "GameEvents.h"
#include <ranges>
#include <algorithm>
#include <unordered_set>

Level::Level()
{
	CharactersManager::GetInstance().GetOnEnemyKilled().AddListener(this);
}

Level::~Level()
{
	CharactersManager::GetInstance().GetOnEnemyKilled().RemoveListener(this);
}

void Level::StartLevel(const std::queue<EnemyEnteringData>& data)
{
	m_EnemyEnteringData = data;

	m_Time = 0.0f;
	m_EnemySpawnTimer = 0.0f;
	m_EnemyExitTimer = m_EnemyDiveInterval;
	m_Playing = true;
	m_RemovedLevelName = false;
	m_HaveEnemiesEnteredIdle = false;
}

void Level::Update(const float deltaTime)
{
	if (!m_Playing)
		return;

	m_Time += deltaTime;

	if (!m_RemovedLevelName && m_Time >= m_RemoveLevelNameTime)
	{
		GameEvents::RemoveLevelStartText.Invoke();
		m_RemovedLevelName = true;
	}

	if (!m_EnemyEnteringData.empty())
	{
		m_EnemySpawnTimer -= deltaTime;

		const EnemyEnteringData& data{ m_EnemyEnteringData.front() };

		if (m_Time >= data.time && m_EnemySpawnTimer <= 0.0f)
		{
			EnemyCharacter* pEnemy{ CharactersManager::GetInstance().SpawnEnemy(data) };

			pEnemy->SetEnteringPath(data.path);
			pEnemy->SetState(EnemyStates::Entering);
			m_Enemies.push_back(pEnemy);

			m_EnemyEnteringData.pop();

			m_EnemySpawnTimer = m_MinEnemiesSpawnInterval;
		}
	}
	else if (AreAllEnemiesIdle())
	{
		if (!m_HaveEnemiesEnteredIdle)
		{
			m_OnEnemiesIdleStart.Invoke();
			m_HaveEnemiesEnteredIdle = true;
		}

		m_EnemyExitTimer -= deltaTime;

		HandleEnemyDiving();
	}
}

bool Level::AreAllEnemiesIdle() const
{
	return std::ranges::find_if(m_Enemies,
		[](const auto& pEnemy)
		{
			return pEnemy->GetState() != EnemyStates::Idle;
		}) == m_Enemies.end();
}

void Level::HandleEnemyDiving()
{
	if (m_EnemyExitTimer >= 0.0f || m_Enemies.empty())
		return;

	const int maxRand{ std::min(m_MaxEnemiesDivingCount, int(m_Enemies.size())) };
	int enemiesCountToDive{ (rand() % maxRand) + 1 };

	while (enemiesCountToDive > 0)
	{
		const int randomEnemyIndex{ rand() % int(m_Enemies.size()) };

		if (m_Enemies.at(randomEnemyIndex)->GetState() == EnemyStates::Idle)
		{
			m_Enemies.at(randomEnemyIndex)->SetState(EnemyStates::Diving);
			--enemiesCountToDive;
		}
	}

	m_EnemyExitTimer = m_EnemyDiveInterval;
}

void Level::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* pParam /*= nullptr*/)
{
	switch (eventType)
	{
	case Fluffy::EventType::OnEnemyKilled:
		if (const CharacterDeathParam * pCharacterDeathParam{ static_cast<const CharacterDeathParam*>(pParam) })
		{
			m_Enemies.erase(std::ranges::find(m_Enemies, pCharacterDeathParam->GetCharacter()));
		}
		break;
	}
}
