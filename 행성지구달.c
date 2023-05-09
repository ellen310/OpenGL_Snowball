#include <glut.h>
#include <gl.h>
#include <glu.h> 
#include <stdio.h>

static int Day = 0, Time = 0;
static float vX, vY, vZ = 0.2, uX, uY = 1.0, uZ;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(vX, vY, vZ, 0.0, 0.0, 0.0, uX, uY, uZ);

	glColor3f(1.0, 0.3, 0.3);
	glutWireSphere(0.2, 20, 16); //태양
	glPushMatrix();

	glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
	glTranslatef(0.7, 0.0, 0.0);
	glRotated((GLfloat)Time, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.6, 0.7);
	glutWireSphere(0.1, 10, 8); //지구
	glPushMatrix(); //지구의 좌표계를 stack에 저장. 나중에 필요할때 pop해서 쓸라고
	
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.2, 0.0);
	glColor3f(0.9, 0.8, 0.2);
	glutWireSphere(0.04, 10, 8); //달
	
	glPopMatrix(); //임의로 지구 종속 행성을 하나 더 만들기 위해 지구 좌표계로 돌아가려고 pop함
	glPushMatrix(); //다시 지구위치 돌아왔으니 저장. 또 돌아오기위해서
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glTranslatef(0.2, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glutWireSphere(0.05, 10, 8); //임의의 지구 종송 행성 하나 더 만들어본것


	//실습 1---------------------
	glPopMatrix(); //내가 그냥 임의로 지구 주변 행성 하나 추가
	glPushMatrix();// 다시 지구위치 돌아왔으니 지구위치 저장. 나중에 또 pop해서 돌아오기위해
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glTranslatef(0.0, -0.2, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glutWireSphere(0.05, 10, 8);

	glPopMatrix(); //내가 그냥 임의로 지구 주변 행성 하나 추가
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glTranslatef(-0.2, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glutWireSphere(0.05, 10, 8); 

	//실습2-------------------지금 위에 코드까지는 지구위치를 pop해서 지구기준 행성 하나 생성한 상태. 이제 지구위치는 pop했기 때문에 없다. 여기서 한번 더 pop하면 태양위치로 돌아가겠죠? 그렇게 태양주변행성 두개 추가해봄
	glPopMatrix(); //태양위치로 이동
	glPushMatrix(); //태양위치 저장. 나중에 태양주변행성 하나 더 추가할거라서
	glTranslatef(-0.4, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.5);
	glutWireSphere(0.15, 20, 16);

	glPopMatrix(); //태양위치로 이동
	glTranslatef(0.0, -0.4, 0.0);
	glColor3f(0.0, 0.0, 0.5);
	glutWireSphere(0.15, 20, 16);


	glutSwapBuffers();
	glFlush();
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		Day = (Day + 10) % 360;
		glutPostRedisplay();
		break;
	case 't':
		Time = (Time + 5) % 360;
		glutPostRedisplay();
		break;
	case 'q':
		vX += 0.01;
		glutPostRedisplay();
		break;
	case 'w':
		vX -= 0.01;
		glutPostRedisplay();
		break;
	case 'a':
		vY += 0.01;
		glutPostRedisplay();
		break;
	case 's':
		vY -= 0.01;
		glutPostRedisplay();
		break;
	case 'z':
		vZ += 0.01;
		glutPostRedisplay();
		break;
	case 'x':
		vZ -= 0.01;
		glutPostRedisplay();
		break;
	case 'o':
		uX += 0.01;
		glutPostRedisplay();
		break;
	case 'p':
		uX -= 0.01;
		glutPostRedisplay();
		break;
	case 'k':
		uY += 0.01;
		glutPostRedisplay();
		break;
	case '1':
		uY -= 0.01;
		glutPostRedisplay();
		break;
	case 'n':
		uZ += 0.01;
		glutPostRedisplay();
		break;
	case 'm':
		uZ -= 0.01;
		glutPostRedisplay();
		break;
	default:
		break;
	}
	printf("vX : %f, vY: %f, vZ: %f\n", vX, vY, vZ);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
	return 0;
}