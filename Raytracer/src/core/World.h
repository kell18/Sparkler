#pragma once 

#include "Scene.h"

namespace raytracer 
{
	class Scene;

	class World
	{
		static Scene* activeScene;
	public:
		static void		renderActiveScene();

		static Scene*	getActiveScene();
		static void		setActiveScene(Scene* scene);

		static void		deinitialize();
	};
}