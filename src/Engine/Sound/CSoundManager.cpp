#include "Resources/CSoundEffect.h"
#include "Resources/CMusicTrack.h"
#include "Resources/CResourceManager.h"
#include "CSoundManager.h"
#include "Core/CCoreEngine.h"
#include "Core/Defines.h"
#include "Utils/CXMLParserPUGI.h"
#include "SDL2/SDL_mutex.h"
//#include "SDL2/SDL_mixer.h"
#include "Core/CLogManager.h"
#include <algorithm>
#include <set>
/*
void OnSoundStop(int a_Channel)
{
	CCoreEngine::Instance().GetSoundManager().StopSound(a_Channel);
}

CSoundManager::CSoundManager() :
	m_CurrentTrack(NULL),
	m_MusicVolume(MIX_MAX_VOLUME),
	m_SndMutex(SDL_CreateMutex())
{

}

CSoundManager::~CSoundManager()
{
	SDL_DestroyMutex(m_SndMutex);
}

void CSoundManager::StartUp(void)
{
	CXMLParserPUGI Parser(EVTENGINE::CONFIG::AUDIO_CONFIG_XML_PATH);

	if (Mix_OpenAudio(Parser.GetIntAttributeValue("AUDIO/OPTIONS", "Frequency"),
				MIX_DEFAULT_FORMAT,
				Parser.GetIntAttributeValue("AUDIO/OPTIONS", "Channels"),
				Parser.GetIntAttributeValue("AUDIO/OPTIONS", "ChunkSize")))
	{
		CCoreEngine::Instance().GetLogManager().LogOutput(LOG_ERROR, LOGSUB_SOUND, "%s", SDL_GetError());
	}

	int MixingChannels = Parser.GetIntAttributeValue("AUDIO/OPTIONS", "MixingChannels");
	if (Mix_AllocateChannels(MixingChannels) != MixingChannels)
	{
		CCoreEngine::Instance().GetLogManager().LogOutput(LOG_ERROR, LOGSUB_SOUND, "%s", SDL_GetError());
	}

	Mix_ChannelFinished(OnSoundStop);
}

void CSoundManager::ShutDown(void)
{
	Mix_CloseAudio();
}

void CSoundManager::Update(f64 dt)
{

}

void CSoundManager::PlaySound(const std::string& a_ID, int a_Loops)
{
	CResourceManager& ResourceManager = CCoreEngine::Instance().GetResourceManager();

	CSoundEffect* Sound = ResourceManager.GrabSound(a_ID);
	if (Sound)
	{
		int Channel = Mix_PlayChannel(-1, Sound->GetChunk(), a_Loops);
		if (Channel != -1)
		{
			SDL_mutexP(m_SndMutex);
			m_PlayingSnds[Channel] = Sound;
			SDL_mutexV(m_SndMutex);
		}
		else
		{
			ResourceManager.DropSound(a_ID);
		}
	}
}

void CSoundManager::StopSound(const std::string& a_ID)
{
	uint SndCount = 0;

	SDL_mutexP(m_SndMutex);

	t_PlayingSnds::iterator itSnd = m_PlayingSnds.begin();
	while(itSnd != m_PlayingSnds.end())
	{
		CSoundEffect* Sound = itSnd->second;
		if (Sound->GetID() == a_ID)
		{
			Mix_HaltChannel(itSnd->first);
			t_PlayingSnds::iterator ToErase = itSnd;
			itSnd++;
			m_PlayingSnds.erase(ToErase);
			SndCount++;
		}
		else
			itSnd++;
	}

	SDL_mutexV(m_SndMutex);

	if (SndCount > 0)
	{
		CCoreEngine::Instance().GetResourceManager().DropSound(a_ID, SndCount);
	}
}

void CSoundManager::StopSound(int a_Channel)
{
	if (a_Channel < 0)
		return;

	SDL_mutexP(m_SndMutex);

	t_PlayingSnds::iterator itSnd = m_PlayingSnds.find(a_Channel);
	if (itSnd != m_PlayingSnds.end())
	{
		Mix_HaltChannel(a_Channel);
		CCoreEngine::Instance().GetResourceManager().DropSound(itSnd->second->GetID());
		m_PlayingSnds.erase(itSnd);
	}

	SDL_mutexV(m_SndMutex);
}

void CSoundManager::PlayMusic(const std::string& a_ID, int a_Loops)
{
	StopMusic();

	CMusicTrack* Track =  CCoreEngine::Instance().GetResourceManager().GetTrack(a_ID);
	if (Track)
	{
		Track->SetVolume(m_MusicVolume);
		Track->Play(a_Loops);
		m_CurrentTrack = Track;
		m_CurrentTrackID = a_ID;
	}
}

void CSoundManager::StopMusic()
{
	if (m_CurrentTrack)
	{
		m_CurrentTrack->Stop();
		m_CurrentTrack = NULL;
		m_CurrentTrackID = "";
	}
}

void CSoundManager::SetMusicVolume(int a_Volume)
{
	m_MusicVolume = a_Volume;
	if (m_CurrentTrack)
	{
		m_CurrentTrack->SetVolume(a_Volume);
	}
}

int CSoundManager::GetMusicVolume()
{
	return m_MusicVolume;
}

const std::string& CSoundManager::GetPlayingTrack()
{
	return m_CurrentTrackID;
}

std::vector< std::string > CSoundManager::GetPlayingSounds()
{
	std::set< std::string > SetPlayingIDs;

	SDL_mutexP(m_SndMutex);
	for (t_PlayingSnds::iterator itSnd = m_PlayingSnds.begin(); itSnd != m_PlayingSnds.end(); itSnd++)
	{
		SetPlayingIDs.insert(itSnd->second->GetID());
	}
	SDL_mutexV(m_SndMutex);

	std::vector< std::string > PlayingIDs(SetPlayingIDs.size());
	std::copy(SetPlayingIDs.begin(), SetPlayingIDs.end(), PlayingIDs.begin());

	return PlayingIDs;
}

void CSoundManager::StopSounds()
{
	CResourceManager& ResourceManager = CCoreEngine::Instance().GetResourceManager();
	for (t_PlayingSnds::iterator itSnd = m_PlayingSnds.begin(); itSnd != m_PlayingSnds.end(); itSnd++)
	{
		Mix_HaltChannel(itSnd->first);
		ResourceManager.DropSound(itSnd->second->GetID());
	}

	m_PlayingSnds.clear();
}

void CSoundManager::Mute()
{
	StopSounds();
	StopMusic();
}
*/
