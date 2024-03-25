#pragma once
// Empty interface
struct IEventParam
{
};

struct OnCharacterDeathParam : public IEventParam
{
	OnCharacterDeathParam(int playerIndex)
		: killer { playerIndex }
	{
	}

	int killer;
};
