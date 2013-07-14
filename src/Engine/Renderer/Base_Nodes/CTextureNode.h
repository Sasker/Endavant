#ifndef CTEXTURE_H_
#define CTEXTURE_H_

#include "Renderer/Base_Nodes/CBaseNode.h"

// OpenGL Objects
#include "Renderer/GL/CGLTexture.h"
#include "Renderer/GL/CGLBufferObject.h"
#include "GLLoad/GLFuncs.h"


#include <string>
#include <SDL2/SDL.h>

enum TTextureAlign
{
	TEXTUREALIGN_CENTER			= 0x00,			// ALIGN = TEXTUREALIGN_CENTERMIDDLE por defecto
	TEXTUREALIGN_LEFT			= 0x01,			// ALIGN = TEXTUREALIGN_LEFTMIDDLE por defecto
	TEXTUREALIGN_RIGHT			= 0x02,			// ALIGN = TEXTUREALIGN_RIGHTERMIDDLE por defecto

	TEXTUREALIGN_CENTERMIDDLE	= 0x00,
	TEXTUREALIGN_CENTERBOTTOM	= 0x10,
	TEXTUREALIGN_CENTERTOP		= 0x20,
	TEXTUREALIGN_LEFTMIDDLE		= 0x01,
	TEXTUREALIGN_LEFTBOTTOM		= 0x11,
	TEXTUREALIGN_LEFTTOP		= 0x21,
	TEXTUREALIGN_RIGHTMIDDLE	= 0x02,
	TEXTUREALIGN_RIGHTBOTTOM	= 0x12,
	TEXTUREALIGN_RIGHTTOP		= 0x22,

	TEXTUREVALIGN_MIDDLE		= 0x00,			// ALIGN = TEXTUREALIGN_CENTERMIDDLE por defecto
	TEXTUREVALIGN_BOTTOM		= 0x10,			// ALIGN = TEXTUREALIGN_CENTERBOTTOM por defecto
	TEXTUREVALIGN_TOP			= 0x20,			// ALIGN = TEXTUREALIGN_CENTERTOP por defecto
};

class CTextureNode: public CBaseNode
{
public:
	CTextureNode();
	virtual 			~CTextureNode();
	void				Render();
	virtual void		Update(f64 dt);

	bool				LoadTextureFromFile(const std::string &aPath);
	bool				LoadTextureFromFile(const std::string &aPath, const glm::uvec2 aSize);
	bool				LoadTextureFromFile(const std::string &aPath, const glm::uvec2 aSize, const u32 aCols, const u32 aRows, const u32 aNumFrames );
	bool				LoadTextureFromFile(const std::string &aPath, const u32 aCols, const u32 aRows, const u32 aNumFrames );
	bool				LoadTextureFromFile(const std::string &aPath, const u32 aNumFrames, const std::vector<glm::vec4> &aFrameData );

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
	inline void 		ResetTextureSize() { m_TextureSize = m_TextureRawSize; SetVBOData( TEXTUREALIGN_CENTER ); }

	inline void			FrameSet( const u32 aFrameNum  ) { m_FrameNum = aFrameNum; }
	inline void			FrameIncrement() { m_FrameNum = (m_FrameNum >= (m_VBO.size() - 1) ? 0 : (m_FrameNum + 1) ); }
	inline void			FrameDecrement() { m_FrameNum = (m_FrameNum < 1 ? (m_VBO.size() - 1) :(m_FrameNum - 1) ); }

protected:
	bool				LoadTextureFromSurface(const SDL_Surface &aSurface, const TTextureAlign aAlign = TEXTUREALIGN_CENTER ); // Convert SDL_Surface and upload texture data to the GPU

private:
	void				SetVBOData( const u32 aFrame = 0, const f32 aX_i = 0.0f, const f32 aX_f = 1.0f, const f32 aY_i = 0.0f, const f32 aY_f = 1.0f, const f32 aU_i = 0.0f, const f32 aU_f = 1.0f, const f32 aV_i = 0.0f, const f32 aV_f = 1.0f );
	void				SetVBODataAligned( const TTextureAlign aAlign = TEXTUREALIGN_CENTER, const u32 aFrame = 0, const u32 aW = 0, const u32 aH = 0, const f32 aU_i = 0.0f, const f32 aU_f = 1.0f, const f32 aV_i = 0.0f, const f32 aV_f = 1.0f );	// Upload Vertex Data to the GPU, Aligned
	void				EraseVBOData();
	void				AddVBOData();
	bool				LoadInternalTextureFromFile(const std::string &aPath);
	bool 				LoadInternalTextureFromSurface(const SDL_Surface &aSurface);

	CGLTexture			m_GLTexture;
	glm::uvec2			m_TextureSize;
	glm::uvec2			m_TextureRawSize;
	std::string			m_PathToTexture;
	u32					m_FrameNum;

	std::vector< CGLBufferObject< D5_QUAD<D5_T2F_V3F> > * >	m_VBO;
	D5_QUAD<D5_T2F_V3F>										m_QuadData;
};

#endif /* CTEXTURE_H_ */
