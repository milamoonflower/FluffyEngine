#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FluffyEngine.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Text.h"
#include "Scene.h"
#include "GameObject.h"
#include "Sprite.h"
#include "FPSCounter.h"
#include "Rotator.h"
#include "InputManager.h"
#include "Controller.h"
#include "Keyboard.h"
#include "GameManager.h"
#include "ScoreComponent.h"
#include "PlayerCharacter.h"
#include "HealthDisplayComponent.h"
#include "MoveCommand.h"
#include "ShootCommand.h"
#include "SkipLevelCommand.h"
#include "ToggleSoundCommand.h"
#include "BulletsManager.h"
#include "CollidersHandler.h"
#include "CollisionLayers.h"
#include "Structs.h"
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"
#include "SoundManager.h"
#include "UIManager.h"
#include "CharactersManager.h"
#include "BackgroundScroller.h"

using namespace Fluffy;

static void CreateScene()
{
	CollidersHandler::GetInstance().RegisterCollisionLayers(CollisionLayers::LAYERS, CollisionLayers::LAYER_INTERACTIONS);

	auto& scene = SceneManager::GetInstance().CreateScene("MainScene");

	std::shared_ptr<GameObject> pBackground{ std::make_shared<GameObject>(SCREEN_SIZE / 2.0f) };
	pBackground->AddComponent<BackgroundScroller>("bg.png");
	scene.Add(pBackground);

	std::shared_ptr<GameObject> pGameManager{ std::make_shared<GameObject>(SCREEN_SIZE / 2.0f) };
	pGameManager->AddComponent<GameManager>();
	scene.Add(pGameManager);

	CharactersManager::GetInstance().SetScene(&scene);
	BulletsManager::GetInstance().SetScene(&scene);

	UIManager::GetInstance().CreateUIPanels(&scene);

	std::unique_ptr<Keyboard> keyboard = std::make_unique<Keyboard>();

	const KeyboardInput k_left{ SDL_SCANCODE_A, InputState::Held };
	const KeyboardInput k_right{ SDL_SCANCODE_D, InputState::Held };
	const KeyboardInput k_Space{ SDL_SCANCODE_SPACE, InputState::Held };
	const KeyboardInput k_F1{ SDL_SCANCODE_F1, InputState::Released };
	const KeyboardInput k_F2{ SDL_SCANCODE_F2, InputState::Released };

	keyboard->AddCommand(k_left, std::make_unique<MoveCommand>(0, glm::vec2(-1.0f, 0.0f), 200.0f));
	keyboard->AddCommand(k_right, std::make_unique<MoveCommand>(0, glm::vec2(1.0f, 0.0f), 200.0f));
	keyboard->AddCommand(k_Space, std::make_unique<ShootCommand>(0));
	keyboard->AddCommand(k_F1, std::make_unique<SkipLevelCommand>());
	keyboard->AddCommand(k_F2, std::make_unique<ToggleSoundCommand>());

	std::unique_ptr<Controller> controller = std::make_unique<Controller>();

	const ControllerInput c_left{ Button::GAMEPAD_DPAD_LEFT, InputState::Held };
	const ControllerInput c_right{ Button::GAMEPAD_DPAD_RIGHT, InputState::Held };
	const ControllerInput c_B{ Button::GAMEPAD_B, InputState::Held };

	// since we don't have multiplayer right now, we're using both keyboard and gamepad for the same player index
	controller->AddCommand(c_left, std::make_unique<MoveCommand>(0, glm::vec2(-1.0f, 0.0f), 200.0f));
	controller->AddCommand(c_right, std::make_unique<MoveCommand>(0, glm::vec2(1.0f, 0.0f), 200.0f));
	controller->AddCommand(c_B, std::make_unique<ShootCommand>(0));

	auto& input = InputManager::GetInstance();
	input.AddDevice(std::move(keyboard));
	input.AddDevice(std::move(controller));

	ServiceLocator::RegisterSoundSystem(std::make_unique<SDLSoundSystem>());
	SoundManager::GetInstance();	// Create the sound manager

	GameManager::GetInstance()->StartLevel(1);

	std::shared_ptr<GameObject> pPlayerHealthDisplay{ std::make_shared<GameObject>(30.0f, SCREEN_SIZE.y - 30.0f) };
	pPlayerHealthDisplay->AddComponent<HealthDisplayComponent>(0);
	scene.Add(pPlayerHealthDisplay);

	std::shared_ptr<GameObject> pPlayerScoreDisplay{ std::make_shared<GameObject>(20.0f, 20.0f) };
	pPlayerScoreDisplay->AddComponent<ScoreComponent>(0, UIManager::GetInstance().GetDefaultFont());
	scene.Add(pPlayerScoreDisplay);
}

void load()
{
	CreateScene();
}

int main(int, char* [])
{
	Fluffy::FluffyEngine engine("../Data/");
	engine.Run(load);
	return 0;
}
