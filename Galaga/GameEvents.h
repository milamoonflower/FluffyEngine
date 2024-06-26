#pragma once
#include "Event.h"

struct GameEvents
{
public:
	static Fluffy::Event OnLevelStart;
	static Fluffy::Event RemoveLevelStartText;
	static Fluffy::Event OnLevelCompleted;
	static Fluffy::Event OnGameOver;
	static Fluffy::Event OnPlayerShoot;
	static Fluffy::Event OnBulletHit;
};
