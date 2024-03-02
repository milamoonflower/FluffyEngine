#include <string>
#include <typeinfo>
#include <algorithm>
#include <cassert>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "Utils.h"

GameObject::GameObject(const float x, const float y)
{
	SetWorldPosition(x, y);
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

void GameObject::SetWorldPosition(const float x, const float y)
{
	SetWorldPosition(glm::vec2(x, y));
}

void GameObject::SetWorldPosition(const glm::vec2& position)
{
	m_Transform.SetPosition(position);

	if (m_pParent)
	{
		m_LocalPosition = m_pParent->GetTransform().GetPosition() - m_Transform.GetPosition();
	}
}

void GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{
	// Parent should not be one of the children, the GameObject itself, or the current parent
	if (IsChild(pParent) || (!pParent && pParent == this) || m_pParent == pParent)
		return;

	if (pParent == nullptr)
	{
		// Set new localPosition as current worldPosition
		m_Transform = m_LocalPosition;
	}
	else
	{
		if (keepWorldPosition)
		{
			// Set localPosition as (worldPosition - parent.WorldPositon)
			m_LocalPosition = m_Transform.GetPosition() - m_pParent->GetTransform().GetPosition();
		}

		// SetPositionDirty()
		// did not add this right now because we need the worldPosition immeadiately for Render()
	}

	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}

	m_pParent = pParent;

	if (m_pParent)
	{
		m_pParent->AddChild(this);
	}
}

void GameObject::AddChild(GameObject* pChild)
{
	assert(pChild != nullptr);
	
	if (std::ranges::find(m_Children, pChild) == m_Children.end())
	{
		m_Children.push_back(pChild);
	}
}

void GameObject::RemoveChild(GameObject* pChild)
{
	assert(pChild != nullptr);

	const auto it{ std::ranges::find(m_Children, pChild) };

	if (it != m_Children.end())
	{
		m_Children.erase(it);
	}
}

bool GameObject::IsChild(const GameObject* pChild)
{
	//std::ranges::find does not work here, some issue with move constructor, which weak_ptr doesn't have
	return std::find(m_Children.begin(), m_Children.end(), pChild) != m_Children.end();
}

void GameObject::SetLocalPosition(const glm::vec3& position)
{
	m_LocalPosition.SetPosition(position);
	//m_LocalPositionIsDirty = true;
}
