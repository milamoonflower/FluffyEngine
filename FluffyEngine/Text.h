#pragma once
#include "Component.h"
#include "Transform.h"
#include "IRenderable.h"
#include "glm\glm.hpp"
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
		void Update(const float deltaTime) override;
		//std::string GetTypeName() override { return typeid(*this).name(); }
		void Render() const override;

		void SetText(const std::string& text);

		Text(class GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& pFont, const TextAlignment alignment = TextAlignment::BottomLeft);
		Text(class GameObject* pOwner, const std::string& text, const std::string& path, int fontSize, const TextAlignment alignment = TextAlignment::BottomLeft);

		virtual ~Text() = default;
		Text(const Text&) = delete;
		Text(Text&&) = delete;
		Text& operator=(const Text&) = delete;
		Text& operator=(Text&&) = delete;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		TextAlignment m_Alignment;
		glm::vec2 m_AlignmentOffset{};
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTextTexture;

		void UpdateAlignmentOffset();
	};
}
