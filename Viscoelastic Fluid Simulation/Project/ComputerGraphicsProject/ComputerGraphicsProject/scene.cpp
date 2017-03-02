#include "scene.h"
#include<GL/glut.h>
#include <iostream>
#define PARTICLE_RADIUS 0.1
#define delT 0.5f //in seconds
#define k 0.004f //stiffness parameter
#define k_near 0.01f //near stiffness parameter
#define h 1.0f //interaction radius
#define rho_0 10.0f //rest density
#define k_spring 0.3f //spring constant
#define gamma 0.1f //yield ratio
#define alpha 0.3 //plasticity constant
#define L_ 0.1f //spring rest length
#define sigma 1 //for viscosity
#define beta 1 //for viscosity

glm::vec3 g(0, 0.1, 0);

void scene::storeRandomPoints(int n)
{
	num_particles = n;
	x.resize(num_particles);
	v.resize(num_particles);
	x_prev.resize(num_particles);
	for (int i = 0; i < num_particles; ++i)
	{
		x[i].x = rand() / double(RAND_MAX) * 2;
		x[i].y = rand() / double(RAND_MAX) * 2;
		x[i].z = rand() / double(RAND_MAX) * 2;
		v[i] = glm::vec3(0.5, -0.5, 0);
		for (int j = 0; j < num_particles; ++j)
		{
			L[i][j] = 0;
		}
	}
}

void scene::makeScene()
{
	for (int i = 0; i < num_particles; ++i)
	{
		glTranslatef(x[i].x, x[i].y, x[i].z);
		glutSolidSphere(PARTICLE_RADIUS, 20, 20);
		glTranslatef(-x[i].x, -x[i].y, -x[i].z);
	}
}

void scene::simulate()
{
	std::cout << "in simulation\n";
	std::cout << "original x[0] = " << x[0].x << ", " << x[0].y << ", " << x[0].z << std::endl;
	for (int i = 0; i < num_particles; ++i)
	{
	  //change added SPHERE
	  if(x[i].y < 5.2 && (insphere(x[i])==0))
		v[i] = v[i] + delT * g;
	}
	applyViscosity();
	for (int i = 0; i < num_particles; ++i)
	{
		x_prev[i] = x[i];
		x[i] = x[i] + delT * v[i];
	}
	adjustSprings();
	applySpringDisplacements();
	doubleDensityRelaxation();
	resolveCollisions();
	for (int i = 0; i < num_particles; ++i)
	{
		v[i] = (x[i] - x_prev[i]) / delT;
	}
	std::cout << "x[0] = " << x[0].x << ", " << x[0].y << ", " << x[0].z << std::endl;
	//int x;
	//std::cin >> x;
	makeScene();
	std::cout << "finished one simulation\n";
}

void scene::doubleDensityRelaxation() 
{
	float q;
	glm::vec3 D, dx;
	for (int i = 0; i < num_particles; ++i)
	{
		rho = 0;
		rho_near = 0;
		for (int j = 0; j < num_particles; ++j)
		{
			if (i == j) continue;
			q = glm::length(x[j] - x[i]) / h;
			if (q < 1)
			{
				rho = rho + (1 - q) * (1 - q);
				rho_near = rho_near + (1 - q) * (1 - q) * (1 - q);
			}
		}
		P = k * (rho - rho_0);
		P_near = k_near * rho_near;
		dx = glm::vec3(0, 0, 0);
		for (int j = 0; j < num_particles; ++j)
		{
			if (i == j) continue;
			q = glm::length(x[j] - x[i]) / h;
			if (q < 1)
			{
				D = delT * delT * (P * (1 - q) + P_near * (1 - q) * (1 - q)) * glm::normalize(x[j] - x[i]);
				x[j] = x[j] + 0.5f * D;
				dx = dx - 0.5f * D;
			}
		}
		x[i] = x[i] + dx;
	}
}

void scene::applySpringDisplacements()
{
	glm::vec3 D;
	for (int i = 0; i < num_particles; ++i)
	{
		for (int j = 0; j < num_particles; ++j)
		{
			D = delT * delT * k_spring * (1 - L[i][j] / h) * (L[i][j] - glm::length(x[j] - x[i])) * glm::normalize(x[j] - x[i]);
		}
	}
	
}

void scene::adjustSprings() 
{
	float q, d;
	for (int i = 0; i < num_particles; ++i)
	{
		for (int j = 0; j < num_particles; ++j)
		{
			if (L[i][j] == 0)
				L[i][j] = h;
			d = gamma * L[i][j];
			if (glm::length(x[j] - x[i]) > L_ + d)
			{
				L[i][j] = L[i][j] + delT * alpha * (glm::length(x[j] - x[i]) - L_ - d);
			}
			else if (glm::length(x[i] - x[j]) < L_ - d)
			{
				L[i][j] = L[i][j] - delT * alpha * (L_ - d - glm::length(x[j] - x[i]));
			}
		}
	}
	for (int i = 0; i < num_particles; ++i)
	{
		for (int j = 0; j < num_particles; ++j)
		{
			if (L[i][j] > h)
			{
				L[i][j] = 0;
			}
		}
	}
}

void scene::applyViscosity()
{
	float q, u;
	vec3 I;
	for (int i = 0; i < num_particles - 1; ++i)
	{
		for (int j = i + 1; j < num_particles; ++j)
		{
			q = glm::length(x[j] - x[i]) / h;
			if (q < 1)
			{
				u = glm::dot(v[i] - v[j], x[j] - x[i]);
				if (u > 0)
				{
					I = delT * (1 - q) * (sigma * u + beta * u * u) * normalize(x[j] - x[i]);
					v[i] = v[i] - 0.5f * I;
					v[j] = v[j] + 0.5f * I;
				}
			}
			
		}
	}
}
int scene::insphere(vec3 v)
{
	if ((v.x - 1)*(v.x - 1) + (v.y - 5)*(v.y - 5) + (v.z - 1)*(v.z - 1) - 4 < 0.8)
		return 1;
	else
		return 0;
}
void scene::resolveCollisions() 
{
	float elastic = 0.9;
	for (int i = 0; i < num_particles; ++i)
	{
		//INSPHERE PART
		if (insphere(x[i]))
		{
			x_prev[i] = x[i];
			vec3 n(x[i].x-1,x[i].y-5,x[i].z-2);
			n = normalize(n);
			v[i] = (glm::reflect(v[i], n)) * elastic;
			x[i] = x[i] + delT * v[i];

		}
		if (x[i].y > 5)
		{
			x_prev[i] = x[i];
			vec3 n(0, -1, 0);
			v[i] = (glm::reflect(v[i], n)) * elastic;
			x[i] = x[i] + delT * v[i];
		}
		if (x[i].x < -1)
		{
			x_prev[i] = x[i];
			vec3 n(1, 0, 0);
			v[i] = glm::reflect(v[i], n) * elastic;
			x[i] = x[i] + delT * v[i];

		}
		if (x[i].x > 3)
		{
			x_prev[i] = x[i];
			vec3 n(-1, 0, 0);
			v[i] = glm::reflect(v[i], n) * elastic;
			x[i] = x[i] + delT * v[i];
		}
		if (x[i].z < -1)
		{
			x_prev[i] = x[i];
			vec3 n(0, 0, 1);
			v[i] = glm::reflect(v[i], n) * elastic;
			x[i] = x[i] + delT * v[i];
		}
		if (x[i].z > 3)
		{
			x_prev[i] = x[i];
			vec3 n(0, 0, -1);
			v[i] = glm::reflect(v[i], n) * elastic;
			x[i] = x[i] + delT * v[i];
		}
	}
}
