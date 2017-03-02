#pragma once
#include <glm/glm.hpp>
#include "point3.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
class camera
{
	// !temporary eye used for storage before sitting
	point3 origeye; 
	// !main eye that is used for viewing
	point3 eye; 
	// !look direction (only for initializing)
	point3 look; 
	// !up direction (only for initializing)
	vec3 up;
	// !u, v, n perpendicular vectors for eye directions
	vec3 u, v, n;
	// !to set the camera free of restrictions
	bool free;
	// !to tell if the "student" has "sat"
	bool sit;
	// !viewing angle
	float vAng;
	// !aspect ratio
	float asp;
	// !Location of near plane
	float nearD;
	// !Location of far plane
	float farD;
	/* !forms the matrix for multiplication and loads matrix into stack
	*/
	void setModelviewMatrix();
public:
	/* !sets the camera with the passed parameters
	*/
	camera(point3,point3,vec3,bool);
	/* !calculates u, v, n for the camera
	*/
	void set();
	/* !calculates u, v, n from the passed parameters
	*/
	void set(point3, point3, vec3,bool); //like gluLookAt
	/* !rotate function dominates all rotation roll, yaw and pitch
	*/
	void rotate(float, float, float);
	/* !rolls the camera by specified angle
	*/
	void roll(float);
	/* !pitches the camera by specified angle
	*/
	void pitch(float);
	/* !yaws the camera by specified angle
	*/
	void yaw(float);
	/* !slides the camera by specified u, v, n distance
	if plane is true then the transformation will remain in the same XZ plane
	*/
	bool slide(float, float, float, bool plane = true);
	/* !sets projection matrix
	*/
	void setShape(float vAng, float asp, float nearD, float farD);
	/* !takes inputs from user
	*/
	void getShape(float &vAng, float &asp, float &nearD, float &farD);
	/* !checks if eye is inside a desk or table or outside the classroom
	*/
	bool checkInside();
	/* !returns true if eye is close to a chair and changes the location of the eye to center of the chair and lowers the height
	toggles. If already sat, then the eye moves up to its original location
	*/
	bool interact(float,bool&);
	/* !changes the camera to free flow
	*/
	void setsetting(bool);
	/* !returns a component of eye
	*/
	float eyeComponent(int component);
	/* !changes a component of eye
	*/
	void changeComponent(int component, float value);
	/* !get setting of camera
	*/
	bool getsetting();
};

