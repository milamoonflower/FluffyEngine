#include "ScoreComponent.h"
#include "Text.h"
#include "GameObject.h"
#include "IEventParam.h"
#include "CharactersManager.h"
#include <sstream>

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
		if (const Fluffy::OnCharacterDeathParam* pCharacterDeathParam{ static_cast<const Fluffy::OnCharacterDeathParam*>(pParam) })
		{
			if (pCharacterDeathParam->killer == m_PlayerIndex)
			{
				++m_Score;
				m_pText->SetText(GetScoreString());
			}
		}
		break;
	}
}

std::string ScoreComponent::GetScoreString() const
{
	std::stringstream ss{};
	ss << "Player " << m_PlayerIndex << " Score: " << m_Score;
	return ss.str();
}
