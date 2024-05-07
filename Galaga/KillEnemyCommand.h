#pragma once
#include "Command.h"
#include "glm/glm.hpp"

namespace Fluffy
{
	class Command;
}

class KillEnemyCommand final : public Fluffy::Command
{
public:
	KillEnemyCommand(int playerIndex);
	~KillEnemyCommand() = default;

	KillEnemyCommand(const KillEnemyCommand& other) = default;
	KillEnemyCommand& operator=(const KillEnemyCommand& other) = default;
	KillEnemyCommand(KillEnemyCommand&& other) = default;
	KillEnemyCommand& operator=(KillEnemyCommand&& other) = default;

	void Execute() override;

private:
	const int m_PlayerIndex;
};
