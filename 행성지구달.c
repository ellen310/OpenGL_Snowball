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
	glutWireSphere(0.2, 20, 16); //�¾�
	glPushMatrix();

	glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
	glTranslatef(0.7, 0.0, 0.0);
	glRotated((GLfloat)Time, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.6, 0.7);
	glutWireSphere(0.1, 10, 8); //����
	glPushMatrix(); //������ ��ǥ�踦 stack�� ����. ���߿� �ʿ��Ҷ� pop�ؼ� �����
	
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.2, 0.0);
	glColor3f(0.9, 0.8, 0.2);
	glutWireSphere(0.04, 10, 8); //��
	
	glPopMatrix(); //���Ƿ� ���� ���� �༺�� �ϳ� �� ����� ���� ���� ��ǥ��� ���ư����� pop��
	glPushMatrix(); //�ٽ� ������ġ ���ƿ����� ����. �� ���ƿ������ؼ�
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glTranslatef(0.2, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glutWireSphere(0.05, 10, 8); //������ ���� ���� �༺ �ϳ� �� ������


	//�ǽ� 1---------------------
	glPopMatrix(); //���� �׳� ���Ƿ� ���� �ֺ� �༺ �ϳ� �߰�
	glPushMatrix();// �ٽ� ������ġ ���ƿ����� ������ġ ����. ���߿� �� pop�ؼ� ���ƿ�������
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glTranslatef(0.0, -0.2, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glutWireSphere(0.05, 10, 8);

	glPopMatrix(); //���� �׳� ���Ƿ� ���� �ֺ� �༺ �ϳ� �߰�
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glTranslatef(-0.2, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glutWireSphere(0.05, 10, 8); 

	//�ǽ�2-------------------���� ���� �ڵ������ ������ġ�� pop�ؼ� �������� �༺ �ϳ� ������ ����. ���� ������ġ�� pop�߱� ������ ����. ���⼭ �ѹ� �� pop�ϸ� �¾���ġ�� ���ư�����? �׷��� �¾��ֺ��༺ �ΰ� �߰��غ�
	glPopMatrix(); //�¾���ġ�� �̵�
	glPushMatrix(); //�¾���ġ ����. ���߿� �¾��ֺ��༺ �ϳ� �� �߰��ҰŶ�
	glTranslatef(-0.4, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.5);
	glutWireSphere(0.15, 20, 16);

	glPopMatrix(); //�¾���ġ�� �̵�
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