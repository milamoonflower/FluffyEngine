#pragma once
#include "Component.h"
#include "Transform.h"
#include "IRenderable.h"
#include "glm\glm.hpp"
#include <SDL_ttf.h>
#include <string>
#include <memory>

class Font;
class Texture2D;

namespace Fluffy
{
	enum TextAlignment
	{
		BottomLeft,
		BottomCenter,
		BottomRight,
		Left,
		Center,
		Right,
		TopLeft,
		TopCenter,
		TopRight,
	};

	class Text final : public Component, public IRenderable
	{
	public:
		void Render() const override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);
		glm::vec2 GetSize() const;

		Text(class GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& pFont, const TextAlignment alignment = TextAlignment::BottomLeft, const SDL_Color color = { 255, 255, 255, 255 });
		Text(class GameObject* pOwner, const std::string& text, const std::string& path, int fontSize, const TextAlignment alignment = TextAlignment::BottomLeft, const SDL_Color color = { 255, 255, 255, 255 });

		virtual ~Text() = default;
		Text(const Text&) = delete;
		Text(Text&&) = delete;
		Text& operator=(const Text&) = delete;
		Text& operator=(Text&&) = delete;

	private:
		std::string m_Text;
		TextAlignment m_Alignment;
		glm::vec2 m_AlignmentOffset{};
		std::shared_ptr<Font> m_pFont;
		SDL_Color m_Color;
		std::shared_ptr<Texture2D> m_pTextTexture;

		void RegenerateTexture();
		void UpdateAlignmentOffset();
	};
}
