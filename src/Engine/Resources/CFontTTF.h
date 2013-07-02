/*
 * CFontTTF.h
 *
 *  Created on: 02/07/2013
 *      Author: Dani
 */

#ifndef CFONTTTF_H_
#define CFONTTTF_H_

#include <Core/CBasicTypes.h>
#include <Renderer/CRenderTypes.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class CFontTTF
{
	public:
		CFontTTF();
		bool FontLoad(const std::string &FontFile);

		SDL_Surface* GetTextSurface(const std::string &aText, const EV_Color &aColor);

		~CFontTTF();

	private:
		std::string	m_FontFile;
		TTF_Font	*m_pTTFont;

		u32	m_PointSize;

};

#endif /* CFONTTTF_H_ */
