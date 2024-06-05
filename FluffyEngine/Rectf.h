#pragma once
#include <glm\glm.hpp>

namespace Fluffy
{
	struct Rectf
	{
	public:
		Rectf()
			: Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }
		{
		}

		Rectf(float left, float top, float width, float height)
			: left{ left }
			, top{ top }
			, width{ width }
			, height{ height }
		{
		}

		Rectf(const glm::vec2& topLeft, const glm::vec2& size)
			: left{ topLeft.x }
			, top{ topLeft.y }
			, width{ size.x }
			, height{ size.y }
		{
		}

		float left;
		float top;
		float width;
		float height;

		float Bottom() const
		{
			return top + height;
		}

		float Right() const
		{
			return left + width;
		}

		glm::vec2 Center() const
		{
			return { left + (width / 2.0f), top + (height / 2.0f) };
		}
	};
}
