#pragma once
#include <vector>

namespace Fluffy
{
	enum class EventType
	{
		OnGameStart,
		OnLevelCompleted,
		OnGameOver,
		OnPlayerShoot,
		OnDamageTaken,
		OnCharacterDeath,
		OnPlayerKilled,
		OnEnemyKilled,
		OnCollisionEnter,
		OnCollisionExit,
		OnBulletHit,
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

		void Invoke(const struct IEventParam* param = nullptr);

		inline void AddListener(class IEventListener* pListener) { m_Listeners.push_back(pListener); }
		void RemoveListener(class IEventListener* pListener);

	private:
		const EventType m_EventType;
		std::vector<class IEventListener*> m_Listeners;
	};
}

