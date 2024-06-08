#pragma once
#include "Character.h"
#include "FiniteStateMachine.h"
#include "EnemyStates.h"
#include "Structs.h"
#include "CollisionLayers.h"

namespace Fluffy
{
	class GameObject;
}

class EnemyCharacter final : public Character
{
public:
	EnemyCharacter(Fluffy::GameObject* pOwner, const EnemyType type, const float speed);
	~EnemyCharacter() = default;

	EnemyCharacter(const EnemyCharacter&) = delete;
	EnemyCharacter(EnemyCharacter&&) = delete;
	EnemyCharacter& operator=(const EnemyCharacter&) = delete;
	EnemyCharacter& operator=(EnemyCharacter&&) = delete;

	void Update(const float deltaTime) override;
	inline EnemyType GetType() const { return m_Type; }
	inline EnemyStates GetState() const { return m_State; }
	void SetState(EnemyStates newState);
	FiniteStateMachine& GetFSM() { return m_FSM; }
	inline float GetSpeed() const { return m_Speed; }
	inline const BezierPath& GetEnteringPath() const { return m_EnteringPath; }
	inline const BezierPath& GetExitingPath() const { return m_ExitingPath; }
	inline void SetEnteringPath(const BezierPath& path) { m_EnteringPath = path; }

	void Kill(int killerIndex = INVALID_PLAYER_INDEX) override;

protected:
	const std::string& GetCollisionLayer() const override { return CollisionLayers::ENEMY; }
	void OnCollisionEnter(Fluffy::GameObject* pOtherGameObject) override;

private:
	BezierPath m_EnteringPath{};
	BezierPath m_ExitingPath{};

	EnemyType m_Type{};
	EnemyStates m_State{ EnemyStates::None };
	FiniteStateMachine m_FSM{};

	EnemyEnteringState m_EnteringState;
	EnemyIdleState m_IdleState;
	EnemyDivingState m_ExitingState;

	float m_Speed{ 10.0f };

	void CreateExitingPath();
};
