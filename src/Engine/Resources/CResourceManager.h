#ifndef CRESOURCEMANAGER_H_
#define CRESOURCEMANAGER_H_

#include "Core/ISubSystem.h"
#include "Core/CBasicTypes.h"
#include <map>
#include <string>
#include <vector>

class CTexture;
class CSoundEffect;
class CMusicTrack;
class CXMLParserPUGI;

class CResourceManager: public ISubSystem
{
public:
	typedef std::map< std::string, CTexture* >		t_Textures;
	typedef std::map< std::string, CSoundEffect* >	t_Sounds;
	typedef std::map< std::string, CMusicTrack* >	t_Music;

	CResourceManager();
	virtual ~CResourceManager();

	void StartUp(void);
	void ShutDown(void);
	void Update(float dt);

	CTexture* GetTexture(const std::string& a_ID);
	bool LoadTexture(const std::string& a_PathToTexture);

	CSoundEffect* GrabSound(const std::string& a_ID);
	void DropSound(const std::string& a_ID);
	void DropSound(const std::string& a_ID, uint a_Count);

	CMusicTrack* GetTrack(const std::string& a_ID);

private:
	bool LoadTextures();
	void FreeTextures();

	void ParseXMLAudioGroup(CXMLParserPUGI& a_Parser, const std::string& a_NodePath,
			std::vector< std::string >& a_IDs, std::vector< std::string >& a_Paths);
	bool LoadAudio();
	void FreeAudio();

	t_Textures									m_Textures;
	t_Sounds									m_Sounds;
	t_Music										m_Music;
};

#endif /* CRESOURCEMANAGER_H_ */
