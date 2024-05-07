#pragma once
#include "Command.h"
#include "glm/glm.hpp"

namespace Fluffy
{
	class Command;
}

class MoveCommand final : public Fluffy::Command
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
