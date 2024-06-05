#include "Level.h"
#include "EnemyStates.h"
#include "EnemyCharacter.h"
#include "CharactersManager.h"
#include "Event.h"
#include "EventParams.h"
#include <algorithm>

void Level::StartLevel(const std::queue<EnemyEnteringData>& data)
{
	m_EnemyEnteringData = data;

	m_Time = 0.0f;
	m_Playing = true;
}

void Level::Update(const float deltaTime)
{
	if (!m_Playing)
		return;

	m_Time += deltaTime;
	m_EnemyExitTimer += deltaTime;

	if (!m_EnemyEnteringData.empty())
	{
		const EnemyEnteringData& data{ m_EnemyEnteringData.front() };

		if (m_Time >= data.time)
		{
			EnemyCharacter* pEnemy{ CharactersManager::GetInstance()->SpawnEnemy(data) };

			pEnemy->SetEnteringPath(data.path);
			pEnemy->SetState(EnemyStates::Entering);
			m_Enemies.push_back(pEnemy);

			m_EnemyEnteringData.pop();
		}
	}

	HandleEnemyDiving();
}

void Level::HandleEnemyDiving()
{
	if (m_EnemyExitTimer < m_EnemyDiveInterval)
		return;

	const auto& pEnemy{ std::ranges::find_if(m_Enemies, [](const EnemyCharacter* pEnemy)
		{
			return pEnemy->GetState() == EnemyStates::Idle;
		}) };

	if (pEnemy != m_Enemies.end())
	{
		(*pEnemy)->SetState(EnemyStates::Exiting);
	}

	m_EnemyExitTimer = 0.0f;
}

void Level::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* pParam /*= nullptr*/)
{
	switch (eventType)
	{
	case Fluffy::EventType::OnEnemyKilled:
		if (const CharacterDeathParam * pCharacterDeathParam{ static_cast<const CharacterDeathParam*>(pParam) })
		{
			m_Enemies.erase(std::ranges::find(m_Enemies, pCharacterDeathParam->GetCharacter()), m_Enemies.end());
		}
		break;
	}
}
