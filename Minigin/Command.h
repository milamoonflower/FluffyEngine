#pragma once
#include <SDL.h>

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() {};
};
