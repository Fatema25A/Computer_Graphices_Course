#include<windows.h>
#include <GL/glut.h>

// Function to draw filled triangle
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glBegin(GL_POLYGON);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();
}

// Function to draw filled rectangle / trunk
void drawRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    glBegin(GL_POLYGON);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glVertex2f(x4, y4);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // =========================
    // Tree leaves
    // =========================
    glColor3f(0.0f, 0.55f, 0.0f);

    // Top triangle
    // A = (0, 8), B = (-4, 4), C = (4, 4)
    drawTriangle(0.0f, 8.0f, -4.0f, 4.0f, 4.0f, 4.0f);

    // Middle triangle
    // D = (0, 6), E = (-4, 0), F = (4, 0)
    drawTriangle(0.0f, 6.0f, -4.0f, 0.0f, 4.0f, 0.0f);

    // Bottom triangle
    // N = (0, 2), G = (-4, -4), I = (4, -4)
    drawTriangle(0.0f, 2.0f, -4.0f, -4.0f, 4.0f, -4.0f);

    // =========================
    // Tree trunk
    // =========================
    glColor3f(0.45f, 0.22f, 0.05f);

    // L = (-0.81, -3.99)
    // M = (0.81, -3.96)
    // K = (0.75, -6)
    // J = (-0.81, -6)
    drawRectangle(
        -0.81f, -3.99f,
         0.81f, -3.96f,
         0.75f, -6.0f,
        -0.81f, -6.0f
    );

    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Tree coordinate range
    gluOrtho2D(-6, 6, -7, 9);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800, 700);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Tree Without Black Border");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
