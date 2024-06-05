#pragma once
#include "Command.h"
#include "glm/glm.hpp"

namespace Fluffy
{
	class Command;
}

class ShootCommand final : public Fluffy::Command
{
public:
	ShootCommand(int playerIndex);
	~ShootCommand() = default;

	ShootCommand(const ShootCommand& other) = default;
	ShootCommand& operator=(const ShootCommand& other) = default;
	ShootCommand(ShootCommand&& other) = default;
	ShootCommand& operator=(ShootCommand&& other) = default;

	void Execute() override;

private:
	const int m_PlayerIndex;
	int m_ShotsFired{ 0 };
};

