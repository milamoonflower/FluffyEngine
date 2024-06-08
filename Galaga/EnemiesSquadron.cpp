#include "EnemiesSquadron.h"
#include "GameObject.h"
#include "Event.h"

void EnemiesSquadron::Initialize(Fluffy::GameObject* pSquadronObject, Fluffy::Event& onEnemiesIdleStartEvent)
{
	m_pEnemiesSquadron = pSquadronObject;
	m_StartingPos = pSquadronObject->GetWorldPosition();

	onEnemiesIdleStartEvent.AddListener(this);
}

void EnemiesSquadron::Update(const float deltaTime)
{
	if (!m_ShouldSway)
		return;

	m_pEnemiesSquadron->GetTransform().Translate(m_CurrentDirection * m_SwaySpeed * deltaTime, 0.0f);

	const float swayDistance{ m_pEnemiesSquadron->GetWorldPosition().x - m_StartingPos.x };

	// squared for absolute distance
	if (swayDistance * swayDistance >= m_MaxSwayDistance * m_MaxSwayDistance)
		m_CurrentDirection *= -1.0f;
}

void EnemiesSquadron::Reset()
{
	m_pEnemiesSquadron->SetWorldPosition(m_StartingPos);
	m_ShouldSway = false;
}

void EnemiesSquadron::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* /*= nullptr*/)
{
	switch (eventType)
	{
	case Fluffy::EventType::OnEnemiesIdleStart:
		m_ShouldSway = true;
		break;
	}
}
