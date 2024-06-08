#pragma once
#include "Command.h"

class ToggleSoundCommand final : public Fluffy::Command
{
public:
	ToggleSoundCommand() = default;
	~ToggleSoundCommand() = default;

	ToggleSoundCommand(const ToggleSoundCommand& other) = default;
	ToggleSoundCommand& operator=(const ToggleSoundCommand& other) = default;
	ToggleSoundCommand(ToggleSoundCommand&& other) = default;
	ToggleSoundCommand& operator=(ToggleSoundCommand&& other) = default;

	void Execute() override;
};
