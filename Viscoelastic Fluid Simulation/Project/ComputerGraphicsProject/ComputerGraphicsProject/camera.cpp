#include "camera.h"
#include "point3.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<math.h>
#include<GLFW/glfw3.h>
#define PI 3.14159265
using namespace glm;

void camera::setModelviewMatrix()
{
	float m[16];
	vec3 eVec(eye.x, eye.y, eye.z);
	m[0] = u.x;
	m[1] = v.x;
	m[2] = n.x;
	m[3] = 0;
	m[4] = u.y;
	m[5] = v.y;
	m[6] = n.y;
	m[7] = 0;
	m[8] = u.z;
	m[9] = v.z;
	m[10] = n.z;
	m[11] = 0;
	m[12] = -dot(eVec,u);
	m[13] = -dot(eVec,v);
	m[14] = -dot(eVec,n);
	m[15] = 1.0f;
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadMatrixf(m);
}

camera::camera(point3 EYE,point3 LOOK,vec3 UP,bool set)
{
	free = set;
	eye.set(EYE);
	look.set(LOOK);
	up = UP;
}

void camera::set()
{
	std::cout <<"Setting\n";
	n.x = eye.x - look.x;
	n.y = eye.y - look.y;
	n.z = eye.z - look.z;
	u = cross(up, n);
	n = normalize(n);
	u = normalize(u);
	v = cross(n, u);
	setModelviewMatrix();
}

void camera::set(point3 EYE, point3 LOOK, vec3 UP,bool set)
{
	free = set;
	eye.set(EYE);
	n.x = eye.x - LOOK.x;
	n.y = eye.y - LOOK.y;
	n.z=eye.z - LOOK.z;
	u=cross(UP,n);
	n=normalize(n);
	u=normalize(u);
	v=cross(n,u);
	setModelviewMatrix();
}

void camera::rotate(float pitch, float yaw, float roll)
{
	float COSpitch = cos(PI * pitch / 180);
	float SINpitch = sin(PI * pitch / 180);
	float COSyaw = cos(PI * yaw / 180);
	float SINyaw = sin(PI * yaw / 180);
	float COSroll = cos(PI * roll / 180);
	float SINroll = sin(PI * roll / 180);
	n.x = COSpitch * SINyaw;
	n.y = SINpitch;
	n.z = COSpitch * COSyaw;
	u.x = -COSyaw*COSroll;
	u.y = SINroll;
	u.z = SINyaw*COSroll;
	v = normalize(cross(n, u));
	setModelviewMatrix();
}

void camera::roll(float angle)
{
	float cs = cos(PI*angle/180);
	float sn = sin(PI*angle / 180);
	vec3 t = u;
	u.x = sn*v.x + cs*t.x;
	u.y = sn*v.y + cs*t.y;
	u.z = sn*v.z + cs*t.z;
	v.x = cs*v.x - sn*t.x;
	v.y = cs*v.y - sn*t.y;
	v.z = cs*v.z - sn*t.z;
	setModelviewMatrix();
}

void camera::pitch(float angle)
{
	float cs = cos(PI*angle / 180);
	float sn = sin(PI*angle / 180);
	vec3 t = v;
	v.x = sn*n.x + cs*t.x;
	v.y = sn*n.y + cs*t.y;
	v.z = sn*n.z + cs*t.z;
	n.x = cs*n.x - sn*t.x;
	n.y = cs*n.y - sn*t.y;
	n.z = cs*n.z - sn*t.z;
	setModelviewMatrix();
}

void camera::yaw(float angle)
{
	float cs = cos(PI*angle / 180);
	float sn = sin(PI*angle / 180);
	vec3 t = n;
	n.x = sn*u.x + cs*t.x;
	n.y = sn*u.y + cs*t.y;
	n.z = sn*u.z + cs*t.z;
	u.x = cs*u.x - sn*t.x;
	u.y = cs*u.y - sn*t.y;
	u.z = cs*u.z - sn*t.z;
	setModelviewMatrix();
}

bool camera::slide(float delU, float delV, float delN, bool plane)
{
	bool inside = false;
	float origx = eye.x, origy = eye.y, origz = eye.z;
	if (plane == true)
	{
		std::cout << "eye x updated from " << eye.x;
		eye.x += delU*u.x + delV*v.x + delN*n.x;
		std::cout << " to " << eye.x << "\n";
		std::cout << "eye y updated from " << eye.y;
		if (free) eye.y += delU*u.y + delV*v.y + delN*n.y;
		else eye.y += 0;
		std::cout << " to " << eye.y << "\n";
		std::cout << "eye z updated from " << eye.z;
		eye.z += delU*u.z + delV*v.z + delN*n.z;
		std::cout << " to " << eye.z << "\n";
	}
	else
	{
		std::cout << "eye x updated from " << eye.x;
		eye.x += delU;
		std::cout << " to " << eye.x << "\n";
		std::cout << "eye y updated from " << eye.y;
		eye.y += delV;
		std::cout << " to " << eye.y << "\n";
		std::cout << "eye z updated from " << eye.z;
		eye.z += delN;
		std::cout << " to " << eye.z << "\n";
	}

	if (!free)
	{
		if (checkInside())
		{
			eye.x = origx;
			eye.y = origy;
			eye.z = origz;
			std::cout << "sorry didn't change any values, intersection occured" << std::endl;
			inside = true;
		}
	}
	setModelviewMatrix();
	if (inside) return true;
	else return false;
}

void camera::setShape(float vAng, float asp, float nearD, float farD)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(vAng,asp, nearD, farD);
}

void camera::getShape(float & vang, float & Asp, float & near, float & far)
{
	vAng = vang;
	asp = Asp;
	nearD = near;
	farD = far;
}

bool camera::checkInside()
{
	if (eye.y < -3.5) return false;
	if (eye.x > 39 || eye.x < -39) return true;
	if (eye.z > 47.8 || eye.z < -10.1) return true;
	int objects = 25, count;
	float cover = 0.2;
	float XMinLm, XMaxLm, ZMinLm, ZMaxLm;
	for (int i = 1; i <= objects; ++i)
	{
		count = 0;
		//student desks
		//row 1
		if (i == 1)
		{
			XMinLm = 18.16;
			XMaxLm = 23.86;
			ZMinLm = 6.12;
			ZMaxLm = 10.52;
		}
		else if (i == 2)
		{
			XMinLm = 3.16;
			XMaxLm = 8.86;
			ZMinLm = 6.12;
			ZMaxLm = 10.52;
		}
		else if (i == 3)
		{
			XMinLm = -11.84;
			XMaxLm = -6.14;
			ZMinLm = 6.12;
			ZMaxLm = 10.52;
		}
		else if (i == 4)
		{
			XMinLm = -26.84;
			XMaxLm = -21.14;
			ZMinLm = 6.12;
			ZMaxLm = 10.52;
		}
		//************************************************************************************************
		//row 2
		else if (i == 5)
		{
			XMinLm = 18.16;
			XMaxLm = 23.86;
			ZMinLm = 20.12;
			ZMaxLm = 24.52;
		}
		else if (i == 6)
		{
			XMinLm = 3.16;
			XMaxLm = 8.86;
			ZMinLm = 20.12;
			ZMaxLm = 24.52;
		}
		else if (i == 7)
		{
			XMinLm = -11.84;
			XMaxLm = -6.14;
			ZMinLm = 20.12;
			ZMaxLm = 24.52;
		}
		else if (i == 8)
		{
			XMinLm = -26.84;
			XMaxLm = -21.14;
			ZMinLm = 20.12;
			ZMaxLm = 24.52;
		}
		//************************************************************************************************
		//row 3
		else if (i == 9) //5
		{
			XMinLm = 18.16;
			XMaxLm = 23.86;
			ZMinLm = 34.12;
			ZMaxLm = 38.52;
		}
		else if (i == 10)
		{
			XMinLm = 3.16;
			XMaxLm = 8.86;
			ZMinLm = 34.12;
			ZMaxLm = 38.52;
		}
		else if (i == 11)
		{
			XMinLm = -11.84;
			XMaxLm = -6.14;
			ZMinLm = 34.12;
			ZMaxLm = 38.52;
		}
		else if (i == 12)
		{
			XMinLm = -26.84;
			XMaxLm = -21.14;
			ZMinLm = 34.12;
			ZMaxLm = 38.52;
		}
		//************************************************************************************************
		//chairs
		//row 1
		if (i == 13)
		{
			XMinLm = 19.57;
			XMaxLm = 22.27;
			ZMinLm = 11.92;
			ZMaxLm = 14.01;
		}
		else if (i == 14)
		{
			XMinLm = 4.64;
			XMaxLm = 7.34;
			ZMinLm = 11.92;
			ZMaxLm = 14.01;
		}
		else if (i == 15)
		{
			XMinLm = -10.3;
			XMaxLm = -7.6;
			ZMinLm = 11.92;
			ZMaxLm = 14.01;
		}
		else if (i == 16)
		{
			XMinLm = -25.43;
			XMaxLm = -22.73;
			ZMinLm = 11.92;
			ZMaxLm = 14.01;
		}
		//************************************************************************************************
		//row 2
		if (i == 17)
		{
			XMinLm = 19.58;
			XMaxLm = 22.28;
			ZMinLm = 26.22;
			ZMaxLm = 28.31;
		}
		else if (i == 18)
		{
			XMinLm = 4.64;
			XMaxLm = 7.34;
			ZMinLm = 26.22;
			ZMaxLm = 28.31;
		}
		else if (i == 19)
		{
			XMinLm = -10.3;
			XMaxLm = -7.6;
			ZMinLm = 26.22;
			ZMaxLm = 28.31;
		}
		else if (i == 20)
		{
			XMinLm = -25.24;
			XMaxLm = -22.54;
			ZMinLm = 26.22;
			ZMaxLm = 28.31;
		}
		//************************************************************************************************
		//row 3
		if (i == 21)
		{
			XMinLm = 19.57;
			XMaxLm = 22.27;
			ZMinLm = 40.52;
			ZMaxLm = 42.61;
		}
		else if (i == 22)
		{
			XMinLm = 4.64;
			XMaxLm = 7.34;
			ZMinLm = 40.52;
			ZMaxLm = 42.61;
		}
		else if (i == 23)
		{
			XMinLm = -10.3;
			XMaxLm = -7.6;
			ZMinLm = 40.52;
			ZMaxLm = 42.61;
		}
		else if (i == 24)
		{
			XMinLm = -25.24;
			XMaxLm = -22.54;
			ZMinLm = 40.52;
			ZMaxLm = 42.61;
		}
		//************************************************
		//Teacher Table
		else if (i == 25)
		{
			XMinLm = -10.1;
			XMaxLm = 6.1;
			ZMinLm = -4.7;
			ZMaxLm = -1.3;
		}
		if (eye.x > XMinLm - cover && eye.x < XMaxLm + cover) ++count;
		if (eye.z > ZMinLm - cover && eye.z < ZMaxLm + cover) ++count;
		if (count == 2) return true;
	}
	return false;
}

bool camera::interact(float height,bool &toggle)
{
	float XMinLm, XMaxLm, ZMinLm, ZMaxLm;
	float Xcent, Zcent, Xsit, Zsit,MIN=100;
	
	if (toggle)
	{
		origeye.set(eye);
		float cover = 5;
		//************************************************************************************************
		//chairs
		//row 1
		for (int i = 1;i <= 12;i++)
		{
			if (i == 1)
			{
				XMinLm = 19.57;
				XMaxLm = 22.27;
				ZMinLm = 11.92;
				ZMaxLm = 14.01;
			}
			else if (i == 2)
			{
				XMinLm = 4.64;
				XMaxLm = 7.34;
				ZMinLm = 11.92;
				ZMaxLm = 14.01;
			}
			else if (i == 3)
			{
				XMinLm = -10.3;
				XMaxLm = -7.6;
				ZMinLm = 11.92;
				ZMaxLm = 14.01;
			}
			else if (i == 4)
			{
				XMinLm = -25.43;
				XMaxLm = -22.73;
				ZMinLm = 11.92;
				ZMaxLm = 14.01;
			}
			//************************************************************************************************
			//row 2
			else if (i == 5)
			{
				XMinLm = 19.58;
				XMaxLm = 22.28;
				ZMinLm = 26.22;
				ZMaxLm = 28.31;
			}
			else if (i == 6)
			{
				XMinLm = 4.64;
				XMaxLm = 7.34;
				ZMinLm = 26.22;
				ZMaxLm = 28.31;
			}
			else if (i == 7)
			{
				XMinLm = -10.3;
				XMaxLm = -7.6;
				ZMinLm = 26.22;
				ZMaxLm = 28.31;
			}
			else if (i == 8)
			{
				XMinLm = -25.24;
				XMaxLm = -22.54;
				ZMinLm = 26.22;
				ZMaxLm = 28.31;
			}
			//************************************************************************************************
			//row 3
			else if (i == 9)
			{
				XMinLm = 19.57;
				XMaxLm = 22.27;
				ZMinLm = 40.52;
				ZMaxLm = 42.61;
			}
			else if (i == 10)
			{
				XMinLm = 4.64;
				XMaxLm = 7.34;
				ZMinLm = 40.52;
				ZMaxLm = 42.61;
			}
			else if (i == 11)
			{
				XMinLm = -10.3;
				XMaxLm = -7.6;
				ZMinLm = 40.52;
				ZMaxLm = 42.61;
			}
			else if (i == 12)
			{
				XMinLm = -25.24;
				XMaxLm = -22.54;
				ZMinLm = 40.52;
				ZMaxLm = 42.61;
			}
			Xcent = (XMinLm + XMaxLm) / 2;
			Zcent = (ZMinLm + ZMaxLm) / 2;
			if (sqrt((eye.x - Xcent)*(eye.x - Xcent) + (eye.z - Zcent)*(eye.z - Zcent)) <= MIN)
			{
				MIN = sqrt((eye.x - Xcent)*(eye.x - Xcent) + (eye.z - Zcent)*(eye.z - Zcent));
				Xsit = Xcent;
				Zsit = Zcent;
			}
			
		}
		//std::cout << "\nANS=\n" << sqrt((eye.x - Xsit)*(eye.x - Xsit) + (eye.z - Zsit)*(eye.z - Zsit));
		if (sqrt((eye.x - Xsit)*(eye.x - Xsit) + (eye.z - Zsit)*(eye.z - Zsit)) <= cover)
		{
			std::cout << "Xsit:" << Xsit << " Zsit:" << Zsit << "\n";
			eye.x = Xsit;
			eye.y = height;
			eye.z = Zsit;
			sit = true;
		}
		else
			toggle = false;
	}
	else if(sit==true)
	{
			eye.set(origeye);
			sit = false;
	}
	setModelviewMatrix();
	return sit;
}

float camera::eyeComponent(int component)
{
	if (component == 1) return eye.x;
	if (component == 2) return eye.y;
	if (component == 3) return eye.z;
}

void camera::changeComponent(int component, float value)
{
	if (component == 1) eye.x = value;
	if (component == 2) eye.y = value;
	if (component == 3) eye.z = value;
}

bool camera::getsetting()
{
	bool ret = free;
	return ret;
}

void camera::setsetting(bool set)
{
	free= set;
}
