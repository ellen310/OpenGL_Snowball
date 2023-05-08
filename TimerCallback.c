#include <glut.h>
#include <gl.h>
#include <glu.h> 

GLfloat Delta = 0.0;
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.5, 0.8);
	glVertex3f(-1.0+Delta, -0.5, 0.0);
	glVertex3f(0.0+Delta, -0.5, 0.0);
	glVertex3f(0.0+Delta, 0.5, 0.0);
	glVertex3f(-1.0+Delta, 0.5, 0.0);
	glEnd();
	glFlush();
}

void MyTimer(int Value) {
	Delta = Delta + 0.001;
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); //GLUT 윈도우 함수
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(40,MyTimer,1);
	glutMainLoop();
	return 0;

}