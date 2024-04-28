#pragma once
#include "Component.h"

class FPSCounter : public Component
{
public:
	FPSCounter(GameObject* pOwner, class Text* pText);
	void Update(const float deltaTime) override;
	std::string GetTypeName() override { return typeid(*this).name(); }
	inline float GetCurrentFPS() const { return m_FPS; }

private:
	class Text* m_pText;
	float m_FPS{ 0.0f };
	const float m_UpdateFrequency{ 0.5f };
	float m_UpdateTimer{ 0.0f };
	int m_CurrentIntervalFrameCount{ 0 };
};
