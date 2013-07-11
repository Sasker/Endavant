
#include "CMainMenuState.h"

CMainMenuState::CMainMenuState()
{


}

void CMainMenuState::Init()
{

	m_graphicmodel =std::unique_ptr<CSprite>( new CSprite());
	m_graphicmodel->InitSprite("Textures/Exemple.bmp");
	m_graphicmodel->SetPosition(glm::vec2(150,150));

	m_graphicmodel2 =std::unique_ptr<CSprite>( new CSprite());
	m_graphicmodel2->InitSprite("Textures/privado.png");
	m_graphicmodel2->SetPosition(glm::vec2(350,250));

	m_graphicbomberman =std::unique_ptr<CSpriteAnimated>( new CSpriteAnimated());
	m_graphicbomberman->InitSprite("Textures/down.png", 6, 0.1f);
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
	static f64 mydt = 0.0f;

	mydt += dt;

	if ( mydt < 10.0f )
	{
		if ( mydt > 8.0f )
			m_graphicbomberman->Show();
		else if ( mydt > 4.0f )
			m_graphicbomberman->Hide();
	}
}

CMainMenuState::~CMainMenuState()
{

}

