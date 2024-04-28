#pragma once
#include "Character.h"

class EnemyCharacter final : public Character
{
public:
	EnemyCharacter(class GameObject* pOwner);
	~EnemyCharacter() = default;

	/*EnemyCharacter(const EnemyCharacter&) = delete;
	EnemyCharacter(EnemyCharacter&&) = delete;
	EnemyCharacter& operator=(const EnemyCharacter&) = delete;
	EnemyCharacter& operator=(EnemyCharacter&&) = delete;*/

	std::string GetTypeName() override { return typeid(*this).name(); }
};

