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

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	std::shared_ptr<GameObject> pBackground{ std::make_shared<GameObject>() };
	std::shared_ptr<Sprite> pBackgroundSprite{ std::make_shared<Sprite>(pBackground, "background.tga") };
	pBackground->AddComponent(pBackgroundSprite);
	scene.Add(pBackground);

	std::shared_ptr<GameObject> pLogo{ std::make_shared<GameObject>(216.0f, 180.0f) };
	std::shared_ptr<Sprite> pLogoSprite{ std::make_shared<Sprite>(pLogo, "logo.tga") };
	pLogo->AddComponent(pLogoSprite);
	scene.Add(pLogo);

	const auto font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	std::shared_ptr<GameObject> pTitle{ std::make_shared<GameObject>(80.0f, 20.0f) };
	std::shared_ptr<Text> pText{ std::make_shared<Text>(pTitle, "Programming 4 Assignment", font) };
	pTitle->AddComponent(pText);
	scene.Add(pTitle);

	std::shared_ptr<GameObject> pFPS{ std::make_shared<GameObject>(250.0f, 250.0f) };
	std::shared_ptr<Text> pFPSText{ std::make_shared<Text>(pFPS, " ", font) };
	std::shared_ptr<FPSCounter> pFPSCounter{ std::make_shared<FPSCounter>(pFPS, pFPSText) };
	pFPS->AddComponent(pFPSText);
	pFPS->AddComponent(pFPSCounter);
	scene.Add(pFPS);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}