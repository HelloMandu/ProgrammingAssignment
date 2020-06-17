#include <glut.h>
#include <glu.h>

void MyLightInit() {

	GLfloat global_ambient[] = { 0.5, 0.5, 0.5, 1.0 };	//전역 주변반사

	GLfloat Light0_Ambient[] = { 1.0, 1.0, 1.0, 1.0 };	//0번 광원 특성 (색상)
	GLfloat Light0_Diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat Light0_Specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat Light1_Ambient[] = { 0.3, 0.3, 0.3, 1.0 };	//1번 광원 특성 (색상)
	GLfloat Light1_Diffuse[] = { 0.3, 0.3, 0.3, 0.3 };
	GLfloat Light1_Specular[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat Light0_Position[] = { 0.0, 0.0, 1.0, 1.0 };	//0번 광원위치 (스포트라이트)
	GLfloat Light0_Direction[] = { 0.0, 0.0, -1.0 };	//0번 광원 방향
	GLfloat Light0_Cutoff[] = { 7.0 };		//0번 광원 각도
	GLfloat Light1_Position[] = { 0.0, 0.0, 1.0, 1.0 };	//1번 광원위치 (전체 살짝)

	glLightfv(GL_LIGHT0, GL_AMBIENT, Light0_Ambient);	//0번 광원 특성할당
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0_Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light0_Specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Light1_Ambient);	//1번 광원 특성할당
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1_Diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Light1_Specular);  

	glLightfv(GL_LIGHT0, GL_POSITION, Light0_Position);	//스포트라이트
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light0_Direction); //방향
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, Light0_Cutoff); //각도
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0);	//코사인 승수

	GLfloat material_ambient[] = { 0.0, 0.0, 0.0, 1.0 };	//물체 특성
	GLfloat material_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat material_shininess[] = { 127.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);//물체 특성할당
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);//전역주변반사 
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); //근접시점
	glShadeModel(GL_SMOOTH);	//구로 셰이딩

	glEnable(GL_DEPTH_TEST);	//깊이 버퍼 활성화
	glEnable(GL_LIGHTING);	//조명 활성화
	glEnable(GL_LIGHT0);	//0번 광원 활성화
	glEnable(GL_LIGHT1);	//1번 광원 활성화
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);		//모델뷰 행렬
	glLoadIdentity();			//항등행렬 로드
	gluLookAt(1.5, 1.5, 1.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	//시점변환
	//gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);	//시점변환

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			glPushMatrix();			glTranslatef(-0.5 + i * 0.3, -0.5 + j * 0.3, 0.0);		glutSolidSphere(0.2, 500, 500);
			glPopMatrix();
		}
	}
	glDisable(GL_LIGHTING);    // 서비스차원에서 광원 위치에 꼬깔콘 표시
	glTranslatef(0.0, 0.0, 1.0);
	glutWireCone(0.05, 0.1, 50, 50);
	glEnable(GL_LIGHTING);
	glFlush();
}


void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION); 	//투상행렬
	glLoadIdentity();		//항등행렬 로드
	gluPerspective(60.0, (GLsizei)w / (GLsizei)h, 0.1, 100);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Spotlight");
	glClearColor(0.5, 0.5, 0.5, 0.5);
	MyLightInit();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}
