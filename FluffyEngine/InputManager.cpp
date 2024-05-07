#include "InputManager.h"
#include <SDL.h>

namespace Fluffy
{
	void InputManager::AddDevice(std::unique_ptr<BaseInputDevice> pDevice)
	{
		m_InputDevices.push_back(std::move(pDevice));
	}

	void InputManager::RemoveDevice(std::unique_ptr<BaseInputDevice> pDevice)
	{
		m_InputDevices.erase(std::ranges::find(m_InputDevices, pDevice));
	}

	bool InputManager::ProcessInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				return false;
			}

			for (const auto& pDevice : m_InputDevices)
			{
				pDevice->Update();
				pDevice->HandleInput();
			}

			//ImGui_ImplSDL2_ProcessEvent(&e);
		}

		return true;
	}
}
