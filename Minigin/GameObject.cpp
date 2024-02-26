#include <string>
#include <typeinfo>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "Utils.h"

GameObject::GameObject(const float x, const float y)
{
	SetPosition(x, y);
}

void GameObject::AddComponent(const std::weak_ptr<Component> pComponent)
{
	const auto component{ pComponent.lock() };

	if (component)
	{
		const std::string name = typeid(component.get()).name();

		m_Components.try_emplace(name);
		m_Components[name].push_back(pComponent.lock());
	}
}

void GameObject::Update(const float deltaTime)
{
	for (const auto& components : m_Components)
	{
		for (auto& component : components.second)
		{
			component.get()->Update(deltaTime);
		}
	}
}

void GameObject::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
