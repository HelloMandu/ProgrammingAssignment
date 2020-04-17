#include <glut.h>
#include<stdio.h>
#include<math.h>
#define Pi 3.1415

GLfloat glSpringX, glSpringY;
int gCount = 0;

void flower(GLfloat x, GLfloat y) {
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle) + x, 0.035*sin(Angle) + y + 0.035, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle) + x - 0.03, 0.03*sin(Angle) + y - 0.035, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle) + x + 0.03, 0.03*sin(Angle) + y - 0.035, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle) + x + 0.04, 0.03*sin(Angle) + y + 0.02, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle) + x - 0.04, 0.03*sin(Angle) + y + 0.02, 0.0);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.04*cos(Angle) + x, 0.04*sin(Angle) + y, 0.0);
	glEnd();
}

void butterfly(GLfloat x, GLfloat y) {
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.1 + x, 0.05 + y, 0.0);
	glVertex3f(-0.05 + x, -0.1 + y, 0.0);
	glVertex3f(0.0 + x, 0.0 + y, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.0 + x, 0.0 + y, 0.0);
	glVertex3f(0.1 + x, 0.05 + y, 0.0);
	glVertex3f(0.05 + x, -0.1 + y, 0.0);
	glEnd();
}

void plant(GLfloat x, GLfloat y) {
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.1 + x, 0.1 + y, 0.0);
	glVertex3f(-0.05 + x, 0.0 + y, 0.0);
	glVertex3f(0.0 + x, 0.0 + y, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.0 + x, 0.0 + y, 0.0);
	glVertex3f(0.05 + x, 0.0 + y, 0.0);
	glVertex3f(0.1 + x, 0.1 + y, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.0 + x, 0.1 + y, 0.0);
	glVertex3f(-0.05 + x, 0.0 + y, 0.0);
	glVertex3f(0.05 + x, 0.0 + y, 0.0);
	glEnd();
}

void MyDisplay() {
	printf("%f %f\n", glSpringX, glSpringY);
	if (gCount == 0) {
		glClear(GL_COLOR_BUFFER_BIT);
	}
	else {
		plant(glSpringX, glSpringY + 0.1);
		butterfly(glSpringX - 0.1, glSpringY - 0.1);
		flower(glSpringX + 0.1, glSpringY - 0.1);
	}
	glFlush();
}
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) { // ÁÂÅ¬¸¯ÇÏ¸é ³×¸ð ½ÃÀÛÁ¡ µÊ
		glSpringX = 2 * (X / 500.0) - 1;
		glSpringY = 2 * ((500 - Y) / 500.0) - 1;
		gCount++;
		printf("%f %f\n", glSpringX, glSpringY);
	}
	glutPostRedisplay();
}
void MyInit() {
	glClearColor(1.0, 0.43, 0.78, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Å¬¸¯ÇÏ¸é º½");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutMouseFunc(MyMouseClick);
	glutMainLoop();
	return 0;
}
