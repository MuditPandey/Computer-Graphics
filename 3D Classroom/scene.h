#pragma once
class scene
{
public:
	// !draws cube 
	void drawCube(float,float,float);
	// !draws long teacher table
	void drawLTable(float, float, float);
	// !draws colored cube with r,g,b values passed as parameters
	void drawColoredCube(float, float, float);
	// !draws walls of classroom
	void drawWalls();
	// !draws window
	void drawWindow(float,float,float);
	// !draws student table
	void drawSTable();
	// !draws student table
	void drawChair(double);
	void chairLeg(double, double, double);
	// !draws door
	void drawDoor();
	// !draws tube light
	void drawLight(float, float, float);
	// !draws blackboard
	void drawScreen();
	// !draws classroom scenes
	void DRAW_CLASSROOM();
};

