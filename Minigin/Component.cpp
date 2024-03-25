#include "Component.h"

Component::Component(const std::weak_ptr<GameObject> pOwner)
	: m_pOwner{ pOwner }
{

}

std::shared_ptr<GameObject> Component::GetGameObject() const
{
	if (!m_pOwner.expired())
		return m_pOwner.lock();

	return nullptr;
}
