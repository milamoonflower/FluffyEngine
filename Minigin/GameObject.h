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
	void AddComponent(const std::weak_ptr<Component> pComponent);

	template<typename T>
	const std::vector<std::shared_ptr<Component>>& GetComponentsOfType()
	{
		const std::string name{ type_info(T).name() };
		return m_Components[name];
	}

	inline const std::unordered_map<std::string, std::vector<std::shared_ptr<Component>>>& GetAllComponents() const { return m_Components; }
	
	template<typename T>
	void RemoveAllComponentsOfType()
	{
		const std::string name{ type_info(T).name() };
		m_Components.erase(name);
	}
	void Update(const float deltaTime);

	inline Transform GetTransform() const { return m_Transform; }
	void SetPosition(const float x, const float y);

	GameObject() = default;
	GameObject(const float x, const float y);
	~GameObject() = default;
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

private:
	Transform m_Transform{};

	std::unordered_map<std::string, std::vector<std::shared_ptr<Component>>> m_Components;
};
