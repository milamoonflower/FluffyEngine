#pragma once
#include "Command.h"
#include "GameObject.h"
#include "glm/glm.hpp"

class MoveCommand final : public Command
{
public:
	MoveCommand(GameObject* pGameObject, glm::vec2 direction, float speed);
	~MoveCommand() = default;

	MoveCommand(const MoveCommand& other) = default;
	MoveCommand& operator=(const MoveCommand& other) = default;
	MoveCommand(MoveCommand&& other) = default;
	MoveCommand& operator=(MoveCommand&& other) = default;

	void Execute() override;

private:
	GameObject* m_pGameObject;
	float m_Speed{};
	glm::vec2 m_Direction{};
};
