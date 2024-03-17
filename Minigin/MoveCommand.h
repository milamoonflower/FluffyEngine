#pragma once
#include "Command.h"
#include "GameObject.h"
#include "MoveComponent.h"
#include "glm/glm.hpp"

class MoveCommand final : public Command
{
public:
	void Execute(GameObject* pGameObject, SDL_Scancode input) override
	{
		glm::vec2 movement{0.0f, 0.0f};

		if (input == SDL_SCANCODE_W)
			++movement.y;
		else if (input == SDL_SCANCODE_A)
			++movement.x;
		else if (input == SDL_SCANCODE_S)
			--movement.y;
		else if (input == SDL_SCANCODE_D)
			--movement.x;

		pGameObject->GetComponentOfType<MoveComponent>()->Move(movement);
	}
};
