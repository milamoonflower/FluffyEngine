#pragma once
#include <glm/glm.hpp>

namespace Fluffy
{
	class GameObject;

	class Transform final
	{
		friend GameObject;

	public:
		Transform() = default;
		Transform(const glm::vec2& position);
		inline const glm::vec2& GetPosition() const { return m_Position; }
		void Translate(const glm::vec2& translation);
		void Translate(const float x, const float y);

	private:
		glm::vec2 m_Position;

		void SetPosition(const float x, const float y);
		void SetPosition(const glm::vec2& position);
	};
}
