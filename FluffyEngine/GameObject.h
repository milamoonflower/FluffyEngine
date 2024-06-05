#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include "Transform.h"

namespace Fluffy
{
	class Component;

	class GameObject final
	{
	public:

		template <typename ComponentType, typename... Args>
			requires std::derived_from<ComponentType, Component>
		ComponentType* AddComponent(Args&&... args)
		{
			std::unique_ptr<ComponentType> newComponent = std::make_unique<ComponentType>(this, std::forward<Args>(args)...);

			Component* pRawComponent{ newComponent.get() };

			if (pRawComponent)
			{
				const std::string name = typeid(ComponentType).name();

				m_Components.try_emplace(name);
				m_Components[name].push_back(std::move(newComponent));
				m_RawComponents.push_back(pRawComponent);
			}

			pRawComponent->Awake();

			return reinterpret_cast<ComponentType*>(pRawComponent);
		}

		template<typename ComponentType>
		ComponentType* GetComponent()
		{
			const std::string name{ typeid(ComponentType).name() };

			const auto& components{ m_Components.find(name) };
			if (components == m_Components.end() || components->second.empty())
				return nullptr;

			return reinterpret_cast<ComponentType*>(components->second.at(0).get());
		}

		template<typename ComponentType>
		const ComponentType* GetComponent() const
		{
			const std::string name{ typeid(ComponentType).name() };

			const auto& components{ m_Components.find(name) };
			if (components == m_Components.end() || components->second.empty())
				return nullptr;

			return reinterpret_cast<const ComponentType*>(components->second.at(0).get());
		}

		template<typename ComponentType>
		bool TryGetComponent(ComponentType*& pOutComponent)
		{
			pOutComponent = GetComponent<ComponentType>();
			return pOutComponent != nullptr;
		}

		template<typename ComponentType>
		bool TryGetComponent(const ComponentType*& pOutComponent) const
		{
			pOutComponent = GetComponent<ComponentType>();
			return pOutComponent != nullptr;
		}

		template<typename ComponentType>
		bool HasComponent() const
		{
			return GetComponent<ComponentType>() != nullptr;
		}

		template<typename ComponentType>
		const std::vector<Component*>& GetComponents()
		{
			const std::string name{ typeid(ComponentType).name() };
			std::vector<ComponentType*> components{};

			for (const auto& component : m_Components[name])
			{
				components.push_back(component.get());
			}

			return components;
		}

		const std::vector<Component*>& GetAllComponents() const;

		template<typename ComponentType>
		void RemoveAllComponentsOfType()
		{
			const std::string name{ typeid(ComponentType).name() };

			for (int i{ m_Components[name].size() }; i > 0; --i)
			{
				m_RawComponents.erase(std::ranges::find(m_RawComponents, m_Components[name][i]));
			}

			m_Components.erase(name);
		}

		void Start() const;
		void Update(const float deltaTime) const;
		inline class Scene* GetScene() const { return m_pScene; }
		inline void SetCurrentScene(class Scene* pScene) { m_pScene = pScene; }

		void SetParent(GameObject* pParent, const bool keepWorldPosition);

		inline Transform& GetTransform() { return m_LocalTransform; }
		inline const Transform& GetTransform() const { return m_LocalTransform; }
		glm::vec2 GetWorldPosition() const;
		void SetWorldPosition(const float x, const float y);
		void SetWorldPosition(const glm::vec2& position);
		void SetLocalPosition(const float x, const float y);
		void SetLocalPosition(const glm::vec2& position);
		inline bool IsActive() const { return m_IsActive && !m_IsDestroyed; }
		inline void SetActive(bool isActive) { m_IsActive = isActive; }
		inline void Destroy() { m_IsDestroyed = true; }
		inline bool IsDestroyed() const { return m_IsDestroyed; }
		//inline bool IsLocalPositionDirty() const { return m_LocalPositionIsDirty; }

		GameObject() = default;
		GameObject(const float x, const float y);
		GameObject(const glm::vec2& position);
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<Component*> m_RawComponents{};
		Transform m_LocalTransform{};
		//bool m_LocalPositionIsDirty{ false };
		bool m_IsActive{ true };
		bool m_IsDestroyed{ false };

		class Scene* m_pScene{ nullptr };

		GameObject* m_pParent{ };
		std::vector<GameObject*> m_Children{ };

		std::unordered_map<std::string, std::vector<std::unique_ptr<Component>>> m_Components;

		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);
		bool IsChild(const GameObject* pChild);
	};
}
