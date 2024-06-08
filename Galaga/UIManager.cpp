#include "UIManager.h"
#include "GameObject.h"
#include "Structs.h"
#include "Font.h"
#include "GameEvents.h"
#include "EventParams.h"
#include "Scene.h"
#include "Text.h"
#include "GameOverScreen.h"
#include <format>

UIManager::UIManager()
{
	GameEvents::OnLevelStart.AddListener(this);
	GameEvents::RemoveLevelStartText.AddListener(this);
	GameEvents::OnGameOver.AddListener(this);
}

UIManager::~UIManager()
{
	GameEvents::OnLevelStart.RemoveListener(this);
	GameEvents::RemoveLevelStartText.RemoveListener(this);
	GameEvents::OnGameOver.RemoveListener(this);
}

void UIManager::CreateUIPanels(Fluffy::Scene* pScene)
{
	std::shared_ptr<Fluffy::GameObject> pLevelIntroText{ std::make_shared<Fluffy::GameObject>(SCREEN_SIZE / 2.0f) };
	pScene->Add(pLevelIntroText);

	m_pLevelIntroText = pLevelIntroText->AddComponent<Fluffy::Text>("Stage X", GetDefaultFont(), Fluffy::TextAlignment::Center);
	pLevelIntroText->SetActive(false);

	std::shared_ptr<Fluffy::GameObject> pGameOverScreen{ std::make_shared<Fluffy::GameObject>(SCREEN_SIZE / 2.0f) };
	pScene->Add(pGameOverScreen);

	m_pGameOverScreen = pGameOverScreen->AddComponent<GameOverScreen>();
	pGameOverScreen->SetActive(false);
}

void UIManager::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* param)
{
	switch (eventType)
	{
	case Fluffy::EventType::OnLevelStart:
		if (const LevelStartParam* levelStartParam{ static_cast<const LevelStartParam*>(param) })
		{
			m_pLevelIntroText->SetText(std::format("Stage {}", levelStartParam->GetLevelIndex()));
			m_pLevelIntroText->GetGameObject()->SetActive(true);
		}
		break;

	case Fluffy::EventType::RemoveLevelStartText:
		m_pLevelIntroText->GetGameObject()->SetActive(false);
		break;

	case Fluffy::EventType::OnGameOver:
		if (const GameOverParam * gameOverParam{ static_cast<const GameOverParam*>(param) })
		{
			m_pGameOverScreen->SetGameStats(gameOverParam->GetShotsCount(), gameOverParam->GetHitsCount());
			m_pGameOverScreen->GetGameObject()->SetActive(true);
		}
		break;
	}
}
