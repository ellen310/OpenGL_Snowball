#include <glut.h>
#include <gl.h>
#include <glu.h> 

void MyLightInit() {
	GLfloat global_ambient[] = { 0.1,0.1,0.1,1.0 };

	GLfloat light0_ambient[] = { 0.5,0.4,0.3,1.0 };
	GLfloat light0_diffuse[] = { 0.5,0.4,0.3,1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat light1_ambient[] = { 0.0,0.0,0.0,1.0 };
	GLfloat light1_diffuse[] = { 0.5,0.2,0.3,1.0 };
	GLfloat light1_specular[] = { 0.0, 0.0, 0.0, 1.0 };

	GLfloat material_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat material_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat material_specular[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat material_shininess[] = { 25.0 };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light0_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light0_specular);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void MyDisplay() {
	GLfloat LightPosition0[] = { 0.0, 0.0, 2.0, 1.0 };
	GLfloat LightPosition1[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat LightDirection1[] = { -0.5, -1.0, -1.0 };
	GLfloat SpotAngle1[] = { 25.0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.5, 0.5, 0.5, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	glTranslatef(0.3, 0.3, 0.0);

	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirection1);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, SpotAngle1);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);
	glutSolidTorus(0.3, 0.6, 800, 800);
	glFlush();
}

void MyReshape(int w, int h) {
	glViewport(0, 0,(GLsizei) w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
	glutInit(&argv, argv);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("openGL Sample Drawing");
	MyLightInit();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}