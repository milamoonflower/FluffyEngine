#include "SceneManager.h"
#include "Scene.h"

namespace Fluffy
{
	void SceneManager::Update(const float deltaTime)
	{
		for (auto& scene : m_Scenes)
		{
			scene->Update(deltaTime);
		}
	}

	void SceneManager::Render()
	{
		for (const auto& scene : m_Scenes)
		{
			scene->Render();
		}
	}

	Scene& SceneManager::CreateScene(const std::string& name)
	{
		const auto& scene = std::shared_ptr<Scene>(new Scene(name));
		m_Scenes.push_back(scene);
		return *scene;
	}
}
