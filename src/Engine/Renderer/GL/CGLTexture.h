/*
 * CGLTexture.h
 *
 *  Created on: 29/01/2013
 *      Author: dani
 */

#ifndef CGLTEXTURE_H_
#define CGLTEXTURE_H_

#include "GLLoad/GLFuncs.h"

// http://www.opengl.org/sdk/docs/man/xhtml/glTexImage2D.xml

class CGLTexture
{
public:
	CGLTexture();
	virtual ~CGLTexture();

	void	InitWithData(const GLvoid* aRawDataPixels, GLint aInternalFormat,
								GLsizei aWidth, GLsizei aHeight, GLenum aFormat);
	void 	UnLoad();

	void	Bind();
	void	UnBind();

	bool	IsLoaded();

private:
	GLuint 		m_TextureID;

};

#endif /* CGLTEXTURE_H_ */
