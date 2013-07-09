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
	bool				LoadTextureFromFile(const std::string &aPath, glm::uvec2 aSize);
	bool				LoadTextureFromFile(const std::string &aPath, glm::uvec2 aSize, u32 aCols, u32 aRows, u32 aNumFrames );

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

	inline void			FrameSet( const u32 aFrameNum  ) { m_FrameNum = aFrameNum; }
	inline void			FrameIncrement() { m_FrameNum = (m_FrameNum >= (m_VBO.size() - 1) ? 0 : (m_FrameNum + 1) ); }
	inline void			FrameDecrement() { m_FrameNum = (m_FrameNum < 1 ? (m_VBO.size() - 1) :(m_FrameNum - 1) ); }

protected:
	bool				LoadTextureFromSurface(const SDL_Surface &aSurface); // Convert SDL_Surface and upload texture data to the GPU

private:
	void				SetVBOData( u32 aFrame = 0, f32 aU_i = 0.0f, f32 aU_f = 1.0f, f32 aV_i = 0.0f, f32 aV_f = 1.0f );	// Upload Vertex Data to the GPU
	bool				LoadInternalTextureFromFile(const std::string &aPath);

	CGLTexture	m_GLTexture;
	glm::uvec2	m_TextureSize;
	glm::uvec2	m_TextureRawSize;
	std::string	m_PathToTexture;
	u32			m_FrameNum;

	std::vector< CGLBufferObject< D5_QUAD<D5_T2F_V3F> >	> 	m_VBO;
	D5_QUAD<D5_T2F_V3F>										m_QuadData;
};

#endif /* CTEXTURE_H_ */
