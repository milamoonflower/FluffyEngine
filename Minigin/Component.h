#pragma once
#include <memory>
#include <string>

class Component
{
public:
	virtual ~Component() = default;
	virtual void Update(const float /*deltaTime*/) {}
	virtual std::string GetTypename() = 0;

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

protected:
	Component(const std::weak_ptr<class GameObject> pOwner);
	// Returning as shared_ptr so that components can use it, instead of having to check for validity and lock every time everywhere
	std::shared_ptr<class GameObject> GetOwner() const;

private:
	std::weak_ptr<class GameObject> m_pOwner;
};
