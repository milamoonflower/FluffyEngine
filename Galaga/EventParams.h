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