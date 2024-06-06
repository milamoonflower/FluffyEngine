#include "Sprite.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Rectf.h"

namespace Fluffy
{
	Sprite::Sprite(GameObject* pOwner, const std::string& fileName, const int textureColumns, const int textureRows, const float framesPerSecond)
		: Component(pOwner)
	{
		glm::vec2 textureSize{};

		if (!fileName.empty())
		{
			m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
			textureSize = m_pTexture->GetSize();
		}

		m_Animation = Animation(textureSize, textureColumns, textureRows, framesPerSecond);
	}

	Sprite::Sprite(class GameObject* pOwner, const std::string& fileName, const glm::vec2& offset, const int textureColumns, const int textureRows, const float framesPerSecond)
		: Sprite(pOwner, fileName, textureColumns, textureRows, framesPerSecond)
	{
		m_Offset = offset;
	}

	Rectf Sprite::GetRect() const
	{
		return Rectf
		{
			m_pOwner->GetWorldPosition() - (m_pTexture->GetSize() * 0.5f) + m_Offset,
			m_pTexture->GetSize()
		};
	}

	void Sprite::Update(const float deltaTime)
	{
		if (m_Animation.HasFrames())
			m_Animation.Update(deltaTime);
	}

	void Sprite::Render() const
	{
		if (m_pTexture == nullptr)
			return;

		const glm::vec2 size{ m_Animation.GetSourceRect().width, m_Animation.GetSourceRect().height };
		const auto& pos = m_pOwner->GetWorldPosition() - (size * 0.5f) + m_Offset;
		Renderer::GetInstance().RenderTexture(*m_pTexture, m_Animation.GetSourceRect(), pos.x, pos.y);
	}

	void Sprite::SetTexture(const std::string& fileName)
	{
		m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
	}
}
