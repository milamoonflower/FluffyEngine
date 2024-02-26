#include <stdexcept>
#include <SDL_ttf.h>
#include "Text.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"

Text::Text(const std::weak_ptr<GameObject> pOwner, const std::string& text, std::shared_ptr<Font> font)
	: Component(pOwner)
	, m_NeedsUpdate(true)
	, m_Text(text)
	, m_pFont(std::move(font))
	, m_pTextTexture(nullptr)
{ 

}

void Text::Update(const float)
{
	if (!m_NeedsUpdate)
		return;

	const SDL_Color color = { 255, 255, 255, 255 }; // only white text is supported now

	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}

	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}

	SDL_FreeSurface(surf);
	m_pTextTexture = std::make_shared<Texture2D>(texture);
	m_NeedsUpdate = false;
}

void Text::Render() const
{
	if (m_pTextTexture == nullptr)
		return;

	if (const auto owner{ GetOwner() })
	{
		const auto& pos = owner->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void Text::SetText(const std::string& text)
{
	//Update only if the text has been changed
	if (m_Text != text)
	{
		m_Text = text;
		m_NeedsUpdate = true;
	}
}
