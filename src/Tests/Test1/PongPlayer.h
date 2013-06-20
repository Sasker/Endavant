

#ifndef PONGPLAYER_H_
#define PONGPLAYER_H_
#include "Renderer/Base_Nodes/CBaseNode.h"
#include "Renderer/Draw_Nodes/CRectangle.h"
#include <memory>

class PongPlayer
{
public:

	PongPlayer();

	void Update(f64 dt);

	~PongPlayer();

	glm::vec2	m_position;
	std::unique_ptr<CRectangle>	m_graphicmodel;

private:
	//Autos

};

#endif /* PONGPLAYER_H_ */
