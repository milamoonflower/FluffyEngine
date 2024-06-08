#pragma once
#include <stdexcept>
#include <SDL_ttf.h>
#include "Text.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "ResourceManager.h"

namespace Fluffy
{
	Text::Text(GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& pFont, const TextAlignment alignment /*= TextAlignment::Left*/)
		: Component(pOwner)
		, m_NeedsUpdate(true)
		, m_Text(text)
		, m_Alignment{ alignment }
		, m_pFont(pFont)
		, m_pTextTexture(nullptr)
	{

	}

	Text::Text(GameObject* pOwner, const std::string& text, const std::string& path, int fontSize, const TextAlignment alignment /*= TextAlignment::Left*/)
		: Component(pOwner)
		, m_NeedsUpdate(true)
		, m_Text(text)
		, m_Alignment{ alignment }
		, m_pTextTexture(nullptr)
	{
		m_pFont = ResourceManager::GetInstance().LoadFont(path, fontSize);
	}

	void Text::Update(const float)
	{
		if (!m_NeedsUpdate)
			return;

		const SDL_Color color = { 255, 255, 255, 255 }; // only white text is supported now

		const auto surf = TTF_RenderUTF8_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
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
		UpdateAlignmentOffset();

		m_NeedsUpdate = false;
	}

	void Text::Render() const
	{
		if (m_pTextTexture == nullptr)
			return;

		const auto& pos = m_pOwner->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x - m_AlignmentOffset.x, pos.y - m_AlignmentOffset.y);
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

	void Text::UpdateAlignmentOffset()
	{
		switch (m_Alignment)
		{
		case TextAlignment::BottomLeft:
			m_AlignmentOffset = {};
			break;

		case TextAlignment::BottomCenter:
			m_AlignmentOffset = m_pTextTexture->GetSize() / 2.0f;
			m_AlignmentOffset.y = 0.0f;
			break;

		case TextAlignment::BottomRight:
			m_AlignmentOffset = m_pTextTexture->GetSize();
			m_AlignmentOffset.y = 0.0f;
			break;

		case TextAlignment::Left:
			m_AlignmentOffset = m_pTextTexture->GetSize() / 2.0f;
			m_AlignmentOffset.x = 0.0f;
			break;

		case TextAlignment::Center:
			m_AlignmentOffset = m_pTextTexture->GetSize() / 2.0f;
			break;

		case TextAlignment::Right:
			m_AlignmentOffset = m_pTextTexture->GetSize();
			m_AlignmentOffset.y /= 2.0f;
			break;

		case TextAlignment::TopLeft:
			m_AlignmentOffset = m_pTextTexture->GetSize();
			m_AlignmentOffset.x = 0.0f;
			break;

		case TextAlignment::TopCenter:
			m_AlignmentOffset = m_pTextTexture->GetSize();
			m_AlignmentOffset.x /= 2.0f;
			break;

		case TextAlignment::TopRight:
			m_AlignmentOffset = m_pTextTexture->GetSize();
			break;
		}
	}
}
