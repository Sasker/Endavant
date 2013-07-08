
#include "CMainMenuState.h"

CMainMenuState::CMainMenuState()
{


}

void CMainMenuState::Init()
{

	m_graphicmodel =std::unique_ptr<CSprite>( new CSprite());
	m_graphicmodel->InitSprite("BomberMan/Textures/Exemple.bmp");
	m_graphicmodel->SetPosition(glm::vec2(150,150));


	m_menuscene	  = std::unique_ptr<CScene>(new CScene());
	m_menuscene->AddChild(m_graphicmodel.get());


	CCoreEngine::Instance().GetRenderManager().PushScene(m_menuscene.get());


}

void CMainMenuState::Cleanup()
{
}

void CMainMenuState::Pause()
{
}

void CMainMenuState::Resume()
{
}

void CMainMenuState::Update(f64 dt)
{

}

CMainMenuState::~CMainMenuState()
{

}

