#include <glut.h>
#include<math.h>
#define Pi 3.1415

unsigned char gKey = 'u';
double gX, gY;

void angry() {
	/*传舅*/
	GLfloat Angle;
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.1*cos(Angle) + 0.25, 0.1*sin(Angle) + 0.1, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(-0.1*cos(Angle) - 0.25, -0.1*sin(Angle) + 0.1, 0.0);
	glEnd();
	/*传界*/
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(10);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.15, 0.3, 0);
	glVertex3f(0.45, 0.4, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.15, 0.3, 0);
	glVertex3f(-0.45, 0.4, 0);
	glEnd();
	/*涝贱*/
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.2, -0.3, 0);
	glVertex3f(0.0, -0.2, 0);
	glVertex3f(0.2, -0.3, 0);
	glEnd();
}

void smile() {
	/*传舅*/
	glColor3f(1.0, 0.0, 0.0);
	/*glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.1*cos(Angle) + 0.25, 0.1*sin(Angle) + 0.1, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(-0.1*cos(Angle) - 0.25, -0.1*sin(Angle) + 0.1, 0.0);
	glEnd();*/
	glLineWidth(20);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.35, 0.2, 0);
	glVertex3f(-0.1, 0.1, 0);
	glVertex3f(-0.35, 0, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.35, 0.2, 0);
	glVertex3f(0.1, 0.1, 0);
	glVertex3f(0.35, 0, 0);
	glEnd();
	/*传界*/
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(10);
	glBegin(GL_LINE_STRIP);
	for (GLfloat Angle = 0.8; Angle <= Pi - 0.8; Angle += Pi / 20.0)
		glVertex3f(0.2*cos(Angle) + 0.25, 0.2*sin(Angle) + 0.15, 0.0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (GLfloat Angle = 0.8; Angle <= Pi - 0.8; Angle += Pi / 20.0)
		glVertex3f(0.2*cos(Angle) - 0.25, 0.2*sin(Angle) + 0.15, 0.0);
	glEnd();
	/*涝贱*/
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (GLfloat Angle = Pi; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.3*cos(Angle), 0.3*sin(Angle) - 0.2, 0.0);
	glEnd();
}

void usual() {
	/*传舅*/
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.1*cos(Angle) + 0.25, 0.1*sin(Angle) + 0.1, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(-0.1*cos(Angle) - 0.25, -0.1*sin(Angle) + 0.1, 0.0);
	glEnd();
	/*传界*/
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(10);
	glBegin(GL_LINE_STRIP);
	for (GLfloat Angle = 0.8; Angle <= Pi - 0.8; Angle += Pi / 20.0)
		glVertex3f(0.2*cos(Angle) + 0.25, 0.2*sin(Angle) + 0.15, 0.0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (GLfloat Angle = 0.8; Angle <= Pi - 0.8; Angle += Pi / 20.0)
		glVertex3f(0.2*cos(Angle) - 0.25, 0.2*sin(Angle) + 0.15, 0.0);
	glEnd();
	/*涝贱*/
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (GLfloat Angle = Pi; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.1*cos(Angle), 0.1*sin(Angle) - 0.3, 0.0);
	glEnd();
}

void heart() {
	glColor3f(0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.5 + gX, 0 + gY, 0);
	glVertex3f(0.6 + gX, 0.1 + gY, 0);
	glVertex3f(0.55 + gX, 0.15 + gY, 0);
	glVertex3f(0.5 + gX, 0.1 + gY, 0);
	glVertex3f(0.45 + gX, 0.15 + gY, 0);
	glVertex3f(0.4 + gX, 0.1 + gY, 0);
	glEnd();
}

void MyDisplay() {
	GLfloat Size[2], Angle;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.5, 0.0);
	glGetFloatv(GL_POINT_SIZE_RANGE, Size);
	/*倔奔*/
	glBegin(GL_POLYGON);
	for (Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.6*cos(Angle), 0.6*sin(Angle), 0.0);
	glEnd();
	/*传*/
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.2*cos(Angle) + 0.25, 0.2*sin(Angle) + 0.1, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.2*cos(Angle) - 0.25, 0.2*sin(Angle) + 0.1, 0.0);
	glEnd();
	/*内*/
	glColor3f(1.0, 0.7, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.05, -0.1, 0.0);
	glVertex3f(0.0, 0.1, 0.0);
	glVertex3f(-0.05, -0.1, 0.0);
	glEnd();
	/*传界*/
	switch (gKey) {
	case 'u':
		usual();
		break;
	case 'a':
		angry();
		break;
	case 's':
		smile();
		break;
	}
	heart();
	glutSwapBuffers();
}

void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)600;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)600;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
	case 's':
	case 'u':
		gKey = key;
		break;
	case 'W':
		glClearColor(1.0, 1.0, 1.0, 1.0);
		break;
	case 'R':
		glClearColor(1.0, 0, 0, 1.0);
		break;
	case 'G':
		glClearColor(0, 1.0, 0, 1.0);
		break;
	case 'B':
		glClearColor(0, 0, 1.0, 1.0);
		break;
	}
	glutPostRedisplay();
}

void MySpecial(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		gX -= 0.1;
		break;
	case GLUT_KEY_RIGHT:
		gX += 0.1;
		break;
	case GLUT_KEY_UP:
		gY += 0.1;
		break;
	case GLUT_KEY_DOWN:
		gY -= 0.1;
		break;
	case GLUT_KEY_F5:
		gX = 0, gY = 0;
		break;
	}
	glutPostRedisplay();
}

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("a:拳巢, s:固家, u:乞家, W:拳捞飘, G:弊赴, R:饭靛 1525342炼己刮");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecial);
	glutMainLoop();
	return 0;
}