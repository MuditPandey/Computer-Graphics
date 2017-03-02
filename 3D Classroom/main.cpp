
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
#pragma comment(lib, "Winmm.lib")

#define JUMP_HEIGHT 5
#define WINDOW_X 1366.0
#define WINDOW_Y 768.0
#define STEP_DISTANCE 1
#define EYE_LEVEL_STAND 1.24622
#define EYE_LEVEL_SIT 3.25038

using namespace std;

/* Global variables */
bool TOGGLE = false;
char title[] = "3D Shapes";
point3 eye(0, EYE_LEVEL_STAND, 15);
point3 look(0, EYE_LEVEL_STAND, 0);
vec3 up(0, 1, 0);
float FOV = 45.0;
float ASP = WINDOW_X / WINDOW_Y;
float NEARD = 1.0;
float FARD = 100.0;
camera c(eye, look, up,false);
scene classroom;
float YAW = 0, PITCH = 0, ROLL = 0;
int rolled = 1;
int PREVX = WINDOW_X / 2, PREVY = WINDOW_Y / 2;
int XNEW = WINDOW_X / 2, YNEW = WINDOW_Y / 2;
float zoom = 0;
/*Function Prototypes*/

wchar_t *convertCharArrayToLPCWSTR(const char* charArray);
void initGL();
void mouse_move(int );
void shutter(int);
void jumper(int);
void roller(int);
void handle_keyboard(unsigned char, int, int);
void handle_mouse(int, int);
void handle_click(int, int, int, int);
void display();
void reshape(GLsizei, GLsizei );

/* !Main function: GLUT runs as a console application starting at main() */

int main(int argc, char** argv) {
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(WINDOW_X, WINDOW_Y);   // Set the window's initial width & height
	glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
	glutCreateWindow(title);          // Create window with the given title
	initGL();                       // Our own OpenGL initialization
	//PlaySound(convertCharArrayToLPCWSTR("footstep.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	glutDisplayFunc(display); 
	glutKeyboardFunc(handle_keyboard);// Register callback handler for window re-paint event
	glutPassiveMotionFunc(handle_mouse);
	glutMouseFunc(handle_click);
	glutReshapeFunc(reshape);  // Register callback handler for window re-size event
	mouse_move(0);
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}

/* !Converts a charachter array to LPCWSTR (for music)
*/
wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

/* !Initializes window, matrix for openGL
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
	cout << "Initialising..\n";
}

/* !mouse_move is called every 10 milliseconds and updates the pitch and yaw depending on the mouse movements
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

/* !shutter is called for small camera rolls when hitting the floor in dropping or jumping
*/
void shutter(int val)
{
	if (val == 100)
	{
		val = 2;
		if (rolled == 1) ROLL = 0;
		else ROLL = 180;
	}
	if (val > 0) ++ROLL;
	else if (val < 0) --ROLL;
	if (val == ROLL || val == ROLL - 180)
	{
		if (val > 0) val = -(val - 1);
		else if (val < 0) val = -(val + 1);
	}
	c.rotate(PITCH, YAW, ROLL);
	if (val == -1 && ROLL == 0) return;
	glutTimerFunc(10, shutter, val);
}

/* !jumper is called for "jumping"
	The function is split in two cases (normal and anti-gravity)
	If an interaction is detected with the tables/chairs, then the camera y doesn't change until no interaction with the chairs/tables
*/
void jumper(int value)
{
	//CALCULATE JUMPER VARIABLES
	float expr;
	if (rolled == 1)
	{
		if (value >= 0)
			expr = 0.7 - .03 *(2 * value - 1);
		else
			expr = 0.03 * (2 * value + 1);
		if (c.eyeComponent(2) <= EYE_LEVEL_STAND)
		{
			if (c.slide(0, -expr, 0, false) == false)
			{
				if (value >= 0) ++value;
				else --value;
			}
			else
				value = -1;
		}
		else
		{
			c.changeComponent(2, EYE_LEVEL_STAND);
			shutter(100);
			return;
		}
	}
	else
	{
		expr = 0.49 - .01 *(2 * value - 1);
		c.slide(0, expr, 0, false);
		if (c.eyeComponent(2) >= -7.55378)
			++value;
		else
		{
			c.changeComponent(2, -7.55378);
			shutter(100);
			return;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(10, jumper, value);
}

/* !the anti-gravity function
	rolls the camera 180 degrees and moves the camera closer to the ceiling or floor
	toggles the gravity from floor to ceiling
*/
void roller(int value)
{
	ROLL -= 2;
	c.slide(0, 0.1 * rolled, 0, false);
	c.rotate(PITCH, YAW, ROLL);
	glutPostRedisplay();
	if (value < 89)
		glutTimerFunc(10, roller, ++value);
	else
	{
		if (rolled == 1)
		{
			if (c.eyeComponent(2) > EYE_LEVEL_STAND)
				c.changeComponent(2, EYE_LEVEL_STAND);
			else jumper(-1);
		}
	}
}

/* !keyboard handler which handles what action takes place when a ceratin key is pressed
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
	case 32:cout << "pressed J\nJump\n";
		if (abs(c.eyeComponent(2) - EYE_LEVEL_STAND) < 0.0001 || rolled == -1) jumper(0);
		break;
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
	case 'e':cout << "pressed E\n";
		if (c.eyeComponent(2) < EYE_LEVEL_STAND - 0.01) break;
		TOGGLE = !TOGGLE;
		if (c.interact(EYE_LEVEL_SIT, TOGGLE))
		{
			YAW = 0;PITCH = 0;
			c.rotate(PITCH, YAW, ROLL);
		}
		break;
	case 'n': cout << "pressed P\n";
		if (abs(c.eyeComponent(2) - EYE_LEVEL_STAND) > 0.0001 && rolled != -1) break;
		roller(0);
		if (rolled == 1) rolled = -1;
		else rolled = 1;
		//cout << "rolled is " << rolled << endl;
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
	}
	glutPostRedisplay();
}

/* !saves the mouse location whenever the mouse moves
*/
void handle_mouse(int x, int y)
{
	XNEW = x;
	YNEW = y;
}
// !Handles what happens in an event of mouse click
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
/* !display function which displays the scene and runs in a loop
*/
void display() {
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, WINDOW_X / WINDOW_Y, 1.0, 100.0);*/
	c.setShape(FOV, ASP, NEARD, FARD);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	//glLoadIdentity();  // Reset the model-view matrix
	//gluLookAt(10, 1, 22, 0, 0, -10, 0, 1, 0);	
	//camera c;
	//makecube();
	classroom.DRAW_CLASSROOM();
	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

/* !Handler for window re-size event. Called back when the window first appears and
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