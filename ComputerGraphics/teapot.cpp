#include <glut.h>
#include <glu.h>

void MyDisplay() {
	GLUquadricObj *qobj = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidTeapot(1.0);
	glColor3f(1.0, 1.0, 0.0);
	gluQuadricDrawStyle(qobj, GLU_FILL); // Quadrics에 원하는 Draw Style을 지정
	gluSphere(qobj, 0.7, 50, 50);
	glColor3f(1.0, 0.0, 0.0);
	glutWireTeapot(0.5);

	glutSwapBuffers();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("GLU 및 GLUT 사용해보기");
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}