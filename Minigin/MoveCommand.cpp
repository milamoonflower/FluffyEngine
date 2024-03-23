#include "MoveCommand.h"
#include "Time.h"

MoveCommand::MoveCommand(GameObject* pGameObject, glm::vec2 direction, float speed)
	: m_pGameObject(pGameObject)
	, m_Direction{ direction }
	, m_Speed{ speed }
{

}

void MoveCommand::Execute()
{
	glm::vec2 position{ m_pGameObject->GetWorldPosition() };
	position += m_Direction * (m_Speed * Time::DeltaTime());
	m_pGameObject->SetWorldPosition(position);
}
