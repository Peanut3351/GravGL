#include <GL/glut.h>
#include <vector>
#include <cmath>

#define M_PI 3.14159265358979323846264338327950288

struct Point
{
	int x;
	int y;
};

struct Line
{
	float x1;
	float y1;
	float x2;
	float y2;
};

struct Particle
{
	Point pos = { 0, 0 };
	Point vel = { 0, 0 };
	int rad;
	int mass;
	float color[3] = { 1, 1, 1 };
};

void Timer(int = 0);
void Display();
void Mouse(int, int, int, int);
void MouseMotion(int, int);
void AddParticle(float, float, bool = true, float = 0, float = 0);
void RemoveParticles();
void Keyboard(unsigned char, int, int);

int mX, mY;
int gWin;
bool mLeft = false;
bool mRight = false;
bool mMiddle = false;
bool mDrag = false;

std::vector<Particle> pVec;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	gWin = glutCreateWindow("GravGL");

	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250.0, 250.0, 250.0, -250.0, 0, 1);

	glutDisplayFunc(Display);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutKeyboardFunc(Keyboard);
	Timer();

	glutMainLoop();
	return 0;
}

void Timer(int)
{
	Display();
	glutTimerFunc(1, Timer, 0);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
	glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y)
{

}

void MouseMotion(int x, int y)
{

}

void AddParticle(float m, float r, bool randColor, float vx, float vy)
{

}

void RemoveParticles()
{

}

void Keyboard(unsigned char key, int x, int y)
{

}