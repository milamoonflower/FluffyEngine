#pragma once
#include "Component.h"

namespace Fluffy
{
	class GameObject;
	class Text;
}

class GameOverScreen final : public Fluffy::Component
{
public:
	GameOverScreen(Fluffy::GameObject* pOwner);

	void SetGameStats(const int shotsCount, const int hitsCount);

private:
	Fluffy::Text* m_pShotsCountText{};
	Fluffy::Text* m_pHitsCountText{};
	Fluffy::Text* m_pHitsRatioText{};
};
