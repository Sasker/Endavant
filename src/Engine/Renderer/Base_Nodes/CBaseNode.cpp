#include "CBaseNode.h"

CBaseNode::CBaseNode()
{
	// position of the node
	m_Position = glm::vec3(0);
	m_PositionAbsolute = glm::vec3(0);

	// rotation angle
	m_Rotation = 0.0F;

	// scaling factors
	SetScale(1.0);

	// array of children
	m_Childrens.clear();
	m_Childrens.reserve(10);
}

CBaseNode::~CBaseNode()
{
	m_Childrens.clear();
}

const std::vector<CBaseNode*>& CBaseNode::GetChildrens() const
{
	return m_Childrens;
}

const glm::vec3& CBaseNode::GetPosition() const
{
	return m_Position;
}

void CBaseNode::SetPosition(const glm::vec3& position)
{
	m_PositionAbsolute -= m_Position;
	m_Position = position;
	UpdateChildPositions( m_PositionAbsolute );
}

void CBaseNode::SetPosition(const glm::vec2& position)
{
	m_PositionAbsolute -= m_Position;
	m_Position.x = position.x;
	m_Position.y = position.y;
	UpdateChildPositions( m_PositionAbsolute );
}

void CBaseNode::UpdateChildPositions( const glm::vec3& position )
{
	m_PositionAbsolute = m_Position + position;
	std::vector<CBaseNode * >::iterator ChildrensIt = m_Childrens.begin();
	while ( ChildrensIt != m_Childrens.end() )
	{
		(*ChildrensIt)->UpdateChildPositions( m_PositionAbsolute );
		ChildrensIt++;
	}
}

float CBaseNode::GetRotation() const
{
	return m_Rotation;
}

void CBaseNode::SetRotation(float rotation)
{
	m_Rotation = rotation;
}


const glm::vec2& CBaseNode::GetScale() const
{
	return m_Scale;
}

void CBaseNode::SetScale(float scale)
{
	m_Scale = glm::vec2(scale);
}

void CBaseNode::SetScale(glm::vec2& scale)
{
	m_Scale = scale;
}

float CBaseNode::GetScaleX() const
{
	return m_Scale.x;
}

void CBaseNode::SetScaleX(float scaleX)
{
	m_Scale.x = scaleX;
}

float CBaseNode::GetScaleY() const
{
	return m_Scale.y;
}

void CBaseNode::SetScaleY(float scaleY)
{
	m_Scale.x = scaleY;
}

void CBaseNode::Render()
{
	// OVERRIDE ME
	// Only use this to draw things!
	// Always call CBaseNode::Render to render childrens
	std::vector<CBaseNode * >::iterator ChildrensIt = m_Childrens.begin();
	while ( ChildrensIt != m_Childrens.end() )
	{
		(*ChildrensIt)->Render();
		ChildrensIt++;
	}
}

void CBaseNode::Update(float dt)
{
	// OVERRIDE ME
	// Only use this to update game logic!
	// Always call CBaseNode::Update to update childrens
	std::vector<CBaseNode * >::iterator ChildrensIt = m_Childrens.begin();
	while ( ChildrensIt != m_Childrens.end() )
	{
		(*ChildrensIt)->Update( dt);
		ChildrensIt++;
	}
}


void CBaseNode::AddChild(CBaseNode* child)
{
	if (!child)
		return;

	m_Childrens.push_back(child);
	child->UpdateChildPositions(m_PositionAbsolute);
}

const glm::vec2& CBaseNode::GetAnchor() const
{
	return m_AnchorPoint;
}

const float& CBaseNode::GetZOrder() const
{
	return m_Position.z;
}

void CBaseNode::SetAnchor(const glm::vec2& anchor)
{
	m_AnchorPoint = anchor;
}
