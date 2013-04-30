#ifndef CTEXTURE_H_
#define CTEXTURE_H_

#include "Renderer/Base_Nodes/CBaseNode.h"
#include "Renderer/GL/CGLTexture.h"

#include <string>

class CTextureNode: public CBaseNode
{
public:
	CTextureNode();

	bool 		LoadTexture(const std::string &aPath);
	inline uint GetTextureWidth() { return m_Width; }
	inline uint GetTextureHeight() { return m_Height; }

	virtual ~CTextureNode();

protected:
	CGLTexture	m_GLTexture;

private:

	inline bool IsPowerOf2(int a_Value) { return !(a_Value & (a_Value - 1)); }

	std::string	m_PathToTexture;
	uint		m_Width;
	uint		m_Height;
};

#endif /* CTEXTURE_H_ */
