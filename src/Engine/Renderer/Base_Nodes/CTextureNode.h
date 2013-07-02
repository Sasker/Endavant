#ifndef CTEXTURE_H_
#define CTEXTURE_H_

#include "Renderer/Base_Nodes/CBaseNode.h"

// OpenGL Objects
#include "Renderer/GL/CGLTexture.h"
#include "Renderer/GL/CGLBufferObject.h"
#include "GLLoad/GLFuncs.h"


#include <string>
#include <SDL2/SDL.h>

class CTextureNode: public CBaseNode
{
public:
	CTextureNode();
	virtual 			~CTextureNode();
	void				Render();

	bool				LoadTextureFromFile(const std::string &aPath);

	// Current Size
	inline u32			GetTextureWidth() const { return m_TextureSize.x; }
	inline u32			GetTextureHeight() const { return m_TextureSize.y; }
	inline glm::uvec2	GetTextureSize() const { return m_TextureSize; }
	inline void			SetTextureWidth(const u32 aWidth) { m_TextureSize.x = aWidth; }
	inline void			SetTextureHeight(const u32 aHeight) { m_TextureSize.y = aHeight; }
	inline void			SetTextureSize(const glm::uvec2 &aSize) { m_TextureSize = aSize; }

	// Original Size
	inline u32			GetTextureRawWidth() const { return m_TextureRawSize.x; }
	inline u32			GetTextureRawHeight() const { return m_TextureRawSize.y; }
	inline glm::uvec2	GetTextureRawSize() const { return m_TextureRawSize; }
	inline void 		ResetTextureSize() { m_TextureSize = m_TextureRawSize; SetVBOData(); }

protected:
	bool				LoadTextureFromSurface(const SDL_Surface &aSurface); // Convert SDL_Surface and upload texture data to the GPU

private:
	void				SetVBOData();	// Upload Vertex Data to the GPU

	CGLTexture	m_GLTexture;
	glm::uvec2	m_TextureSize;
	glm::uvec2	m_TextureRawSize;
	std::string	m_PathToTexture;

	CGLBufferObject< D5_QUAD<D5_T2F_V3F> >	m_VBO;
	D5_QUAD<D5_T2F_V3F>						m_QuadData;


};

#endif /* CTEXTURE_H_ */
