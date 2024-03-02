#include "Sprite.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"

Sprite::Sprite(std::weak_ptr<GameObject> pOwner, const std::string& fileName)
	: Component(pOwner)
{
	if (!fileName.empty())
		m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
}

void Sprite::Render() const
{
	if (m_pTexture == nullptr)
		return;

	if (const auto owner{ GetOwner() })
	{
		const auto& pos = owner->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void Sprite::SetTexture(const std::string& fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
}
