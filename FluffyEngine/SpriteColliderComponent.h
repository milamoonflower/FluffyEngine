#pragma once
#include "Component.h"
#include "Event.h"
#include "RectColliderComponent.h"
#include <glm\glm.hpp>

namespace Fluffy
{
	class GameObject;

	class SpriteColliderComponent : public RectColliderComponent
	{
	public:
		SpriteColliderComponent(GameObject* pOwner, const class Sprite* pSprite, const std::string& collisionLayerName);

		SpriteColliderComponent(const SpriteColliderComponent& other) = default;
		SpriteColliderComponent& operator=(const SpriteColliderComponent& other) = default;
		SpriteColliderComponent(SpriteColliderComponent&& other) = default;
		SpriteColliderComponent& operator=(SpriteColliderComponent&& other) = default;

		Rectf GetRect() const override;

	private:
		const class Sprite* m_pSprite;
	};
}
