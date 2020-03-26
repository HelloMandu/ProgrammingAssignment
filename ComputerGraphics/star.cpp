#include <glut.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(10);
	glBegin(GL_POLYGON);
		glVertex3f(0.4, 0.1, 0.0);
		glVertex3f(0.8, -0.1, 0.0);
		glVertex3f(0.6, 0.3, 0.0);
		glVertex3f(0.4, 0.1, 0.0);
		glVertex3f(1.0, 0.6, 0.0);
		glVertex3f(0.6, 0.6, 0.0);
		glVertex3f(0.4, 0.1, 0.0);
		glVertex3f(0.6, 0.6, 0.0);
		glVertex3f(0.4, 1.0, 0.0);
		glVertex3f(0.4, 0.1, 0.0);
		glVertex3f(0.4, 1.0, 0.0);
		glVertex3f(0.2, 0.6, 0.0);
		glVertex3f(0.4, 0.1, 0.0);
		glVertex3f(0.2, 0.6, 0.0);
		glVertex3f(-0.2, 0.6, 0.0);
		glVertex3f(0.4, 0.1, 0.0);
		glVertex3f(0.2, 0.3, 0.0);
		glVertex3f(0.0, -0.1, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-0.6, -0.6, 0.0);
		glVertex3f(-0.4, -0.7, 0.0);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(-0.6, -0.6, 0.0);
		glVertex3f(-0.3, -0.4, 0.0);
		glVertex3f(-0.5, -0.4, 0.0);
		glVertex3f(-0.6, -0.6, 0.0);
		glVertex3f(-0.5, -0.4, 0.0);
		glVertex3f(-0.6, -0.2, 0.0);
		glVertex3f(-0.6, -0.6, 0.0);
		glVertex3f(-0.6, -0.2, 0.0);
		glVertex3f(-0.7, -0.4, 0.0);
		glVertex3f(-0.6, -0.6, 0.0);
		glVertex3f(-0.7, -0.4, 0.0);
		glVertex3f(-0.6, -0.6, 0.0);
		glVertex3f(-0.6, -0.6, 0.0);
		glVertex3f(-0.7, -0.4, 0.0);
		glVertex3f(-0.9, -0.4, 0.0);
		glVertex3f(-0.6, -0.6, 0.0);
		glVertex3f(-0.7, -0.5, 0.0);
		glVertex3f(-0.8, -0.7, 0.0);
	glEnd();
	glFlush();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("1525342Á¶¼º¹Î");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}