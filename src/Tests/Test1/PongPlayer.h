

#ifndef PONGPLAYER_H_
#define PONGPLAYER_H_
#include "Renderer/Base_Nodes/CBaseNode.h"
#include "Renderer/Draw_Nodes/CRectangle.h"
#include <glm/glm.hpp>

#include <string>
#include <memory>
class PongPlayer
{
public:

	PongPlayer(const glm::vec2 &position, const std::string &ActionUp, const std::string &ActionDown);

	void Update(f64 dt);

	~PongPlayer();


private:
	void Move(f64 dt);


	std::string m_ActionUp, m_ActionDown;
	std::unique_ptr<CRectangle>	m_graphicmodel;





};

#endif /* PONGPLAYER_H_ */
