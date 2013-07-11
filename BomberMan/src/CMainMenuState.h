/*
 * CMainMenuState.h
 *
 *  Created on: 08/07/2013
 *      Author: Dani
 */

#ifndef CMAINMENUSTATE_H_
#define CMAINMENUSTATE_H_

#include "EVMain.h"

class CMainMenuState: public CState
{
public:
	CMainMenuState();

	virtual void Init();
	virtual void Cleanup();
	virtual void Pause();
	virtual void Resume();
	virtual void Update(f64 dt);

	virtual ~CMainMenuState();

private:
	std::unique_ptr<CSprite>			m_graphicmodel;
	std::unique_ptr<CSprite>			m_graphicmodel2;
	std::unique_ptr<CSpriteAnimated>	m_graphicbomberman;
	std::unique_ptr<CSpriteAnimated>	m_graphicbombermanwalk;
	std::unique_ptr<CScene>				m_menuscene;
};

#endif /* CMAINMENUSTATE_H_ */
