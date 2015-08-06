#include "ShittyParser.h"

void ShittyParser::rightmultiply(const mat4 & M, stack<mat4> &transform_stack) {
	mat4 &T = transform_stack.top() ; 
	// Right multiply M, but do this left to account for row/column major 
	T = T * M ; 
}

// Function to read the input data values
// Use is optional, but should be very helpful in parsing.  
bool ShittyParser::readvals(stringstream &s, const int numvals, float *values) {
	for (int i = 0 ; i < numvals ; i++) {
		s >> values[i] ; 
		if (s.fail()) {
			cout << "Failed reading value " << i << " will skip\n" ; 
			return false ;
		}
	}
	return true ; 
}

Scene* ShittyParser::readfile(const string &filename) {
	string str, cmd ; 
	ifstream in ;
	in.open(filename.c_str()); 
	if (!in.is_open()) {
		cerr << "Open " << filename << " failed!" << endl;
		throw 2;
	}
	// I need to implement a matrix stack to store transforms.  
	// This is done using standard STL Templates 
	stack<mat4> transform_stack ; 
	transform_stack.push(mat4(1.0)) ;  // identity

	getline (in, str) ; 
	while (in) {
		if (!((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#'))) {
            getline(in, str);
            continue;
		}
		// Ruled out comment and blank lines 
		stringstream s(str);
		s >> cmd; 
		float values[10]; // position and color for light, colors for others
		// Up to 10 params for cameras.  
		bool validinput ; // validity of input 
        
        if (cmd == "output") {
            // s >> outputFile;
        }
		// Process the light, add it to database.
		// directional light
		else if (cmd == "directional" || cmd == "point") {
            validinput = readvals(s, 6, values) ; // Position/color for lts.
            if (validinput) {
                vec3 positionOrDirection = vec3(values[0], values[1], values[2]);
                Color color = Color(values[3], values[4], values[5]);
                if (cmd == "directional") {
					lights.push_back(new DirectionalLight(positionOrDirection, color, 1.f));
				}
				else if (cmd == "point") {
					lights.push_back(new PointLight(positionOrDirection, color, 1.f));
				}
            }
		}
		else if (cmd == "attenuation") {
		    /*validinput = readvals(s, 3, values);
		    if (validinput) 
                for (i = 0; i < 3; ++i) attenuation[i] = values[i];*/
		}
		// materials Commands 
		// Ambient, diffuse, specular, shininess
		// Filling this in is pretty straightforward, so I've left it in 
		// the skeleton, also as a hint of how to do the more complex ones.
		// Note that no transformrs/stacks are applied to the colors. 
		else if (cmd == "ambient") {
			validinput = readvals(s, 3, values) ; // colors 
			if (validinput) 
                material.ambient = Color(values[0], values[1], values[2]); 
		}
		else if (cmd == "diffuse") {
			validinput = readvals(s, 3, values) ; 
			if (validinput) 
                material.diffuse = Color(values[0], values[1], values[2]); 
		}
		else if (cmd == "specular") {
			validinput = readvals(s, 3, values) ; 
			if (validinput) 
                material.specular = Color(values[0], values[1], values[2]); 
		}
		else if (cmd == "emission") {
			validinput = readvals(s, 3, values) ; 
			if (validinput) 
                material.emissive = Color(values[0], values[1], values[2]); 
		}
		else if (cmd == "shininess") {
			validinput = readvals(s, 1, values) ; 
			if (validinput) 
                material.shininess = values[0] ; 
		}
		else if (cmd == "size") {
			validinput = readvals(s, 2, values) ; 
			if (validinput) { 
				width = (int) values[0] ; 
				height = (int) values[1] ; 
			}
		}
		else if (cmd == "camera") {
			validinput = readvals(s, 10, values) ; // 10 values eye cen up fov
			if (validinput) {
				camera = new Camera(width, height, values[9]);
				camera->lookAt(vec3(values[0], values[1], values[2]),
							   vec3(values[3], values[4], values[5]),
							   vec3(values[6], values[7], values[8]));
			}
		}
		else if (cmd == "maxdepth") {
			validinput = readvals(s, 1, values);
			if (validinput) recursionDepth = values[0];
		}
		else if (cmd == "vertex") {
			validinput = readvals(s, 3, values);
			if (validinput) vertexBuffer.push_back(vec3(values[0], values[1], values[2]));
		}
		else if (cmd == "vertexnormal") {
			validinput = readvals(s, 6, values);
			if (validinput) {
				//vertexBufferWithNormal.push_back(vec3(values[0], values[1], values[2]));
				//vertexNormalBuffer.push_back(vec3(values[3], values[4], values[5]));
			}
		}
		else if (cmd == "tri") {
			validinput = readvals(s, 3, values);
			if (validinput) {
				Triangle* triangle = new Triangle(vertexBuffer[values[0]], 
					vertexBuffer[values[1]], vertexBuffer[values[2]], material);
				mat4 t = transform_stack.top();
				triangle->transform(t);
				primitives.push_back(triangle);
			}
		}
		else if (cmd == "trinormal") {
			/*validinput = readvals(s, 6, values);
			if (validinput) {
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
				objects.back()->transform = transform_stack.top();
				objects.back()->InversedTransform = glm::inverse(transform_stack.top());
			}*/
		}

		else if (cmd == "sphere") {
			validinput = readvals(s, 4, values);
			Sphere* sphere = new Sphere(vec3(values[0], values[1], values[2]), values[3], material);
			mat4 t = transform_stack.top();
			sphere->transform(t);
			primitives.push_back(sphere);
		}
		
		else if (cmd == "maxverts" || cmd == "maxvertnorms") { // just ignore
		}

		else if (cmd == "translate") {
			validinput = readvals(s,3,values) ; 
			if (validinput) {
				rightmultiply(translate(vec3(values[0], values[1], values[2])), transform_stack);
			}
		}
		else if (cmd == "scale") {
			validinput = readvals(s,3,values) ; 
			if (validinput) {
				rightmultiply(scale(vec3(values[0], values[1], values[2])), transform_stack);
			}
		}
		else if (cmd == "rotate") {
			validinput = readvals(s,4,values) ; 
			if (validinput) {
				mat4 rot = rotate(radians(values[3]), vec3(values[0], values[1], values[2]));
				rightmultiply(rot, transform_stack);
			}
		}

		// I include the basic push/pop code for matrix stacks
		else if (cmd == "pushTransform") 
			transform_stack.push(transform_stack.top()) ; 
		else if (cmd == "popTransform") {
			if (transform_stack.size() <= 1) 
				cerr << "Stack has no elements.  Cannot Pop\n" ; 
			else transform_stack.pop() ; 
		}

		else {
			cerr << "Unknown Command: " << cmd << " Skipping \n" ; 
		}
		getline (in, str) ; 
    }
	return new Scene((*camera), primitives, lights);
}


ShittyParser::ShittyParser() 
{
}

ShittyParser::~ShittyParser()
{
}