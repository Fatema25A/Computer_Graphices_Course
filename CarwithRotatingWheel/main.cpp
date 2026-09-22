#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <cmath>

using namespace std;

float wheelAngle = 0.0f;
float carMove = -2.8f;

// Draw a filled circle
void drawCircle(float cx, float cy, float r)
{
    glBegin(GL_POLYGON);

    for (int i = 0; i < 100; i++)
    {
        float theta = 2.0f * 3.1416f * i / 100;

        float x = r * cos(theta);
        float y = r * sin(theta);

        glVertex2f(cx + x, cy + y);
    }

    glEnd();
}

// Draw a wheel with rotating spokes
void drawWheel(float cx, float cy, float r)
{
    // Outer black wheel
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(cx, cy, r);

    // Inner gray hub
    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(cx, cy, r * 0.3f);

    // Rotating spokes
    glPushMatrix();

    // Move the rotation point to the wheel center
    glTranslatef(cx, cy, 0.0f);

    // Rotate around the Z-axis
    glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINES);

        // Horizontal spoke
        glVertex2f(-r, 0.0f);
        glVertex2f(r, 0.0f);

        // Vertical spoke
        glVertex2f(0.0f, -r);
        glVertex2f(0.0f, r);

        // First diagonal spoke
        glVertex2f(-r * 0.7f, -r * 0.7f);
        glVertex2f(r * 0.7f, r * 0.7f);

        // Second diagonal spoke
        glVertex2f(-r * 0.7f, r * 0.7f);
        glVertex2f(r * 0.7f, -r * 0.7f);

    glEnd();

    glPopMatrix();
}

// Draw the car
void drawCar()
{
    // Car body
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);
        glVertex2f(-0.8f, -0.1f);
        glVertex2f(0.8f, -0.1f);
        glVertex2f(0.8f, 0.3f);
        glVertex2f(-0.8f, 0.3f);
    glEnd();

    // Upper part of the car
    glColor3f(0.8f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, 0.3f);
        glVertex2f(0.3f, 0.3f);
        glVertex2f(0.1f, 0.6f);
        glVertex2f(-0.25f, 0.6f);
    glEnd();

    // Window
    glColor3f(0.5f, 0.8f, 1.0f);

    glBegin(GL_POLYGON);
        glVertex2f(-0.32f, 0.33f);
        glVertex2f(0.22f, 0.33f);
        glVertex2f(0.08f, 0.55f);
        glVertex2f(-0.20f, 0.55f);
    glEnd();

    // Wheels
    drawWheel(-0.45f, -0.1f, 0.18f);
    drawWheel(0.45f, -0.1f, 0.18f);
}

// Display function
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    // Move the whole car from left to right
    glTranslatef(carMove, 0.0f, 0.0f);

    drawCar();

    glPopMatrix();

    glutSwapBuffers();
}

// Animation update function
void update(int value)
{
    // Move car to the right
    carMove += 0.02f;

    // Rotate wheels clockwise
    wheelAngle -= 5.0f;

    // Restart from the left after leaving the right side
    if (carMove > 2.8f)
    {
        carMove = -2.8f;
    }

    // Reset the wheel angle
    if (wheelAngle < -360.0f)
    {
        wheelAngle = 0.0f;
    }

    glutPostRedisplay();

    // Call update again after 20 milliseconds
    glutTimerFunc(20, update, 0);
}

// OpenGL initialization
void init()
{
    // White background
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Coordinate system
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}

// Main function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 800);

    glutCreateWindow("Moving Car with Rotating Wheels");

    init();

    glutDisplayFunc(drawScene);

    glutTimerFunc(20, update, 0);

    glutMainLoop();

    return 0;
}
