#ifndef CGLBUFFEROBJECT_H_
#define CGLBUFFEROBJECT_H_

#include "GLLoad/GLFuncs.h"

template<typename TBData>
class CGLBufferObject
{

public:
	// 	aTarget : must be
	//	GL_ARRAY_BUFFER, GL_ATOMIC_COUNTER_BUFFER, GL_COPY_READ_BUFFER,	GL_COPY_WRITE_BUFFER,
	//	GL_DRAW_INDIRECT_BUFFER, GL_DISPATCH_INDIRECT_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER,
	//	GL_PIXEL_UNPACK_BUFFER,	GL_SHADER_STORAGE_BUFFER, GL_TEXTURE_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER OR
	//	GL_UNIFORM_BUFFER.
	CGLBufferObject(const GLenum aTarget);
	~CGLBufferObject();

	// aData:   Location from which to copy the data (if NULL, only reserves memory)
	// aSizeOfData:  Number of data elements (of type TBData) in buffer
	// @aUsage:  	Hint to the graphics system as to how the buffer will be used - one
	//   			of 9 possible: GL_{STATIC, DYNAMIC, STREAM}_{READ, COPY, DRAW}
	GLuint			LoadBufferData(const TBData * const aData,const GLsizeiptr aSizeOfData,const GLenum aUsage);
	void			DestroyBufferData();

	void			BindBuffer();
	void			UnBindBuffer();


private:

	GLenum 	m_TargetBuffer;
	GLuint	m_GLBufferID;
	GLenum 	m_Usage;

};

template<typename TBData>
CGLBufferObject<TBData>::CGLBufferObject(const GLenum aTarget):
m_TargetBuffer(aTarget),
m_GLBufferID(GL_ZERO),
m_Usage(GL_ZERO)
{

}

template<typename TBData>
CGLBufferObject<TBData>::~CGLBufferObject()
{
	DestroyBufferData();
}

template<typename TBData>
GLuint CGLBufferObject<TBData>::LoadBufferData( const TBData * const  aData,const GLsizeiptr aSizeOfData, const GLenum aUsage)
{


	// Check if the buffer is created
	if (m_GLBufferID == GL_ZERO)
		glGenBuffers(1, &m_GLBufferID);

	m_Usage = aUsage;

	BindBuffer();
	glBufferData(m_TargetBuffer, aSizeOfData * sizeof(TBData), &aData[0], m_Usage);
	UnBindBuffer();

	return m_GLBufferID;
}


template<typename TBData>
void CGLBufferObject<TBData>::DestroyBufferData()
{
	if (glIsBuffer(m_GLBufferID))
	{
		glDeleteBuffers(1, &m_GLBufferID);
	}

	m_GLBufferID = GL_ZERO;
}


template<typename TBData>
void CGLBufferObject<TBData>::BindBuffer()
{
	glBindBuffer(m_TargetBuffer, m_GLBufferID);
}

template<typename TBData>
void CGLBufferObject<TBData>::UnBindBuffer()
{
	glBindBuffer(m_TargetBuffer, 0);
}



#endif /* CGLBUFFEROBJECT_H_ */
