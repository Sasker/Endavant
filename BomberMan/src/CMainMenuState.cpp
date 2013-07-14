
#include "CMainMenuState.h"

CMainMenuState::CMainMenuState()
{


}

void CMainMenuState::Init()
{

	m_graphicmodel =std::unique_ptr<CSprite>( new CSprite());
	m_graphicmodel->InitSprite("Textures/Exemple.bmp");
	m_graphicmodel->SetPosition(glm::vec3(150,150,0));

	m_graphicmodel2 =std::unique_ptr<CSprite>( new CSprite());
	m_graphicmodel2->InitSprite("Textures/privado.png");
	m_graphicmodel2->SetPosition(glm::vec3(350,250,0));

	m_text =std::unique_ptr<CTextTTF>( new CTextTTF());
	m_text->InitTextTTF("Fonts/arial.ttf");
	m_text->SetTextTTF("MIERDAA  AAAA", EV_Color{255,0,255,128});
	m_text->SetPosition(glm::vec3(150,370,0));

	m_graphicbomberman =std::unique_ptr<CSpriteAnimated>( new CSpriteAnimated());
	m_graphicbomberman->InitSpriteAnimated("Textures/downwait.png", 4, 0.25f);
	m_graphicbomberman->SetPosition(glm::vec3(250,450,1));

	m_graphicbombermanwalk =std::unique_ptr<CSpriteAnimated>( new CSpriteAnimated());
	m_graphicbombermanwalk->InitSpriteAnimated("Textures/down.png", 6, 0.15f);
	m_graphicbombermanwalk->SetPosition(glm::vec3(250,450,1));
	m_graphicbombermanwalk->Hide();

	m_menuscene	= std::unique_ptr<CScene>(new CScene());
	m_menuscene->AddChild(m_graphicmodel.get());
	m_menuscene->AddChild(m_graphicmodel2.get());
	m_menuscene->AddChild(m_graphicbomberman.get());
	m_menuscene->AddChild(m_graphicbombermanwalk.get());
	m_menuscene->AddChild(m_text.get());

	CCoreEngine::Instance().GetRenderManager().PushScene(m_menuscene.get());

	m_text->SetTextTTF("TROLL", EV_Color{255,128,0,128});
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
	static f64 mydtwalk = 0.0f;

	mydt += dt;

	if ( mydt > 9.0f )
	{
		m_graphicbomberman->Show();
		m_graphicbombermanwalk->Hide();
	}
	else if ( mydt > 4.0f )
	{
		if (mydtwalk == 0.0f)
		{
			mydtwalk = mydt;
			m_graphicbomberman->Hide();
			m_graphicbombermanwalk->Show();
		}
		else
		{
			u32 distancia = ((mydt - mydtwalk) * 40);
			m_graphicbombermanwalk->SetPosition( glm::vec2(250, (450 - distancia) ));
			m_graphicbomberman->SetPosition( glm::vec2(250, (450 - distancia) ));
		}
	}
}

CMainMenuState::~CMainMenuState()
{

}

