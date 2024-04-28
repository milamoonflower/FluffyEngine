#pragma once
#include "Component.h"
#include "Event.h"
class Character : public Component
{
public:
	virtual ~Character() = default;

	inline int GetLivesCount() const { return m_LivesCount; }
	inline Event& GetOnDamageTaken() { return m_OnDamageTaken; }
	inline Event& GetOnDeath() { return m_OnDeath; }

	void Kill(int killerIndex = 0);

protected:
	Character(class GameObject* pOwner, int livesCount);
	
	int m_LivesCount;

	Event m_OnDamageTaken{ EventType::OnDamageTaken };
	Event m_OnDeath{ EventType::OnCharacterDeath };
};

