#pragma once
#include "Command.h"
#include "glm/glm.hpp"

class SuicideCommand final : public Command
{
public:
	SuicideCommand(int playerIndex);
	~SuicideCommand() = default;

	SuicideCommand(const SuicideCommand& other) = default;
	SuicideCommand& operator=(const SuicideCommand& other) = default;
	SuicideCommand(SuicideCommand&& other) = default;
	SuicideCommand& operator=(SuicideCommand&& other) = default;

	void Execute() override;

private:
	const int m_PlayerIndex;
};
