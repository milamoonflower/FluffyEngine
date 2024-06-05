#include "HealthDisplayComponent.h"
#include "Sprite.h"
#include "PlayerCharacter.h"
#include "GameObject.h"
#include "IEventParam.h"
#include "CharactersManager.h"
#include <sstream>
#include <memory>
#include <format>

HealthDisplayComponent::HealthDisplayComponent(Fluffy::GameObject* pOwner, int playerIndex)
	: Fluffy::Component(pOwner)
	, m_PlayerIndex{ playerIndex }
{
	if (PlayerCharacter* pPlayer{ CharactersManager::GetInstance()->GetPlayer(playerIndex) })
	{
		pPlayer->GetOnDeath().AddListener(this);

		std::string fileName = std::format("galaga_player{}.png", playerIndex + 1);
		const float padding{ 5.0f };
		float spriteWidth{ 0.0f };

		for (int i{ 0 }; i < pPlayer->GetLivesCount() - 1; ++i)
		{
			m_Lives.push_back(pOwner->AddComponent<Fluffy::Sprite>(fileName, glm::vec2((spriteWidth + padding) * i, 0.0f)));

			if (i == 0)
				spriteWidth = m_Lives[0]->GetTextureSize().x;
		}
	}
}

HealthDisplayComponent::~HealthDisplayComponent()
{
	if (CharactersManager::GetInstance() == nullptr)
		return;

	if (PlayerCharacter* pPlayer{ CharactersManager::GetInstance()->GetPlayer(m_PlayerIndex) })
	{
		pPlayer->GetOnDeath().RemoveListener(this);
	}
}

void HealthDisplayComponent::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam*)
{
	int lives{ 0 };

	switch (eventType)
	{
	case Fluffy::EventType::OnCharacterDeath:
		if (PlayerCharacter * pPlayer{ CharactersManager::GetInstance()->GetPlayer(m_PlayerIndex) })
		{
			lives = pPlayer->GetLivesCount();
		}

		if (lives != 0)
			m_Lives[lives-1]->SetEnabled(false);

		break;
	}
}

std::string HealthDisplayComponent::GetLivesString() const
{
	std::stringstream ss{};
	ss << "Player " << m_PlayerIndex;

	int lives{ 0 };

	if (PlayerCharacter* pPlayer{ CharactersManager::GetInstance()->GetPlayer(m_PlayerIndex) })
	{
		lives = pPlayer->GetLivesCount();
	}

	ss << " Lives: " << lives;
	return ss.str();
}
