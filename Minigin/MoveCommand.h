#pragma once
#include "Command.h"
#include "glm/glm.hpp"

class MoveCommand final : public Command
{
public:
	MoveCommand(int playerIndex, glm::vec2 direction, float speed);
	~MoveCommand() = default;

	MoveCommand(const MoveCommand& other) = default;
	MoveCommand& operator=(const MoveCommand& other) = default;
	MoveCommand(MoveCommand&& other) = default;
	MoveCommand& operator=(MoveCommand&& other) = default;

	void Execute() override;

private:
	int m_PlayerIndex;
	float m_Speed{};
	glm::vec2 m_Direction{};
};
