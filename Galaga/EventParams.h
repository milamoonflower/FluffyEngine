#pragma once
#include "IEventParam.h"

struct CharacterDeathParam : public Fluffy::IEventParam
{
public:
	CharacterDeathParam(class Character* pCharacter, int playerIndex)
		: m_pDeadCharacter{ pCharacter }
		, m_killerIndex{ playerIndex }
	{
	}

	inline class Character* GetCharacter() const { return m_pDeadCharacter; }
	inline int GetKillerIndex() const { return m_killerIndex; }

private:
	class Character* m_pDeadCharacter;
	int m_killerIndex;
};

struct BulletHitParam : public Fluffy::IEventParam
{
public:
	BulletHitParam(class Bullet* pBullet)
		: m_pBullet{ pBullet }
	{
	}

	inline class Bullet* GetBullet() const { return m_pBullet; }

private:
	class Bullet* m_pBullet;
};

struct LevelStartParam : public Fluffy::IEventParam
{
public:
	LevelStartParam(const int levelIndex)
		: m_LevelIndex{ levelIndex }
	{
	}

	inline int GetLevelIndex() const { return m_LevelIndex; }

private:
	int m_LevelIndex;
};

struct GameOverParam : public Fluffy::IEventParam
{
public:
	GameOverParam(const int shotsCount, const int hitsCount)
		: m_ShotsCount{ shotsCount }
		, m_HitsCount{ hitsCount }
	{
	}

	inline int GetShotsCount() const { return m_ShotsCount; }
	inline int GetHitsCount() const { return m_HitsCount; }

private:
	int m_ShotsCount;
	int m_HitsCount;
};
