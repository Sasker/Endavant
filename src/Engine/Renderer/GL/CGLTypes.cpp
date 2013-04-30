#include "CGLTypes.h"

D5_C3F_V3F::D5_C3F_V3F(const glm::vec3& aColor,const glm::vec3& aVertex):
m_color(aColor), m_vertex(aVertex)
{
}


D5_C3F_V3F::D5_C3F_V3F(const D5_C3F_V3F& aD5_C3F_V3F)
{
	this->m_color = aD5_C3F_V3F.m_color;
	this->m_vertex = aD5_C3F_V3F.m_vertex;
}


D5_T2F_V3F::D5_T2F_V3F(const glm::vec2& aTexCoords,const glm::vec3& aVertex ):
m_texCoord(aTexCoords),m_vertex(aVertex)
{}
D5_T2F_V3F::D5_T2F_V3F(const D5_T2F_V3F& aD5_T2F_V3F)
{
	this->m_texCoord = aD5_T2F_V3F.m_texCoord;
	this->m_vertex = aD5_T2F_V3F.m_vertex;
}

