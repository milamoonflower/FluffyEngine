#include "Sprite.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Rectf.h"

namespace Fluffy
{
	Sprite::Sprite(GameObject* pOwner, const std::string& fileName)
		: Component(pOwner)
	{
		if (!fileName.empty())
			m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
	}

	Sprite::Sprite(class GameObject* pOwner, const std::string& fileName, const glm::vec2& offset)
		: Sprite(pOwner, fileName)
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

	void Sprite::Render() const
	{
		if (m_pTexture == nullptr)
			return;

		const auto& pos = m_pOwner->GetWorldPosition() - (m_pTexture->GetSize() * 0.5f) + m_Offset;
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}

	void Sprite::SetTexture(const std::string& fileName)
	{
		m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
	}
}
