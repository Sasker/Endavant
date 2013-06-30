
#include "CGLTexture.h"

CGLTexture::CGLTexture():
m_TextureID(GL_ZERO)
{
}


void CGLTexture::InitWithData(const GLvoid* aRawDataPixels, GLint aInternalFormat,GLsizei aWidth, GLsizei aHeight, GLenum aFormat)
{
	UnLoad();
	glGenTextures(1, &m_TextureID);


	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, aInternalFormat, aWidth, aHeight, 0,aFormat,GL_UNSIGNED_BYTE, aRawDataPixels);
	UnBind();

}

inline void CGLTexture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

inline void CGLTexture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CGLTexture::UnLoad()
{
	if (m_TextureID != GL_ZERO)
	{
		glDeleteTextures(1, &m_TextureID);
		m_TextureID = GL_ZERO;
	}
}

CGLTexture::~CGLTexture()
{
	UnLoad();
}

bool	CGLTexture::IsLoaded()
{
	if (m_TextureID == GL_ZERO)
		return false;
	else
		return true;
}

