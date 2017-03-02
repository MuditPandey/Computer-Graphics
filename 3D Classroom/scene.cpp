#include "scene.h"
#include<GL/glut.h>

void scene::drawColoredCube(float r, float g, float b)
{
	//Draws A Unit Cube With Specified RGB Color
	glColor4f(r, g, b, 1.0f);
	glBegin(GL_QUADS);
	// Top Face
	glVertex3f(1.0 / 2, 1.0 / 2, -1.0 / 2);
	glVertex3f(-1.0 / 2, 1.0 / 2, -1.0 / 2);
	glVertex3f(-1.0 / 2, 1.0 / 2, 1.0 / 2);
	glVertex3f(1.0 / 2, 1.0 / 2, 1.0 / 2);
	// Bottom Face
	glVertex3f(1.0 / 2, -1.0 / 2, 1.0 / 2);
	glVertex3f(-1.0 / 2, -1.0 / 2, 1.0 / 2);
	glVertex3f(-1.0 / 2, -1.0 / 2, -1.0 / 2);
	glVertex3f(1.0 / 2, -1.0 / 2, -1.0 / 2);
	// Front Face
	glVertex3f(1.0 / 2, 1.0 / 2, 1.0 / 2);
	glVertex3f(-1.0 / 2, 1.0 / 2, 1.0 / 2);
	glVertex3f(-1.0 / 2, -1.0 / 2, 1.0 / 2);
	glVertex3f(1.0 / 2, -1.0 / 2, 1.0 / 2);
	// Back Face
	glVertex3f(1.0 / 2, -1.0 / 2, -1.0 / 2);
	glVertex3f(-1.0 / 2, -1.0 / 2, -1.0 / 2);
	glVertex3f(-1.0 / 2, 1.0 / 2, -1.0 / 2);
	glVertex3f(1.0 / 2, 1.0 / 2, -1.0 / 2);
	// Left Face
	glVertex3f(-1.0 / 2, 1.0 / 2, 1.0 / 2);
	glVertex3f(-1.0 / 2, 1.0 / 2, -1.0 / 2);
	glVertex3f(-1.0 / 2, -1.0 / 2, -1.0 / 2);
	glVertex3f(-1.0 / 2, -1.0 / 2, 1.0 / 2);
	// Right Face
	glVertex3f(1.0 / 2, 1.0 / 2, -1.0 / 2);
	glVertex3f(1.0 / 2, 1.0 / 2, 1.0 / 2);
	glVertex3f(1.0 / 2, -1.0 / 2, 1.0 / 2);
	glVertex3f(1.0 / 2, -1.0 / 2, -1.0 / 2);
	glEnd();
}
void scene::drawCube(float r, float g, float b)
{
	//Function Which Calls drawColored Cube And Specifies That The Cube Drawn Is Solid
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawColoredCube(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(0.75, 1.0);
	drawColoredCube(r, g, b);
	glDisable(GL_POLYGON_OFFSET_FILL);
}
void scene::drawLTable(float x, float y, float z)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotated(180, 1, 0, 0);
	//Back
	glPushMatrix();
	glTranslated(-6, -0.4, 0);
	glScaled(0.5, 3.2, 8);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	//Box
	glPushMatrix();
	glTranslated(-5, -0.4, 2.7);
	glScaled(1.75, 3.2, 2.5);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	//Boxline
	glPushMatrix();
	glTranslated(-4.9, -0.4, 2.7);
	glScaled(1.5, 3.2, 2.5);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	//Minibox
	glPushMatrix();
	glTranslated(-5, -0.4, 2.7);
	glScaled(1.75, 1, 2.46);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	//Box2
	glPushMatrix();
	glTranslated(-5, -0.4, -2.7);
	glScaled(1.82, 3.2, 2.5);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	//Boxline2
	glPushMatrix();
	glTranslated(-4.9, -0.4, -2.7);
	glScaled(1.6, 3.2, 2.5);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	//Minibox2
	glPushMatrix();
	glTranslated(-5, -0.4, -2.7);
	glScaled(1.82, 1, 2.46);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	//Top
	glPushMatrix();
	glTranslated(-5.12, 1.3, 0);
	glScaled(2.25, 0.22, 8.1);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	//Handles
	glPushMatrix();
	glTranslated(-4.075, -1.5, 2.75);
	glScaled(0.095, 0.1, 0.5);
	drawCube(0.85f, 0.85f, 0.85f);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-4.075, -0.45, 2.75);
	glScaled(0.095, 0.1, 0.5);
	drawCube(0.85f, 0.85f, 0.85f);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-4.075, 0.6, 2.75);
	glScaled(0.095, 0.1, 0.5);
	drawCube(0.85f, 0.85f, 0.85f);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-4.045, -1.5, -2.75);
	glScaled(0.095, 0.1, 0.5);
	drawCube(0.85f, 0.85f, 0.85f);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-4.045, -0.45, -2.75);
	glScaled(0.095, 0.1, 0.5);
	drawCube(0.85f, 0.85f, 0.85f);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-4.045, 0.6, -2.75);
	glScaled(0.095, 0.1, 0.5);
	drawCube(0.85f, 0.85f, 0.85f);
	glPopMatrix();

	glPopMatrix();

}
void scene::drawWalls()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotated(180, 1, 0, 0);
	glBegin(GL_QUADS);
	//Floor
	glColor4d(0.85f, 0.85f, 0.85f, 1.0);
	glVertex3f(-10, -5.0, 3);
	glVertex3f(10, -5.0, 3);
	glVertex3f(10, -5.0, -12.5);
	glVertex3f(-10, -5.0, -12.5);

	//Ceiling 
	glColor3d(0.95f, 0.95f, 0.75f);
	glVertex3f(-10, 5.0, 3);
	glVertex3f(10, 5.0, 3);
	glColor3d(1.0f, 1.0f, 0.65f);
	glVertex3f(10, 5.0, -12.5);
	glVertex3f(-10, 5.0, -12.5);

	//Left Wall
	glColor3d(1.0f, 1.0f, 0.6f);
	glVertex3f(-10, -5.0, -12.5);
	glColor4d(1.0f, 1.0f, 0.75f, 1.0);
	glVertex3f(-10, 5.0, -12.5);
	glColor3d(1.0f, 1.0f, 0.75f);
	glVertex3f(-10, 5.0, 3);
	glColor3d(1.0f, 1.0f, 0.6f);
	glVertex3f(-10, -5.0, 3);

	//Front Wall
	glColor4d(1.0f, 1.0f, 0.75f, 1.0);
	glVertex3f(-10, 5.0, -12.5);
	glVertex3f(10, 5.0, -12.5);
	glColor4d(1.0f, 1.0f, 0.65f, 1.0);
	glVertex3f(10, -5.0, -12.5);
	glVertex3f(-10, -5.0, -12.5);

	//Back Wall
	glColor4d(1.0f, 1.0f, 0.75f, 1.0);
	glColor3d(1.0f, 1.0f, 0.75f);
	glVertex3f(-10, 5.0, 3);
	glVertex3f(10, 5.0, 3);
	glColor4d(1.0f, 1.0f, 0.65f, 1.0);
	glVertex3f(10.0, -5.0, 3);
	glVertex3f(-10.0, -5.0, 3);

	//right wall with the door
	glVertex3f(10, -5.0, -6);
	glColor4d(1.0f, 1.0f, 0.75f, 1.0);
	glVertex3f(10, 5.0, -6);
	glColor3d(1.0f, 1.0f, 0.75f);
	glVertex3f(10, 5.0, 3);
	glVertex3f(10, -5.0, 3);

	glColor3d(1.0f, 1.0f, 0.6f);
	glVertex3f(10, -5.0, -12.5);
	glColor4d(1.0f, 1.0f, 0.75f, 1.0);
	glVertex3f(10, 5.0, -12.5);
	glColor3d(1.0f, 1.0f, 0.75f);
	glVertex3f(10, 5.0, -10);
	glVertex3f(10, -5.0, -10);

	glVertex3f(10, 2.5, -10);
	glVertex3f(10, 5.0, -10);
	glColor3d(1.0f, 1.0f, 0.75f);
	glVertex3f(10, 5.0, -6);
	glVertex3f(10, 2.5, -6);

    glEnd();
	glPopMatrix();
}
void scene::drawWindow(float x, float y, float z)
{
	glPushMatrix();
	glTranslated(x, y, z);

	//Window Glass
	glPushMatrix();
	glScaled(0.05, 1.4 * 2, 1.65 * 2);
	drawCube(0.8, 0.9, 1);
	glPopMatrix();

	//Frames
	glPushMatrix();
	glTranslated(0.0, 0.0, 1.75);
	glScaled(0.2, 2.8, 0.2);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.0, 0.0, -1.75);
	glScaled(0.2, 2.8, 0.2);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.0, 0.0, 0);
	glScaled(0.2, 2.8, 0.2);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.0, 1.5, 0.0);
	glScaled(0.2, 0.2, 3.7);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.0, -1.5, 0.0);
	glScaled(0.2, 0.2, 3.7);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.0, 0, 0.0);
	glScaled(0.2, 0.2, 3.5);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();

	glPopMatrix();
}
void scene::drawSTable()
{
	//Top
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotated(180, 1, 0, 0);

	glPushMatrix();
	glTranslated(0, -1, -1.2);
	glScaled(1.9, 0.3, 2.2);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();

	//Legs
	glPushMatrix();
	glTranslated(-0.75, -1.5, -0.4);
	glScaled(0.3, 1, 0.3);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.75, -1.5, -0.4);
	glScaled(0.3, 1, 0.3);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.75, -1.5, -2);
	glScaled(0.3, 1, 0.3);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-0.75, -1.5, -2);
	glScaled(0.3, 1, 0.3);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
	
	glPopMatrix();

}
void scene::chairLeg(double t, double b, double l)
{
	//Draws A Chair Leg Based On The Passed Parameters
	glPushMatrix();
	glTranslated(0, l / 2, 0);
	glScaled(t, l, b);
	drawCube(0.6, 0.6, 0.6);
	glPopMatrix();
}

void scene::drawChair(double height)
{
	//Draws Chair At Given Position And Also On The Specified Leg Height
	glPushMatrix();
	glRotated(180, 1, 0, 0);
	//Chair Seat
	glPushMatrix();
	glTranslated(0, height, 0);
	glScaled(1.5, 0.075, 1.5);
	drawCube(0.7, 0.1, 0.1);
	glPopMatrix();

	//Chair Legs
	double thick = 0.075;
	double dist = 0.95* 1.5 / 2.0 - 0.1;

	glPushMatrix();
	glTranslated(dist, 0, dist);
	chairLeg(thick, thick, height);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1 * dist, 0, dist);
	chairLeg(thick, thick, height);
	glPopMatrix();

	glPushMatrix();
	glTranslated(dist, 0, -1 * dist);
	chairLeg(thick, thick, height);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1 * dist, 0, -1 * dist);
	chairLeg(thick, thick, height);
	glPopMatrix();

	//Support bars For The Chair
	double s_shift = -1 * (1.5 / 2 + thick / 2);
	double height_bar = height - 0.25;
	glPushMatrix();
	glTranslated(-1 * dist, height - thick / 2, s_shift);
	chairLeg(thick, thick, height_bar);
	glPopMatrix();

	glPushMatrix();
	glTranslated(dist, height - thick / 2, s_shift);
	chairLeg(thick, thick, height_bar);
	glPopMatrix();

	//Chair Back Support
	glPushMatrix();
	glTranslated(0, height + height * 2 / 3, -1 * (1.5 / 2 - thick / 2));
	glScaled(1.5, height / 2, thick);
	drawCube(0.7, 0.1, 0.1);
	glPopMatrix();

	glPopMatrix();
}
void scene::drawDoor()
{
	//Door Plane
	glPushMatrix();
	glTranslated(3.5, -1.55, 3);
	glScaled(2.8, 6.9, 0.05);
	drawCube(0.53725, 0.25098, 0.04313);
	glPopMatrix();

	//Door Frame
	glPushMatrix();
	glTranslated((5.0 - 0.05), -1.5, 3);
	glScaled(0.1, 7.0, 0.1);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();

	glPushMatrix();
	glTranslated((2.0 + 0.05), -1.5, 3);
	glScaled(0.1, 7.0, 0.1);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();

	glPushMatrix();
	glTranslated(3.5, 1.95, 3);
	glScaled(2.8, 0.1, 0.1);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();

	//Door Handle
	glPushMatrix();
	glTranslated(2.5, -1.5, 3); 
	glScaled(0.1, 0.5, 0.2);
	drawCube(0.92549, 0.68235, 0.39608);
	glPopMatrix();
}
void scene::drawLight(float x, float y, float z)
{
	//Draws Tubelight On Given Position
	glPushMatrix();
	glTranslated(x, y, z);
	glPushMatrix();
	glTranslated(0.0, 5.0 - 0.2 / 2 - 0.01, 3.0 - 0.2 / 2 - 0.01);
	//Side Fittings
	glPushMatrix();
	glTranslated(3.0 + 0.2 / 2, 0.0, 0.0);
	glScaled(0.2, 0.2, 0.2);
	drawCube(0.0, 0.0, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-3.0 - 0.2 / 2, 0.0, 0.0);
	glScaled(0.2, 0.2, 0.2);
	drawCube(0.0, 0.0, 0.0);
	glPopMatrix();

	//Tube
	glPushMatrix();
	glScaled(6.0, 0.15, 0.15);
	drawColoredCube(1.0, 1.0, 1.0);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}
void scene::drawScreen()
{
	//Screen
	glPushMatrix();
	glTranslated(0.0, -0.5, -12.5 + 0.05);
	glScaled(5.6, 2.6, 0.05);
	drawCube(0.6, 0.6, 0.6);
	glPopMatrix();

	//Frames
	glPushMatrix();
	glTranslated(0.0, 0.9, -12.5 + 0.05);
	glScaled(6.0, 0.2, 0.1);
	drawCube(0.3, 0.3, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -1.9, -12.5 + 0.05);
	glScaled(6.0, 0.2, 0.1);
	drawCube(0.3, 0.3, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.9, -0.5, -12.5 + 0.07);
	glScaled(0.2, 2.6, 0.1);
	drawCube(0.3, 0.3, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.9, -0.5, -12.5 + 0.07);
	glScaled(0.2, 2.6, 0.1);
	drawCube(0.3, 0.3, 0.3);
	glPopMatrix();

	glEnd();
}

void scene::DRAW_CLASSROOM()
{
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glScaled(4, 2, 4);
	drawWalls();
	glTranslated(-0.51, 0, 9.5); 
	glScaled(1.8, 1.6, 1);
	drawScreen();
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glTranslated(-51, 5.68, 28);
	glScaled(5.4,2.17,4);
	drawDoor();
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glScaled(1.5, 1.5,2);
	glTranslated(7, 4.63,-1);
	drawLTable(0,0,0);
	glPopMatrix();

	//Student Desks--Start
	glPushMatrix();
	glScaled(3, 4, 2);
	glTranslated(7, 0.5, 3);
	drawSTable();
	//Left-Front Reference Desk
	//Same Column Desks
	glPushMatrix();
	glTranslated(0, 0, 7);
	drawSTable();
	glTranslated(0, 0, 7);
	drawSTable();
	glPopMatrix();
	//2nd Column
	glPushMatrix();
	glTranslated(-5, 0, 0);
	drawSTable();
	glTranslated(0, 0, 7);
	drawSTable();
	glTranslated(0, 0, 7);
	drawSTable();
	glPopMatrix();
	//3rd Column
	glPushMatrix();
	glTranslated(-10, 0, 0);
	drawSTable();
	glTranslated(0, 0, 7);
	drawSTable();
	glTranslated(0, 0, 7);
	drawSTable();
	glPopMatrix();
	//4th Column
	glPushMatrix();
	glTranslated(-15, 0, 0);
	drawSTable();
	glTranslated(0, 0, 7);
	drawSTable();
	glTranslated(0, 0, 7);
	drawSTable();
	glPopMatrix();

	glPopMatrix(); //Student Desks--End

    //Student Chairs--Start
	glPushMatrix();
	glScaled(1.8, 1.6, 1.3);
	glTranslated(11.62, 6.2506, 10);
	drawChair(2);//Left-Front Reference Chair
    //Same Column Chairs
	glPushMatrix();
	glTranslated(0, 0, 11);
	drawChair(2);
	glTranslated(0, 0, 11);
	drawChair(2);
	glPopMatrix();
	//2nd Column
	glPushMatrix();
	glTranslated(-8.3, 0, 0);
	drawChair(2);
	glTranslated(0, 0, 11);
	drawChair(2);
	glTranslated(0, 0, 11);
	drawChair(2);
	glPopMatrix();
	//3rd Column
	glPushMatrix();
	glTranslated(-8.3*2, 0, 0);
	drawChair(2);
	glTranslated(0, 0, 11);
	drawChair(2);
	glTranslated(0, 0, 11);
	drawChair(2);
	glPopMatrix();
	//4th Column
	glPushMatrix();
	glTranslated(-8.3 * 3, 0, 0);
	drawChair(2);
	glTranslated(0, 0, 11);
	drawChair(2);
	glTranslated(0, 0, 11);
	drawChair(2);
	glPopMatrix();
	
    glPopMatrix();//Student Chairs--End
	
	//drawLight(0,0,0); where to put this shit?
	
	//Random Books on Teacher Table--START
	glPushMatrix();
	glTranslated(4, 4.118, -2);
	glScaled(0.8, 0.2, 1);
	drawColoredCube(0.23, 0.212, 0.352);
	glTranslated(0, 1, 0);
	drawColoredCube(0.18, 0.873, 0.651);
	glTranslated(0, 1, 0);
	drawColoredCube(0.732, 0.7612, 0.4121);
	glTranslated(0, 1, 0);
	drawColoredCube(0.832, 0.1612, 0.1121);
	glPopMatrix(); ////Random Books on Teacher Table--END

	//glPushMatrix();
	//drawWindow(0, 0, 0);
	//glPopMatrix();

}
