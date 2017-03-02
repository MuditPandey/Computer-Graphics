
#include <windows.h> // for MS Windows
#include<iostream>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "camera.h"
#include "point3.h"
#include "scene.h"
#include <Mmsystem.h>
#include <mciapi.h>

#define NO_PARTICLES 150
#define WINDOW_X 640.0
#define WINDOW_Y 480.0
#define STEP_DISTANCE 1
#define PARTICLE_RADIUS 0.1
#define delT 1 //in milliseconds

using namespace std;

/* Global variables */
bool TOGGLE = false;
char title[] = "3D Shapes";
point3 eye(0, 1.2, 15);
point3 look(0, 1.2, 0);
vec3 up(0, 1, 0);
float FOV = 45.0;
float ASP = WINDOW_X / WINDOW_Y;
float NEARD = 1.0;
float FARD = 100.0;
camera c(eye, look, up, true);
scene classroom;
float YAW = 0, PITCH = 0, ROLL = 0;
int rolled = 1;
int PREVX = WINDOW_X / 2, PREVY = WINDOW_Y / 2;
int XNEW = WINDOW_X / 2, YNEW = WINDOW_Y / 2;
float zoom = 0;
bool pause = true;
/*Function Prototypes*/

void initGL();
void mouse_move(int );
void handle_keyboard(unsigned char, int, int);
void handle_mouse(int, int);
void handle_click(int, int, int, int);
void display();
void reshape(GLsizei, GLsizei );
void sim(int);

/*!Main function: GLUT runs as a console application starting at main() */

int main(int argc, char** argv) {
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(WINDOW_X, WINDOW_Y);   // Set the window's initial width & height
	glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
	glutCreateWindow(title);          // Create window with the given title
	initGL();                       // Our own OpenGL initialization
	glutDisplayFunc(display); 
	glutKeyboardFunc(handle_keyboard);// Register callback handler for window re-paint event
	glutPassiveMotionFunc(handle_mouse);
	glutMouseFunc(handle_click);
	glutReshapeFunc(reshape);  // Register callback handler for window re-size event
	mouse_move(0);
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}

/*!Initializes window, matrix for openGL
*/
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);// Nice perspective corrections
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
									// Render a color-cube consisting of 6 quads with different colors
	c.setShape(FOV, ASP, NEARD ,FARD);
	glLoadIdentity();  // Reset the model-view matrix
	c.set();
	classroom.storeRandomPoints(NO_PARTICLES);
	sim(0);
	cout << "Initialising..\n";
	
}

void sim(int val)
{
	if (!pause)
		classroom.simulate();
	glutTimerFunc(delT, sim, 0);
}

/*!mouse_move is called every 10 milliseconds and updates the pitch and yaw depending on the mouse movements
	the mouse is then centered to the middle of the screen window
*/
void mouse_move(int val)
{
	PITCH -= rolled * (YNEW - (float)PREVY) / 10;
	YAW += rolled * (XNEW - (float)PREVX) / 10;
	c.rotate(PITCH, YAW, ROLL);
	PREVX = WINDOW_X / 2;
	PREVY = WINDOW_Y / 2;
	glutWarpPointer(WINDOW_X / 2, WINDOW_Y / 2);
	glutPostRedisplay();
	glutTimerFunc(10, mouse_move, 0);
}

/*!keyboard handler which handles what action takes place when a ceratin key is pressed
*/
void handle_keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':cout << "pressed W\n";
		c.slide(0, 0, -STEP_DISTANCE);
		break;
	case 'd':cout << "pressed D\n";
		c.slide(STEP_DISTANCE, 0, 0);
		break;
	case 'a':cout << "pressed A\n";
		c.slide(-STEP_DISTANCE, 0, 0);
		break;
	case 's':cout << "pressed S\n";
		c.slide(0, 0, STEP_DISTANCE);
		break;
	case 't':cout << "pressed T\nTurn Around\n";
		YAW += 180;
		c.rotate(PITCH, YAW, ROLL);
		break;
	case 'h':cout << "pressed H\n";
		c.slide(0, STEP_DISTANCE, 0, true);
		break;
	case 'j':cout << "pressed J\n";
		c.slide(0, -STEP_DISTANCE, 0, true);
		break;
	case 'f':cout << "pressed F\n";
		c.setsetting(true);
		break;
	case 'r':cout << "pressed R\nReset\n";
		YAW = 0;PITCH = 0;ROLL = 0;rolled = 1;FOV = 45;
		c.setShape(FOV, ASP, 1, 100);
		c.set(eye, look, up, false);
		break;
	case 'p': cout << "pressed P\n";
		ROLL += 3;
		c.rotate(PITCH, YAW, ROLL);
		break;
	case 'o': cout << "pressed O\n";
		ROLL -= 3;
		c.rotate(PITCH, YAW, ROLL);
		break;
	case 27:
		exit(0);
		break;
	case 32:
		pause = !pause;
	}
	glutPostRedisplay();
}

/*!saves the mouse location whenever the mouse moves
*/
void handle_mouse(int x, int y)
{
	XNEW = x;
	YNEW = y;
}
//!Handles what happens in an event of mouse click
void handle_click(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		//zoom in
		FOV = FOV - 5;
		cout << "Zoom In\n";
	}
	else if (button = GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//zoom out
		FOV = FOV + 5;
		cout << "Zoom In\n";
	}
}
/*!display function which displays the scene and runs in a loop
*/
void display() {
	c.setShape(FOV, ASP, NEARD, FARD);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

	glLineWidth(2.5);
	
	//SPHERE PART
	double clipEq[1][4] = { 0,-1,0,5 };
	glEnable(GL_CLIP_PLANE0);
	glPushMatrix();
	glClipPlane(GL_CLIP_PLANE0, clipEq[0]);
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(1, 5, 1);
	glutSolidSphere(2.0f, 20, 20);
	glPopMatrix();
	glDisable(GL_CLIP_PLANE0);
	//SPHERE PART END

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(-1, 5.5, -1);
	glVertex3f(-1, 5.5, 3);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-1, 5.5, 3);
	glVertex3f(3, 5.5, 3);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(3, 5.5, 3);
	glVertex3f(3, 5.5, -1);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(3, 5.5, -1);
	glVertex3f(-1, 5.5, -1);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-1, 5.5, -1);
	glVertex3f(-1, -5, -1);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-1, 5.5, 3);
	glVertex3f(-1, -5, 3);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(3, 5.5, 3);
	glVertex3f(3, -5, 3);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(3, 5.5, -1);
	glVertex3f(3, -5, -1);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);

	classroom.makeScene();
	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

/*!Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
											   // Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
								  // Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

