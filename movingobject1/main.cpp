#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>

using namespace std;

float moveBox1 = 0.0f;
float moveBox2 = 0.0f;

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // First box moves to the right
    glPushMatrix();

    glTranslatef(moveBox1, 0.5f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f( 0.2f, -0.2f);
        glVertex2f( 0.2f,  0.2f);
        glVertex2f(-0.2f,  0.2f);
    glEnd();

    glPopMatrix();

    // Second box moves to the left
    glPushMatrix();

    glTranslatef(moveBox2, -0.5f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f( 0.2f, -0.2f);
        glVertex2f( 0.2f,  0.2f);
        glVertex2f(-0.2f,  0.2f);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void update(int value)
{
    // Red box moves right
    moveBox1 += 0.02f;

    // Blue box moves left
    moveBox2 -= 0.02f;

    // Return the red box to the left side
    if (moveBox1 > 2.2f)
    {
        moveBox1 = -2.2f;
    }

    // Return the blue box to the right side
    if (moveBox2 < -2.2f)
    {
        moveBox2 = 2.2f;
    }

    glutPostRedisplay();

    glutTimerFunc(20, update, 0);
}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 800);

    glutCreateWindow("Two Boxes Moving in Opposite Directions");

    init();

    glutDisplayFunc(drawScene);

    glutTimerFunc(20, update, 0);

    glutMainLoop();

    return 0;
}
