#include <glut.h>
#include <gl.h>
#include <glu.h>


#define WIDTH 500
#define HEIGHT 500

GLfloat camX = 5.0, camY = 2.0, camZ = -5.0;
GLfloat objX = 0.0, objY = 0.0, objZ = 0.0;
GLfloat cam_upX = 0.0, cam_upY = 1.0, cam_upZ = 0.0;

GLfloat Delta = 0.0;
GLboolean isSnowPressed = GL_FALSE;


void InitLight() {
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	
	// 조명 1 세팅 (기본 조명)
	GLfloat global_ambient[] = { 0.1, 0.1, 0.1, 1.0 }; //전역 주변광 세팅. RGBA
	GLfloat light0_pos[] = { 16.0, 16.0, 0.0, 1.0 }; // 전역 주변광의 위치 설정

	// 전역 주변광의 색깔
	GLfloat light0_ambient[] = { 1.0, 1.0, 1.0, 1.0 }; //주변광
	GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; //반사광(난반사, 확산)
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 }; //경면광

	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);

}

void DrawPlane(GLfloat y) {
	glDisable(GL_COLOR_MATERIAL); 
	
	GLfloat material_ambient[] = { 0.5, 0.7, 1.0, 1.0 };
	GLfloat material_diffuse[] = { 0.5, 0.7, 1.0, 1.0 };
	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat material_shininess[] = { 25.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
	

	GLfloat x = -2.5, z = -1.5, width = 4;
	
	glNormal3f(0, 1, 0); 
	glBegin(GL_POLYGON);
		glVertex3f(x, y, z);
		glVertex3f(x, y, z+width);
		glVertex3f(x+width, y, z+width);
		glVertex3f(x+width, y, z);
	glEnd();

}

void DrawWall(GLfloat z) {
	glDisable(GL_COLOR_MATERIAL);
	GLfloat material_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat material_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat material_shininess[] = { 25.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	GLfloat x = -2.5, y = -2.5, width = 4;
	glNormal3f(-1, 0, -1);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y + width, z);
	glVertex3f(x + width, y + width, z);
	glVertex3f(x + width, y, z);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
	glNormal3f(1, 0, -1);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y + width, z);
	glVertex3f(x, y + width, 2.5 - width);
	glVertex3f(x, y, 2.5 - width);
	glEnd();
	
}

void DrawProp() {
	glDisable(GL_COLOR_MATERIAL);
	GLfloat material_ambient[] = { 0.5, 0.5, 1.0, 1.0};
	GLfloat material_diffuse[] = { 0.2, 0.2, 1.0, 1.0 };
	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat material_shininess[] = { 25.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glPushMatrix();
	GLUquadricObj* obj;
	obj = gluNewQuadric();
	glTranslatef(0, -2.3f, 0);
	glRotatef(-90, 1.0, 0, 0);
	gluCylinder(obj, 1.0f, 0.8f, 0.8f, 32, 8);
	glTranslatef(0, 0.0f, 0.79f);
	gluDisk(obj, 0.0f, 0.8f, 16, 4); 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -2.3f, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.05f, 1.0f, 20, 20);
	glPopMatrix();
}

void DrawGlass() {
	glDisable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);

	GLfloat material_ambient[] = { 1.0, 1.0, 1.0, 0.2};
	GLfloat material_diffuse[] = { 1.0, 1.0, 1.0, 0.2};
	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 0.2}; 
	GLfloat material_shininess[] = { 0.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
	
	glPushMatrix();
	glTranslatef(0, -1.0f, 0);
	glutSolidSphere(1.0, 20, 20);
	glPopMatrix();

	glDisable(GL_BLEND);
}

void DrawTree() {
	glDisable(GL_COLOR_MATERIAL);

	//나무 밑둥
	GLfloat material_ambient[] = { 0.5, 0.15, 0, 1.0 };
	GLfloat material_diffuse[] = { 0.5, 0.15, 0, 1.0 };
	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat material_shininess[] = { 25.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glPushMatrix();
	GLUquadricObj* obj;
	obj = gluNewQuadric();	
	glTranslatef(0.4f, -1.4f, 0.1f);
	glRotatef(-90, 1.0, 0, 0);
	gluCylinder(obj, 0.08f, 0.08f, 0.3f, 32, 8);
	glPopMatrix();

	//나뭇잎
	GLfloat material_ambient2[] = { 0, 1.0, 0, 1.0 };
	GLfloat material_diffuse2[] = { 0, 1.0, 0, 1.0 };
	GLfloat material_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat material_shininess2[] = { 25.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular2);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess2);

	glPushMatrix();
	glTranslatef(0.4f, -1.2f, 0.1f);
	glRotatef(270, 1, 0, 0);
	glutSolidCone(0.2f, 0.3f, 20, 20);
	glTranslatef(0.0f, 0.0f, 0.15f);
	glutSolidCone(0.17f, 0.3f, 20, 20);
	glTranslatef(0.0f, 0.0f, 0.15f);
	glutSolidCone(0.15f, 0.3f, 20, 20);
	glTranslatef(0.0f, 0.0f, 0.15f);
	glutSolidCone(0.13f, 0.2f, 20, 20);
	
	glPopMatrix();
}

void DrawSnowman() {
	glDisable(GL_COLOR_MATERIAL);

	GLfloat material_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat material_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat material_shininess[] = { 25.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glPushMatrix();
	glTranslatef(-0.0f, -1.3f, -0.4f);
	glutSolidSphere(0.2, 10, 10);
	glTranslatef(0.0f, 0.2f, 0.0f);
	glutSolidSphere(0.15, 10, 10);
	glPopMatrix();
}

void DrawSnow() {
	glDisable(GL_COLOR_MATERIAL);

	float Delta_OE = Delta / 0.005; 
	if (  (int)Delta_OE % 2 == 0) {
		GLfloat material_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat material_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat material_shininess[] = { 125.0 };

		glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
	}
	else {
		GLfloat material_ambient[] = { 0, 1.0, 1.0, 1.0 };
		GLfloat material_diffuse[] = { 0, 1.0, 1.0, 1.0 };
		GLfloat material_specular[] = { 0, 1.0, 1.0, 1.0 };
		GLfloat material_shininess[] = { 0.0 };

		glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
	}

	glPushMatrix();
	glTranslatef(0, -0.2-Delta, 0);
	glutSolidSphere(0.02, 10, 10);

	glTranslatef(-0.4, -0.2, -0.4);
	glutSolidSphere(0.02, 10, 10);

	glTranslatef(0.8, -0.1, 0.6);
	glutSolidSphere(0.02, 10, 10);

	glTranslatef(0.2, -0.3, 0.2);
	glutSolidSphere(0.02, 10, 10);

	glTranslatef(-0.3, -0.1, -0.7);
	glutSolidSphere(0.02, 10, 10);

	glTranslatef(0.3, -0.1, -0);
	glutSolidSphere(0.02, 10, 10);

	glTranslatef(-1.0, -0.2, 0);
	glutSolidSphere(0.02, 10, 10);

	glTranslatef(-0.3, 0.3, 0);
	glutSolidSphere(0.02, 10, 10);

	glTranslatef(0.4, 0.3, 0);
	glutSolidSphere(0.02, 10, 10);

	glTranslatef(0.4, 0, 0);
	glutSolidSphere(0.02, 10, 10);
	glPopMatrix();
}



void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camX, camY, camZ, objX, objY, objZ, cam_upX, cam_upY, cam_upZ);

	DrawPlane(-2.5);
	DrawWall(2.5);

	DrawProp();
	DrawTree();
	DrawSnowman();
	if(isSnowPressed) DrawSnow();
	DrawGlass();

	glFlush();
}

void Reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = (float)width / height;
	gluPerspective(45, ratio, 0.1, 1000);
}

void Keyboard(unsigned char KeyPressed, int X, int Y) {
	switch (KeyPressed) {
	case 'Q':
		exit(0); 
		break;
	case 'q':
		exit(0); 
		break;
	case 27:
		break; // esc의 아스키코드값

	case 's':
		isSnowPressed = GL_TRUE;
		break;
	}
}

void Timer() {
	if (isSnowPressed) 
		Delta = Delta + 0.005;

	glutPostRedisplay();
	glutTimerFunc(40, Timer, 1);
}




int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutCreateWindow("OpenGL Snowball Drawing");

	InitLight();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(40, Timer, 1);

	glutMainLoop();

	return 0;
}