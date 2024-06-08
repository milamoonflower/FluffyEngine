#include "GameOverScreen.h"
#include "GameObject.h"
#include "Scene.h"
#include "Text.h"
#include "UIManager.h"
#include "glm\glm.hpp"
#include <SDL_ttf.h>
#include <memory>
#include <format>
#include <cmath>

GameOverScreen::GameOverScreen(Fluffy::GameObject* pOwner)
	: Fluffy::Component(pOwner)
{
	const auto& font{ UIManager::GetInstance().GetDefaultFont() };
	Fluffy::Scene* pScene{ pOwner->GetScene() };

	std::shared_ptr<Fluffy::GameObject> pGameOverText{ std::make_shared<Fluffy::GameObject>()};
	pGameOverText->SetParent(pOwner, false);
	const Fluffy::Text* pText{ pGameOverText->AddComponent<Fluffy::Text>("~~ Game Over ~~", font, Fluffy::TextAlignment::Center, SDL_Color{ 255, 0, 0, 255 })};

	// add half text height as padding
	const float textLineHeight{ pText->GetSize().y * 1.5f };

	pGameOverText->SetLocalPosition(0.0f, textLineHeight * -1.5f);
	pScene->Add(pGameOverText);

	std::shared_ptr<Fluffy::GameObject> pShotsCount{ std::make_shared<Fluffy::GameObject>(0.0f, textLineHeight * -0.5f) };
	pShotsCount->SetParent(pOwner, false);
	m_pShotsCountText = pShotsCount->AddComponent<Fluffy::Text>("0", font, Fluffy::TextAlignment::Center, SDL_Color{255, 255, 0, 255});
	pScene->Add(pShotsCount);

	std::shared_ptr<Fluffy::GameObject> pHitsCount{ std::make_shared<Fluffy::GameObject>(0.0f, textLineHeight * 0.5f) };
	pHitsCount->SetParent(pOwner, false);
	m_pHitsCountText = pHitsCount->AddComponent<Fluffy::Text>("0", font, Fluffy::TextAlignment::Center, SDL_Color{ 255, 255, 0, 255 });
	pScene->Add(pHitsCount);

	std::shared_ptr<Fluffy::GameObject> pHitsRatio{ std::make_shared<Fluffy::GameObject>(0.0f, textLineHeight * 1.5f) };
	pHitsRatio->SetParent(pOwner, false);
	m_pHitsRatioText = pHitsRatio->AddComponent<Fluffy::Text>("0", font, Fluffy::TextAlignment::Center, SDL_Color{ 255, 255, 0, 255 });
	pScene->Add(pHitsRatio);
}

void GameOverScreen::SetGameStats(const int shotsCount, const int hitsCount)
{
	m_pShotsCountText->SetText(std::format("SHOTS FIRED:		{}", shotsCount));
	m_pHitsCountText->SetText(std::format("NUMBER OF HITS:	{}", hitsCount));
	m_pHitsRatioText->SetText(std::format("HITS RATIO:		{}%", std::round((float(hitsCount) / shotsCount) * 100.0f)));
}
