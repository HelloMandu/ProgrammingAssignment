#include <random>
#include <glut.h>

int window_width = 1200;
int window_height = 800;

const GLfloat red[] = { 0.8f, 0.0, 0.0, 1.0 };
const GLfloat blue[] = { 0.0, 0.2f, 1.0, 1.0 };
const GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat gray[] = { 0.8, 0.8, 0.8, 1.0 };
const GLfloat polished[] = { 100.0 };
const GLfloat dull[] = { 0.0 };
const GLfloat light_pos[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat starX[500];
GLfloat starY[500];
GLfloat starFar[500];

GLfloat move_y = 0.0;
GLfloat move_z = 0.0;
GLfloat const_att = 0.05;
int gTimeslot = -1;
GLfloat ufoX = 0.0;
GLfloat ufoY = 0.0;
int shootingX, shootingY;

void makeStars() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> X(-10, 10);
	std::uniform_int_distribution<int> Y(-10, 10);
	GLfloat n = 0.003;
	for (int i = 0; i < 500; i++) {
		GLfloat &x = starX[i], &y = starY[i], &c = starFar[i];
		x = X(gen), y = Y(gen);
		if (i % 4 == 0) { x += n * i; y += n * i; c = 0; }
		else if (i % 4 == 1) { x += n * i; y -= n * i; c = 3; }
		else if(i % 4 == 2){ x -= n * i; y += n * i; c = 6; }
		else{ x -= n * i; y -= n * i; c = 9; }
	}
}

void makeUFO() {
	glPushMatrix();
	glRotatef((GLfloat)-50, 1, 0, 0); // 원점 기준 회전
	glTranslatef(ufoX, ufoY, 0); // Pivot을 원점으로 이동
		glPushMatrix(); // 원점을 기준으로 객체 생성 및 축소/확대
			glColor3f(1, 1, 1);
			glScalef(2, 0.4, 1);
			glutSolidTorus(0.1, 0.5, 20, 20); // 팔 상부
		glPopMatrix();
	glPopMatrix();
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);

	glTranslatef(0.0, 0.0, -20.0);
	glPushMatrix();
	glTranslatef(5, 5, move_z);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, const_att);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glDisable(GL_LIGHTING);
	glColor3f(0.8, 0.8, 0.8);
	glutSolidSphere(0.7, 30, 30);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
	glMaterialfv(GL_FRONT, GL_SHININESS, polished);

	makeUFO();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gray);
	glMaterialfv(GL_FRONT, GL_SHININESS, polished);
	for (int i = 0; i < 500; i++) {
		glPushMatrix();
		glTranslatef(starX[i], starY[i], -starFar[i]);
		glutSolidSphere(0.03, 10, 10);
		glPopMatrix();
	}

	glLineWidth(3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(starX[gTimeslot], starY[gTimeslot], 0); 
	glVertex3f(starX[gTimeslot] - 1.5, starY[gTimeslot] - 1.5, 0);
	glEnd();

	glutSwapBuffers();
	glFlush();
}

void MyReshape(int w, int h) {
	window_width = w;
	window_height = h;

	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(35.0, GLfloat(window_width) / GLfloat(window_height), 1.0, 50.0);
	glutPostRedisplay();
}

void MySpecial(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		ufoX -= 0.2;
	}
	else if (key == GLUT_KEY_RIGHT) {
		ufoX += 0.2;
	}
	else if (key == GLUT_KEY_DOWN) {
		ufoY -= 0.2;
	}
	else if (key == GLUT_KEY_UP) {
		ufoY += 0.2;
	}
	glutPostRedisplay();
}

void MyTimer(int Value) {
	gTimeslot = (gTimeslot + 1) % 100;
	glutPostRedisplay();
	glutTimerFunc(400, MyTimer, 1);
}

void MyInit() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);

	glEnable(GL_DEPTH_TEST);
	makeStars();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("One Lighting Two Objects");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutSpecialFunc(MySpecial);
	glutTimerFunc(400, MyTimer, 1);
	glutMainLoop();
	return 0;
}