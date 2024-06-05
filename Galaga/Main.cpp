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
#include "Structs.h"
/*
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"*/

using namespace Fluffy;

static void CreateLevel1()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Level1");

	const auto font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 15) };

	std::shared_ptr<GameObject> pBackground{ std::make_shared<GameObject>(SCREEN_SIZE / 2.0f) };
	pBackground->AddComponent<Sprite>("bg.png");
	scene.Add(pBackground);

	std::shared_ptr<GameObject> pCharactersManager{ std::make_shared<GameObject>(0.0f, 0.0f) };
	pCharactersManager->AddComponent<CharactersManager>();
	scene.Add(pCharactersManager);

	CharactersManager::GetInstance()->CreatePlayerCharacters(scene);

	// TODO: pass <EnemyType, glm::vec2 spawnPosition>
	//CharactersManager::GetInstance()->SpawnEnemy(scene);
	BulletsManager::GetInstance().SetScene(&scene);

	std::shared_ptr<GameObject> pPlayer1ScoreDisplay{ std::make_shared<GameObject>(20.0f, 20.0f) };
	pPlayer1ScoreDisplay->AddComponent<ScoreComponent>(0, "emulogic.ttf", 15);
	scene.Add(pPlayer1ScoreDisplay);

	std::shared_ptr<GameObject> pPlayer1HealthDisplay{ std::make_shared<GameObject>(30.0f, SCREEN_SIZE.y - 30.0f) };
	pPlayer1HealthDisplay->AddComponent<HealthDisplayComponent>(0);
	scene.Add(pPlayer1HealthDisplay);

	/*std::shared_ptr<GameObject> pPlayer2ScoreDisplay{ std::make_shared<GameObject>(40.0f, 110.0f) };
	pPlayer2ScoreDisplay->AddComponent<ScoreComponent>(1, "Lingua.otf", 15);
	scene.Add(pPlayer2ScoreDisplay);

	std::shared_ptr<GameObject> pPlayer2HealthDisplay{ std::make_shared<GameObject>(40.0f, 125.0f) };
	pPlayer2HealthDisplay->AddComponent<HealthDisplayComponent>(1, "Lingua.otf", 15);
	scene.Add(pPlayer2HealthDisplay);*/

	std::unique_ptr<Keyboard> keyboard = std::make_unique<Keyboard>();

	KeyboardInput k_left{ SDL_SCANCODE_A, InputState::Held };
	KeyboardInput k_right{ SDL_SCANCODE_D, InputState::Held };
	KeyboardInput k_Space{ SDL_SCANCODE_SPACE, InputState::Held };

	keyboard->AddCommand(k_left, std::make_unique<MoveCommand>(0, glm::vec2(-1.0f, 0.0f), 200.0f));
	keyboard->AddCommand(k_right, std::make_unique<MoveCommand>(0, glm::vec2(1.0f, 0.0f), 200.0f));
	keyboard->AddCommand(k_Space, std::make_unique<ShootCommand>(0));

	std::unique_ptr<Controller> controller = std::make_unique<Controller>();

	ControllerInput left{ Button::XINPUT_GAMEPAD_DRAD_LEFT, InputState::Held };
	ControllerInput right{ Button::XINPUT_GAMEPAD_DRAD_RIGHT, InputState::Held };
	ControllerInput B{ Button::XINPUT_CONTROLLER_B, InputState::Held };

	controller->AddCommand(left, std::make_unique<MoveCommand>(1, glm::vec2(-1.0f, 0.0f), 200.0f));
	controller->AddCommand(right, std::make_unique<MoveCommand>(1, glm::vec2(1.0f, 0.0f), 200.0f));
	controller->AddCommand(B, std::make_unique<ShootCommand>(1));

	auto& input = InputManager::GetInstance();
	input.AddDevice(std::move(keyboard));
	input.AddDevice(std::move(controller));

	/*ServiceLocator::RegisterSoundSystem(std::make_unique<SDLSoundSystem>());

	ServiceLocator::GetSoundSystem()->AddSFX("../Data/sound.wav", 1);
	ServiceLocator::GetSoundSystem()->Play(1, 30);*/


	CharactersManager::GetInstance()->StartLevel1();
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
