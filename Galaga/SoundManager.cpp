#include "SoundManager.h"
#include "IEventParam.h"
#include "GameEvents.h"
#include "CharactersManager.h"
#include "ServiceLocator.h"
#include "ISoundSystem.h"

SoundManager::SoundManager()
	: m_SoundSystem{ Fluffy::ServiceLocator::GetSoundSystem() }
{
	if (m_SoundSystem == nullptr)
		return;

	m_SoundSystem->AddSFX("../Data/Audio/Start.mp3", SOUND_ID(GameStart));
	m_SoundSystem->AddSFX("../Data/Audio/PlayerShoot.mp3", SOUND_ID(PlayerShoot));
	m_SoundSystem->AddSFX("../Data/Audio/BulletHit.mp3", SOUND_ID(BulletHit));
	m_SoundSystem->AddSFX("../Data/Audio/PlayerDies.mp3", SOUND_ID(PlayerKilled));

	GameEvents::OnGameStart.AddListener(this);
	GameEvents::OnPlayerShoot.AddListener(this);
	GameEvents::OnBulletHit.AddListener(this);

	CharactersManager::GetInstance().GetOnPlayerKilled().AddListener(this);
}

SoundManager::~SoundManager()
{
	GameEvents::OnGameStart.RemoveListener(this);
	GameEvents::OnPlayerShoot.RemoveListener(this);
	GameEvents::OnBulletHit.RemoveListener(this);

	CharactersManager::GetInstance().GetOnPlayerKilled().RemoveListener(this);
}

void SoundManager::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam*)
{
	const int volume{ 30 };

	switch (eventType)
	{
	case Fluffy::EventType::OnGameStart:
		m_SoundSystem->Play({ SOUND_ID(GameStart), volume });
		break;

	case Fluffy::EventType::OnPlayerShoot:
		m_SoundSystem->Play({ SOUND_ID(PlayerShoot), volume });
		break;

	case Fluffy::EventType::OnBulletHit:
		m_SoundSystem->Play({ SOUND_ID(BulletHit), volume });
		break;

	case Fluffy::EventType::OnPlayerKilled:
		m_SoundSystem->Play({ SOUND_ID(PlayerKilled), volume });
		break;
	}
}
