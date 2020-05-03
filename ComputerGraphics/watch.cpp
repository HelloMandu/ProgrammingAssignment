#include <glut.h>

GLint gSecondHand = 0.0;
GLint gMinuteHand = 0.0;

void rotate(GLfloat x, GLfloat y, GLfloat theta) {
	glTranslatef(x, y, 0);
	glRotatef(theta, 0, 0, 1);
	glTranslatef(-x, -y, 0);
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0.6, 0.4, 0.12);

	glPushMatrix();
	glTranslatef(3, 2, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.8, 20, 20);
	glColor3f(0.60, 0.40, 0.70);
	glutSolidTorus(0.05, 0.75, 20, 20);
	glPopMatrix();

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
		glVertex3f(3, 2 + 0.05, 0);
		glVertex3f(3 - 0.05, 2 - 0.05, 0);
		glVertex3f(3 + 0.05, 2 - 0.05, 0);
	glEnd();

	glLineWidth(4);
	glColor3f(0, 0, 1);
	glPushMatrix();
	rotate(3, 2, gSecondHand);
	glBegin(GL_LINES);
		glVertex3f(3, 2, 0);
		glVertex3f(3, 2.4, 0);
	glEnd();
	glPopMatrix();

	glLineWidth(1);
	glColor3f(0, 0, 0);
	glPushMatrix();
	rotate(3, 2, gMinuteHand);
	glBegin(GL_LINES);
		glVertex3f(3, 2, 0);
		glVertex3f(3, 2.7, 0);
	glEnd();
	glPopMatrix();

	//2
	glPushMatrix();
	glTranslatef(-2, 0, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(2.1, 20, 20);
	glColor3f(0.7, 0.45, 0.22);
	glutSolidTorus(0.1, 2, 20, 20);
	glPopMatrix();

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-2, 0 + 0.05, 0);
	glVertex3f(-2 - 0.05, 0 - 0.05, 0);
	glVertex3f(-2 + 0.05, 0 - 0.05, 0);
	glEnd();

	glLineWidth(4);
	glColor3f(0, 1, 0);
	glPushMatrix();
	rotate(-2, 0, gSecondHand);
	glBegin(GL_LINES);
	glVertex3f(-2, 0, 0);
	glVertex3f(-2, 1.4, 0);
	glEnd();
	glPopMatrix();

	glLineWidth(1);
	glColor3f(0, 0, 0);
	glPushMatrix();
	rotate(-2, 0, gMinuteHand);
	glBegin(GL_LINES);
	glVertex3f(-2, 0, 0);
	glVertex3f(-2, 2, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, -1.6, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(1.1, 20, 20);
	glColor3f(0.98, 0.04, 0.7);
	glutSolidTorus(0.075, 1.025, 20, 20);
	glPopMatrix();

	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(2, -1.6 + 0.05, 0);
	glVertex3f(2 - 0.05, -1.6 - 0.05, 0);
	glVertex3f(2 + 0.05, -1.6 - 0.05, 0);
	glEnd();

	glLineWidth(4);
	glColor3f(1, 0, 0);
	glPushMatrix();
	rotate(2, -1.6, gSecondHand);
	glBegin(GL_LINES);
	glVertex3f(2, -0.9, 0);
	glVertex3f(2, -1.6, 0);
	glEnd();
	glPopMatrix();

	glLineWidth(1);
	glColor3f(0, 0, 0);
	glPushMatrix();
	rotate(2, -1.6, gMinuteHand);
	glBegin(GL_LINES);
	glVertex3f(2, -0.6, 0);
	glVertex3f(2, -1.6, 0);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}
void MyTimer(int Value) {
	gSecondHand -= 1;
	if (gSecondHand % 60 == 0) { gMinuteHand -= 1; }
	glutPostRedisplay();
	glutTimerFunc(20, MyTimer, 1);
}
void MyInit() {
	glClearColor(0.8, 0.8, 0.8, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.0, 4.0, -3.0, 3.0, -4.0, 4.0);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("½Ã°è");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(20, MyTimer, 1); 
	glutMainLoop();
	return 0;
}
