#include "ScoreComponent.h"
#include "Text.h"
#include "GameObject.h"
#include "EventParams.h"
#include "CharactersManager.h"
#include "EnemyCharacter.h"
#include "Font.h"
#include <sstream>

ScoreComponent::ScoreComponent(Fluffy::GameObject* pOwner, int playerIndex, const std::shared_ptr<Font>& pFont)
	: Fluffy::Component(pOwner)
	, m_PlayerIndex{ playerIndex }
{
	m_pText = pOwner->AddComponent<Fluffy::Text>(GetScoreString(), pFont);

	CharactersManager::GetInstance().GetOnEnemyKilled().AddListener(this);
}

ScoreComponent::ScoreComponent(Fluffy::GameObject* pOwner, int playerIndex, const std::string& fontPath, int fontSize)
	: Fluffy::Component(pOwner)
	, m_PlayerIndex{ playerIndex }
{
	m_pText = pOwner->AddComponent<Fluffy::Text>(GetScoreString(), fontPath, fontSize);

	CharactersManager::GetInstance().GetOnEnemyKilled().AddListener(this);
}

ScoreComponent::~ScoreComponent()
{
	CharactersManager::GetInstance().GetOnEnemyKilled().RemoveListener(this);
}

void ScoreComponent::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* pParam)
{
	switch (eventType)
	{
	case Fluffy::EventType::OnEnemyKilled:
		if (const CharacterDeathParam* pCharacterDeathParam{ static_cast<const CharacterDeathParam*>(pParam) })
		{
			if (pCharacterDeathParam->GetKillerIndex() == m_PlayerIndex)
			{
				if (const EnemyCharacter * pEnemy{ static_cast<const EnemyCharacter*>(pCharacterDeathParam->GetCharacter()) })
				{
					m_Score += CalculateScore(pEnemy);
				}

				m_pText->SetText(GetScoreString());
			}
		}
		break;
	}
}

std::string ScoreComponent::GetScoreString() const
{
	std::stringstream ss{};
	ss << "Player " << m_PlayerIndex + 1 << " Score: " << m_Score;
	return ss.str();
}

int ScoreComponent::CalculateScore(const class EnemyCharacter* pEnemy)
{
	EnemyType type{ pEnemy->GetType() };
	EnemyStates state{ pEnemy->GetState() };

	int score{ 0 };

	switch (type)
	{
	case EnemyType::Bee:
			score = state == EnemyStates::Idle ? m_IdleBeeKillScore : m_MovingBeeKillScore;
			break;
	case EnemyType::Butterfly:
			score = state == EnemyStates::Idle ? m_IdleButterflyKillScore : m_MovingButterflyKillScore;
			break;
	case EnemyType::Boss:
			score = state == EnemyStates::Idle ? m_IdleBossKillScore : m_MovingBossKillScore;
			break;
	}

	return score;
}
