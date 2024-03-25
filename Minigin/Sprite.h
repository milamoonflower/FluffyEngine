#pragma once
#include <memory>
#include <string>
#include "Component.h"
#include "IRenderable.h"

class Texture2D;

class Sprite : public Component, public IRenderable
{
public:
	std::string GetTypeName() override { return typeid(*this).name(); }
	void Render() const override;
	void SetTexture(const std::string& fileName);

	Sprite(const std::weak_ptr<class GameObject> pOwner, const std::string& fileName);
	virtual ~Sprite() = default;
	Sprite(const Sprite& other) = delete;
	Sprite(Sprite&& other) = delete;
	Sprite& operator=(const Sprite& other) = delete;
	Sprite& operator=(Sprite&& other) = delete;

private:
	std::shared_ptr<Texture2D> m_pTexture{};
};
