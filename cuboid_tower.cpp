#include <GL/glut.h>

GLfloat lightpos[2][4] = {{1, 1, 2, 0}, {-1, -1, 2, 0}};
GLfloat light_diffuse[2][4] = {{1, 1, 1, 1}, {1, 1, 1, 1}};
GLint width = 500, height = 500;
GLdouble v[32][3];
GLdouble X[] = {1, 0, 0};
GLdouble _X[] = {-1, 0, 0};
GLdouble Y[] = {0, 1, 0};
GLdouble _Y[] = {0, -1, 0};
GLdouble Z[] = {0, 0, 1};
GLdouble _Z[] = {0, 0, -1};
GLint faces[21][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {12, 13, 14, 15}, {20, 21, 22, 23}, {28, 29, 30, 31},
{0, 1, 5, 4}, {8, 9, 13, 12}, {16, 17, 21, 20}, {24, 25, 29, 28},
{1, 2, 6, 5}, {9, 10, 14, 13}, {17, 18, 22, 21}, {25, 26, 30, 29},
{2, 3, 7, 6}, {10, 11, 15, 14}, {18, 19, 23, 22}, {26, 27, 31, 30},
{3, 0, 4, 7}, {11, 8, 12, 15}, {19, 16, 20, 23}, {27, 24, 28, 31}
};
GLdouble *n[21] = {_Z, Z, Z, Z, Z, X, X, X, X, Y, Y, Y, Y, _X, _X, _X, _X, _Y, _Y, _Y, _Y};

void init() {
	GLdouble x = 1, y = 1, z = 0;
	GLint dir[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
	int l = 0;
	for (int i = -1; ++i < 4;) {
		for (int j = -1; ++j < 2;) {
			for (int k = -1; ++k < 4;) {
				v[l][0] = dir[k][0] * x;
				v[l][1] = dir[k][1] * y;
				v[l][2] = z;
				l++;
			}
			z += x;
		}
		z -= x;
		x *= 0.75;
		y *= 0.75;
	}
	for (int i = -1; ++i < 2;) {
		glLightfv(GL_LIGHT0 | i, GL_POSITION, lightpos[i]);
		glLightfv(GL_LIGHT0 | i, GL_DIFFUSE, light_diffuse[i]);
		glEnable(GL_LIGHT0 | i);
	}
	glEnable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50, (width * 1.0) / height, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW_MATRIX);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glTranslatef(0, 0, -1);
}

void draw_quad(GLint index) {
	glBegin(GL_QUADS);
		glNormal3dv(n[index]);
	for (int i = -1; ++i < 4;)
		glVertex3dv(v[faces[index][i]]);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);
	glRotated(1, 0, 1, 2);
	for (int i = -1; ++i < 21; draw_quad(i));
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Tower!!!");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}