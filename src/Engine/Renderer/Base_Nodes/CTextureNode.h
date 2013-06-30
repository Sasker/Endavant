#ifndef CTEXTURE_H_
#define CTEXTURE_H_

#include "Renderer/Base_Nodes/CBaseNode.h"
#include "Renderer/GL/CGLTexture.h"

#include "GLLoad/GLFuncs.h"

#include <string>

class CTextureNode: public CBaseNode
{
public:
	CTextureNode();

	bool		LoadTexture(const std::string &aPath);
	inline u32	GetTextureWidth() { return m_TextureSize.x; }
	inline u32	GetTextureHeight() { return m_TextureSize.y; }

	virtual ~CTextureNode();

protected:
	CGLTexture	m_GLTexture;
	glm::uvec2	m_TextureSize;
	std::string	m_PathToTexture;


};

#endif /* CTEXTURE_H_ */
