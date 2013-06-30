#include "CTextureNode.h"
#include <SDL2/SDL.h>

// TODO: Load more than bitmaps (BMP)
// TODO: mipmaps?


CTextureNode::CTextureNode():
CBaseNode(),
m_TextureSize(0,0),
m_PathToTexture("")
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

	m_TextureSize.x = Surface->w;
	m_TextureSize.y = Surface->h;

	m_GLTexture.InitWithData(Surface->pixels,Surface->format->BytesPerPixel,m_TextureSize.x,m_TextureSize.y,TextureFormat);
	SDL_FreeSurface(Surface);

	return true;
}

