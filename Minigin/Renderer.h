#pragma once
#include <SDL.h>
#include "Singleton.h"

class Texture2D;
/**
 * Simple RAII wrapper for the SDL renderer
 */
class Renderer final : public Singleton<Renderer>
{
public:
	void Init(SDL_Window* pWindow);
	void Render() const;
	void Destroy();

	void RenderTexture(const Texture2D& texture, float x, float y) const;
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

	SDL_Renderer* GetSDLRenderer() const;

	inline const SDL_Color& GetBackgroundColor() const { return m_ClearColor; }
	inline void SetBackgroundColor(const SDL_Color& color) { m_ClearColor = color; }

private:
	SDL_Renderer* m_pRenderer{};
	SDL_Window* m_pWindow{};
	SDL_Color m_ClearColor{};
};
