
#include "CFontTTF.h"
#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"


CFontTTF::CFontTTF():
m_FontFile(""),
m_pTTFont(nullptr),
m_PointSize(20)
{
}


CFontTTF::~CFontTTF()
{
	if (m_pTTFont != nullptr)
		TTF_CloseFont(m_pTTFont);
}

bool CFontTTF::FontLoad(const std::string& FontFile)
{
	m_FontFile 	= FontFile;
	m_pTTFont 	= TTF_OpenFont(m_FontFile.c_str(), m_PointSize);
	if (m_pTTFont == nullptr)
	{
		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_ERROR, LOGSUB_RESOURCES, "Unable to load font: %s %s \n", m_FontFile.c_str(), TTF_GetError() );
		m_FontFile.clear();
		return false;
	}

	return true;
}


SDL_Surface* CFontTTF::GetTextSurface(const std::string &Text,const EV_Color &aColor)
{
	SDL_Surface * l_surface = TTF_RenderUTF8_Blended(m_pTTFont, Text.c_str(), aColor);
	//SDL_Surface * l_surface = TTF_RenderUTF8_Solid(m_pTTFont, Text.c_str(), aColor);
	return l_surface;
}



