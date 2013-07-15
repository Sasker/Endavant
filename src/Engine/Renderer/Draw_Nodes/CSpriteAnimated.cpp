#include "CSpriteAnimated.h"
#include "GLLoad/GLFuncs.h"

#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"
#include "Utils/CXMLParserPUGI.h"
#include "Utils/CConversions.h"

CSpriteAnimated::CSpriteAnimated():
CTextureNode(),
m_SpriteSize(0,0)
{
	m_TimerID = 0;
	m_speedAnimation = 0.1f;
}

void CSpriteAnimated::InitSpriteAnimated(const std::string& aPathToTexture, const u32 aNumFrames, const f32 aSpeed)
{
	if ( !GetFrameDataFromXml( aPathToTexture) )
	{
		LoadTextureFromFile(aPathToTexture, aNumFrames, 1, aNumFrames);
	}
	m_speedAnimation = aSpeed;
	m_TimerID  = CCoreEngine::Instance().GetTimerManager().CreateTimer(m_speedAnimation,true );
}

void CSpriteAnimated::InitSpriteAnimated(const std::string& aPathToTexture, const u32 aCols, const u32 aRows, const u32 aNumFrames, const f32 aSpeed)
{
	if ( !GetFrameDataFromXml( aPathToTexture) )
	{
		LoadTextureFromFile(aPathToTexture, aCols, aRows, aNumFrames);
	}
	m_speedAnimation = aSpeed;
	m_TimerID  = CCoreEngine::Instance().GetTimerManager().CreateTimer(m_speedAnimation,true );
}

void CSpriteAnimated::Update(f64 dt)
{
	if (m_TimerID)
	{
		if ( CCoreEngine::Instance().GetTimerManager().IsEndTimer(m_TimerID) )
		{
			FrameIncrement();
		}
	}
	CTextureNode::Update( dt);
}

CSpriteAnimated::~CSpriteAnimated()
{
}

void CSpriteAnimated::SetSpriteSize(const glm::uvec2& aSize)
{
	m_SpriteSize = aSize;
}

glm::uvec2 CSpriteAnimated::GetSpriteSize()
{
	return m_SpriteSize;
}

bool CSpriteAnimated::GetFrameDataFromXml( const std::string& aPathToTexture)
{
	bool retValue = false;
	std::string PathToImage;
	std::vector<glm::vec4> FrameData;

	std::size_t found = aPathToTexture.find(".xml");
	if (found!=std::string::npos)
	{
		CXMLParserPUGI Parser( aPathToTexture );
		if (!Parser.Ready())
		{
			CCoreEngine::Instance().GetLogManager().LogOutput( LOG_ERROR, LOGSUB_RESOURCES, "FAILED LOADING %s", aPathToTexture.c_str() );
			return retValue;
		}
		std::size_t founddir = aPathToTexture.rfind("/");
		if (founddir!=std::string::npos)
		{
			PathToImage = aPathToTexture.substr(0,(founddir+1));
		}
		std::string l_File = Parser.GetStringAttributeValue( "TextureAtlas", "imagePath");
		PathToImage += l_File;

		u32 FramesCount = Parser.GetNodeNameCount("TextureAtlas/sprite");
		for ( u32 c = 0; c < FramesCount; c++ )
		{
			std::string XmlNode("TextureAtlas/sprite#");
			XmlNode += to_string( c );

			s32 l_Xi = Parser.GetIntAttributeValue( XmlNode, "x");
			s32 l_Yi = Parser.GetIntAttributeValue( XmlNode, "y");
			s32 l_Xf = l_Xi + Parser.GetIntAttributeValue( XmlNode, "w");
			s32 l_Yf = l_Yi + Parser.GetIntAttributeValue( XmlNode, "h");

			FrameData.push_back( glm::vec4(l_Xi,l_Yi,l_Xf,l_Yf) );
		}

		LoadTextureFromFile(PathToImage, FrameData.size(), FrameData );
		retValue = true;
	}

	return retValue;
}
