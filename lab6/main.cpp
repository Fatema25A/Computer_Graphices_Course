#include<windows.h>
#include <GL/glut.h>

bool changeColor = false;

void display()
{
    if (changeColor)
    {
        // Blue background
        glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
    }
    else
    {
        // Red background
        glClearColor(1.0f, 0.2f, 0.2f, 1.0f);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();
}

void update(int value)
{
    // Change between two colors
    changeColor = !changeColor;

    glutPostRedisplay();

    // Call update() again after 20 milliseconds
    glutTimerFunc(20, update, 0);
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Background Color Animation");

    init();

    glutDisplayFunc(display);

    // Start animation after 20 ms
    glutTimerFunc(20, update, 0);

    glutMainLoop();

    return 0;
}
