#pragma once
#include "Text.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include <stdexcept>
#include <SDL_ttf.h>

namespace Fluffy
{
	Text::Text(GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& pFont, const TextAlignment alignment /*= TextAlignment::Left*/, const SDL_Color color /*= { 255, 255, 255, 255 }*/)
		: Component(pOwner)
		, m_Text{ text }
		, m_Alignment{ alignment }
		, m_pFont{ pFont }
		, m_Color{ color }
		, m_pTextTexture{ nullptr }
	{
		RegenerateTexture();
	}

	Text::Text(GameObject* pOwner, const std::string& text, const std::string& path, int fontSize, const TextAlignment alignment /*= TextAlignment::Left*/, const SDL_Color color /*= { 255, 255, 255, 255 }*/)
		: Component(pOwner)
		, m_Text{ text }
		, m_Alignment{ alignment }
		, m_Color{ color }
		, m_pTextTexture{ nullptr }
	{
		m_pFont = ResourceManager::GetInstance().LoadFont(path, fontSize);
		RegenerateTexture();
	}

	void Text::Render() const
	{
		if (m_pTextTexture == nullptr)
			return;

		const auto& pos = m_pOwner->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x - m_AlignmentOffset.x, pos.y - m_AlignmentOffset.y);
	}

	void Text::SetText(const std::string& text)
	{
		if (m_Text != text)
		{
			m_Text = text;
			RegenerateTexture();
		}
	}

	void Text::SetColor(const SDL_Color& color)
	{
		if (m_Color.r != color.r ||
			m_Color.g != color.g ||
			m_Color.b != color.b ||
			m_Color.a != color.a)
		{
			m_Color = color;
			RegenerateTexture();
		}
	}

	glm::vec2 Text::GetSize() const
	{
		return m_pTextTexture->GetSize();
	}

	void Text::RegenerateTexture()
	{
		const auto surf = TTF_RenderUTF8_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
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
