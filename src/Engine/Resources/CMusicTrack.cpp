#include "CMusicTrack.h"
#include "CCoreEngine.h"
#include "CLogManager.h"

CMusicTrack::CMusicTrack(const std::string& a_ID, const std::string& a_Path) :
	m_Music(NULL),
	m_Volume(MIX_MAX_VOLUME),
	m_Playing(false),
	m_ID(a_ID),
	m_Path(a_Path)
{

}

CMusicTrack::~CMusicTrack()
{
	Mix_FreeMusic(m_Music);
}

bool CMusicTrack::Load()
{
	m_Music = Mix_LoadMUS(m_Path.c_str());
	if (!m_Music)
	{
		CCoreEngine::Instance().GetLogManager().LogOutput(LOG_ERROR, LOGSUB_SOUND, "%s", SDL_GetError());
		return false;
	}

	return true;
}

bool CMusicTrack::IsLoaded()
{
	return m_Music != NULL;
}

void CMusicTrack::Play(int a_Loops)
{
	Mix_PlayMusic(m_Music, a_Loops);
	m_Playing = true;
}

void CMusicTrack::Stop()
{
	Mix_HaltMusic();
	m_Playing = false;
}

void CMusicTrack::SetVolume(int a_Volume)
{
	m_Volume = a_Volume;
	Mix_VolumeMusic(a_Volume);
}

int CMusicTrack::GetVolume(int a_Volume)
{
	return m_Volume;
}

bool CMusicTrack::IsPlaying()
{
	return m_Playing;
}
