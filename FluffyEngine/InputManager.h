#pragma once
#include "BaseInputDevice.h"
#include "Singleton.h"
#include <SDL.h>
#include <memory>
#include <vector>

namespace Fluffy
{
	enum class InputDeviceType
	{
		Controller,
		Keyboard
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		~InputManager() = default;

		InputManager(const InputManager& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

		void AddDevice(std::unique_ptr<BaseInputDevice> pDevice);
		void RemoveDevice(std::unique_ptr<BaseInputDevice> pDevice);

		bool ProcessInput();

	private:
		std::vector<std::unique_ptr<BaseInputDevice>> m_InputDevices{};
	};

}
