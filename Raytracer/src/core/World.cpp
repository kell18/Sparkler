#include "World.h"

namespace raytracer 
{
	Scene* World::activeScene = nullptr;

	void World::renderActiveScene()
	{
		if (activeScene != nullptr) {
			activeScene->render();
		} else {
			cerr << "Error: try to render unset scene.";
			assert(false);
		}
	}

	Scene* World::getActiveScene() 
	{
		if (activeScene != nullptr) {
			return activeScene;
		} else {
			cerr << "Error: try to get unset scene.";
			assert(false); return nullptr;
		}
	}

	void World::setActiveScene(Scene* scene) 
	{
		activeScene = scene;
	}

	void World::deinitialize() 
	{
		delete activeScene;
	}
}