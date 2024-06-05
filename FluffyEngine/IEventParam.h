#pragma once
namespace Fluffy
{
	struct IEventParam
	{
		// Empty interface
	};

	struct CollisionParam : public Fluffy::IEventParam
	{
	public:
		CollisionParam(class RectColliderComponent* pReceiverCollider, class RectColliderComponent* pOtherCollider)
			: m_pReceiverCollider{ pReceiverCollider }
			, m_pOtherCollider{ pOtherCollider }
		{
		}

		inline class RectColliderComponent* GetReceiverCollider() const { return m_pReceiverCollider; }
		inline class RectColliderComponent* GetOtherCollider() const { return m_pOtherCollider; }

	private:
		class RectColliderComponent* m_pReceiverCollider;
		class RectColliderComponent* m_pOtherCollider;
	};
}
