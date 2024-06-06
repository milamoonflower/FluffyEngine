#pragma once
#include <glm\glm.hpp>
#include <vector>

const glm::vec2 SCREEN_SIZE{ 640.0f, 480.0f };

struct BezierCurve
{
public:
	BezierCurve() = default;
	BezierCurve(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3)
		: m_P0{ p0 }
		, m_P1{ p1 }
		, m_P2{ p2 }
		, m_P3{ p3 }
	{

	}

	inline const glm::vec2& GetStartPoint() const { return m_P0; }
	inline const glm::vec2& GetEndPoint() const { return m_P3; }

	glm::vec2 CalculateCurvePoint(const float progress) const
	{
		const float progressSqrd = (progress * progress);
		const float progressPow3 = progressSqrd * progress;

		const float inverseProgress = 1.0f - progress;
		const float inverseProgressSqrd = inverseProgress * inverseProgress;
		const float inverseProgressPow3 = inverseProgressSqrd * inverseProgress;

		glm::vec2 point =	(inverseProgressPow3 * m_P0) +
							(3.0f * inverseProgressSqrd * progress * m_P1) +
							(3.0f * inverseProgress * progressSqrd * m_P2) +
							(progressPow3 * m_P3);

		point.x = glm::round(point.x);
		point.y = glm::round(point.y);
		return point;
	}

private:
	glm::vec2 m_P0{};
	glm::vec2 m_P1{};
	glm::vec2 m_P2{};
	glm::vec2 m_P3{};
};

struct BezierPath
{
public:
	inline glm::vec2 GetStartPoint() const
	{
		return !m_Curves.empty() ? m_Curves[0].GetStartPoint() : glm::vec2();
	}

	inline bool HasCurve(const int index) const { return (int)m_Curves.size() > index; }
	inline const BezierCurve& GetCurve(const int index) const { return m_Curves[index]; }

	inline void AddCurve(BezierCurve curve, const int samples)
	{
		m_Curves.push_back(curve);
		m_Samples.push_back(samples);
	}

	void Sample(std::vector<glm::vec2>& sampledPath)
	{
		for (int i = 0; i < (int)m_Curves.size(); i++)
		{
			const float incrementSize{ 1.0f / m_Samples[i] };

			for (float t = 0; t <= 1.0f; t += incrementSize)
			{
				sampledPath.push_back(m_Curves[i].CalculateCurvePoint(t));
			}
		}
	}

private:
	std::vector<BezierCurve> m_Curves{};
	std::vector<int> m_Samples{};
};

enum class EnemyType
{
	Boss,
	Butterfly,
	Bee,
};

struct EnemyEnteringData
{
public:
	float time{ 0.0f };
	glm::vec2 position{};
	BezierPath path{};
	EnemyType type{};
	int order{ 0 }; // order of entering the scene
};
