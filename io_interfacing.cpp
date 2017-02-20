#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

void rand_color() {
    GLdouble c[3];
    for (int i = -1; ++i < 3; c[i] = 1.0 / (1 + rand() & 3));
    glColor3dv(c);
}

void display() {}

/*
void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}
*/

void draw_square(int x, int y, int size) {
    glBegin(GL_QUADS);
    rand_color();
    glVertex2i(x - size, y - size);
    rand_color();
    glVertex2i(x + size, y - size);
    rand_color();
    glVertex2i(x + size, y + size);
    rand_color();
    glVertex2i(x - size, y + size);
    glEnd();
}

void draw_triangle(int x, int y, int size) {
    glBegin(GL_TRIANGLES);
    rand_color();
    glVertex2i(x - size, y - size * 2 / 3);
    rand_color();
    glVertex2i(x + size, y - size * 2 / 3);
    rand_color();
    glVertex2i(x, y + size);
    glEnd();
}

void draw_circle(int x, int y, int radius) {
    glBegin(GL_TRIANGLE_FAN);
    rand_color();
    glVertex2i(x, y);
    rand_color();
    for (int i = -1; ++i < 361;) {
        glVertex2d(x + radius * cos(i), y + radius * sin(i));
    }
    glEnd();
}

void mouse_callback(GLint button, GLint state, GLint x, GLint y) {
    if (state == GLUT_DOWN) {
        glClear(GL_COLOR_BUFFER_BIT);
        if (button == GLUT_LEFT_BUTTON)
            draw_square(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 7);
        else if (button == GLUT_RIGHT_BUTTON)
            draw_triangle(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 7);
        glFlush();
    }
}

void keyboard_callback(unsigned char key, GLint x, GLint y) {
    if (key == 'Q' || key == 'q')
        exit(0);
    if (key == '2') {
        glClear(GL_COLOR_BUFFER_BIT);
        draw_circle(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 15);
        glFlush();
    }
    if (key == '1') {
        glClear(GL_COLOR_BUFFER_BIT);
        printf("Enter the number of points: ");
        int n, k, w = glutGet(GLUT_WINDOW_WIDTH);
        scanf("%d", &n);
        if (n < 2 || n > 50)
            return;
        printf("Enter the points: ");
        glBegin(GL_LINE_STRIP);
        for (int i = -1; ++i < n;) {
            scanf("%d", &k);
            glVertex2i(w * i / n, k);
        }
        glEnd();
        glFlush();
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    srand(time(NULL));
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Fake Painter");
    glutDisplayFunc(display);
    // glutReshapeFunc(reshape);
    glutMouseFunc(mouse_callback);
    glutKeyboardFunc(keyboard_callback);
    init();
    glutMainLoop();
    return 0;
}