#pragma once
#include <vector>
#include "point3.h"


class scene
{

public:
	//!Density value
	float rho;
	//!Near density value
	float rho_near;
	//!Pressure value
	float P;
	//!Near pressure value
	float P_near;
	//!Stores the spring length value between two fluid particles
	float L[1000][1000];
	//!Vector storing the previous positions for all particles
	std::vector<glm::vec3> x_prev;
	//!Vector storing the current positions for all particles
	std::vector<glm::vec3> x;
	//!Vector storing the velocities for all particles
	std::vector<glm::vec3> v;
	//!Number of particles
	int num_particles;
	//!Function which generates fluid particles at random locations
	void storeRandomPoints(int);
	//!Function which draws the scene for simulation
	void makeScene();
	//!Function which runs a single simultaion cycle for the fluid
	void simulate();
	//!Function that applies displacement and velocity changes due to viscosity of fluid
	void applyViscosity();
	//!Function that updates spring length and spring rest length after each simulation
	void adjustSprings();
	//!Function that handles elasticity by applying spring displacements to each fluid particles
	void applySpringDisplacements();
	//!Function which handles attraction and repulsion between particles based on the fluid density and neraby particles
	void doubleDensityRelaxation();
	//!Function which resolves collisions between particles and the objects
	void resolveCollisions();
	int insphere(vec3 v);
};

