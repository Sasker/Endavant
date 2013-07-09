
#include "CMainMenuState.h"

CMainMenuState::CMainMenuState()
{


}

void CMainMenuState::Init()
{

	m_graphicmodel =std::unique_ptr<CSprite>( new CSprite());
	m_graphicmodel->InitSprite("BomberMan/Textures/Exemple.bmp");
	m_graphicmodel->SetPosition(glm::vec2(150,150));

	m_graphicmodel2 =std::unique_ptr<CSprite>( new CSprite());
	m_graphicmodel2->InitSprite("BomberMan/Textures/privado.png");
	m_graphicmodel2->SetPosition(glm::vec2(350,250));

	m_graphicbomberman =std::unique_ptr<CSpriteAnimated>( new CSpriteAnimated());
	m_graphicbomberman->InitSprite("BomberMan/Textures/down.png");
	m_graphicbomberman->SetPosition(glm::vec2(250,450));

	m_menuscene	  = std::unique_ptr<CScene>(new CScene());
	m_menuscene->AddChild(m_graphicmodel.get());
	m_menuscene->AddChild(m_graphicmodel2.get());
	m_menuscene->AddChild(m_graphicbomberman.get());

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

