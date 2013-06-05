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
	inline u32	GetTextureWidth() { return m_Width; }
	inline u32	GetTextureHeight() { return m_Height; }

	virtual ~CTextureNode();

protected:
	CGLTexture	m_GLTexture;

private:

	inline bool IsPowerOf2(int a_Value) { return !(a_Value & (a_Value - 1)); }

	std::string	m_PathToTexture;
	u32			m_Width;
	u32			m_Height;
};

#endif /* CTEXTURE_H_ */
