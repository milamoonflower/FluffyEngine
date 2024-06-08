#pragma once
#include "Character.h"
#include "CollisionLayers.h"
#include <glm\glm.hpp>

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

	int GetPlayerIndex() const override { return m_PlayerIndex; }
	void Kill(int killerIndex = INVALID_PLAYER_INDEX) override;
	bool IsDead() const override;
	void Respawn();

protected:
	const std::string& GetCollisionLayer() const override { return CollisionLayers::PLAYER; }
	void OnCollisionEnter(Fluffy::GameObject* pOtherGameObject) override;

private:
	const int m_PlayerIndex;
	const glm::vec2 m_RespawnPosition;
};
