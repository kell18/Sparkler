#pragma once 

#include "Scene.h"

namespace raytracer 
{
	class Scene;
	// TODO: Add time from init and render time
	class World
	{
		static Scene* activeScene;
		static clock_t initTime;
	public:
		static double	renderActiveScene();

		static Scene*	getActiveScene();
		static void		setActiveScene(Scene* scene);

		static clock_t	getInitTime();
		static clock_t	getWorkTime();

		static void		initialize();
		static void		deinitialize();
	};
}