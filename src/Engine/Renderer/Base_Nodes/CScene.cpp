#include "CScene.h"

CScene::CScene(): CBaseNode()
{
	CBaseNode::SetAnchor(glm::vec2(0.5,0.5));
}

CScene::~CScene()
{

}

void CScene::SetAnchor(const glm::vec2& anchor)
{
}
