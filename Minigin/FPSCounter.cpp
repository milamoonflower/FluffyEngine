#include "FPSCounter.h"
#include "Text.h"
#include <sstream>
#include <format>
#include <iomanip>

FPSCounter::FPSCounter(GameObject* pOwner, Text* pText)
	: Component(pOwner)
	, m_pText{ pText }
{

}

void FPSCounter::Update(const float deltaTime)
{
	m_UpdateTimer += deltaTime;
	++m_CurrentIntervalFrameCount;

	if (m_UpdateTimer < m_UpdateFrequency)
		return;

	m_FPS = m_CurrentIntervalFrameCount / m_UpdateFrequency;
	m_UpdateTimer -= m_UpdateFrequency;
	m_CurrentIntervalFrameCount = 0;

	std::stringstream string{ };
	string << std::fixed << std::setprecision(1) << m_FPS << " FPS";
	m_pText->SetText(string.str());
}
