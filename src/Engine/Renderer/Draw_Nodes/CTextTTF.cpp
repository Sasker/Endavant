/*
 * CTextTTF.cpp
 *
 *  Created on: 02/07/2013
 *      Author: Dani
 */

#include "CTextTTF.h"

CTextTTF::CTextTTF()
{
}

void CTextTTF::InitTextTTF(const std::string& aPathToTTF)
{
	m_TTFont.FontLoad(aPathToTTF);
}

void CTextTTF::SetTextTTF(const std::string& aText, const EV_Color &aColor, const TTextureAlign aAlign)
{
	SDL_Surface *l_surface = m_TTFont.GetTextSurface(aText, aColor);
	LoadTextureFromSurface(*l_surface, aAlign);
	SDL_FreeSurface(l_surface);
}

void CTextTTF::SetTextSizeTTF(const u32 aTextSize)
{

}

CTextTTF::~CTextTTF()
{

}

