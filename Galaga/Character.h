#pragma once
#include "Component.h"
#include "Event.h"

namespace Fluffy
{
	class GameObject;
	class Event;
}
class Character : public Fluffy::Component
{
public:
	virtual ~Character() = default;

	inline int GetLivesCount() const { return m_LivesCount; }
	inline Fluffy::Event& GetOnDamageTaken() { return m_OnDamageTaken; }
	inline Fluffy::Event& GetOnDeath() { return m_OnDeath; }

	void Kill(int killerIndex = 0);

protected:
	Character(Fluffy::GameObject* pOwner, int livesCount);
	
	int m_LivesCount;

	Fluffy::Event m_OnDamageTaken{ Fluffy::EventType::OnDamageTaken };
	Fluffy::Event m_OnDeath{ Fluffy::EventType::OnCharacterDeath };
};

