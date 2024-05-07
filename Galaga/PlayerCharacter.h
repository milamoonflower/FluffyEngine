#pragma once
#include "Character.h"

namespace Fluffy
{
	class GameObject;
}

class PlayerCharacter final : public Character
{
public:
	PlayerCharacter(Fluffy::GameObject* pOwner, int livesCount, int playerIndex);
	~PlayerCharacter() = default;

	PlayerCharacter(const PlayerCharacter&) = delete;
	PlayerCharacter(PlayerCharacter&&) = delete;
	PlayerCharacter& operator=(const PlayerCharacter&) = delete;
	PlayerCharacter& operator=(PlayerCharacter&&) = delete;

	std::string GetTypeName() override { return typeid(*this).name(); }
	inline const int GetPlayerIndex() const { return m_PlayerIndex; }

private:
	const int m_PlayerIndex;
};

