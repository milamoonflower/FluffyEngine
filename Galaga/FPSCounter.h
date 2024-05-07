#pragma once
#include "Component.h"

namespace Fluffy
{
	class GameObject;
	class Component;
	class Text;
}

class FPSCounter : public Fluffy::Component
{
public:
	FPSCounter(Fluffy::GameObject* pOwner, Fluffy::Text* pText);
	void Update(const float deltaTime) override;
	std::string GetTypeName() override { return typeid(*this).name(); }
	inline float GetCurrentFPS() const { return m_FPS; }

private:
	class Fluffy::Text* m_pText;
	float m_FPS{ 0.0f };
	const float m_UpdateFrequency{ 0.5f };
	float m_UpdateTimer{ 0.0f };
	int m_CurrentIntervalFrameCount{ 0 };
};
