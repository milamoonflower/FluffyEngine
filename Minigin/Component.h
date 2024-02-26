#pragma once
#include <memory>

class Component
{
public:
	Component(const std::weak_ptr<class GameObject> pOwner);
	virtual ~Component() = default;
	virtual void Update(const float /*deltaTime*/) {}

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

protected:
	// Returning as shared_ptr so that components can use it, instead of having to check for validity and lock every time everywhere
	std::shared_ptr<class GameObject> GetOwner() const;

private:
	std::weak_ptr<class GameObject> m_pOwner;
};
