#include "SceneBuilder.h"

namespace raytracer 
{
	Scene* SceneBuilder::buildScene() 
	{
		if (camera == nullptr) {
			cerr << "Scene build error: camera don't set up.\n\n";
			assert(false);
		}
		if (outputFile == "") {
			cerr << "Scene build error: outputFile don't set up.\n\n";
			assert(false);
		}
		Film *film = new Film(camera->width, camera->height, string(outputFile), bitsPerPixel);
		Scene* scene = new Scene(camera, film, primitives, lights);
		scene->setFragmentsPerPixel(fragmentsPerPixel);
		scene->recursionDepth = recursionDepth;
		scene->bgColor = bgColor;
		return scene;
	}

	void SceneBuilder::setupCamera(int width, int heght, float fovXDeg, vec3 lookFrom, vec3 lookTo, vec3 up)
	{
		camera = new Camera(width, heght, fovXDeg);
		camera->lookAt(lookFrom, lookTo, up);
	}

	void SceneBuilder::addPrimitive(Primitive* primitive)
	{
		if (isAnyTrsnform) {
			primitive->transform(transformStack.top());
		}
		if (textureFile != "") {
			primitive->loadTexture(string(textureFile));
			textureFile = "";
		}
		primitives.push_back(primitive);
	}

	Primitive*	SceneBuilder::getPrimitive(int index) 
	{
		Primitive *p = nullptr;
		try {
			p = primitives.at(index);
		} catch (const out_of_range &ex) {
			cerr << ex.what();
		}
		return p;
	}

	void SceneBuilder::addLight(Light* light) 
	{
		if(isAttenuationSet) {
			light->atten = attenuation;
		}
		lights.push_back(light);
	}

	void SceneBuilder::setOutputFile(string pathAndName) 
	{
		this->outputFile = pathAndName;
	}

	void SceneBuilder::setAttenuation(float constant, float linear, float quad) 
	{
		isAttenuationSet = true;
		attenuation.constant = constant;
		attenuation.linear	 = linear;
		attenuation.quad	 = quad;
	}

	void SceneBuilder::setTexture(string pathAndName)
	{
		textureFile = pathAndName;
	}

	void SceneBuilder::addTransform(const mat4& transform)
	{
		isAnyTrsnform = true;
		mat4& t = transformStack.top();
		t *= transform;
	}

	void SceneBuilder::pushTransform()
	{
		transformStack.push(transformStack.top());
	}

	void SceneBuilder::popTransform() 
	{
		if (transformStack.size() <= 1) {
			cerr << "Stack has no elements.  Cannot Pop\n" ; 
		}
		else {
			transformStack.pop();
		}
	}

	SceneBuilder::SceneBuilder(int approxPrimitivesCnt, int approxLightCnt) 
	{
		primitives.reserve(approxPrimitivesCnt);
		lights.reserve(approxLightCnt);
		transformStack.push(mat4(1.0f));
		camera = nullptr;
		bgColor = Colors::BLACK;
	}
}