#pragma once
#include <string>
#include <functional>

namespace Fluffy
{
	class FluffyEngine
	{
	public:
		explicit FluffyEngine(const std::string& dataPath);
		~FluffyEngine();
		void Run(const std::function<void()>& load);

		FluffyEngine(const FluffyEngine& other) = delete;
		FluffyEngine(FluffyEngine&& other) = delete;
		FluffyEngine& operator=(const FluffyEngine& other) = delete;
		FluffyEngine& operator=(FluffyEngine&& other) = delete;
	};
}