#include "GameEvents.h"

Fluffy::Event GameEvents::OnGameStart{ Fluffy::EventType::OnGameStart };
Fluffy::Event GameEvents::OnLevelCompleted{ { Fluffy::EventType::OnLevelCompleted } };
Fluffy::Event GameEvents::OnGameOver{ Fluffy::EventType::OnGameOver };
Fluffy::Event GameEvents::OnPlayerShoot{ Fluffy::EventType::OnPlayerShoot };
Fluffy::Event GameEvents::OnBulletHit{ Fluffy::EventType::OnBulletHit };
