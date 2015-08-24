#pragma once

#include <FreeImage.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>

#include "../utils/Mathf.h"
#include "../utils/Color.h"

using namespace glm;
using namespace std;

namespace raytracer 
{

	class Film {
	private:
		int width, height;
		string outputFile;
		FIBITMAP* raw_imageBitmap;

		int logInterval;
		string progressMsg = "";

	public:
		int logFrequency = 20;

		void                commitFragment(int x, int y, Color color);
		void                pushFragments();
		void				logProgress(int param);

							Film(int width, int height, string outputFile, 
								short bitsPerPixel = 24);
							~Film();

							Film(const Film&) = delete;
							Film& operator = (const Film&) = delete;
	};

}