#include "GameEvents.h"

Fluffy::Event GameEvents::OnLevelStart{ Fluffy::EventType::OnLevelStart };
Fluffy::Event GameEvents::RemoveLevelStartText{ Fluffy::EventType::RemoveLevelStartText };
Fluffy::Event GameEvents::OnLevelCompleted{ { Fluffy::EventType::OnLevelCompleted } };
Fluffy::Event GameEvents::OnGameOver{ Fluffy::EventType::OnGameOver };
Fluffy::Event GameEvents::OnPlayerShoot{ Fluffy::EventType::OnPlayerShoot };
Fluffy::Event GameEvents::OnBulletHit{ Fluffy::EventType::OnBulletHit };
