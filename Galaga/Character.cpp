#include "Character.h"
#include "IEventParam.h"

Character::Character(Fluffy::GameObject* pOwner, int livesCount)
	: Fluffy::Component(pOwner)
	, m_LivesCount{ livesCount }
{

}

void Character::Kill(int killerIndex)
{
	--m_LivesCount;

	const Fluffy::OnCharacterDeathParam eventParam{ killerIndex };
	m_OnDeath.Invoke(&eventParam);
}
