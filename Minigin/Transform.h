#pragma once
#include <glm/glm.hpp>

class Transform final
{
public:
	inline const glm::vec3& GetPosition() const { return m_Position; }
	void SetPosition(const float x, const float y, const float z);

private:
	glm::vec3 m_Position;
};
