#include "Animation.h"

Fluffy::Animation::Animation(const glm::vec2& textureSize, int textureColumns, const int textureRows, float framesPerSecond)
	: m_TextureSize{ textureSize }
	, m_TextureColumns{ textureColumns }
	, m_TextureRows{ textureRows }
	, m_FramesPerSecond{ framesPerSecond }
	, m_SourceRect{ 0.0f, 0.0f, m_TextureSize.x / m_TextureColumns, m_TextureSize.y / m_TextureRows }
{

}

void Fluffy::Animation::Reset()
{
	m_SourceRect.left = 0.0f;
	m_SourceRect.top = 0.0f;

	m_CurrentFrame.x = 0;
	m_CurrentFrame.y = 0;
	m_AccumulatedSeconds = 0.0f;
}

void Fluffy::Animation::Update(float deltaTime)
{
	m_AccumulatedSeconds += deltaTime;

	if (m_AccumulatedSeconds >= (1.0f / m_FramesPerSecond))
	{
		m_AccumulatedSeconds = 0.0f;

		if (++m_CurrentFrame.x >= m_TextureColumns)
		{
			m_CurrentFrame.x = 0.0f;

			if (++m_CurrentFrame.y >= m_TextureRows)
			{
				m_CurrentFrame.y = 0.0f;
			}

			m_SourceRect.top = m_SourceRect.height * m_CurrentFrame.y;
		}

		m_SourceRect.left = m_SourceRect.width * m_CurrentFrame.x;
	}
}
