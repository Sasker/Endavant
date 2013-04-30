#ifndef CSCENE_H_
#define CSCENE_H_
#include "Renderer/Base_Nodes/CBaseNode.h"

/*
 *  Container with fixed anchor point
 */

class CScene : public CBaseNode
{
public:
	CScene();
	~CScene();

	void SetAnchor(const glm::vec2 &anchor);

};

#endif /* CSCENE_H_ */
