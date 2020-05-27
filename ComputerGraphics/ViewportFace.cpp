#include <glut.h> 

GLint gW, gH;

void DrawUsualFace() {

	glColor3f(1, 1, 0); // yellow face
	glutSolidSphere(0.8, 30, 30);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(-0.3, 0.1, 0.0); // eye
	glVertex3f(-0.1, 0.1, 0.0);
	glVertex3f(0.1, 0.1, 0.0);
	glVertex3f(0.3, 0.1, 0.0);
	glVertex3f(-0.1, -0.1, 0.0); // mouth
	glVertex3f(0.1, -0.1, 0.0);
	glEnd();

}



void DrawAngryFace() {

	glColor3f(1, 1, 0); // yellow face
	glutSolidSphere(0.8, 30, 30);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES); // eye
	glVertex3f(-0.3, 0.2, 0.0);
	glVertex3f(-0.1, 0.0, 0.0);
	glVertex3f(0.1, 0.0, 0.0);
	glVertex3f(0.3, 0.2, 0.0);
	glEnd();
	glBegin(GL_LINE_LOOP); // mouth
	glVertex3f(-0.1, -0.1, 0.0);
	glVertex3f(0.1, -0.1, 0.0);
	glVertex3f(0.1, -0.2, 0.0);
	glVertex3f(-0.1, -0.2, 0.0);
	glEnd();

}



void DrawSmileFace() {

	glColor3f(1, 1, 0); // yellow face
	glutSolidSphere(0.8, 30, 30);
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.3, 0.1, 0.0); // eye
	glVertex3f(-0.2, 0.15, 0.0);
	glVertex3f(-0.1, 0.1, 0.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(0.1, 0.1, 0.0);
	glVertex3f(0.2, 0.15, 0.0);
	glVertex3f(0.3, 0.1, 0.0);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP); // mouth
	glVertex3f(-0.1, -0.1, 0.0);
	glVertex3f(0.1, -0.1, 0.0);
	glVertex3f(0, -0.2, 0.0);
	glEnd();
	glColor3f(0, 0, 0);
}



void MyDisplay() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//½ÃÇè³ª¿È
	glViewport(0, 0, gW * 2 / 3, gH * 2 / 3);
	DrawSmileFace();

	glViewport(0, gH * 2 / 3, gW * 1 / 3, gH * 1 / 3);
	DrawUsualFace();

	glViewport(gW * 2 / 3, gH * 2 / 3, gW * 1 / 3, gH * 1 / 3);
	DrawUsualFace();

	glViewport(gW * 2 / 3, 0, gW * 1 / 3, gH * 1 / 3);
	DrawUsualFace();

	glViewport(gW * 1 / 3, gH * 2 / 3, gW * 1 / 3, gH * 1 / 3);
	DrawAngryFace();

	glViewport(gW * 2 / 3, gH * 1 / 3, gW * 1 / 3, gH * 1 / 3);
	DrawAngryFace();

	glFlush();
}



void MyReshape(int NewWidth, int NewHeight) {
	gW = NewWidth;
	gH = NewHeight;
}



int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("viewport");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();

	return 0;

}