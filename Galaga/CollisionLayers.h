#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace CollisionLayers
{
	const std::string PLAYER{ "Player" };
	const std::string ENEMY{ "Enemy" };
	const std::string BULLET{ "Bullet" };
	const std::string PLAYABLE_AREA{ "PlayableArea" };

	const std::vector<std::string> LAYERS
	{
		PLAYER,
		ENEMY,
		BULLET,
		PLAYABLE_AREA,
	};

	const std::unordered_map<std::string, std::vector<std::string>> LAYER_INTERACTIONS
	{
		{ PLAYER, { ENEMY, BULLET } },
		{ ENEMY, { PLAYER, BULLET } },
		{ BULLET, { } },	// Bullet doesn't need to check any collisions itself; the PLAYER and ENEMIES will check bullets
		{ PLAYABLE_AREA, { BULLET } },
	};
}
