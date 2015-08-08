#pragma once

#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <FreeImage.h>
#include <stdio.h>
#include <vector>
#include <iostream>

#include "Color.h"

using namespace glm;
using namespace std;

namespace raytracer 
{

	class Film {
	private:
		int _width, _height;
		FIBITMAP* _imageBitmap;
		FIBITMAP* loadedImg;
		string outputFile;

	public:

		void                commitFragment(int x, int y, Color color);

		void                pushFragments();

							Film(int width, int height, string outputFile, 
								short bitsPerPixel = 24);
							~Film();

							Film(const Film&) = delete;
							Film& operator = (const Film&) = delete;
	};

}