#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>
using namespace glm;
class point3
{
public:
	// !X coordinate
	float x;
	// !Y coordinate
	float y;
	// !Z coordinate
	float z;
	// !Sets the coordinates of the points with values passed as parameters
	void set(float,float,float);
	// !Sets the coordinates of the points with values passed as parameters
	void set(point3 &);
	// !Build a 4-tuple of the point
	void build4tuple(vec4);
	// !Default constructor that initializes the point as origin
	point3();
	// !Constructor that set the values of coordinates with values passed as parameters
	point3(float,float,float);	
};

