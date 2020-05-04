/*-----------------------------------------------------------
  6th week (2020. 4. 20)

Keyboard
u a s : face
l k : blueleg
f d : blackleg
p o : right lower arm (90 ~ -90 restict)
r e : left lower arm
0 9 : 팔길이

Special
UP and DOWN : jump
LEFT and RIGHT : moving-X

6주차
(1) 회전시키려면 어떤 기하변환 함수가 필요할까요? -> glRotatef(각도, x축, y축, z축);
(2) 방금 보신 영상에서 막시무스의 다리는 어느 축을 기준으로 회전하고 있나요? -> z축 기준
(3) blue leg만 회전시키고 다른 부분에 영향을 안주려면 어떤 함수를 호출해야 하나요? -> glPushMatrix(); glPopMatrix();
(4) 회전시키니까 다리가 몸체에서 분리됩니다. 그 원인은 뭘까요? -> 원점을 기준으로 회전하기 때문에, 다리가 원점이 아닌 다른 지점에서 돌고 싶어도 원점기준으로 회전
(5) 정확히 고관절을 중심으로 회전하려면 어떻게 하면 될까요?
	-> 1.다리를 원점으로 이동 -> 2.회전 -> 3.원상복귀 (움직임의 순서)
	코딩순서
	push
	3. 다리 시작지점 위치와 동일
	2. 회전
	1. 다리 시작지점 위치와 반대
	다리(Begin ~ End)
	pop

7주차
(1) 현재 팔꿈치 아래(forearm)만 움직입니다. 팔 전체 회전 기능을 추가하세요 (P O R E)
   변수명의 혼동이 예상되므로 gRedforearm -> gRedforearm, gBlackforearm -> gBlackforearm 으로
   팔 전체의 변수명은 gRedupperarm, gBlackupperarm으로
(2) 빨간팔에 늘어나는 기능을 추가
   '0'(zero) 누르면 점점 길어지고, '9' 누르면 점점 원상복귀하는 코드를 추가
(3) 만약 scale 함수가 translate 하지않고 바로 모델에 적용하면 결과는? -> 원점이 고정이 아니기 때문에 팔이 늘어나는게 아니고 점점 커짐
(4) 만약 scale 함수가 전체팔 감싸는 push/pop 보다 위에 있으면 결과는? -> 전체가 그냥 막 커짐
(5) 두 발의 끝위치를 고정하고 shear를 적용해보세요.
   전역변수 1개, 배열선언, 행렬곱 함수(위아래로 tanslate), special함수에서 F1,F2,F3 추가
(6) 2차원 배열을 MyDisplay 함수안에 지역변수로 선언했는데, 전역변수로 바꾸면 어떤 결과? 그이유는?
   -> 배열 선언 시 안에 변수가 들어있으면 그건 선언 당시 변수의 값이 들어있는거랑 동일, 전역변수로 선언하면 그냥 0이 들어있는거랑 동일, 지역변수면 함수 호출시마다 배열이 선언되므로
   special함수에서 바뀐 값이 초기값으로 들어가게 됨
(7) 다리에만 전단
-------------------------------------------------------------*/

#include <glut.h>
#include <math.h>
#define WIN_WIDTH 1000  // window 4:3
#define WIN_HEIGHT 750
#define Pi 3.141592

unsigned char gFace = 'u';   // u:usual  a:angry   s:smiling
GLfloat gY = 0.0;  // jump
GLfloat gX = 0.0;  // moving-X
GLfloat gBlueleg = 0.0, gBlackleg = 0.0; // 회전각도
GLfloat gRedforearm = 0.0, gBlackforearm = 0.0, gRedupperarm = 0.0, gBlackupperarm = 0.0; // 회전각도
GLfloat gRedarmlength = 1; // 빨간팔의 길이
GLfloat gShear = 0.0, gShearleg = 0.0; // 7-(5), 7-(7)
GLfloat gFlowerShear = 0.0, gRootShear = 0.0; // 꽃 전단

void MyBackground();
void MyMat();
void MyFace();
void MyEyeMouth();
void MyBody();
void MyFlower();

void MyFlower() {
	// 꽃의 윗부분
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(-2.8, -1.5, 0);
	glScalef(4, 4, 0);
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle), 0.035*sin(Angle) + 0.035, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle) - 0.03, 0.03*sin(Angle) - 0.035, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle) + 0.03, 0.03*sin(Angle) - 0.035, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle) + 0.04, 0.03*sin(Angle) + 0.02, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.03*cos(Angle) - 0.04, 0.03*sin(Angle) + 0.02, 0.0);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (GLfloat Angle = 0.0; Angle <= 2.0*Pi; Angle += Pi / 20.0)
		glVertex3f(0.04*cos(Angle), 0.04*sin(Angle), 0.0);
	glEnd();
	glPopMatrix();

	// 꽃의 아랫부분

	glPushMatrix();
	GLfloat flowerRoot_arr[4][4] = {
	   {1,0,0,0},
	   {gRootShear,1,0,0},
	   {0,0,1,0},
	   {0,0,0,1},
	};
	glTranslatef(-2.8, -1.65, 0);
	glMultMatrixf((float*)flowerRoot_arr);
	glTranslatef(2.8, 1.65, 0);

	glColor3f(1, 1, 1);
	glLineWidth(4);
	glBegin(GL_LINES);
	glVertex3f(-2.8, -1.65, 0);
	glVertex3f(-2.8, -2.3, 0); 
	glEnd();
	glLineWidth(1);
	glPopMatrix();
}
void MyDisplay() {
	// 아래 세개는 항상 고정
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); // display는 Modelview
	glLoadIdentity();

	//glScalef(1, -1, 1); // 2d에서 x축에 대한 반사
	//glScalef(-1, 1, 1); // 2d에서 y축에 대한 반사

	MyBackground();
	MyMat();

	//// y=x 에 대한 반사
	//glRotatef(-45, 0, 0, 1);
	//glScalef(-1, 1, 1);
	//glRotatef(45, 0, 0, 1);

	// 여기서부터는 Maximus
	//glTranslatef(2, 0, 0); // y=x에 대한 반사
	glPushMatrix();
	glTranslatef(gX, gY, 0); // left, right, jump
	GLfloat Shear_arr[4][4] = {
	   {1,0,0,0},
	   {gShear,1,0,0},
	   {0,0,1,0},
	   {0,0,0,1},
	};
	glTranslatef(0, -1, 0); // 막시무스의 발끝
	glMultMatrixf((float*)Shear_arr);
	glTranslatef(0, 1, 0);
	glPushMatrix();
	MyFace();
	glPopMatrix();

	MyEyeMouth();
	MyBody();
	glPopMatrix();

	// 전단만 따라하는 작은 무언가
	glPushMatrix();
	GLfloat Flower_arr[4][4] = {
	   {1,0,0,0},
	   {gFlowerShear,1,0,0},
	   {0,0,1,0},
	   {0,0,0,1},
	};
	glTranslatef(-2.8, -2.3, 0);
	glMultMatrixf((float*)Flower_arr);
	glTranslatef(2.8, 2.3, 0);
	glPushMatrix();
	MyFlower();
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();

} // MyDisplay
void MyBackground() {

	glColor3f(0, 1, 1); // sky 

	glBegin(GL_POLYGON);
	glVertex3f(-4, 0, -4);
	glVertex3f(4, 0, -4);
	glVertex3f(4, 3, -4);
	glVertex3f(-4, 3, -4);
	glEnd();

	glColor3f(0, 1, 0); // green 

	glBegin(GL_POLYGON);
	glVertex3f(-4, -3, -4);
	glVertex3f(4, -3, -4);
	glVertex3f(4, 0, -4);
	glVertex3f(-4, 0, -4);
	glEnd();

}
void MyMat() {

	glColor3f(0xE4 / 255.0, 0xBE / 255.0, 0xFE / 255.0); // 연보라색   
	glBegin(GL_POLYGON);
	glVertex3f(-1.5, -1.3, 0); // 바닥에 펼쳐있어야 하는데, 아직 2D라서 공중에 떠있는 평행사변형
	glVertex3f(1.2, -1.3, 0); // 3D로가면, 진짜 바닥에 펼쳐진 매트로 전환할 예정
	glVertex3f(1.5, -0.8, 0);
	glVertex3f(-1.2, -0.8, 0);
	glEnd();

} // MyMat
void MyFace() {

	glColor3f(251 / 255.0, 206 / 255.0, 177 / 255.0); // 살구색

	glPushMatrix(); // 행렬 스택(3장에서 자세히 배움)
	glTranslatef(0, 1, 0); // 구를 이동시키기 위해서
	glutSolidSphere(0.5, 50, 50); // glut는 원점을 기준으로 그려짐
	glPopMatrix(); // push를 했으면 pop

} // MyFace 
void MyEyeMouth() {

	if (gFace == 'a') {  // angry

		glColor3f(0, 0, 0); // black
		glBegin(GL_LINES);
		glVertex3f(-0.3, 1.2, 0.0); // eye
		glVertex3f(-0.1, 1.0, 0.0);
		glVertex3f(0.1, 1.0, 0.0); // eye
		glVertex3f(0.3, 1.2, 0.0);
		glEnd();

		glBegin(GL_LINE_LOOP); // mouth
		glVertex3f(-0.1, 0.9, 0.0);
		glVertex3f(0.1, 0.9, 0.0);
		glVertex3f(0.1, 0.8, 0.0);
		glVertex3f(-0.1, 0.8, 0.0);
		glEnd();
	}
	else if (gFace == 's') { // smiling

		glColor3f(0, 0, 0); // black
		glBegin(GL_LINE_STRIP); // eye
		glVertex3f(-0.3, 1.1, 0.0);
		glVertex3f(-0.2, 1.15, 0.0);
		glVertex3f(-0.1, 1.1, 0.0);
		glEnd();

		glBegin(GL_LINE_STRIP);   // eye
		glVertex3f(0.1, 1.1, 0.0);
		glVertex3f(0.2, 1.15, 0.0);
		glVertex3f(0.3, 1.1, 0.0);
		glEnd();

		glColor3f(1, 0, 0); // red
		glBegin(GL_LINE_LOOP); // mouth
		glVertex3f(-0.1, 0.9, 0.0);
		glVertex3f(0.1, 0.9, 0.0);
		glVertex3f(0, 0.8, 0.0);
		glEnd();
	}
	else if (gFace == 'u') { // usual

		glColor3f(0, 0, 0); // black
		glBegin(GL_LINES);
		glVertex3f(-0.3, 1.1, 0.0); // eye
		glVertex3f(-0.1, 1.1, 0.0);
		glVertex3f(0.1, 1.1, 0.0); // eye
		glVertex3f(0.3, 1.1, 0.0);
		glVertex3f(-0.1, 0.9, 0.0); // mouth
		glVertex3f(0.1, 0.9, 0.0);
		glEnd();
	}

} // MyEyeMouth
void MyBody() {

	glColor3f(0, 0, 0); // black neck
	glBegin(GL_LINES);
	glVertex3f(0, 0.5, 0.0);
	glVertex3f(0, 0.3, 0.0);
	glEnd();

	glColor3f(0.5, 0.5, 0.5); // gray spine
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, -0.3, 0.0);
	glVertex3f(0.05, -0.3, 0.0);
	glVertex3f(0.05, 0.3, 0.0);
	glVertex3f(-0.05, 0.3, 0.0);
	glEnd();


	glPushMatrix(); // red 큰 팔 시작
	glTranslatef(0.05, 0.3, 0.0);
	glRotatef(gRedupperarm, 0, 0, 1);
	glScalef(gRedarmlength, gRedarmlength, 1);
	glTranslatef(-0.05, -0.3, 0.0);
	glLineWidth(3); // line 
	glColor3f(1, 0, 0); // red arm
	glBegin(GL_LINES); // upper
	glVertex3f(0.05, 0.3, 0.0);
	glVertex3f(0.25, 0.1, 0.0);
	glEnd();

	glPushMatrix();
	glTranslatef(0.25, 0.1, 0.0);
	glRotatef(gRedforearm, 0, 0, 1);
	glTranslatef(-0.25, -0.1, 0.0);
	glBegin(GL_LINES); // lower   
	glVertex3f(0.25, 0.1, 0.0);
	glVertex3f(0.5, -0.2, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix(); // 큰 팔 pop

	glPushMatrix(); // black 큰 팔 시작
	glTranslatef(-0.05, 0.3, 0.0);
	glRotatef(gBlackupperarm, 0, 0, 1);
	glTranslatef(0.05, -0.3, 0.0);
	glColor3f(0, 0, 0); // black arm
	glBegin(GL_LINES); //upper
	glVertex3f(-0.05, 0.3, 0.0);
	glVertex3f(-0.25, 0.1, 0.0);
	glEnd();

	glPushMatrix();
	glTranslatef(-0.25, 0.1, 0.0);
	glRotatef(gBlackforearm, 0, 0, 1);
	glTranslatef(0.25, -0.1, 0.0);
	glBegin(GL_LINES); //lower
	glVertex3f(-0.25, 0.1, 0.0);
	glVertex3f(-0.5, -0.2, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix(); // 큰 팔 pop

	// 다리만 전단
	glPushMatrix(); // 다리 두개 묶음
	GLfloat Shearleg_arr[4][4] = {
	   {1,0,0,0},
	   {gShearleg,1,0,0},
	   {0,0,1,0},
	   {0,0,0,1},
	};
	glTranslatef(0, -0.3, 0);
	glMultMatrixf((float*)Shearleg_arr);
	glTranslatef(0, 0.3, 0);

	glColor3f(0, 0, 1); // blue leg
	glPushMatrix();
	glTranslatef(0.05, -0.3, 0.0); // (3) 다리를 원상복귀
	glRotatef(gBlueleg, 0, 0, 1); // (2) z축 기준으로 회전
	glTranslatef(-0.05, 0.3, 0.0); // (1) 다리가 원점에서 시작하도록 이동
	glBegin(GL_LINES);
	glVertex3f(0.05, -0.3, 0.0); // leg high point
	glVertex3f(0.3, -1.0, 0.0);
	glEnd();
	glPopMatrix();

	glColor3f(0, 0, 0); // black leg
	glPushMatrix();
	glTranslatef(-0.05, -0.3, 0.0);
	glRotatef(gBlackleg, 0, 0, 1);
	glTranslatef(0.05, 0.3, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-0.05, -0.3, 0.0);
	glVertex3f(-0.3, -1.0, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix(); // 두다리 전단한거 pop
	glLineWidth(1);  // line

} // MyBody
void MyKeyboard(unsigned char key, int x, int y) {

	switch (key) {

	case 'Q':
	case 'q':   exit(0);  break;

	case 'a':
	case 's':
	case 'u':   gFace = key;   break;    // face

	case 'l':   gBlueleg += 10; break; // 다리회전
	case 'k':   gBlueleg -= 10; break;

	case 'f':   gBlackleg += 10; break; // 다리회전
	case 'd':   gBlackleg -= 10; break;

	case 'p':   if (gRedforearm < 90) gRedforearm += 3; break;
	case 'o':   if (gRedforearm > -90) gRedforearm -= 3; break;

	case 'r':   if (gBlackforearm < 90) gBlackforearm += 3; break;
	case 'e':   if (gBlackforearm > -90) gBlackforearm -= 3; break;

	case 'P':   if (gRedupperarm < 90) gRedupperarm += 3; break;
	case 'O':   if (gRedupperarm > -90) gRedupperarm -= 3; break;

	case 'R':   if (gBlackupperarm < 90) gBlackupperarm += 3; break;
	case 'E':   if (gBlackupperarm > -90) gBlackupperarm -= 3; break;

	case '0':   gRedarmlength *= 1.1; break;
	case '9':   if (gRedarmlength > 1) gRedarmlength /= 1.1; break;
	}

	glutPostRedisplay();

} // MyKeyboard
void MySpecial(int key, int x, int y) {

	switch (key) {

	case GLUT_KEY_UP:
		gY = 1;
		gFace = 's';
		gRedforearm = 30; // 반시계
		gBlackforearm = -30; // 시계
		gBlueleg = -19.5; // 반시계
		gBlackleg = 19.5; // 시계
		break;
	case GLUT_KEY_DOWN:
		gY = 0;
		gFace = 'u';
		gRedforearm = gBlackforearm = gBlueleg = gBlackleg = 0;
		break;
	case GLUT_KEY_LEFT:
		if (gY == 0) {
			gX -= 0.1;
			if (gX < -1.5 || gX > 1.5) gFace = 'a';
			else gFace = 'u';
		}
		break;
	case GLUT_KEY_RIGHT:
		if (gY == 0) {
			gX += 0.1;
			if (gX < -1.5 || gX > 1.5) gFace = 'a';
			else gFace = 'u';
		}
		break;
	case GLUT_KEY_F1: gShear = -0.5; gFace = 's'; gRedupperarm = 48; gBlackupperarm = -48; gFlowerShear = -0.5; break; // 전신 왼쪽
	case GLUT_KEY_F2: gShear = 0.0; gFace = 'u'; gRedupperarm = 0; gBlackupperarm = 0; gFlowerShear = 0.0; break;
	case GLUT_KEY_F3: gShear = 0.5; gFace = 's'; gRedupperarm = 48; gBlackupperarm = -48; gFlowerShear = 0.5; break;

	case GLUT_KEY_F4: gShearleg = 0.5; gFace = 's'; gRedupperarm = 48; gBlackupperarm = -48; gRootShear = 0.5; break; // 다리 왼쪽 (전신과 부호가 다른 이유 : 상반신이 왼쪽으면 다리는 오른쪽)
	case GLUT_KEY_F5: gShearleg = 0.0; gFace = 'u'; gRedupperarm = 0; gBlackupperarm = 0; gRootShear = 0.0; break;
	case GLUT_KEY_F6: gShearleg = -0.5; gFace = 's'; gRedupperarm = 48; gBlackupperarm = -48; gRootShear = -0.5; break;
	}

	glutPostRedisplay();

} // MySpecial
void MyReshape(int NewWidth, int NewHeight) {

	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)WIN_WIDTH;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)WIN_HEIGHT;

	glMatrixMode(GL_PROJECTION); // reshape에는 projection
	glLoadIdentity();
	glOrtho(-4.0 * WidthFactor, 4.0 * WidthFactor, -3.0 * HeightFactor, 3.0 * HeightFactor, -4.0, 4.0); // z축은 x랑 같은걸로 고정

} // MyReshape
void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// menu callback 

} // MyInit
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutInitWindowPosition(150, 0);
	glutCreateWindow("Maximus");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecial);

	glutMainLoop();
	return 0;
}