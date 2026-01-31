////////////////////////////////////////////////////          
// sineCosineWave.cpp
// (modifying experimentLines.cpp)
// 
// Sumanta Guha.
// 
// Joseph Thallas and his Summary:
// 
// This program creates a 500x500 OpenGL window that contains a sine or cosine wave.
// It handles user input to modify the waves characteristics.
// And since I'm a JUMPer, the arrow keys adjust the sampling position of the wave.
// 
// Key Functions:
// 
// * MakeWave(): Computes and draws the sine or cosine wave based on the current number of points and wave type.
//               Uses global variables to determine the number of points and type of wave.
// * drawScene(): Initial rendering of the scene, and draws the y=0 line (though it's really y=50).
// * keyInput(): Handles keyboard input to increase/decrease the number of wave points or toggle wave types.
//               It does this by changing the global variables.
////////////////////////////////////////////////////

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>

// Global variables
int wavePointCount = 5;
float sampleOffset = 0;
bool isSine = true;
double pi = 2 * acos(0.0);   // https://www.geeksforgeeks.org/cpp/pi-in-c-with-examples/

// Function to draw a sine wave
void makeWave()
{
	// Set increments
	float hor = 100.0f / (float)(wavePointCount - 1);
	float rad = (2.0f * pi) / (float)(wavePointCount - 1);

	// Set colors
	// Red is sine, blue is cosine
	float r = 1.0 ? isSine : 0.0;
	float g = 0.0;
	float b = 1.0 ? !isSine : 0.0;
	glColor3f(r, g, b);

	// Create wave
	glLineWidth(1.0);		// default
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < wavePointCount; i++)
	{
		float x = i * hor;
		float y = 0.0f;
		float offsetRad = (pi * sampleOffset) / 8.0f;
		if (isSine) {
			y = (sin((i * rad) + offsetRad) * 50) + 50;
		}
		else {
			y = (cos((i * rad) + offsetRad) * 50) + 50;
		}

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
	makeWave();

	glFlush();
}

// Handle arrow input to adjust sample offset
void arrowInput(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		sampleOffset++;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		sampleOffset--;
		glutPostRedisplay();
		break;
	default:
		break;
	}
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
	case '=':
		wavePointCount++;
		glutPostRedisplay();
		break;
	case '-' :
		if (wavePointCount > 2) {
			wavePointCount--;
			glutPostRedisplay();
		}
		break;
	case ' ':
		isSine = !isSine;   // Toggle between sine and cosine
		glutPostRedisplay();
	default:
		break;
	}
}

// Main routine
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
	glutSpecialFunc(arrowInput);

	glewExperimental = GL_TRUE;
	glewInit();	

	setup();

	glutMainLoop();
}
