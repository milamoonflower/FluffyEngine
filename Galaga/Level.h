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

// Level knows when to spawn enemies but still goes though characters manager
class Level final : public Fluffy::IEventListener
{
public:
	Level();
	~Level();

	void StartLevel(const std::queue<EnemyEnteringData>& data);
	void Update(const float deltaTime);

	Level(const Level&) = delete;
	Level(Level&&) = delete;
	Level& operator=(const Level&) = delete;
	Level& operator=(Level&&) = delete;

private:
	float m_Time{ 0.0f };
	std::queue<EnemyEnteringData> m_EnemyEnteringData{};

	const float m_MinEnemiesSpawnInterval{ 0.1f };
	const float m_RemoveLevelNameTime{ 2.0f };

	std::vector<class EnemyCharacter*> m_Enemies{};	// each enemy type will have its own container
	const float m_EnemyDiveInterval{ 2.0f };
	const int m_MaxEnemiesDivingCount{ 4 };

	float m_EnemyExitTimer{ 0.0f };	// each enemy type will have its own interval and timer
	float m_EnemySpawnTimer{ 0.0f };

	bool m_Playing{ false };
	bool m_RemovedLevelName{ false };

	bool AreAllEnemiesIdle() const;
	void HandleEnemyDiving();

	void OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* pParam = nullptr) override;
};
