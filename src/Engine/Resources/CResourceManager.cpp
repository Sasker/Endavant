#include <sstream>
#include "CResourceManager.h"
#include "Renderer/Base_Nodes/CTextureNode.h"
#include "Utils/CXMLParserPUGI.h"
#include "Core/Defines.h"
#include "CSoundEffect.h"
#include "CMusicTrack.h"

#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


CResourceManager::CResourceManager()
{

}

CResourceManager::~CResourceManager()
{

}

void CResourceManager::StartUp(void)
{
	//SDL_Image
	if ( !IMG_Init(IMG_INIT_PNG) )
	{
		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_RESOURCES,"Starting Up! (FAILED LOADING SDL_Image)");
	}
	else
	{
		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_RESOURCES,"Starting Up! SDL_Image Loaded!");
	}

	LoadTextures();
	LoadAudio();
}

void CResourceManager::ShutDown(void)
{
	FreeTextures();
	FreeAudio();
}

void CResourceManager::Update(f64 dt)
{

}

CTexture* CResourceManager::GetTexture(const std::string& a_ID)
{/*
	t_Textures::iterator itTexture = m_Textures.find(a_ID);
	if (itTexture != m_Textures.end())
	{
		return itTexture->second;
	}
*/
	return NULL;
}

bool CResourceManager::LoadTextures()
{
	/*
	XMLParserPUGI Parser(TEXTURES_XML_DATA);

	uint NumTextures = Parser.GetNodeNameCount("TEXTURES/TEXTURE");
	for (uint Texture = 0; Texture < NumTextures; Texture++)
	{
		std::string NodePath("TEXTURES/TEXTURE#");
		std::stringstream ss;
		ss << Texture;
		NodePath.append(ss.str());

		std::string ID = Parser.GetStringAttributeValue(NodePath,"Id");
		std::string Path(PATH_TEXTURES);
		Path.append(Parser.GetStringAttributeValue(NodePath,"File"));

		t_Textures::iterator itTexture = m_Textures.find(ID);
		if (itTexture == m_Textures.end())
		{
			m_Textures[ID] = new CTexture(Parser.GetBoolAttributeValue(NodePath,"LoadOnCreate"), Path);
		}
	}
*/
	return true;
}

bool CResourceManager::LoadTexture(const std::string& a_PathToTexture)
{
	return true;
}

void CResourceManager::FreeTextures()
{
	/*
	for (t_Textures::iterator itTexture = m_Textures.begin(); itTexture != m_Textures.end(); itTexture++)
	{
		if (itTexture->second)
			delete itTexture->second;
	}
	*/
}

void CResourceManager::ParseXMLAudioGroup(CXMLParserPUGI& a_Parser, const std::string& a_NodePath, std::vector< std::string >& a_IDs, std::vector< std::string >& a_Paths)
{
	/*
	 * TODO OOOOOOOOOOOOOOOOOOOOOOOOOO
	 */
	/*a_IDs.clear();
	a_Paths.clear();

	uint Elements = a_Parser.GetNodeNameCount(a_NodePath);
	for (uint Element = 0; Element < Elements; Element++)
	{
		std::string NodePath(a_NodePath);
		NodePath.append("#");
		std::stringstream ss;
		ss << Element;
		NodePath.append(ss.str());

		a_IDs.push_back(a_Parser.GetStringAttributeValue(NodePath,"Id"));
		std::string Path(PATH_AUDIO);
		Path.append(a_Parser.GetStringAttributeValue(NodePath,"Path"));
		a_Paths.push_back(Path);
	}
	*/
}

bool CResourceManager::LoadAudio()
{
	//TODO
	/*
	CXMLParserPUGI Parser(EVTENGINE::CONFIG::AUDIO_CONFIG_XML_PATH);

	std::vector< std::string > IDs, Paths;

	ParseXMLAudioGroup(Parser, "AUDIO/SOUNDS/SOUND", IDs, Paths);
	for (uint index = 0; index < IDs.size(); index++)
	{
		m_Sounds[IDs[index]] = new CSoundEffect(IDs[index], Paths[index]);
	}

	ParseXMLAudioGroup(Parser, "AUDIO/TRACKS/MUSIC", IDs, Paths);
	for (uint index = 0; index < IDs.size(); index++)
	{
		m_Music[IDs[index]] = new CMusicTrack(IDs[index], Paths[index]);
	}
	 */
	return false;
}

void CResourceManager::FreeAudio()
{
	/*
	for (t_Sounds::iterator itSnd = m_Sounds.begin(); itSnd != m_Sounds.end(); itSnd++)
	{
		delete itSnd->second; // liberamos si o si
	}
	m_Sounds.clear();

	for (t_Music::iterator itMus = m_Music.begin(); itMus != m_Music.end(); itMus++)
	{
		delete itMus->second;
	}
	m_Music.clear();
	*/
}

CSoundEffect* CResourceManager::GrabSound(const std::string& a_ID)
{/*
	t_Sounds::iterator itSnd = m_Sounds.find(a_ID);
	if (itSnd != m_Sounds.end())
	{
		CSoundEffect* Sound = itSnd->second;

		if (!Sound->IsLoaded())
			Sound->Load();

		Sound->Grab();
		return Sound;
	}
*/
	return NULL;
}

void CResourceManager::DropSound(const std::string& a_ID)
{
	/*
	t_Sounds::iterator itSnd = m_Sounds.find(a_ID);
	if (itSnd != m_Sounds.end())
	{
		CSoundEffect* Sound = itSnd->second;

		if (Sound->GetCount() > 1)
			Sound->Drop();
		else
			Sound->UnLoad();
	}
	*/
}

void CResourceManager::DropSound(const std::string& a_ID, u32 a_Count)
{
	/*
	t_Sounds::iterator itSnd = m_Sounds.find(a_ID);
	if (itSnd != m_Sounds.end())
	{
		CSoundEffect* Sound = itSnd->second;

		u32 cnt = a_Count;
		while(cnt)
		{
			if (Sound->GetCount() > 1)
				Sound->Drop();
			else
			{
				Sound->UnLoad();
				break;
			}

			cnt--;
		}
	}
	*/
}

CMusicTrack* CResourceManager::GetTrack(const std::string& a_ID)
{
	/*
	CMusicTrack* Track = NULL;

	t_Music::iterator itMus = m_Music.find(a_ID);
	if (itMus != m_Music.end())
	{
		Track = itMus->second;
		if (!Track->IsLoaded())
			Track->Load();
	}

	return Track;
	*/
	return nullptr;
}
