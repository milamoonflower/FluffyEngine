#pragma once

struct Rectf
{
	Rectf()
		: Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }
	{
	}

	Rectf(float left, float bottom, float width, float height)
		: left{ left }
		, bottom{ bottom }
		, width{ width }
		, height{ height }
	{
	}

	Rectf(const glm::vec2& bottomLeft, const glm::vec2& topRight)
		: left{ bottomLeft.x }
		, bottom{ bottomLeft.y }
		, width{ topRight.x - bottomLeft.x }
		, height{ topRight.y - bottomLeft.y }
	{
	}

	float left;
	float bottom;
	float width;
	float height;

	float Top() const
	{
		return bottom + height;
	}

	float Right() const
	{
		return left + width;
	}

	glm::vec2 Center() const
	{
		return { left + (width / 2.0f), bottom + (height / 2.0f) };
	}
};
