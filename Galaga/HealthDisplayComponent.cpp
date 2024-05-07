#include "HealthDisplayComponent.h"
#include "Text.h"
#include "PlayerCharacter.h"
#include "GameObject.h"
#include "IEventParam.h"
#include "CharactersManager.h"
#include <sstream>

HealthDisplayComponent::HealthDisplayComponent(Fluffy::GameObject* pOwner, int playerIndex, const std::string& fontPath, int fontSize)
	: Fluffy::Component(pOwner)
	, m_PlayerIndex{ playerIndex }
{
	if (PlayerCharacter* pPlayer{ CharactersManager::GetInstance().GetPlayer(playerIndex) })
	{
		pPlayer->GetOnDeath().AddListener(this);
	}

	m_pText = pOwner->AddComponent<Fluffy::Text>(GetLivesString(), fontPath, fontSize);
}

HealthDisplayComponent::~HealthDisplayComponent()
{
	if (PlayerCharacter* pPlayer{ CharactersManager::GetInstance().GetPlayer(m_PlayerIndex) })
	{
		pPlayer->GetOnDeath().RemoveListener(this);
	}
}

void HealthDisplayComponent::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam*)
{
	switch (eventType)
	{
	case Fluffy::EventType::OnCharacterDeath:
		m_pText->SetText(GetLivesString());
		break;
	}
}

std::string HealthDisplayComponent::GetLivesString() const
{
	std::stringstream ss{};
	ss << "Player " << m_PlayerIndex;

	int lives{ 0 };

	if (PlayerCharacter* pPlayer{ CharactersManager::GetInstance().GetPlayer(m_PlayerIndex) })
	{
		lives = pPlayer->GetLivesCount();
	}

	ss << " Lives: " << lives;
	return ss.str();
}
