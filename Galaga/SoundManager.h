#pragma once
#include "Singleton.h"
#include "IEventListener.h"
#include "Event.h"
#include "ISoundSystem.h"

namespace Fluffy
{
	struct IEventParam;
	class ISoundSystem;
}

class SoundManager : public Fluffy::Singleton<SoundManager>, Fluffy::IEventListener
{
	friend Fluffy::Singleton<SoundManager>;

public:
	~SoundManager();

	void OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* pParam = nullptr) override;

private:
	SoundManager();

	Fluffy::ISoundSystem* m_SoundSystem{};

	enum SoundIDs : Fluffy::SoundID
	{
		GameStart		= 0,
		PlayerShoot		= 1,
		BulletHit		= 2,
		PlayerKilled	= 3,
	};

#define SOUND_ID(ENUM_ID) (Fluffy::SoundID(SoundIDs::ENUM_ID))
};
