#include "EnemyCharacter.h"
#include "GameObject.h"

EnemyCharacter::EnemyCharacter(const std::weak_ptr<GameObject> pOwner)
	: Character(pOwner, 1)
{

}
