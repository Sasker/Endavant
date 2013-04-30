#include "CSoundEffect.h"
#include "CCoreEngine.h"
#include "CLogManager.h"

CSoundEffect::CSoundEffect(const std::string& a_ID, const std::string& a_Path) :
	m_Chunk(NULL),
	m_Volume(MIX_MAX_VOLUME),
	m_ID(a_ID),
	m_Path(a_Path)
{

}

CSoundEffect::CSoundEffect(const CSoundEffect& a_Other) :
	m_Chunk(a_Other.m_Chunk),
	m_Volume(a_Other.m_Volume),
	m_ID(a_Other.m_ID),
	m_Path(a_Other.m_Path)
{

}

CSoundEffect::~CSoundEffect()
{
	UnLoad();
}

bool CSoundEffect::Load()
{
	if (m_Chunk)
		return false;

	m_Chunk = Mix_LoadWAV(m_Path.c_str());
	if (!m_Chunk)
	{
		CCoreEngine::Instance().GetLogManager().LogOutput(LOG_ERROR, LOGSUB_SOUND, "%s", SDL_GetError());

		return false;
	}

	return true;
}

void CSoundEffect::UnLoad()
{
	if (m_Chunk)
	{
		Mix_FreeChunk(m_Chunk);
		m_Chunk = NULL;
	}
}

void CSoundEffect::SetVolume(int a_Volume)
{
	if (a_Volume >= 0 && a_Volume <= MIX_MAX_VOLUME)
	{
		m_Volume = a_Volume;
		Mix_VolumeChunk(m_Chunk, m_Volume);
	}
}

int CSoundEffect::GetVolume(int a_Volume)
{
	return a_Volume;
}

bool CSoundEffect::IsLoaded()
{
	return m_Chunk != NULL;
}

const std::string& CSoundEffect::GetID()
{
	return m_ID;
}

Mix_Chunk* CSoundEffect::GetChunk()
{
	return m_Chunk;
}
