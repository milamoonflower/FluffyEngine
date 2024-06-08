#pragma once
#include "Singleton.h"
#include "Event.h"
#include "IEventListener.h"
#include "ResourceManager.h"
#include <memory>

namespace Fluffy
{
	struct IEventParam;
	class Scene;
	class Text;
}

class UIManager final : public Fluffy::Singleton<UIManager>, public Fluffy::IEventListener
{
	friend Fluffy::Singleton<UIManager>;

public:
	~UIManager();

	void CreateUIPanels(Fluffy::Scene* pScene);
	void OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* param) override;

	inline const std::shared_ptr<class Font>& GetDefaultFont()
	{
		static std::shared_ptr<class Font> defaultFont = Fluffy::ResourceManager::GetInstance().LoadFont("emulogic.ttf", 15);
		return defaultFont;
	}

private:
	UIManager();

	Fluffy::Text* m_pLevelIntroText{};
	class GameOverScreen* m_pGameOverScreen{};
};
