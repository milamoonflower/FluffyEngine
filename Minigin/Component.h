#pragma once
#include <memory>
#include <string>

class Component
{
public:
	virtual ~Component() = default;
	virtual void Update(const float /*deltaTime*/) {}
	virtual std::string GetTypeName() = 0;

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	std::shared_ptr<class GameObject> GetGameObject() const;

protected:
	Component(const std::weak_ptr<class GameObject> pOwner);

private:
	std::weak_ptr<class GameObject> m_pOwner;
};
