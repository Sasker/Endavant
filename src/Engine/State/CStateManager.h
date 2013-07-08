/*
 * CStateManager.h
 *
 *  Created on: 07/07/2013
 *      Author: Dani
 */

#ifndef CSTATEMANAGER_H_
#define CSTATEMANAGER_H_

#include "Core/ISubSystem.h"
#include "CState.h"
#include <stack>

class CStateManager: public ISubSystem
{
public:
	CStateManager();
	~CStateManager();

	// ISubSystem
	void StartUp();
	void ShutDown();
	void Update(f64 dt);

	void ChangeState(CState* state);
	void PushState(CState* state);
	void PopState();

private:
	std::stack<CState *>	m_StateStack;


};

#endif /* CSTATEMANAGER_H_ */
