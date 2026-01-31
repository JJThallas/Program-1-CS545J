////////////////////////////////////////////////////          
// sineCosineWave.cpp
// (modifying experimentLines.cpp)
// 
// Sumanta Guha.
// Joseph Thallas.
////////////////////////////////////////////////////

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>

// I love C++
using namespace std;

// Global variables
int wavePointCount = 5;
double pi = 2 * acos(0.0);   // https://www.geeksforgeeks.org/cpp/pi-in-c-with-examples/

// Function to draw a sine wave
void makeWave(bool isSine)
{
	// Set increments
	float hor = 100.0f / (float)(wavePointCount - 1);
	float rad = (2.0f * pi) / (float)(wavePointCount - 1);

	// Create sine wave
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(1.0);		// default
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < wavePointCount; i++)
	{
		float x = i * hor;
		float y = 0.0f;

		if (isSine) {
			y = (sin(i * rad) * 50) + 50;
		}
		else {
			y = (cos(i * rad) * 50) + 50;
		}

		glBegin(GL_POINTS);
		glVertex3f(x, y, 0.0f);
	}
		glEnd();
	}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Create Y=0 line
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1.8);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 50.0f, 0.0f);
	glVertex3f(100.0f, 50.0f, 0.0f);
	glEnd();

	// Draw sine wave
	makeWave(true);

	glFlush();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// Function to compute sine wave value at x
// TODO: Make it actually work
float sinWave(float x)
{
	float pi = 3.14159;
	return 1.0f;
}

// Main routine
/*
* PROJECT REQUIREMENTS:
* 1. Window is 500 by 500
* 2. Bounding box is from (0.0, 0.0, -1.0) to (100.0, 100.0, 1.0)
* 3. Must use ortho projection (obv)
* 4. On init, render a sine wave with 5 points
* 5. Points must reach top and bottom of window but not exceed it
* 6. Wave is rendered using the GL_LINES or GL_LINE_STRIP primitive and calls to glVertex3f
*/
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("sineCosineWave.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}