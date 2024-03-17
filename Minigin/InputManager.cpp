#include <SDL.h>
#include "InputManager.h"
#include "backends/imgui_impl_sdl2.h"

/*
#include "xinput.h"
#include "winbase.h"*/

dae::InputManager::~InputManager()
{
	for (auto& item : m_MappedInputs)
	{
		delete item.second;
	}
}

bool dae::InputManager::ProcessInput()
{
	/*ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);*/

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}

		const auto& command = m_MappedInputs.find(e.key.keysym.scancode);

		if (command != m_MappedInputs.end())
			command->second->Execute(m_pInputReceiver, command->first);

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void dae::InputManager::MapInput(SDL_Scancode input, Command* pCommand)
{
	m_MappedInputs[input] = pCommand;
}
