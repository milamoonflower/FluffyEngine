#pragma once
#include "Command.h"
#include "GameObject.h"
#include "MoveComponent.h"
#include "glm/glm.hpp"

class MoveCommand final : public Command
{
public:
	void Execute(GameObject* pGameObject) override
	{
		pGameObject->GetComponentOfType<MoveComponent>()->Move(glm::vec2(0.0f, 1.0f));
	}
};
