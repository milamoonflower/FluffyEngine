#pragma once
#include "Command.h"

class SkipLevelCommand final : public Fluffy::Command
{
public:
	SkipLevelCommand() = default;
	~SkipLevelCommand() = default;

	SkipLevelCommand(const SkipLevelCommand& other) = default;
	SkipLevelCommand& operator=(const SkipLevelCommand& other) = default;
	SkipLevelCommand(SkipLevelCommand&& other) = default;
	SkipLevelCommand& operator=(SkipLevelCommand&& other) = default;

	void Execute() override;
};
