#include <string>
#include <typeinfo>
#include <algorithm>
#include <cassert>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "Utils.h"

namespace Fluffy
{
	GameObject::GameObject(const float x, const float y)
	{
		SetWorldPosition(x, y);
	}

	const std::vector<Component*>& GameObject::GetAllComponents() const
	{
		return m_RawComponents;
	}

	void GameObject::Update(const float deltaTime)
	{
		for (const auto& components : m_Components)
		{
			for (auto& component : components.second)
			{
				component->Update(deltaTime);
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
			m_LocalTransform.Translate(-m_pParent->GetTransform().GetPosition());
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

	void GameObject::SetParent(GameObject* pParent, const bool keepWorldPosition)
	{
		// Parent should not be one of the children, the GameObject itself, or the current parent
		if (IsChild(pParent) || (!pParent && pParent == this) || m_pParent == pParent)
			return;

		if (keepWorldPosition)
		{
			if (m_pParent != nullptr)
			{
				// Set old worldPosition as new localPosition
				m_LocalTransform.Translate(m_pParent->GetWorldPosition());
			}

			if (pParent != nullptr)
			{
				// Remove new parent's position from the localPosition
				m_LocalTransform.Translate(-pParent->GetWorldPosition());

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
		return std::ranges::find(m_Children, pChild) != m_Children.end();
	}
}
