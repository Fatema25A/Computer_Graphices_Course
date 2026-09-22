#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>

using namespace std;

float bladeAngle = 0.0f;

// Function to draw the windmill
void drawWindmill()
{
    // Tower
    glColor3f(0.6f, 0.3f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, -1.0f);
        glVertex2f(0.1f, -1.0f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(-0.2f, 0.2f);
    glEnd();

    // Hub (center of blades)
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
        glVertex2f(0.0f, 0.2f);
    glEnd();

    // Rotating blades
    glPushMatrix();
        glTranslatef(0.0f, 0.2f, 0.0f);   // move to center of blades
        glRotatef(bladeAngle, 0.0f, 0.0f, 1.0f);

        glColor3f(1.0f, 0.0f, 0.0f);

        // Blade 1
        glBegin(GL_POLYGON);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.7f, 0.05f);
            glVertex2f(0.7f, -0.05f);
        glEnd();

        // Blade 2
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_POLYGON);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.7f, 0.05f);
            glVertex2f(0.7f, -0.05f);
        glEnd();

        // Blade 3
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_POLYGON);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.7f, 0.05f);
            glVertex2f(0.7f, -0.05f);
        glEnd();

        // Blade 4
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_POLYGON);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.7f, 0.05f);
            glVertex2f(0.7f, -0.05f);
        glEnd();

    glPopMatrix();
}

// Display function
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawWindmill();

    glutSwapBuffers();
}

// Animation update
void update(int value)
{
    bladeAngle -= 2.0f;   // rotate clockwise

    if (bladeAngle < -360.0f)
    {
        bladeAngle = 0.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

// Initialization
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}

// Main function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Windmill with Rotating Blades");

    init();
    glutDisplayFunc(drawScene);
    glutTimerFunc(20, update, 0);

    glutMainLoop();
    return 0;
}
