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
	std::shared_ptr<MoveComponent> pPizzaMove{ std::make_shared<MoveComponent>(pPizza, 200.0f, 200.0f) };
	pPizza->AddComponent<Sprite>(pPizzaSprite);
	pPizza->AddComponent<Rotator>(pPizzaRotator);
	pPizza->AddComponent<MoveComponent>(pPizzaMove);
	scene.Add(pPizza);

	std::shared_ptr<GameObject> pFries{ std::make_shared<GameObject>(-20.0f, 0.0f) };
	std::shared_ptr<Sprite> pFriesSprite{ std::make_shared<Sprite>(pFries, "fries.png") };
	std::shared_ptr<Rotator> pFriesRotator{ std::make_shared<Rotator>(pFries, 180.0f, 0.0f, 0.0f) };
	pFries->AddComponent<Sprite>(pFriesSprite);
	pFries->AddComponent<Rotator>(pFriesRotator);
	pFries->SetParent(pPizza.get(), false);
	scene.Add(pFries);

	dae::InputManager::GetInstance().SetInputReceiver(pPizza.get());
	dae::InputManager::GetInstance().MapInput(SDL_SCANCODE_W, new MoveCommand());
}

int main(int, char*[])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}