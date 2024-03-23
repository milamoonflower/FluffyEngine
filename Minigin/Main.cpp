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

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

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
	scene.Add(pPizza);

	auto& input = dae::InputManager::GetInstance();
	std::unique_ptr<Controller> controller = std::make_unique<Controller>();

	std::unique_ptr<MoveCommand> moveUpCommand { std::make_unique<MoveCommand>(pPizza.get(), glm::vec2(0.0f, -1.0f), 100.0f) };
	std::unique_ptr<MoveCommand> moveLeftCommand { std::make_unique<MoveCommand>(pPizza.get(), glm::vec2(-1.0f, 0.0f), 100.0f) };
	std::unique_ptr<MoveCommand> moveDownCommand { std::make_unique<MoveCommand>(pPizza.get(), glm::vec2(0.0f, 1.0f), 100.0f) };
	std::unique_ptr<MoveCommand> moveRightCommand { std::make_unique<MoveCommand>(pPizza.get(), glm::vec2(1.0f, 0.0f), 100.0f) };

	ControllerInput up{ Button::XINPUT_CONTROLLER_Y, InputState::Previous };
	ControllerInput left{ Button::XINPUT_CONTROLLER_X, InputState::Previous };
	ControllerInput down{ Button::XINPUT_CONTROLLER_A, InputState::Previous };
	ControllerInput right{ Button::XINPUT_CONTROLLER_B, InputState::Previous };

	controller->AddCommand(up, std::move(moveUpCommand));
	controller->AddCommand(left, std::move(moveLeftCommand));
	controller->AddCommand(down, std::move(moveDownCommand));
	controller->AddCommand(right, std::move(moveRightCommand));

	std::unique_ptr<Keyboard> keyboard = std::make_unique<Keyboard>();

	std::unique_ptr<MoveCommand> k_moveUpCommand{ std::make_unique<MoveCommand>(pPizza.get(), glm::vec2(0.0f, -1.0f), 30.0f) };
	std::unique_ptr<MoveCommand> k_moveLeftCommand{ std::make_unique<MoveCommand>(pPizza.get(), glm::vec2(-1.0f, 0.0f), 30.0f) };
	std::unique_ptr<MoveCommand> k_moveDownCommand{ std::make_unique<MoveCommand>(pPizza.get(), glm::vec2(0.0f, 1.0f), 30.0f) };
	std::unique_ptr<MoveCommand> k_moveRightCommand{ std::make_unique<MoveCommand>(pPizza.get(), glm::vec2(1.0f, 0.0f), 30.0f) };

	KeyboardInput k_up{ SDL_SCANCODE_W, InputState::Previous };
	KeyboardInput k_left{ SDL_SCANCODE_A, InputState::Previous };
	KeyboardInput k_down{ SDL_SCANCODE_S, InputState::Previous };
	KeyboardInput k_right{ SDL_SCANCODE_D, InputState::Previous };

	keyboard->AddCommand(k_up, std::move(k_moveUpCommand));
	keyboard->AddCommand(k_left, std::move(k_moveLeftCommand));
	keyboard->AddCommand(k_down, std::move(k_moveDownCommand));
	keyboard->AddCommand(k_right, std::move(k_moveRightCommand));

	input.AddDevice(std::move(controller));
	input.AddDevice(std::move(keyboard));
}

int main(int, char*[])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}