#include "UIManager.h"
#include "GameObject.h"
#include "Structs.h"
#include "Font.h"
#include "GameEvents.h"
#include "EventParams.h"
#include "Scene.h"
#include <format>

UIManager::UIManager()
{
	GameEvents::OnLevelStart.AddListener(this);
	GameEvents::RemoveLevelStartText.AddListener(this);
}

UIManager::~UIManager()
{
	GameEvents::OnLevelStart.RemoveListener(this);
	GameEvents::RemoveLevelStartText.RemoveListener(this);
}

void UIManager::CreateUIPanels(Fluffy::Scene* pScene)
{
	std::shared_ptr<Fluffy::GameObject> pLevelIntroText{ std::make_shared<Fluffy::GameObject>(SCREEN_SIZE / 2.0f) };
	m_pLevelIntroText = pLevelIntroText->AddComponent<Fluffy::Text>("Stage X", GetDefaultFont(), Fluffy::TextAlignment::Center);
	pLevelIntroText->SetActive(false);

	pScene->Add(pLevelIntroText);
}

void UIManager::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* param)
{
	switch (eventType)
	{
	case Fluffy::EventType::OnLevelStart:
		if (const LevelStartParam* levelStartParam{ static_cast<const LevelStartParam*>(param) })
		{
			m_pLevelIntroText->SetText(std::format("Stage {}", 1));
			m_pLevelIntroText->GetGameObject()->SetActive(true);
		}
		break;

	case Fluffy::EventType::RemoveLevelStartText:
		m_pLevelIntroText->GetGameObject()->SetActive(false);
		break;
	}
}
