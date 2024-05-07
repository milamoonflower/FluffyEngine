#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <chrono>
#include <thread>
#include "FluffyEngine.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "FluffyTime.h"

namespace Fluffy
{
	SDL_Window* g_Window{};

	void PrintSDLVersion()
	{
		SDL_version version{};
		SDL_VERSION(&version);
		printf("We compiled against SDL version %u.%u.%u ...\n",
			version.major, version.minor, version.patch);

		SDL_GetVersion(&version);
		printf("We are linking against SDL version %u.%u.%u.\n",
			version.major, version.minor, version.patch);

		SDL_IMAGE_VERSION(&version);
		printf("We compiled against SDL_image version %u.%u.%u ...\n",
			version.major, version.minor, version.patch);

		version = *IMG_Linked_Version();
		printf("We are linking against SDL_image version %u.%u.%u.\n",
			version.major, version.minor, version.patch);

		SDL_TTF_VERSION(&version)
			printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
				version.major, version.minor, version.patch);

		version = *TTF_Linked_Version();
		printf("We are linking against SDL_ttf version %u.%u.%u.\n",
			version.major, version.minor, version.patch);
	}

	FluffyEngine::FluffyEngine(const std::string& dataPath)
	{
		PrintSDLVersion();

		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
		}

		g_Window = SDL_CreateWindow(
			"Galaga",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			640,
			480,
			SDL_WINDOW_OPENGL
		);

		if (g_Window == nullptr)
		{
			throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
		}

		Renderer::GetInstance().Init(g_Window);

		ResourceManager::GetInstance().Init(dataPath);
	}

	FluffyEngine::~FluffyEngine()
	{
		Renderer::GetInstance().Destroy();
		SDL_DestroyWindow(g_Window);
		g_Window = nullptr;
		SDL_Quit();
	}

	void FluffyEngine::Run(const std::function<void()>& load)
	{
		load();

		const auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;

		//const float millisecondsPerFrame{ 1.0f / 60.0f };	// 60 FPS

		while (doContinue)
		{
			FluffyTime::Update();
			doContinue = input.ProcessInput();
			sceneManager.Update(FluffyTime::DeltaTime());

			renderer.Render();

			//const auto sleepTime{ Time::GetCurrent() + std::chrono::duration<float>(millisecondsPerFrame) - std::chrono::high_resolution_clock::now()};
			//std::this_thread::sleep_for(sleepTime);
		}
	}
}
