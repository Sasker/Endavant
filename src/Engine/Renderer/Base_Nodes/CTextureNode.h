#ifndef CTEXTURE_H_
#define CTEXTURE_H_

#include "Renderer/Base_Nodes/CBaseNode.h"
#include "Renderer/GL/CGLTexture.h"

#include "GLLoad/GLFuncs.h"

#include <string>
#include <SDL2/SDL.h>

class CTextureNode: public CBaseNode
{
public:
	CTextureNode();

	bool		LoadTextureFromFile(const std::string &aPath);
	inline u32	GetTextureWidth() { return m_TextureSize.x; }
	inline u32	GetTextureHeight() { return m_TextureSize.y; }

	virtual ~CTextureNode();

protected:

	bool		LoadTextureFromSurface(const SDL_Surface &aSurface);
	CGLTexture	m_GLTexture;
	glm::uvec2	m_TextureSize;
	std::string	m_PathToTexture;


};

#endif /* CTEXTURE_H_ */
