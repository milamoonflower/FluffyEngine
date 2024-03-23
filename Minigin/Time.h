#pragma once
#include "Singleton.h"
#include <chrono>

class Time final : public Singleton<Time>
{
public:
	static float DeltaTime();
	static std::chrono::high_resolution_clock::time_point GetCurrent();
	static void Update();

private:
	Time() = default;
	static float m_DeltaTime;
	static std::chrono::high_resolution_clock::time_point m_PreviousTime;
	static std::chrono::high_resolution_clock::time_point m_CurrentTime;
};
