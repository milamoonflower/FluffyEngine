#pragma once
#include "Singleton.h"
#include "MoveCommand.h"
#include <SDL.h>
#include <memory>
#include "BaseInputDevice.h"

namespace dae
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

		template<typename T>
		void AddDevice(std::unique_ptr<T> pDevice)
		{
			m_InputDevices.push_back(std::move(pDevice));
		}

		template<typename T>
		void RemoveDevice(std::unique_ptr<T> pDevice)
		{
			m_InputDevices.erase(std::ranges::find(m_InputDevices, pDevice));
		}

		bool ProcessInput();

	private:
		std::vector<std::unique_ptr<BaseInputDevice>> m_InputDevices{};
	};

}
