#include "EnemyCharacter.h"
#include "GameObject.h"
#include "SpriteColliderComponent.h"
#include "Bullet.h"

EnemyCharacter::EnemyCharacter(Fluffy::GameObject* pOwner, const EnemyType type, const float speed)
	: Character(pOwner, 1)
	, m_Type{ type }
	, m_Speed{ speed }
	, m_EnteringState{ this }
	, m_IdleState{ this }
	, m_ExitingState{ this }
{
	CreateExitingPath();
}

void EnemyCharacter::Update(const float deltaTime)
{
	m_FSM.Update(deltaTime);
}

void EnemyCharacter::SetState(EnemyStates newState)
{
	switch (newState)
	{
	case EnemyStates::Entering:
		m_FSM.EnterState(&m_EnteringState);
		break;

	case EnemyStates::Idle :
		m_FSM.EnterState(&m_IdleState);
		break;

	case EnemyStates::Diving:
		m_FSM.EnterState(&m_ExitingState);
		break;
	}

	m_State = newState;
}

void EnemyCharacter::Kill(int killerIndex /*= INVALID_PLAYER_INDEX*/)
{
	Character::Kill(killerIndex);

	m_pOwner->Destroy();
}

void EnemyCharacter::OnCollisionEnter(Fluffy::GameObject* pOtherGameObject)
{
	Bullet* pBullet{};
	if (pOtherGameObject->TryGetComponent<Bullet>(pBullet) && pBullet->GetOwnerIndex() != INVALID_PLAYER_INDEX)
	{
		Kill(pBullet->GetOwnerIndex());
		pBullet->OnTargetHit();
	}
}

void EnemyCharacter::CreateExitingPath()
{
	const BezierCurve lineDown{ { 0.0f, 0.0f }, { 0.0f, 0.0f },
								{ 0.0f, 480.0f }, { 0.0f, 480.0f } };
	const BezierCurve lineUp{ { 0.0f, 480.0f }, { 0.0f, 480.0f },
								{ 0.0f, 0.0f }, { 0.0f, 0.0f } };
	m_ExitingPath.AddCurve(lineDown, 1);
	m_ExitingPath.AddCurve(lineUp, 1);
}
