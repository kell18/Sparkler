#include "World.h"

namespace raytracer 
{
	Scene* World::activeScene = nullptr;

	clock_t World::initTime = NULL;

	double World::renderActiveScene()
	{
		clock_t start = clock();
		if (activeScene != nullptr) {
			activeScene->render();
		} else {
			cerr << "Error: try to render unset scene.";
			assert(false);
		}
		return (clock() - start) / (double) (CLOCKS_PER_SEC / 1000);
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

	clock_t	World::getInitTime()
	{
		return initTime;
	}

	clock_t	World::getWorkTime()
	{
		return clock() - initTime;
	}

	void World::initialize()
	{
		initTime = clock();
		srand(static_cast<unsigned> (initTime));
	}

	void World::deinitialize() 
	{
		delete activeScene;
	}
}