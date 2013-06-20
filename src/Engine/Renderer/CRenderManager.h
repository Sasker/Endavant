#ifndef CRENDERMANAGER_H_
#define CRENDERMANAGER_H_
#include "Core/ISubSystem.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <vector>

class CScene;
class CWindow;

class CRenderManager: public ISubSystem
{
	public:

		void	StartUp(void);
		void	ShutDown(void);
		void	Update(f64 dt);
		void	Render(void);
		void	ResizeWindow(int, int);

		const glm::vec2 GetWindowSize();

		/**Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
		 * The new scene will be executed.
		 * Try to avoid big stacks of pushed scenes to reduce memory allocation.
		 * ONLY call it if there is a running scene.
		 */
		void	PushScene(CScene *);

		/**Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
		 * The new scene will be executed.
		 * Try to avoid big stacks of pushed scenes to reduce memory allocation.
		 * ONLY call it if there is a running scene.
		 */
		CScene * const GetCurrentScene();

		/**Pops out a scene from the queue.
		 * This scene will replace the running one.
		 * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
		 * ONLY call it if there is a running scene.
		 */
		void	PopScene();

		/**Pops out all scenes from the queue until the root scene in the queue.
		 * This scene will replace the running one.
		 * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
		 * ONLY call it if there is a running scene.
		 */
		void	PopToRootScene();

		/** Replaces the running scene with a new one. The running scene is terminated.
		 * ONLY call it if there is a running scene.
		 */
		void	ReplaceScene(CScene *);


		/** Pauses the running scene.
		 The running scene will be _drawed_ but all scheduled timers will be paused
		 */
		void	PauseScene();

		/** Resumes the paused scene
		 The scheduled timers will be activated again.
		 The "delta time" will be 0 (as if the game wasn't paused)
		 */
		void	ResumeScene();

		/** Ends the execution, releases the running scene.
		 It doesn't remove the OpenGL view from its parent. You have to do it manually.
		 */
		void	End();

		~CRenderManager();

	private:
		CRenderManager();	friend class CCoreEngine;
		void	InitGL();
		void	CreateGLContext();
		void	RenderDebug(void);

		//Printa informacio de renderitzat com els FPS etc etc..
		//void	Render_RenderInfo(void);
		//bool	m_render_info_flag; 	//Flag de mostrar la info de renderitzat.

		SDL_GLContext	m_GLContext;
		CWindow			*m_Window;


		//Scenes
		typedef	std::vector<CScene *>	tSceneStack;
		typedef tSceneStack::iterator	itSceneStack;
		tSceneStack						m_SceneStack;
		itSceneStack					m_itCurrentScene;

};

#endif /* RENDERMANAGER_H_ */
