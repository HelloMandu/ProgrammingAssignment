#include<glut.h>
#include<math.h>
#define Pi 3.1415
void MyDisplay() { 
	GLfloat Size[2], Angle; 
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0, 0.5, 0.0);
	glGetFloatv(GL_POINT_SIZE_RANGE, Size); 
	glBegin(GL_POLYGON); 
		for (Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
			glVertex3f(0.6*cos(Angle), 0.6*sin(Angle), 0.0); 
	glEnd(); 
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.2*cos(Angle) + 0.25, 0.2*sin(Angle) + 0.1, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.2*cos(Angle) - 0.25, 0.2*sin(Angle) + 0.1, 0.0);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.1*cos(Angle) + 0.25, 0.1*sin(Angle) + 0.1, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(-0.1*cos(Angle) - 0.25, -0.1*sin(Angle) + 0.1, 0.0);
	glEnd();
	glColor3f(1.0, 0.7, 0.0);
	glBegin(GL_POLYGON);
		glVertex3f(0.05, -0.1, 0.0);
		glVertex3f(0.0, 0.1, 0.0);
		glVertex3f(-0.05, -0.1, 0.0);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (Angle = Pi; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.1*cos(Angle), 0.1*sin(Angle) - 0.3, 0.0);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(10);
	glBegin(GL_LINE_STRIP);
	for (Angle = 0.8; Angle <= Pi - 0.8; Angle += Pi / 20.0)
		glVertex3f(0.2*cos(Angle) + 0.25, 0.2*sin(Angle) + 0.15, 0.0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (Angle = 0.8; Angle <= Pi - 0.8; Angle += Pi / 20.0)
		glVertex3f(0.2*cos(Angle) - 0.25, 0.2*sin(Angle) + 0.15, 0.0);
	glEnd();
	glFlush(); 
}
int main(int argc, char**argv) { 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGBA); 
	glutInitWindowSize(500, 500); 
	glutInitWindowPosition(100, 50); 
	glutCreateWindow("1525342Á¶¼º¹Î"); 
	glClearColor(1.0, 1.0, 1.0, 1.0); 
	glutDisplayFunc(MyDisplay); 
	glutMainLoop(); 
	return 0; 
}