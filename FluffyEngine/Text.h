#pragma once
#include <string>
#include <memory>
#include "Component.h"
#include "Transform.h"
#include "IRenderable.h"

class Font;
class Texture2D;

namespace Fluffy
{
	class Text final : public Component, public IRenderable
	{
	public:
		void Update(const float deltaTime) override;
		//std::string GetTypeName() override { return typeid(*this).name(); }
		void Render() const override;

		void SetText(const std::string& text);

		Text(class GameObject* pOwner, const std::string& text, std::shared_ptr<Font> font);
		Text(class GameObject* pOwner, const std::string& text, const std::string& path, int fontSize);

		virtual ~Text() = default;
		Text(const Text&) = delete;
		Text(Text&&) = delete;
		Text& operator=(const Text&) = delete;
		Text& operator=(Text&&) = delete;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTextTexture;
	};
}
