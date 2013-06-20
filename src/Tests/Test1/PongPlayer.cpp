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

PongPlayer::PongPlayer()
{
	m_graphicmodel = (decltype(m_graphicmodel)) (new CRectangle ( glm::vec2( 100, 100), 12,glm::vec3(0.0,1.0,0.0) ));
	m_graphicmodel->SetPosition(glm::vec2(0,0));
	CCoreEngine::Instance().GetRenderManager().GetCurrentScene()->AddChild(m_graphicmodel.get());
	CCoreEngine::Instance().GetRenderManager().GetCurrentScene()->SetPosition(glm::vec2(150,300));

}

PongPlayer::~PongPlayer()
{

}

void PongPlayer::Update(f64 dt)
{
	if (CCoreEngine::Instance().GetInputManager().GetMouse().IsButtonPressed(MOUSE_MB))
	{
		m_graphicmodel->IncPosition(glm::vec2(1,0));
	}

}

