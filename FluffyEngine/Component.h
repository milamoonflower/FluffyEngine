#pragma once
#include <memory>
#include <string>

namespace Fluffy
{
	class Component
	{
	public:

		Component(class GameObject* pOwner)
			: m_pOwner{ pOwner }
		{
		}
		virtual ~Component() = default;
		virtual void Awake() {}
		virtual void Start() {}
		virtual void Update(const float /*deltaTime*/) {}

		inline class GameObject* GetGameObject() const { return m_pOwner; }
		inline bool IsEnabled() const { return m_Enabled; }
		inline void SetEnabled(bool enabled) { m_Enabled = enabled; }

		Component(const Component&) = delete;
		Component(Component&&) = delete;
		Component& operator=(const Component&) = delete;
		Component& operator=(Component&&) = delete;

	protected:

		class GameObject* m_pOwner;
		bool m_Enabled{ true };
	};
}
