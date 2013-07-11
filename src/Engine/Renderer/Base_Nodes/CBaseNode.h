#ifndef CBASENODE_H_
#define CBASENODE_H_

#include "Renderer/GL/CGLTypes.h"
#include "Core/CBasicTypes.h"
#include <vector>

/*
 * Is the main element, all that we can Render will be a CBaseNode
 *  Default values:
  - rotation: 0
  - position: (x=0,y=0)
  - scale: (x=1,y=1)
  */

class CBaseNode {

public:
	CBaseNode();
	virtual ~CBaseNode();

	virtual void					Render();
	virtual void					Update(f64 dt);

	virtual const 					std::vector<CBaseNode*>& GetChildrens() const;
	virtual void					AddChild(CBaseNode *child);

	virtual const 					glm::vec3& GetPosition() const;
	virtual const 					float& GetZOrder() const;
	virtual void 					SetPosition(const glm::vec3& position);
	virtual void 					SetPosition(const glm::vec2& position);
	virtual void 					IncPosition(const glm::vec3& position);
	virtual void 					IncPosition(const glm::vec2& position);
	virtual void 					UpdateChildPositions(const glm::vec3& position);

	virtual float 					GetRotation() const;
	virtual void 					SetRotation(float rotation);

	virtual const glm::vec2& 		GetScale() const;
	virtual void					SetScale(float scale);
	virtual void					SetScale(glm::vec2& scale);
	virtual float					GetScaleX() const;
	virtual void					SetScaleX(float scaleX);
	virtual float					GetScaleY() const;
	virtual void					SetScaleY(float scaleY);

	virtual const glm::vec2& 		GetAnchor() const;
	virtual void 					SetAnchor(const glm::vec2& anchor);

	inline void						Show() { m_Visible = true; }
	inline void						Hide() { m_Visible = false; }

protected:
	bool	m_Visible;

	glm::vec3 m_Position; //XYZ pos relative to Parent (node center)
	glm::vec3 m_PositionAbsolute; //XYZ pos absolute

	/*
		m_PivotPoint is the point around which all transformations and positioning manipulations take place.
		It's like a pin in the node where it is "attached" to its parent.
		The anchorPoint is normalized, like a percentage. (0,0) means the bottom-left corner and (1,1) means the top-right corner.
		The default anchorPoint is (0.5,0.5), so it starts in the center of the node.
		Points relative to:
			 ________(1,1)
			|		 |
			|		 |
			|		 |
			|________|
			(0.0)
	*/
	glm::vec2 m_AnchorPoint;

	// rotation angle
	float m_Rotation;

	// scale X,Y
	glm::vec2 m_Scale;

	// array of children
	std::vector<CBaseNode * > m_Childrens;

private:


};

#endif /* CBASENODE_H_ */
