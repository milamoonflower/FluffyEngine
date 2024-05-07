#pragma once
#include "Singleton.h"
#include <chrono>

namespace Fluffy
{
	class FluffyTime final : public Singleton<FluffyTime>
	{
	public:
		static float DeltaTime();
		static std::chrono::high_resolution_clock::time_point GetCurrent();
		static void Update();

	private:
		FluffyTime() = default;
		static float m_DeltaTime;
		static std::chrono::high_resolution_clock::time_point m_PreviousTime;
		static std::chrono::high_resolution_clock::time_point m_CurrentTime;
	};
}
