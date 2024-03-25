#include "Scene.h"
#include "GameObject.h"
#include "Component.h"
#include "IRenderable.h"
#include <algorithm>

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_GameObjects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_GameObjects.erase(std::remove(m_GameObjects.begin(), m_GameObjects.end(), object), m_GameObjects.end());
}

void Scene::RemoveAll()
{
	m_GameObjects.clear();
}

void Scene::Update(const float deltaTime)
{
	for (int i = int(m_GameObjects.size()) - 1; i >= 0; --i)
	{
		const auto& object{ m_GameObjects[i] };

		if (object->IsDestroyed())
		{
			Remove(object);
		}
		else
		{
			object->Update(deltaTime);
		}
	}
}

void Scene::Render() const
{
	for (const auto& object : m_GameObjects)
	{
		const std::unordered_map<std::string, std::vector<std::shared_ptr<Component>>> components{ object->GetAllComponents() };

		for (auto& type : components)
		{
			for (auto& component : type.second)
			{
				// Do NOT do this for every element in the vector, just one is enough
				if (IRenderable* renderable = dynamic_cast<IRenderable*>(component.get()))
				{
					renderable->Render();
				}
			}
		}
	}
}
