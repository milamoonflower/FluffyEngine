#pragma once
#include <memory>
#include <string>

class Component
{
public:

	Component(class GameObject* pOwner)
		: m_pOwner{ pOwner }
	{
	}
	virtual ~Component() = default;
	virtual void Update(const float /*deltaTime*/) {}
	virtual std::string GetTypeName() = 0;

	inline class GameObject* GetGameObject() const { return m_pOwner; }

	Component(const Component&) = delete;
	Component(Component &&) = delete;
	Component& operator=(const Component&) = delete;
	Component& operator=(Component&&) = delete;

protected:

	class GameObject* m_pOwner;
};
