#pragma once
#include <vector>

namespace Fluffy
{
	enum class EventType
	{
		OnDamageTaken,
		OnCharacterDeath,
		OnEnemyKilled,
		OnCollision,
	};

	class Event
	{
	public:
		Event(EventType eventType);
		~Event() = default;

		Event(const Event&) = delete;
		Event(Event&&) = delete;
		Event& operator=(const Event&) = delete;
		Event& operator=(Event&&) = delete;

		void Invoke(const struct IEventParam* param);

		inline void AddListener(class IEventListener* pListener) { m_Listeners.push_back(pListener); }
		void RemoveListener(class IEventListener* pListener);

	private:
		const EventType m_EventType;
		std::vector<class IEventListener*> m_Listeners;
	};
}

