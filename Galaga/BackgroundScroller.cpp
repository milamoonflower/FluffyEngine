#include "BackgroundScroller.h"
#include "GameObject.h"
#include "Sprite.h"

BackgroundScroller::BackgroundScroller(Fluffy::GameObject* pOwner, const std::string& backgroundPath)
	: Fluffy::Component(pOwner)
	, m_StartingPos{ pOwner->GetWorldPosition() }
{
	const Fluffy::Sprite* pBG{ pOwner->AddComponent<Fluffy::Sprite>(backgroundPath) };
	m_BGHeight = pBG->GetTextureSize().y;

	// add one copy of the bg on top of the first one
	pOwner->AddComponent<Fluffy::Sprite>(backgroundPath, glm::vec2(0.0f, -m_BGHeight));
}

void BackgroundScroller::Update(const float deltaTime)
{
	m_pOwner->GetTransform().Translate(0.0f, m_Speed * deltaTime);

	if (m_pOwner->GetWorldPosition().y - m_StartingPos.y >= m_BGHeight)
		m_pOwner->GetTransform().Translate(0.0f, -m_BGHeight);
}
