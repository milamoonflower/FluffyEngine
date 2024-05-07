#include "FluffyTime.h"

namespace Fluffy
{
	float FluffyTime::m_DeltaTime;
	std::chrono::high_resolution_clock::time_point FluffyTime::m_PreviousTime;
	std::chrono::high_resolution_clock::time_point FluffyTime::m_CurrentTime;

	float FluffyTime::DeltaTime()
	{
		return m_DeltaTime;
	}

	std::chrono::high_resolution_clock::time_point FluffyTime::GetCurrent()
	{
		return m_CurrentTime;
	}

	void FluffyTime::Update()
	{
		m_CurrentTime = std::chrono::high_resolution_clock::now();
		m_DeltaTime = std::chrono::duration<float>(m_CurrentTime - m_PreviousTime).count();
		m_PreviousTime = m_CurrentTime;
	}
}
