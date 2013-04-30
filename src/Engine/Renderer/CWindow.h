/*
 * CWindow.h
 *
 *  Created on: 05/01/2013
 *      Author: dani
 */

#ifndef CWINDOW_H_
#define CWINDOW_H_
#include <SDL2/SDL.h>
#include <string>

class CWindow {
public:

	CWindow(SDL_WindowFlags l_SDLlWinFlags, std::string l_WinTitle, int l_WinPosX,
			int l_WinPosY, int l_WinWidth, int l_WinHeight, bool l_WinFullscreen);

	~CWindow();
	SDL_Window *GetWindowHandler();
	void		ResizeWindow(int l_NewWidth, int l_NewHeight);
	int			GetWidth() const;
	int			GetHeight() const;
private:
	bool CreateWindow();

	SDL_Window *m_Window;


	int				m_WinWidth;
	int 			m_WinHeight;
	int 			m_WinPosX;
	int 			m_WinPosY;
	bool 			m_Fullscreen;
	std::string		m_WindowCaption;

	SDL_WindowFlags m_WinFlags;
};

#endif /* CWINDOW_H_ */
