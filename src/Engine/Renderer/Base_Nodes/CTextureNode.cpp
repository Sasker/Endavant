#include "CTextureNode.h"
#include <SDL2/SDL_image.h>

// TODO: mipmaps
// TODO: Check power of 2 ?
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
	GLenum TextureFormat;
	SDL_Surface* Surface = IMG_Load(a_PathToTexture.c_str());
	if (!Surface)
		return false;

	m_Width = Surface->w;
	m_Height = Surface->h;

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

