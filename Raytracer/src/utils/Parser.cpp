#include "Parser.h"

namespace raytracer 
{
	bool Parser::readVals(stringstream &s, const int numvals, float *values) {
		for (int i = 0 ; i < numvals; i++) {
			s >> values[i];
			if (s.fail()) {
				cout << "Failed reading value " << i << ". Will skip.\n" ; 
				return false;
			}
		}
		return true; 
	}

	Scene* Parser::parseFile(const string &fileName) {
		string str, cmd; 
		ifstream in;
		in.open(fileName.c_str()); 
		if (!in.is_open()) {
			cerr << "Open " << fileName << " failed." << endl;
			throw 2;
		}

		vector<vec3> vertexBuffer;
		int width, height;
		Material material;
		SceneBuilder builder;

		getline (in, str); 
		while (in) {
			if (!((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#'))) {
				getline(in, str);
				continue;
			}
			stringstream s(str);
			s >> cmd; 
			 // position and color for light, colors and others
			float values[10];
			bool isInputValid;
        
			if (cmd == "output") {
				string outputFile = "";
				getline(s, outputFile);
				if (!s.fail()) {
					// remove leading spaces
					outputFile = regex_replace(outputFile, regex("^(\\s)+"), "");
					builder.setOutputFile(move(outputFile));
				} else {
					cout << "Failed reading outputFile value. Will skip.\n";
				}
			}
			else if (cmd == "directional" || cmd == "point") {
				isInputValid = readVals(s, 6, values);
				if (isInputValid) {
					vec3 positionOrDirection = vec3(values[0], values[1], values[2]);
					Color color = Color(values[3], values[4], values[5]);
					if (cmd == "directional") {
						builder.addLight(new DirectionalLight(positionOrDirection, color, 1.f));
					}
					else if (cmd == "point") {
						builder.addLight(new PointLight(positionOrDirection, color, 1.f));
					}
				}
			}
			else if (cmd == "attenuation") {
				isInputValid = readVals(s, 3, values);
				if (isInputValid) {
					builder.setAttenuation(values[0], values[1], values[2]);
				}
			}
			else if (cmd == "ambient") {
				isInputValid = readVals(s, 3, values);
				if (isInputValid) 
					material.ambient = Color(values[0], values[1], values[2]); 
			}
			else if (cmd == "diffuse") {
				isInputValid = readVals(s, 3, values); 
				if (isInputValid) 
					material.diffuse = Color(values[0], values[1], values[2]); 
			}
			else if (cmd == "specular") {
				isInputValid = readVals(s, 3, values); 
				if (isInputValid) 
					material.specular = Color(values[0], values[1], values[2]); 
			}
			else if (cmd == "emission") {
				isInputValid = readVals(s, 3, values); 
				if (isInputValid) 
					material.emissive = Color(values[0], values[1], values[2]); 
			}
			else if (cmd == "shininess") {
				isInputValid = readVals(s, 1, values); 
				if (isInputValid) 
					material.shininess = values[0] ; 
			}
			else if (cmd == "reflectRate") {
				isInputValid = readVals(s, 1, values); 
				if (isInputValid) 
					material.reflectRate = values[0] ; 
			}
			else if (cmd == "transmitRate") {
				isInputValid = readVals(s, 1, values); 
				if (isInputValid) 
					material.transmitRate = values[0] ; 
			}
			else if (cmd == "refractInd") {
				isInputValid = readVals(s, 1, values); 
				if (isInputValid) 
					material.refractInd = values[0] ; 
			}
			else if (cmd == "bgColor") {
				isInputValid = readVals(s, 3, values); 
				if (isInputValid) { 
					builder.bgColor = Color(values[0], values[1], values[2]);
				}
			}
			else if (cmd == "fragmentsPerPixel") {
				isInputValid = readVals(s, 1, values); 
				if (isInputValid) { 
					builder.fragmentsPerPixel = (int) values[0];
				}
			}
			else if (cmd == "size") {
				isInputValid = readVals(s, 2, values); 
				if (isInputValid) { 
					width = (int) values[0];
					height = (int) values[1];
				}
			}
			else if (cmd == "camera") {
				isInputValid = readVals(s, 10, values) ; // 10 values eye cen up fov
				if (isInputValid) {
					builder.setupCamera(width, height, values[9], 
										vec3(values[0], values[1], values[2]),
										vec3(values[3], values[4], values[5]),
										vec3(values[6], values[7], values[8]));
				}
			}
			else if (cmd == "maxdepth") {
				isInputValid = readVals(s, 1, values);
				if (isInputValid) builder.recursionDepth = values[0];
			}
			else if (cmd == "vertex") {
				isInputValid = readVals(s, 3, values);
				if (isInputValid) vertexBuffer.push_back(vec3(values[0], values[1], values[2]));
			}
			else if (cmd == "vertexnormal") {
				isInputValid = readVals(s, 6, values);
				if (isInputValid) {
					//vertexBufferWithNormal.push_back(vec3(values[0], values[1], values[2]));
					//vertexNormalBuffer.push_back(vec3(values[3], values[4], values[5]));
				}
			}

			else if (cmd == "sphere") {
				isInputValid = readVals(s, 4, values);
				if (isInputValid) {
					builder.addPrimitive(new Sphere(vec3(values[0], values[1], values[2]), values[3], material));
				}
			}

			else if (cmd == "tri") {
				isInputValid = readVals(s, 3, values);
				if (isInputValid) {
					builder.addPrimitive(new Triangle(vertexBuffer[values[0]], 
						vertexBuffer[values[1]], vertexBuffer[values[2]], material));
				}
			}
			else if (cmd == "trinormal") {
				/*isInputValid = readVals(s, 6, values);
				if (isInputValid) {
					Triangle* triangle = new Triangle(vertexBufferWithNormal[values[0]], 
							vertexBufferWithNormal[values[1]], 
							vertexBufferWithNormal[values[2]],
							vertexNormalBuffer[values[0]],
							vertexNormalBuffer[values[1]],
							vertexNormalBuffer[values[2]]
							);
					objects.push_back(triangle);
					objects.back()->index = objects.size();
					objects.back()->materials = materials;
					objects.back()->transform = transformStack.top();
					objects.back()->InversedTransform = glm::inverse(transformStack.top());
				}*/
			}
		
			else if (cmd == "maxverts") { //  || cmd == "maxvertnorms"
				isInputValid = readVals(s, 1, values);
				if (isInputValid) {
					vertexBuffer.reserve((int) values[0]);
				}
			}

			else if (cmd == "translate") {
				isInputValid = readVals(s, 3, values) ; 
				if (isInputValid) {
					builder.addTransform(translate(vec3(values[0], values[1], values[2])));
				}
			}
			else if (cmd == "scale") {
				isInputValid = readVals(s, 3, values) ; 
				if (isInputValid) {
					builder.addTransform(scale(vec3(values[0], values[1], values[2])));
				}
			}
			else if (cmd == "rotate") {
				isInputValid = readVals(s, 4, values) ; 
				if (isInputValid) {
					builder.addTransform(rotate(radians(values[3]), vec3(values[0], values[1], values[2])));
				}
			}

			// I include the basic push/pop code for matrix stacks
			else if (cmd == "pushTransform") 
				builder.pushTransform();
			else if (cmd == "popTransform") {
				builder.popTransform();
			}

			else {
				cerr << "Unknown Command: " << cmd << " Skipping \n" ; 
			}
			getline (in, str) ; 
		}

		return builder.buildScene();
	}


	Parser::Parser() 
	{
	}

	Parser::~Parser()
	{
	}

}