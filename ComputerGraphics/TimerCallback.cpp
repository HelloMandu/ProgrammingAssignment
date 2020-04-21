#include <glut.h>
GLfloat Delta = 0.0;
GLfloat Delta2 = 0.0;
GLboolean dir = true;
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	//glBegin(GL_POLYGON);
	//glColor3f(0.0, 0.5, 0.8);
	//glVertex3f(-1.0 + Delta, -0.5, 0.0);
	//glVertex3f(0.0 + Delta, -0.5, 0.0);
	//glVertex3f(0.0 + Delta, 0.5, 0.0);
	//glVertex3f(-1.0 + Delta, 0.5, 0.0);
	//glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(10);
	glBegin(GL_POLYGON);
	glVertex3f(0.4, 0.1 + Delta, 0.0);
	glVertex3f(0.8, -0.1 + Delta, 0.0);
	glVertex3f(0.6, 0.3 + Delta, 0.0);
	glVertex3f(0.4, 0.1 + Delta, 0.0);
	glVertex3f(1.0, 0.6 + Delta, 0.0);
	glVertex3f(0.6, 0.6 + Delta, 0.0);
	glVertex3f(0.4, 0.1 + Delta, 0.0);
	glVertex3f(0.6, 0.6 + Delta, 0.0);
	glVertex3f(0.4, 1.0 + Delta, 0.0);
	glVertex3f(0.4, 0.1 + Delta, 0.0);
	glVertex3f(0.4, 1.0 + Delta, 0.0);
	glVertex3f(0.2, 0.6 + Delta, 0.0);
	glVertex3f(0.4, 0.1 + Delta, 0.0);
	glVertex3f(0.2, 0.6 + Delta, 0.0);
	glVertex3f(-0.2, 0.6 + Delta, 0.0);
	glVertex3f(0.4, 0.1 + Delta, 0.0);
	glVertex3f(0.2, 0.3 + Delta, 0.0);
	glVertex3f(0.0, -0.1 + Delta, 0.0);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.6, -0.6 + Delta2, 0.0);
	glVertex3f(-0.4, -0.7 + Delta2, 0.0);
	glVertex3f(-0.5, -0.5 + Delta2, 0.0);
	glVertex3f(-0.6, -0.6 + Delta2, 0.0);
	glVertex3f(-0.3, -0.4 + Delta2, 0.0);
	glVertex3f(-0.5, -0.4 + Delta2, 0.0);
	glVertex3f(-0.6, -0.6 + Delta2, 0.0);
	glVertex3f(-0.5, -0.4 + Delta2, 0.0);
	glVertex3f(-0.6, -0.2 + Delta2, 0.0);
	glVertex3f(-0.6, -0.6 + Delta2, 0.0);
	glVertex3f(-0.6, -0.2 + Delta2, 0.0);
	glVertex3f(-0.7, -0.4 + Delta2, 0.0);
	glVertex3f(-0.6, -0.6 + Delta2, 0.0);
	glVertex3f(-0.7, -0.4 + Delta2, 0.0);
	glVertex3f(-0.6, -0.6 + Delta2, 0.0);
	glVertex3f(-0.6, -0.6 + Delta2, 0.0);
	glVertex3f(-0.7, -0.4 + Delta2, 0.0);
	glVertex3f(-0.9, -0.4 + Delta2, 0.0);
	glVertex3f(-0.6, -0.6 + Delta2, 0.0);
	glVertex3f(-0.7, -0.5 + Delta2, 0.0);
	glVertex3f(-0.8, -0.7 + Delta2, 0.0);
	glEnd();
	glFlush();
	glutSwapBuffers();
}
void MyTimer(int Value) {
	if (dir) {
		Delta = Delta + 0.001;
		Delta2 = Delta2 - 0.001;
		if (Delta > 1.2) {
			dir = !dir;
		}
	}
	else {
		Delta = Delta - 0.001;
		Delta2 = Delta2 + 0.001;
		if (Delta < -2.1) {
			dir = !dir;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(1, MyTimer, 1);
}
void MyInit() {
	glClearColor(1.0, 0.43, 0.78, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Timer Callback");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(20, MyTimer, 1);
	glutMainLoop();
	return 0;
}
