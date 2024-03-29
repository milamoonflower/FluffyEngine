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

#include "Minigin.h"
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

static void CreateLevel1()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Level1");

	const auto font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 15) };

	std::shared_ptr<GameObject> pMovementInfo{ std::make_shared<GameObject>(10.0f, 20.0f) };
	std::shared_ptr<Text> pMovementInfoText{ std::make_shared<Text>(pMovementInfo, "Movement: Keyboard - WASD / Controller - DPAD", font) };
	pMovementInfo->AddComponent<Text>(pMovementInfoText);
	scene.Add(pMovementInfo);

	std::shared_ptr<GameObject> pActionsInfo{ std::make_shared<GameObject>(10.0f, 40.0f) };
	std::shared_ptr<Text> pActionsInfoText{ std::make_shared<Text>(pActionsInfo, "Kill Enemy: Keyboard - T / Controller - B    Kill Self: Keyboard - R / Controller - Y", font) };
	pActionsInfo->AddComponent<Text>(pActionsInfoText);
	scene.Add(pActionsInfo);

	CharactersManager::GetInstance().CreatePlayerCharacters(scene);
	CharactersManager::GetInstance().SpawnEnemies(scene);

	std::shared_ptr<GameObject> pPlayer1{ CharactersManager::GetInstance().GetPlayer(1)->GetGameObject() };
	std::shared_ptr<GameObject> pPlayer2{ CharactersManager::GetInstance().GetPlayer(2)->GetGameObject() };

	std::shared_ptr<GameObject> pPlayer1ScoreDisplay{ std::make_shared<GameObject>(40.0f, 80.0f) };
	std::shared_ptr<ScoreComponent> pPlayer1ScoreText{ std::make_shared<ScoreComponent>(pPlayer1ScoreDisplay, 1, "Lingua.otf", 15) };
	pPlayer1ScoreDisplay->AddComponent<ScoreComponent>(pPlayer1ScoreText);
	scene.Add(pPlayer1ScoreDisplay);

	std::shared_ptr<GameObject> pPlayer1HealthDisplay{ std::make_shared<GameObject>(40.0f, 95.0f) };
	std::shared_ptr<HealthDisplayComponent> pPlayer1HealthDisplayComponent{ std::make_shared<HealthDisplayComponent>(pPlayer1HealthDisplay, 1, "Lingua.otf", 15) };
	pPlayer1HealthDisplay->AddComponent<HealthDisplayComponent>(pPlayer1HealthDisplayComponent);
	scene.Add(pPlayer1HealthDisplay);

	std::shared_ptr<GameObject> pPlayer2ScoreDisplay{ std::make_shared<GameObject>(40.0f, 110.0f) };
	std::shared_ptr<ScoreComponent> pPlayer2ScoreText{ std::make_shared<ScoreComponent>(pPlayer2ScoreDisplay, 2, "Lingua.otf", 15) };
	pPlayer2ScoreDisplay->AddComponent<ScoreComponent>(pPlayer2ScoreText);
	scene.Add(pPlayer2ScoreDisplay);

	std::shared_ptr<GameObject> pPlayer2HealthDisplay{ std::make_shared<GameObject>(40.0f, 125.0f) };
	std::shared_ptr<HealthDisplayComponent> pPlayer2HealthDisplayComponent{ std::make_shared<HealthDisplayComponent>(pPlayer2HealthDisplay, 2, "Lingua.otf", 15) };
	pPlayer2HealthDisplay->AddComponent<HealthDisplayComponent>(pPlayer2HealthDisplayComponent);
	scene.Add(pPlayer2HealthDisplay);

	std::unique_ptr<Keyboard> keyboard = std::make_unique<Keyboard>();

	std::unique_ptr<MoveCommand> k_moveUpCommand{ std::make_unique<MoveCommand>(1, glm::vec2(0.0f, -1.0f), 120.0f) };
	std::unique_ptr<MoveCommand> k_moveLeftCommand{ std::make_unique<MoveCommand>(1, glm::vec2(-1.0f, 0.0f), 120.0f) };
	std::unique_ptr<MoveCommand> k_moveDownCommand{ std::make_unique<MoveCommand>(1, glm::vec2(0.0f, 1.0f), 120.0f) };
	std::unique_ptr<MoveCommand> k_moveRightCommand{ std::make_unique<MoveCommand>(1, glm::vec2(1.0f, 0.0f), 120.0f) };
	std::unique_ptr<SuicideCommand> k_suicideCommand{ std::make_unique<SuicideCommand>(1) };
	std::unique_ptr<KillEnemyCommand> k_killEnemyCommand{ std::make_unique<KillEnemyCommand>(1) };

	KeyboardInput k_up{ SDL_SCANCODE_W, InputState::Previous };
	KeyboardInput k_left{ SDL_SCANCODE_A, InputState::Previous };
	KeyboardInput k_down{ SDL_SCANCODE_S, InputState::Previous };
	KeyboardInput k_right{ SDL_SCANCODE_D, InputState::Previous };
	KeyboardInput k_R{ SDL_SCANCODE_R, InputState::Released };
	KeyboardInput k_T{ SDL_SCANCODE_T, InputState::Released };

	keyboard->AddCommand(k_up, std::move(k_moveUpCommand));
	keyboard->AddCommand(k_left, std::move(k_moveLeftCommand));
	keyboard->AddCommand(k_down, std::move(k_moveDownCommand));
	keyboard->AddCommand(k_right, std::move(k_moveRightCommand));
	keyboard->AddCommand(k_R, std::move(k_suicideCommand));
	keyboard->AddCommand(k_T, std::move(k_killEnemyCommand));

	std::unique_ptr<Controller> controller = std::make_unique<Controller>();

	std::unique_ptr<MoveCommand> moveUpCommand{ std::make_unique<MoveCommand>(2, glm::vec2(0.0f, -1.0f), 100.0f) };
	std::unique_ptr<MoveCommand> moveLeftCommand{ std::make_unique<MoveCommand>(2, glm::vec2(-1.0f, 0.0f), 100.0f) };
	std::unique_ptr<MoveCommand> moveDownCommand{ std::make_unique<MoveCommand>(2, glm::vec2(0.0f, 1.0f), 100.0f) };
	std::unique_ptr<MoveCommand> moveRightCommand{ std::make_unique<MoveCommand>(2, glm::vec2(1.0f, 0.0f), 100.0f) };
	std::unique_ptr<SuicideCommand> suicideCommand{ std::make_unique<SuicideCommand>(2) };
	std::unique_ptr<KillEnemyCommand> killEnemyCommand{ std::make_unique<KillEnemyCommand>(2) };

	ControllerInput up{ Button::XINPUT_GAMEPAD_DRAD_UP, InputState::Previous };
	ControllerInput left{ Button::XINPUT_GAMEPAD_DRAD_LEFT, InputState::Previous };
	ControllerInput down{ Button::XINPUT_GAMEPAD_DRAD_DOWN, InputState::Previous };
	ControllerInput right{ Button::XINPUT_GAMEPAD_DRAD_RIGHT, InputState::Previous };
	ControllerInput Y{ Button::XINPUT_CONTROLLER_Y, InputState::Released };
	ControllerInput B{ Button::XINPUT_CONTROLLER_B, InputState::Released };

	controller->AddCommand(up, std::move(moveUpCommand));
	controller->AddCommand(left, std::move(moveLeftCommand));
	controller->AddCommand(down, std::move(moveDownCommand));
	controller->AddCommand(right, std::move(moveRightCommand));
	controller->AddCommand(Y, std::move(suicideCommand));
	controller->AddCommand(B, std::move(killEnemyCommand));

	auto& input = dae::InputManager::GetInstance();
	input.AddDevice(std::move(keyboard));
	input.AddDevice(std::move(controller));
}

void load()
{
	CreateLevel1();

	/*auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	std::shared_ptr<GameObject> pBackground{ std::make_shared<GameObject>() };
	std::shared_ptr<Sprite> pBackgroundSprite{ std::make_shared<Sprite>(pBackground, "background.tga") };
	pBackground->AddComponent<Sprite>(pBackgroundSprite);
	scene.Add(pBackground);

	std::shared_ptr<GameObject> pLogo{ std::make_shared<GameObject>(216.0f, 180.0f) };
	std::shared_ptr<Sprite> pLogoSprite{ std::make_shared<Sprite>(pLogo, "logo.tga") };
	pLogo->AddComponent<Sprite>(pLogoSprite);
	scene.Add(pLogo);

	const auto font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	std::shared_ptr<GameObject> pTitle{ std::make_shared<GameObject>(80.0f, 20.0f) };
	std::shared_ptr<Text> pText{ std::make_shared<Text>(pTitle, "Programming 4 Assignment", font) };
	pTitle->AddComponent<Text>(pText);
	scene.Add(pTitle);

	std::shared_ptr<GameObject> pFPS{ std::make_shared<GameObject>(250.0f, 250.0f) };
	std::shared_ptr<Text> pFPSText{ std::make_shared<Text>(pFPS, " ", font) };
	std::shared_ptr<FPSCounter> pFPSCounter{ std::make_shared<FPSCounter>(pFPS, pFPSText) };
	pFPS->AddComponent<Text>(pFPSText);
	pFPS->AddComponent<FPSCounter>(pFPSCounter);
	scene.Add(pFPS);

	std::shared_ptr<GameObject> pPizza{ std::make_shared<GameObject>(100.0f, 350.0f) };
	std::shared_ptr<Sprite> pPizzaSprite{ std::make_shared<Sprite>(pPizza, "pizza.png") };
	std::shared_ptr<Rotator> pPizzaRotator{ std::make_shared<Rotator>(pPizza, 90.0f, 150.0f, 300.0f) };
	pPizza->AddComponent<Sprite>(pPizzaSprite);
	scene.Add(pPizza);*/
}

int main(int, char*[])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}