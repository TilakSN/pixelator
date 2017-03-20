#include <iostream>
#include <GL/glut.h>
using namespace std;

GLint width = 500, height = 500;
GLdouble v[8][3] = { {-1, -1, -1}, {-1, -1, 1}, {-1, 1, 1}, {-1, 1, -1}, {1, -1, -1}, {1, -1, 1}, {1, 1, 1}, {1, 1, -1} };
GLint faces[6][4] = { {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 5, 4}, {1, 2, 6, 5}, {2, 3, 7, 6}, {3, 0, 4, 7} };
GLdouble colors[6][3] = {{0, 0, 1}, {0, 1, 0}, {1, 0, 0}, {1, 0, 1}, {0, 1, 1}, {1, 1, 0}};
GLdouble normals[3][3] = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
GLint dir;
GLdouble angle;

void init() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50, (width * 1.0) / height, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW_MATRIX);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

void rotate() {
	glRotatef(angle, normals[dir][0], normals[dir][1], normals[dir][2]);
}

void draw_quad(GLint index) {
	glBegin(GL_QUADS);
		glColor3dv(colors[index]);
	for (int i = -1; ++i < 4;)
		glVertex3dv(v[faces[index][i]]);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	rotate();
	for (int i = -1; ++i < 6; draw_quad(i));
	glPopMatrix();
	glutSwapBuffers();
	// glutPostRedisplay();
}

void getAngle() {
	cout << "Enter the angle to rotate: ";
	cin >> angle;
}

void mouse(int button, int status, int x, int y) {
	if (status == GLUT_UP && button <= GLUT_RIGHT_BUTTON) {
		dir = button;
		getAngle();
	}
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Cube rotation");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return 0;
}