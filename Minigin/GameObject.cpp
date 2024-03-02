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

glm::vec2 GameObject::GetWorldPosition() const
{
	if (m_pParent)
	{
		return m_LocalTransform.GetPosition() + m_pParent->GetWorldPosition();
	}

	return m_LocalTransform.GetPosition();
}

void GameObject::SetWorldPosition(const float x, const float y)
{
	SetWorldPosition(glm::vec2(x, y));
}

void GameObject::SetWorldPosition(const glm::vec2& position)
{
	m_LocalTransform.SetPosition(position);

	if (m_pParent)
	{
		m_LocalTransform.SetPosition(- m_pParent->GetTransform().GetPosition() + m_LocalTransform.GetPosition());
	}
}

void GameObject::SetLocalPosition(const glm::vec2& position)
{
	m_LocalTransform.SetPosition(position);
	//m_LocalPositionIsDirty = true;
}

void GameObject::SetLocalPosition(const float x, const float y)
{
	m_LocalTransform.SetPosition(x, y);
	//m_LocalPositionIsDirty = true;
}

void GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{
	// Parent should not be one of the children, the GameObject itself, or the current parent
	if (IsChild(pParent) || (!pParent && pParent == this) || m_pParent == pParent)
		return;

	if (keepWorldPosition)
	{
		if (m_pParent != nullptr)
		{
			// Set new localPosition as current worldPosition
			m_LocalTransform.SetPosition(m_LocalTransform.GetPosition() + m_pParent->GetWorldPosition());
		}

		if (pParent != nullptr)
		{
			// Set localPosition as (worldPosition - parent.WorldPositon)
			m_LocalTransform.SetPosition(m_LocalTransform.GetPosition() - pParent->GetWorldPosition());

		}
	}

	// SetPositionDirty()
	// did not add this right now because we need the worldPosition immeadiately for Render()

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
