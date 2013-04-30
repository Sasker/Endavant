#ifndef CGLTYPES_H_
#define CGLTYPES_H_

#include "glm/glm.hpp"

// Color and Vertex TYPE
class D5_C3F_V3F
{
public:
	D5_C3F_V3F(){};
	D5_C3F_V3F(const glm::vec3 & aColor,const glm::vec3 & aVertex);
	D5_C3F_V3F(const D5_C3F_V3F &aD5_C3F_V3F);
	~D5_C3F_V3F(){};

	glm::vec3 m_color;
	glm::vec3 m_vertex;

};

// TextCoord and Vertex TYPE
class D5_T2F_V3F
{
public:
	D5_T2F_V3F(){};
	D5_T2F_V3F(const glm::vec2 & aTexCoords,const glm::vec3 & aVertex);
	D5_T2F_V3F(const D5_T2F_V3F &aD5_T2F_V3F);
	~D5_T2F_V3F(){};

	glm::vec2 m_texCoord;
	glm::vec3 m_vertex;

};

// TRIANGLE TEMPLATE CLASS FOR 2D
template<typename TData>
class D5_TRIANGLE
{
public:
	D5_TRIANGLE(){};
	D5_TRIANGLE(const TData &aPoint0,const TData &aPoint1,const TData &aPoint2);
	D5_TRIANGLE(const D5_TRIANGLE &aD5_TRIANGLE);
	~D5_TRIANGLE(){};

	TData m_Point0;
	TData m_Point1;
	TData m_Point2;
};

template<typename TData>
D5_TRIANGLE<TData>::D5_TRIANGLE(const TData &aPoint0,const TData &aPoint1,const TData &aPoint2):
m_Point0(aPoint0),m_Point1(aPoint1),m_Point2(aPoint2)
{}
template<typename TData>
D5_TRIANGLE<TData>::D5_TRIANGLE(const D5_TRIANGLE<TData>& aD5_TRIANGLE)
{
	this->m_Point0  = aD5_TRIANGLE.m_Point0;
	this->m_Point1  = aD5_TRIANGLE.m_Point1;
	this->m_Point2  = aD5_TRIANGLE.m_Point2;
}



// QUAD TEMPLATE CLASS FOR 2D
template<typename TData>
class D5_QUAD
{
public:
	D5_QUAD(){};
	D5_QUAD(const TData &aTopLeft,const TData &aBottomleft,const TData &aTopRight,const TData &aBottomRight );
	D5_QUAD(const D5_QUAD &aD5_C3F_V3F_QUAD);
	~D5_QUAD(){};

	TData m_TopLeft;
	TData m_BottomLeft;
	TData m_BottomRight;
	TData m_TopRight;
};

template<typename TData>
D5_QUAD<TData>::D5_QUAD(const TData& aTopLeft,const TData& aBottomleft,const TData& aTopRight,const TData& aBottomRight):
m_TopLeft(aTopLeft),m_BottomLeft(aBottomleft),m_BottomRight(aBottomRight),m_TopRight(aTopRight)
{}
template<typename TData>
D5_QUAD<TData>::D5_QUAD(const D5_QUAD<TData>& aD5_V3F_T2F_Quad)
{
	this->m_TopLeft  = aD5_V3F_T2F_Quad.m_TopLeft;
	this->m_BottomRight = aD5_V3F_T2F_Quad.m_BottomRight;
	this->m_TopRight = aD5_V3F_T2F_Quad.m_TopRight;
	this->m_BottomLeft = aD5_V3F_T2F_Quad.m_BottomLeft;
}


#endif /* CGLTYPES_H_ */
