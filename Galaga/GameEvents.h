#pragma once
#include "Event.h"

struct GameEvents
{
public:
	static Fluffy::Event OnGameStart;
	static Fluffy::Event OnPlayerShoot;
	static Fluffy::Event OnBulletHit;
};
