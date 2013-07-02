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

bool CTextureNode::LoadTextureFromFile(const std::string& a_PathToTexture)
{



	SDL_Surface* Surface = SDL_LoadBMP(a_PathToTexture.c_str());
	if (!Surface)
	{
		return false;
	}

	bool retval = LoadTextureFromSurface(*Surface);
	SDL_FreeSurface(Surface);
	return retval;
}


bool CTextureNode::LoadTextureFromSurface(const SDL_Surface &aSurface)
{
	GLenum TextureFormat;

	switch(aSurface.format->BytesPerPixel)
	{
	case 3:
		if (aSurface.format->Rmask == 0x000000ff)
			TextureFormat = GL_RGB;
		else
			TextureFormat = GL_BGR;
		break;

	case 4:
		if (aSurface.format->Rmask == 0x000000ff)
			TextureFormat = GL_RGBA;
		else
			TextureFormat = GL_BGRA;
		break;

	default:
		return false;
	}

	m_TextureSize.x = aSurface.w;
	m_TextureSize.y = aSurface.h;

	m_GLTexture.InitWithData(aSurface.pixels,aSurface.format->BytesPerPixel,m_TextureSize.x,m_TextureSize.y,TextureFormat);
	return true;



}
