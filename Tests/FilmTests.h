#pragma once

#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <fstream>

#include "gtest/gtest.h"
#include "glm/glm.hpp"
#include "FreeImage.h"

#include "geometry/primitives/Ray.h"
#include "core/Film.h"
#include "core/Raytracer.h"

using namespace std;
using namespace glm;
using namespace raytracer;

class FilmTests : public ::testing::Test
{
protected:
	const char* fileName;
	Film* film;
	int width = 10,
		height = 10;

	FilmTests()
	{
		fileName = "C:\\Dropbox\\Code\\Cpp\\Raytracer\\resources\\imgs\\testing_out.png";
		film = new Film(width, height, 255.f);
	}

	virtual ~FilmTests()
	{
		if (ifstream(fileName)) {
			DeleteFile(fileName);
		}
		delete film;
	}
};

