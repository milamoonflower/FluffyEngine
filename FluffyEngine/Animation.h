#pragma once
#include "Rectf.h"
#include "glm/glm.hpp"

namespace Fluffy
{
	class Animation final
	{
	public:
		Animation() = default;
		Animation(const glm::vec2& textureSize, int textureColumns, const int textureRows, float framesPerSecond);
		~Animation() = default;

		void Reset();
		void Update(float elapsedSec);
		inline const Rectf& GetSourceRect() const { return m_SourceRect; }
		inline float GetDuration() const { return (m_TextureColumns * m_TextureRows) / m_FramesPerSecond; }
		inline bool HasFrames() const { return m_TextureColumns > 1 || m_TextureRows > 1; }

	private:
		glm::vec2 m_TextureSize{};
		int m_TextureColumns{ 1 };
		int m_TextureRows{ 1 };
		Rectf m_SourceRect{};
		float m_FramesPerSecond{ 8.0f };
		float m_AccumulatedSeconds{ 0.0f };
		glm::vec2 m_CurrentFrame{ 0.0f, 0.0f };
	};
}
