#pragma once
#include "Singleton.h"
#include "MoveCommand.h"
#include <SDL.h>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		inline void SetInputReceiver(GameObject* pReceiver) { m_pInputReceiver = pReceiver; }
		bool ProcessInput();
		void MapInput(SDL_Scancode input, Command* pCommand);

	private:
		GameObject* m_pInputReceiver{ nullptr };
		std::unordered_map<SDL_Scancode, Command*> m_MappedInputs{};
	};

}
