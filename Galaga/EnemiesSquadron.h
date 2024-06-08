#pragma once
#include "Event.h"
#include "IEventListener.h"
#include "glm\glm.hpp"

namespace Fluffy
{
	class GameObject;
	struct IEventParam;
}

class EnemiesSquadron final : public Fluffy::IEventListener
{
public:
	inline bool IsInitialized() const { return m_pEnemiesSquadron != nullptr; }
	void Initialize(Fluffy::GameObject* pSquadronObject, Fluffy::Event& onEnemiesIdleStartEvent);
	inline void SetMaxSwayDistance(const float maxSwayDistance) { m_MaxSwayDistance = maxSwayDistance; }
	void Update(const float deltaTime);
	void Reset();

	void OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* pParam = nullptr) override;

private:
	Fluffy::GameObject* m_pEnemiesSquadron{};
	glm::vec2 m_StartingPos{};
	float m_MaxSwayDistance{};

	const float m_SwaySpeed{ 50.0f };
	float m_CurrentDirection{ 1.0f };

	bool m_ShouldSway{ false };
};
