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

PongPlayer::PongPlayer(const glm::vec2 &position, const std::string &ActionUp, const std::string &ActionDown):
m_ActionUp(ActionUp),
m_ActionDown(ActionDown)
{
	m_graphicmodel = (decltype(m_graphicmodel)) (new CRectangle ( glm::vec2( 10, 120), 12,glm::vec3(0.0,1.0,0.0) ));
	m_graphicmodel->SetPosition(position);
	CCoreEngine::Instance().GetRenderManager().GetCurrentScene()->AddChild(m_graphicmodel.get());

}

PongPlayer::~PongPlayer()
{

}

void PongPlayer::Move(f64 dt)
{
	if (CCoreEngine::Instance().GetInputManager().GetKeyboard().IsActionKeyPressed(m_ActionUp) )
	{
		m_graphicmodel->IncPosition(glm::vec2(0,1));
	}

	if (CCoreEngine::Instance().GetInputManager().GetKeyboard().IsActionKeyPressed(m_ActionDown))
	{
		m_graphicmodel->IncPosition(glm::vec2(0,-1));
	}
}


void PongPlayer::Update(f64 dt)
{
	Move(dt);

}


