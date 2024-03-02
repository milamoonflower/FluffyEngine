#pragma once
#include <glm/glm.hpp>

class Transform final
{
public:
	Transform() = default;
	Transform(const glm::vec2& position);
	inline const glm::vec2& GetPosition() const { return m_Position; }
	void SetPosition(const float x, const float y);
	void SetPosition(const glm::vec2& position);
	void Translate(const glm::vec2& translation);
	void Translate(const float x, const float y);

private:
	glm::vec2 m_Position;
};
