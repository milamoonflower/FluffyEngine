#include "ScoreComponent.h"
#include "Text.h"
#include "GameObject.h"
#include "IEventParam.h"
#include "CharactersManager.h"
#include <sstream>

ScoreComponent::ScoreComponent(const std::weak_ptr<GameObject> pOwner, int playerIndex, const std::string& fontPath, int fontSize)
	: Component(pOwner)
	, m_PlayerIndex{ playerIndex }
{
	m_pText = std::make_shared<Text>(pOwner, GetScoreString(), fontPath, fontSize);
	pOwner.lock()->AddComponent<Text>(m_pText);

	CharactersManager::GetInstance().GetOnEnemyKilled().AddListener(this);
}

ScoreComponent::~ScoreComponent()
{
	CharactersManager::GetInstance().GetOnEnemyKilled().RemoveListener(this);
}

void ScoreComponent::OnNotify(const EventType& eventType, const IEventParam* param)
{
	switch (eventType)
	{
	case EventType::OnEnemyKilled:
		if (const OnCharacterDeathParam* pCharacterDeathParam{ static_cast<const OnCharacterDeathParam*>(param) })
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
