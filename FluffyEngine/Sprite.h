#pragma once
#include <memory>
#include <string>
#include "Component.h"
#include "IRenderable.h"
#include "Texture2D.h"
#include "Rectf.h"
#include "Animation.h"

namespace Fluffy
{
	class Sprite : public Component, public IRenderable
	{
	public:
		void Update(const float deltaTime) override;
		void Render() const override;
		void SetTexture(const std::string& fileName);
		inline glm::vec2 GetTextureSize() const { return m_pTexture->GetSize(); }
		Rectf GetRect() const;

		Sprite(class GameObject* pOwner, const std::string& fileName, const int textureColumns = 1, const int textureRows = 1, const float framesPerSecond = 0.0f);
		Sprite(class GameObject* pOwner, const std::string& fileName, const glm::vec2& offset, const int textureColumns = 1, const int textureRows = 1, const float framesPerSecond = 0.0f);
		virtual ~Sprite() = default;
		Sprite(const Sprite& other) = delete;
		Sprite(Sprite&& other) = delete;
		Sprite& operator=(const Sprite& other) = delete;
		Sprite& operator=(Sprite&& other) = delete;

	private:
		Animation m_Animation{};
		std::shared_ptr<class Texture2D> m_pTexture{};
		glm::vec2 m_Offset{ 0.0f, 0.0f };
	};
}
