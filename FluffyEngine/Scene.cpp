#include "Scene.h"
#include "GameObject.h"
#include "Component.h"
#include "IRenderable.h"
#include <algorithm>

namespace Fluffy
{
	unsigned int Scene::m_idCounter = 0;

	Scene::Scene(const std::string& name) : m_Name(name) {}

	Scene::~Scene() = default;

	void Scene::Add(std::shared_ptr<GameObject> object)
	{
		object->SetCurrentScene(this);
		m_NewlyAddedGameObjects.push(m_GameObjects.emplace_back(std::move(object)).get());
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
		while (!m_NewlyAddedGameObjects.empty())
		{
			m_NewlyAddedGameObjects.front()->Start();
			m_NewlyAddedGameObjects.pop();
		}

		for (int i = int(m_GameObjects.size()) - 1; i >= 0; --i)
		{
			const auto& object{ m_GameObjects[i] };

			if (object->IsDestroyed())
			{
				Remove(object);
			}
			else if (object->IsActive())
			{
				object->Update(deltaTime);
			}
		}
	}

	void Scene::Render() const
	{
		for (const auto& object : m_GameObjects)
		{
			if (!object->IsActive())
				continue;

			const std::vector<Component*> components{ object->GetAllComponents() };

			for (auto& component : components)
			{
				if (component->IsEnabled())
				{
					if (IRenderable* renderable = dynamic_cast<IRenderable*>(component))
					{
						renderable->Render();
					}
				}
			}
		}
	}
}
