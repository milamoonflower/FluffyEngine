#pragma once
#include "Component.h"
#include "Event.h"
#include "IEventListener.h"
#include <string>
#include <glm\glm.hpp>

namespace Fluffy
{
	class GameObject;
	class Event;
	class SpriteColliderComponent;
	struct IEventParam;
}

const int INVALID_PLAYER_INDEX{ -1 };

class Character : public Fluffy::Component, public Fluffy::IEventListener
{
public:
	virtual ~Character() = default;

	void Start() override;

	inline int GetLivesCount() const { return m_LivesCount; }
	inline const glm::vec2& GetSpriteSize() const { return m_SpriteSize; }
	inline Fluffy::Event& GetOnDamageTaken() { return m_OnDamageTaken; }
	inline Fluffy::Event& GetOnDeath() { return m_OnDeath; }

	virtual int GetPlayerIndex() const { return INVALID_PLAYER_INDEX; }
	virtual void Kill(int killerIndex = INVALID_PLAYER_INDEX);

	void OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* pParam) override;

protected:
	Character(Fluffy::GameObject* pOwner, int livesCount);

	virtual const std::string& GetCollisionLayer() const = 0;
	virtual void OnCollisionEnter(Fluffy::GameObject* pOtherGameObject) = 0;

	glm::vec2 m_SpriteSize{};
	int m_LivesCount;

	Fluffy::Event m_OnDamageTaken{ Fluffy::EventType::OnDamageTaken };
	Fluffy::Event m_OnDeath{ Fluffy::EventType::OnCharacterDeath };
};
