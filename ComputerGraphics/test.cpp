#include <glut.h>

void MyDisplay( ) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd( );
	glFlush( );
}

int main(int argc, char** argv) {
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("네모그리기");
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glutDisplayFunc(MyDisplay);
	glutMainLoop( );
	return 0;
}