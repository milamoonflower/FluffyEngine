#pragma once
#include "Component.h"
#include "Structs.h"
#include "IEventListener.h"
#include <vector>
#include <queue>

namespace Fluffy
{
	struct IEventParam;
}

class Level final : public Fluffy::IEventListener
{
public:
	Level() = default;
	~Level() = default;

	void StartLevel(const std::queue<EnemyEnteringData>& data);
	void Update(const float deltaTime);

	Level(const Level&) = delete;
	Level(Level&&) = delete;
	Level& operator=(const Level&) = delete;
	Level& operator=(Level&&) = delete;

private:
	float m_Time{ 0.0f };
	std::queue<EnemyEnteringData> m_EnemyEnteringData{};

	const float m_MaxEnemyCount{ 20 };

	std::vector<class EnemyCharacter*> m_Enemies{};	// each enemy type will have its own container
	const float m_EnemyDiveInterval{ 4.0f };
	float m_EnemyExitTimer{ 0.0f };	// each enemy type will have its own interval and timer

	bool m_Playing{ false };

	void HandleEnemyDiving();

	void OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* pParam = nullptr) override;
};
