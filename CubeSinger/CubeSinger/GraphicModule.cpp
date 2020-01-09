#include "pch.h"
#include "GraphicModule.h"

using namespace std;

GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light_diff[] = { 1, 1, 1, 1 };
GLfloat light_pos[] = { -1, 1, 1, 0 };

GLfloat anglex, angley, anglez;
GLfloat viewx, viewy, viewz;
GLfloat angle = .1;
GLfloat tmp = 0;
GLfloat rtmp = 0;//part rotate
GLfloat stmp = 0;//always rotate

GLfloat yellow[4] = { 1,1,0,1 };
GLfloat red[4] = { 1,0,0,1 };

GLboolean rotateX, rotateY, rotateZ;
GLboolean AutoRotate;

void generateBlock(GLfloat x, GLfloat y, GLfloat z, GLfloat *color)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glutSolidCube(.6);
	glPopMatrix();
}

void showNotes(GLfloat x, GLfloat y, GLfloat z, char *text)
{
	char *p;
	glPushMatrix();
	//glTranslatef(x, y, 0);
	
	glRasterPos3f(x, y, z);
	for (p = text; *p; p ++)
	{
		//glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
	}
	glPopMatrix();
}

void drawBox()
{
	if (anglex)
	{
		glRotatef(angle, 1, 0, 0);
	}
	if (angley)
	{
		glRotatef(angle, 0, 1, 0);
	}
	if (anglez)
	{
		glRotatef(angle, 0, 0, 1);
	}
	
	glPushMatrix();
		if (AutoRotate)
		{
			glRotatef(stmp, 1, 0, 0);
		}
		glPushMatrix();
			if (AutoRotate)
			{
				glTranslatef(.5, .5, 0);
				glRotatef(stmp, 0, 0, 1);
				glTranslatef(-.5, -.5, 0);
			}
			generateBlock(.5, .5, .5, red);

			glPushMatrix();
				if (AutoRotate)
				{
					glTranslatef(.5, .5, -.5);
					glRotatef(stmp, 0, 1, 1);
					glTranslatef(-.5, -.5, .5);
				}
				generateBlock(.5, .5, -.5, yellow);
			glPopMatrix();
		glPopMatrix();

		generateBlock(.5, -.5, -.5, red);
		generateBlock(.5, -.5, .5, yellow);
	glPopMatrix();
	//four cubes
	glPushMatrix();
		showNotes(1, -1, 1, (char*)"press Q/W/E");
		glRotatef(rtmp, 1, 0, 0);
		generateBlock(-.5, .5, .5, red);
		generateBlock(-.5, .5, -.5, yellow);
		generateBlock(-.5, -.5, -.5, red);
		generateBlock(-.5, -.5, .5, yellow);
	glPopMatrix();

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawBox();
	showNotes(1, 2, 0, (char*)"click here!");
	glutSwapBuffers();
}

void keyboardRespon(unsigned char key, int x, int y)
{
	if (key == 'q' && !tmp && !angley && !anglez)
	{
		//anglex = 900;
		tmp = 90;
	}

	if (key == 'w' && !angley && !anglex && !anglez)
		angley = 900;
	if (key == 'e' && !anglez && !anglex && !angley)
		anglez = 900;
	if (key == 'r')
	{
		viewx = viewy = 0;
	}
}

void mouseRespon(int mouse, int state, int x, int y)
{
	if (mouse == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		AutoRotate = !AutoRotate;
	}
	if (mouse == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		viewx = x / 50;
		viewy = y / 50;
	}
	
}

void idle()
{
	if (anglex)
	{
		anglex--;
		//tmp = 90;
	}
	if (angley)
	{
		angley--;
	}
	if (anglez)
	{
		anglez--;
	}
	tmp = tmp > 0 ? tmp - 0.05 : 0;
	rtmp += tmp > 0 ? 0.05 : 0;
	stmp += 0.05;
	glutPostRedisplay();
}

void reshape(int x, int y)
{
	if (y == 0 || x == 0) return;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);
}
void initParameter(void)
{
	viewx = viewy = viewz = 0;
	rotateY = rotateZ = rotateX = false;
	AutoRotate = false;

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diff);
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 1.0, 1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(3, 3, 5,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.);
}

int AlphaThread(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("red 3D lighted cube");
	glutKeyboardFunc(keyboardRespon);
	glutMouseFunc(mouseRespon);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	initParameter();
	glutMainLoop();
	return 0;
}
