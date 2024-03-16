#pragma once
#include "Component.h"

class FPSCounter : public Component
{
public:
	FPSCounter(const std::weak_ptr<GameObject> pOwner, const std::weak_ptr<class Text> pText);
	void Update(const float deltaTime) override;
	std::string GetTypename() override { return "FPSCounter"; }
	inline float GetCurrentFPS() const { return m_FPS; }

private:
	std::shared_ptr<class Text> m_pText;	// Does not own the text component
	float m_FPS{ 0.0f };
	const float m_UpdateFrequency{ 0.5f };
	float m_UpdateTimer{ 0.0f };
	int m_CurrentIntervalFrameCount{ 0 };
};
