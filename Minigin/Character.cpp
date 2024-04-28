#include "Character.h"
#include "IEventParam.h"

Character::Character(GameObject* pOwner, int livesCount)
	: Component(pOwner)
	, m_LivesCount{ livesCount }
{

}

void Character::Kill(int killerIndex)
{
	--m_LivesCount;

	const OnCharacterDeathParam eventParam{ killerIndex };
	m_OnDeath.Invoke(&eventParam);
}
