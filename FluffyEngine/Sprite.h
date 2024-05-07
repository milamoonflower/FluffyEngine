#pragma once
#include <memory>
#include <string>
#include "Component.h"
#include "IRenderable.h"
#include "Texture2D.h"

namespace Fluffy
{
	class Sprite : public Component, public IRenderable
	{
	public:
		std::string GetTypeName() override { return typeid(*this).name(); }
		void Render() const override;
		void SetTexture(const std::string& fileName);
		inline glm::vec2 GetTextureSize() const { return m_pTexture->GetSize(); }

		Sprite(class GameObject* pOwner, const std::string& fileName);
		virtual ~Sprite() = default;
		Sprite(const Sprite& other) = delete;
		Sprite(Sprite&& other) = delete;
		Sprite& operator=(const Sprite& other) = delete;
		Sprite& operator=(Sprite&& other) = delete;

	private:
		std::shared_ptr<class Texture2D> m_pTexture{};
	};
}
