#pragma once
#include <string>
#include <memory>
#include "Component.h"
#include "Transform.h"
#include "IRenderable.h"

class Font;
class Texture2D;

class Text final : public Component, public IRenderable
{
public:
	void Update(const float deltaTime) override;
	std::string GetTypeName() override { return typeid(*this).name(); }
	void Render() const override;

	void SetText(const std::string& text);

	Text(const std::weak_ptr<class GameObject> pOwner, const std::string& text, std::shared_ptr<Font> font);
	Text(const std::weak_ptr<class GameObject> pOwner, const std::string& text, const std::string& path, int fontSize);

	virtual ~Text() = default;
	Text(const Text& other) = delete;
	Text(Text&& other) = delete;
	Text& operator=(const Text& other) = delete;
	Text& operator=(Text&& other) = delete;

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<Font> m_pFont;
	std::shared_ptr<Texture2D> m_pTextTexture;
};
