/*
 * PongPlayer.cpp
 *
 *  Created on: 20/06/2013
 *      Author: dani
 */

#include "PongPlayer.h"
#include "Core/CCoreEngine.h"
#include "Renderer/CRenderManager.h"
#include "Renderer/Base_Nodes/CScene.h"
#include "Input/CInputManager.h"
#include "Input/CInputMouse.h"

PongPlayer::PongPlayer(const glm::vec2 &position, const std::string &ActionUp, const std::string &ActionDown, const std::string &TexFile):
m_ActionUp(ActionUp),
m_ActionDown(ActionDown)
{
	m_graphicmodel = (decltype(m_graphicmodel)) (new CSprite());
	m_graphicmodel->InitSprite(TexFile);
	m_graphicmodel->SetPosition(position);
	CCoreEngine::Instance().GetRenderManager().GetCurrentScene()->AddChild(m_graphicmodel.get());

}

PongPlayer::~PongPlayer()
{

}

void PongPlayer::Move(f64 dt)
{
	if (CCoreEngine::Instance().GetInputManager().GetKeyboard().IsActionKeyPushed(m_ActionUp) )
	{
		m_graphicmodel->IncPosition(glm::vec2(0,0.2));
	}

	if (CCoreEngine::Instance().GetInputManager().GetKeyboard().IsActionKeyDown(m_ActionDown))
	{
		m_graphicmodel->IncPosition(glm::vec2(0,-5));
	}
}


void PongPlayer::Update(f64 dt)
{
	Move(dt);

}


