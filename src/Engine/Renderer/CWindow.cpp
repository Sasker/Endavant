/*
 * CWindow.cpp
 *
 *  Created on: 05/01/2013
 *      Author: dani
 */

#include "CWindow.h"
#include "CCoreEngine.h"
#include "CLogManager.h"

CWindow::CWindow(SDL_WindowFlags l_SDLlWinFlags, std::string l_WinTitle, int l_WinPosX,
		int l_WinPosY, int l_WinWidth, int l_WinHeight, bool l_WinFullscreen):
	m_Window(NULL),
	m_WinWidth(l_WinWidth),
	m_WinHeight(l_WinHeight),
	m_WinPosX(l_WinPosX),
	m_WinPosY(l_WinPosY),
	m_Fullscreen(l_WinFullscreen),
	m_WindowCaption(l_WinTitle),
	m_WinFlags(l_SDLlWinFlags)
{
	CreateWindow();
}

CWindow::~CWindow()
{
	SDL_DestroyWindow(m_Window);
}

int CWindow::GetWidth() const
{
	return m_WinWidth;
}

int CWindow::GetHeight() const
{
	return m_WinHeight;
}

bool CWindow::CreateWindow()
{

	m_Window = SDL_CreateWindow(
			m_WindowCaption.c_str(),       //    window title
			m_WinPosX,           	//    initial x position
			m_WinPosY,           	//    initial y position
			m_WinWidth,             //    width, in pixels
			m_WinHeight,            //    height, in pixels
			m_WinFlags 				//    flags
	);


	if(m_Window == NULL)
	{
		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_ERROR, LOGSUB_VIDEO,"Creating the Window: %s",SDL_GetError());
		return false;
	}


	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_VIDEO,"Window Created OK");
	return true;
}

SDL_Window *CWindow::GetWindowHandler()
{
	return m_Window;
}

void	CWindow::ResizeWindow(int l_NewWidth, int l_NewHeight)
{
	SDL_SetWindowSize(m_Window,l_NewWidth,l_NewHeight);
}

