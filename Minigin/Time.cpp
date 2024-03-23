#include "Time.h"

float Time::m_DeltaTime;
std::chrono::high_resolution_clock::time_point Time::m_PreviousTime;
std::chrono::high_resolution_clock::time_point Time::m_CurrentTime;

float Time::DeltaTime()
{
	return m_DeltaTime;
}

std::chrono::high_resolution_clock::time_point Time::GetCurrent()
{
	return m_CurrentTime;
}

void Time::Update()
{
	m_CurrentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(m_CurrentTime - m_PreviousTime).count();
	m_PreviousTime = m_CurrentTime;
}
