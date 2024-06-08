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

	GameEvents::OnLevelStart.AddListener(this);
	GameEvents::OnPlayerShoot.AddListener(this);
	GameEvents::OnBulletHit.AddListener(this);

	CharactersManager::GetInstance().GetOnPlayerKilled().AddListener(this);
}

SoundManager::~SoundManager()
{
	GameEvents::OnLevelStart.RemoveListener(this);
	GameEvents::OnPlayerShoot.RemoveListener(this);
	GameEvents::OnBulletHit.RemoveListener(this);

	CharactersManager::GetInstance().GetOnPlayerKilled().RemoveListener(this);
}

void SoundManager::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam*)
{
	switch (eventType)
	{
	case Fluffy::EventType::OnLevelStart:
		m_SoundSystem->Play({ SOUND_ID(GameStart), GetSoundVolume() });
		break;

	case Fluffy::EventType::OnPlayerShoot:
		m_SoundSystem->Play({ SOUND_ID(PlayerShoot), GetSoundVolume() });
		break;

	case Fluffy::EventType::OnBulletHit:
		m_SoundSystem->Play({ SOUND_ID(BulletHit), GetSoundVolume() });
		break;

	case Fluffy::EventType::OnPlayerKilled:
		m_SoundSystem->Play({ SOUND_ID(PlayerKilled), GetSoundVolume() });
		break;
	}
}

void SoundManager::ToggleMute()
{
	m_IsMuted = !m_IsMuted;
	m_SoundSystem->SetVolume(GetSoundVolume());
}

int SoundManager::GetSoundVolume() const
{
	const int defaultVolume{ 30 };
	return m_IsMuted ? 0 : defaultVolume;
}
