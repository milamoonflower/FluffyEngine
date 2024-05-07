#pragma once
#include <SDL.h>

namespace Fluffy
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() {};
	};
}
