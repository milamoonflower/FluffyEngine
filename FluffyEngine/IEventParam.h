#pragma once
// Empty interface
namespace Fluffy
{
	struct IEventParam
	{
	};

	struct OnCharacterDeathParam : public IEventParam
	{
		OnCharacterDeathParam(int playerIndex)
			: killer{ playerIndex }
		{
		}

		int killer;
	};

	struct OnCollisionParam : public IEventParam 
	{
		OnCollisionParam(class SpriteColliderComponent* collider)
			: pCollider{ collider }
		{
		}

		class SpriteColliderComponent* pCollider;
	};
}
