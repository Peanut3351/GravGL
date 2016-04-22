#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <iostream>

#define M_PI 3.14159265358979323846264338327950288
#define G    0.002 //Gravitational Constant

struct Particle {
	float x;
	float y;
	float vx;
	float vy;
	float rad;
	float mass;
	float color[3];
};

struct Line {
	float x1;
	float y1;
	float x2;
	float y2;
};

void Timer(int = 0);
void Display();
void Mouse(int, int, int, int);
void MouseMotion(int, int);
void AddParticle(float, float, bool = true, float = 0, float = 0);
void RemoveParticles();
void Keyboard(unsigned char, int, int);
void Resize(int width, int height);
void Evolve();

int mX, mY;
int gWin;
bool mLeft = false;
bool mRight = false;
bool mMiddle = false;
bool pause = false;
bool step = false;

std::vector<Particle> pVec;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(50, 50);
	gWin = glutCreateWindow("GravGL");

	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250.0, 250.0, 250.0, -250.0, 0, 1);

	glutDisplayFunc(Display);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Resize);
	Timer();

	glutMainLoop();
}

void Timer(int)
{
	Display();

	if (mLeft)
	{
		AddParticle(1000, 10, true, 1, -1.f);
		mLeft = false;
	}

	if (mRight)
	{
		AddParticle(1000, 10, true, -1, 1.f);
		mRight = false;
	}

	if (mMiddle)
		RemoveParticles();

	if (!pause)
	{
		Evolve();
	}
	else
	{
		if (step)
		{
			for (int k = 0; k <= 30; k++)
			{
				Evolve();
			}
			step = false;
		}
	}

	glutTimerFunc(1, Timer, 0);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//Draw each particle in the vector
	for (size_t i = 0; i < pVec.size(); i++)
	{
		Particle &p = pVec[i];
		glColor3f(p.color[0], p.color[1], p.color[2]);
		glBegin(GL_POLYGON);
		for (float a = 0; a < 2 * M_PI; a += 0.2)
			glVertex2f(p.rad * cos(a) + p.x, p.rad * sin(a) + p.y);
		glEnd();
	}

	glFlush();
	glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y)
{
	mX = x - 250;
	mY = y - 250;

	if (button == GLUT_LEFT_BUTTON) mLeft = state == GLUT_DOWN;
	else if (button == GLUT_RIGHT_BUTTON) mRight = state == GLUT_DOWN;
	else if (button == GLUT_MIDDLE_BUTTON) mMiddle = state == GLUT_DOWN;
}

void MouseMotion(int x, int y)
{
	mX = x - 250;
	mY = y - 250;
}

void AddParticle(float m, float r, bool randColor, float vx, float vy)
{
	Particle p;
	p.x = mX;
	p.y = mY;
	p.vx = vx / 30;
	p.vy = vy / 30;
	p.mass = m;
	p.rad = r;
	if (randColor)
	{
		p.color[0] = rand() % 255 / 255.f;
		p.color[1] = rand() % 255 / 255.f;
		p.color[2] = rand() % 255 / 255.f;
	}
	else
	{
		p.color[0] = 1;
		p.color[1] = 1;
		p.color[2] = 0;
	}
	pVec.push_back(p);
}

void RemoveParticles()
{
	for (size_t i = 0; i < pVec.size(); i++)
		pVec.pop_back();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 0x1B:
		// Escape
		RemoveParticles();
		glutDestroyWindow(gWin);
		exit(0);
		break;
	case 'p':
		pause = !pause;
		break;
	case 'o':
		step = true;
		break;
	}
}

void Resize(int width, int height)
{
	glutReshapeWindow(500, 500);
}

void Evolve()
{
	for (size_t i = 0; i < pVec.size(); i++)
	{
		Particle &p = pVec[i];
		bool collide = false;

		for (size_t j = 0; j < pVec.size(); j++)
		{
			if (j == i || p.mass >= 1000000)
				continue;

			const Particle &p1 = pVec[j];

			float d = sqrt((p1.x - p.x)*(p1.x - p.x) + (p1.y - p.y)*(p1.y - p.y));

			if (d > p1.rad)
			{
				// Acceleration = Force / Mass
				p.vx += G * p1.mass / (d*d) * (p1.x - p.x) / d;
				p.vy += G * p1.mass / (d*d) * (p1.y - p.y) / d;
			}
			else
				collide = true;
		}

		if (collide)
			pVec.erase(pVec.begin() + i);
		else
		{
			p.x += p.vx;
			p.y += p.vy;
		}
	}
}