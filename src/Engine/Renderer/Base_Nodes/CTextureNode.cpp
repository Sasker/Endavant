#include "CTextureNode.h"
#include <SDL2/SDL.h>

// TODO: Load more than bitmaps (BMP)
// TODO: mipmaps?


CTextureNode::CTextureNode():
CBaseNode(),
m_PathToTexture(""),
m_Width(0),
m_Height(0)
{
}

CTextureNode::~CTextureNode()
{
}

bool CTextureNode::LoadTexture(const std::string& a_PathToTexture)
{



	SDL_Surface* Surface = SDL_LoadBMP(a_PathToTexture.c_str());
	if (!Surface)
	{
		return false;
	}



	m_Width = Surface->w;
	m_Height = Surface->h;


	GLenum TextureFormat;

	switch(Surface->format->BytesPerPixel)
	{
	case 3:
		if (Surface->format->Rmask == 0x000000ff)
			TextureFormat = GL_RGB;
		else
			TextureFormat = GL_BGR;
		break;

	case 4:
		if (Surface->format->Rmask == 0x000000ff)
			TextureFormat = GL_RGBA;
		else
			TextureFormat = GL_BGRA;
		break;

	default:
		return false;
	}

	m_GLTexture.InitWithData(Surface->pixels,Surface->format->BytesPerPixel,m_Width,m_Height,TextureFormat);
	SDL_FreeSurface(Surface);

	return true;
}

