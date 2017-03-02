#include "point3.h"
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
void point3::set(float dx, float dy, float dz)
{
	x = dx;
	y = dy;
	z = dz;
}
void point3:: set(point3 &p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}
void point3::build4tuple(vec4 v)
{
	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 1.0f;
}
point3::point3()
{
	x = y = z = 0;
}

point3::point3(float dx,float dy,float dz)
{
	x = dx;
	y = dy;
	z = dz;
}

