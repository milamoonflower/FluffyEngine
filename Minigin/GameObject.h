#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include "Transform.h"

class Texture2D;
class Component;

class GameObject final
{
public:
	template<typename T>
	void AddComponent(const std::weak_ptr<T> pComponent)
	{
		const auto component{ pComponent.lock() };

		if (component)
		{
			const std::string name = typeid(component.get()).name();

			m_Components.try_emplace(name);
			m_Components[name].push_back(pComponent.lock());
		}
	}

	template<typename T>
	T* GetComponentOfType()
	{
		const std::string name{ typeid(T*).name() };
		return reinterpret_cast<T*>(m_Components[name][0].get());
	}

	template<typename T>
	const std::vector<std::shared_ptr<Component>>& GetComponentsOfType()
	{
		const std::string name{ typeid(T*).name() };
		return m_Components[name];
	}

	inline const std::unordered_map<std::string, std::vector<std::shared_ptr<Component>>>& GetAllComponents() const { return m_Components; }
	
	template<typename T>
	void RemoveAllComponentsOfType()
	{
		const std::string name{ typeid(T).name() };
		m_Components.erase(name);
	}
	void Update(const float deltaTime);

	void SetParent(GameObject* pParent, const bool keepWorldPosition);

	inline Transform GetTransform() const { return m_LocalTransform; }
	glm::vec2 GetWorldPosition() const;
	void SetWorldPosition(const float x, const float y);
	void SetWorldPosition(const glm::vec2& position);
	void SetLocalPosition(const float x, const float y);
	void SetLocalPosition(const glm::vec2& position);
	inline bool IsDestroyed() const { return m_IsDestroyed; }
	//inline bool IsLocalPositionDirty() const { return m_LocalPositionIsDirty; }

	GameObject() = default;
	GameObject(const float x, const float y);
	~GameObject() = default;
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

private:
	Transform m_LocalTransform{};
	//bool m_LocalPositionIsDirty{ false };
	bool m_IsDestroyed{ false };

	GameObject* m_pParent{ };
	std::vector<GameObject*> m_Children{ };

	std::unordered_map<std::string, std::vector<std::shared_ptr<Component>>> m_Components;

	void AddChild(GameObject* pChild);
	void RemoveChild(GameObject* pChild);
	bool IsChild(const GameObject* pChild);
};
