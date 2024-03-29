#include "InputManager.h"
#include "backends/imgui_impl_sdl2.h"
#include <SDL.h>

void dae::InputManager::AddDevice(std::unique_ptr<BaseInputDevice> pDevice)
{
	m_InputDevices.push_back(std::move(pDevice));
}

void dae::InputManager::RemoveDevice(std::unique_ptr<BaseInputDevice> pDevice)
{
	m_InputDevices.erase(std::ranges::find(m_InputDevices, pDevice));
}

bool dae::InputManager::ProcessInput()
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
