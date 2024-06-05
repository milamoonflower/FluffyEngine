#pragma once
#include "Character.h"

namespace Fluffy
{
	class GameObject;
}

class EnemyCharacter final : public Character
{
public:
	EnemyCharacter(Fluffy::GameObject* pOwner);
	~EnemyCharacter() = default;

	/*EnemyCharacter(const EnemyCharacter&) = delete;
	EnemyCharacter(EnemyCharacter&&) = delete;
	EnemyCharacter& operator=(const EnemyCharacter&) = delete;
	EnemyCharacter& operator=(EnemyCharacter&&) = delete;*/

};

