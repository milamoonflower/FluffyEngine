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
#include "CharactersManager.h"
#include "ScoreComponent.h"
#include "PlayerCharacter.h"
#include "HealthDisplayComponent.h"
#include "SuicideCommand.h"
#include "KillEnemyCommand.h"
#include "MoveCommand.h"
#include "ShootCommand.h"
#include "BulletsManager.h"
/*
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"*/

using namespace Fluffy;

static void CreateLevel1()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Level1");

	const auto font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 15) };

	std::shared_ptr<GameObject> pMovementInfo{ std::make_shared<GameObject>(10.0f, 20.0f) };
	pMovementInfo->AddComponent<Text>("Movement: Keyboard - WASD / Controller - DPAD", font);
	scene.Add(pMovementInfo);

	std::shared_ptr<GameObject> pActionsInfo{ std::make_shared<GameObject>(10.0f, 40.0f) };
	pActionsInfo->AddComponent<Text>("Kill Enemy: Keyboard - T / Controller - B    Kill Self: Keyboard - R / Controller - Y", font);
	scene.Add(pActionsInfo);

	CharactersManager::GetInstance().CreatePlayerCharacters(scene);

	// TODO: pass <EnemyType, glm::vec2 spawnPosition>
	CharactersManager::GetInstance().SpawnEnemies(scene);
	BulletsManager::GetInstance().SetScene(&scene);

	std::shared_ptr<GameObject> pPlayer1ScoreDisplay{ std::make_shared<GameObject>(40.0f, 80.0f) };
	pPlayer1ScoreDisplay->AddComponent<ScoreComponent>(1, "Lingua.otf", 15);
	scene.Add(pPlayer1ScoreDisplay);

	std::shared_ptr<GameObject> pPlayer1HealthDisplay{ std::make_shared<GameObject>(40.0f, 95.0f) };
	pPlayer1HealthDisplay->AddComponent<HealthDisplayComponent>(1, "Lingua.otf", 15);
	scene.Add(pPlayer1HealthDisplay);

	std::shared_ptr<GameObject> pPlayer2ScoreDisplay{ std::make_shared<GameObject>(40.0f, 110.0f) };
	pPlayer2ScoreDisplay->AddComponent<ScoreComponent>(2, "Lingua.otf", 15);
	scene.Add(pPlayer2ScoreDisplay);

	std::shared_ptr<GameObject> pPlayer2HealthDisplay{ std::make_shared<GameObject>(40.0f, 125.0f) };
	pPlayer2HealthDisplay->AddComponent<HealthDisplayComponent>(2, "Lingua.otf", 15);
	scene.Add(pPlayer2HealthDisplay);

	std::unique_ptr<Keyboard> keyboard = std::make_unique<Keyboard>();

	KeyboardInput k_up{ SDL_SCANCODE_W, InputState::Previous };
	KeyboardInput k_left{ SDL_SCANCODE_A, InputState::Previous };
	KeyboardInput k_down{ SDL_SCANCODE_S, InputState::Previous };
	KeyboardInput k_right{ SDL_SCANCODE_D, InputState::Previous };
	KeyboardInput k_R{ SDL_SCANCODE_R, InputState::Released };
	KeyboardInput k_T{ SDL_SCANCODE_T, InputState::Released };
	KeyboardInput k_Space{ SDL_SCANCODE_SPACE, InputState::Released };

	keyboard->AddCommand(k_up, std::make_unique<MoveCommand>(1, glm::vec2(0.0f, -1.0f), 120.0f));
	keyboard->AddCommand(k_left, std::make_unique<MoveCommand>(1, glm::vec2(-1.0f, 0.0f), 120.0f));
	keyboard->AddCommand(k_down, std::make_unique<MoveCommand>(1, glm::vec2(0.0f, 1.0f), 120.0f));
	keyboard->AddCommand(k_right, std::make_unique<MoveCommand>(1, glm::vec2(1.0f, 0.0f), 120.0f));
	keyboard->AddCommand(k_R, std::make_unique<SuicideCommand>(1));
	//keyboard->AddCommand(k_T, std::make_unique<KillEnemyCommand>(1));
	keyboard->AddCommand(k_Space, std::make_unique<ShootCommand>(1));

	std::unique_ptr<Controller> controller = std::make_unique<Controller>();

	ControllerInput up{ Button::XINPUT_GAMEPAD_DRAD_UP, InputState::Previous };
	ControllerInput left{ Button::XINPUT_GAMEPAD_DRAD_LEFT, InputState::Previous };
	ControllerInput down{ Button::XINPUT_GAMEPAD_DRAD_DOWN, InputState::Previous };
	ControllerInput right{ Button::XINPUT_GAMEPAD_DRAD_RIGHT, InputState::Previous };
	ControllerInput Y{ Button::XINPUT_CONTROLLER_Y, InputState::Released };
	ControllerInput B{ Button::XINPUT_CONTROLLER_B, InputState::Released };

	controller->AddCommand(up, std::make_unique<MoveCommand>(2, glm::vec2(0.0f, -1.0f), 100.0f));
	controller->AddCommand(left, std::make_unique<MoveCommand>(2, glm::vec2(-1.0f, 0.0f), 100.0f));
	controller->AddCommand(down, std::make_unique<MoveCommand>(2, glm::vec2(0.0f, 1.0f), 100.0f));
	controller->AddCommand(right, std::make_unique<MoveCommand>(2, glm::vec2(1.0f, 0.0f), 100.0f));
	controller->AddCommand(Y, std::make_unique<SuicideCommand>(2));
	//controller->AddCommand(B, std::make_unique<KillEnemyCommand>(2));
	controller->AddCommand(B, std::make_unique<ShootCommand>(2));

	auto& input = InputManager::GetInstance();
	input.AddDevice(std::move(keyboard));
	input.AddDevice(std::move(controller));

	/*ServiceLocator::RegisterSoundSystem(std::make_unique<SDLSoundSystem>());

	ServiceLocator::GetSoundSystem()->AddSFX("../Data/sound.wav", 1);
	ServiceLocator::GetSoundSystem()->Play(1, 30);*/
}

void load()
{
	CreateLevel1();
}

int main(int, char* [])
{
	Fluffy::FluffyEngine engine("../Data/");
	engine.Run(load);
	return 0;
}
