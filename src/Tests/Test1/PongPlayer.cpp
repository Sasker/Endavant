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

PongPlayer::PongPlayer()
{
	m_graphicmodel = (decltype(m_graphicmodel)) (new CRectangle ( glm::vec2( 100, 100), 12,glm::vec3(0.0,1.0,0.0) ));
	CCoreEngine::Instance().GetRenderManager().GetCurrentScene()->AddChild(m_graphicmodel.get());


}

PongPlayer::~PongPlayer()
{

}

void Update(f64 dt)
{

}
void Render()
{

}
