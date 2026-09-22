#include <windows.h>
#include <GL/glut.h>
#include <math.h>

float cloudX = -60;
float birdX = -50;

bool nightMode = false;

float timerValue = 0;

const float PI = 3.1415926f;


// CIRCLE

void circle(float cx, float cy, float r)
{
    glBegin(GL_POLYGON);

    for (int i = 0; i < 100; i++)
    {
        float angle = 2.0f * PI * i / 100.0f;

        glVertex2f(
            cx + r * cos(angle),
            cy + r * sin(angle)
        );
    }

    glEnd();
}

void pond()
{
    glColor3f(0.2f, 0.6f, 0.9f);

    glPushMatrix();

    glScalef(2.8f, 1.0f, 1.0f);

    circle(0, 0, 6);

    glPopMatrix();
}
void drawPond()
{
    glPushMatrix();

    glTranslatef(18, -25, 0);

    pond();

    glPopMatrix();
}
// RECTANGLE

void rectangle(float x1, float y1, float x2, float y2)
{
    glBegin(GL_QUADS);

    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);

    glEnd();
}


// SKY

void drawSky()
{
    if (nightMode)
        glColor3f(0.05f, 0.10f, 0.25f);

    else
        glColor3f(0.4f, 0.8f, 1.0f);


    rectangle(-50, 0, 50, 50);
}


// SUN / MOON

void drawSunMoon()
{
    if (nightMode)
        glColor3f(0.9f, 0.9f, 0.9f);

    else
        glColor3f(1.0f, 1.0f, 0.0f);


    circle(30, 35, 5);
}


// GROUND

void drawGround()
{
    if (nightMode)
        glColor3f(0.05f, 0.25f, 0.08f);

    else
        glColor3f(0.2f, 0.7f, 0.2f);


    rectangle(-50, -50, 50, 0);
}


// HOUSE

void house()
{
    // Wall
    glColor3f(0.8f, 0.5f, 0.3f);
    rectangle(0, 0, 20, 15);


    // Roof
    glColor3f(0.6f, 0.1f, 0.1f);

    glBegin(GL_TRIANGLES);

    glVertex2f(-3, 15);
    glVertex2f(10, 27);
    glVertex2f(23, 15);

    glEnd();


    // Door
    glColor3f(0.3f, 0.15f, 0.05f);
    rectangle(7, 0, 13, 10);


    // Window
    glColor3f(0.6f, 0.9f, 1.0f);
    rectangle(2, 6, 6, 10);
}


void drawHouse()
{
    glPushMatrix();

    glTranslatef(-10, -10, 0);

    house();

    glPopMatrix();
}


// TREE

void tree()
{
    // Trunk
    glColor3f(0.4f, 0.2f, 0.05f);
    rectangle(-2, 0, 2, 15);


    // Leaves
    glColor3f(0.0f, 0.5f, 0.1f);

    circle(0, 18, 7);
    circle(-5, 15, 5);
    circle(5, 15, 5);
}


void drawTrees()
{
    glPushMatrix();
    glTranslatef(-35, -10, 0);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-25, -10, 0);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25, -10, 0);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(35, -10, 0);
    tree();
    glPopMatrix();
}


// CLOUD

void cloud()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    circle(0, 0, 4);
    circle(5, 2, 5);
    circle(10, 0, 4);
}


void drawCloud()
{
    glPushMatrix();

    glTranslatef(cloudX, 30, 0);

    cloud();

    glPopMatrix();
}


// BIRD

void bird()
{
    glColor3f(0.0f, 0.0f, 0.0f);

    glLineWidth(2);

    glBegin(GL_LINES);

    glVertex2f(0, 0);
    glVertex2f(3, 2);

    glVertex2f(3, 2);
    glVertex2f(6, 0);

    glEnd();
}


void drawBird()
{
    glPushMatrix();

    glTranslatef(birdX, 25, 0);

    bird();

    glPopMatrix();
}


// DISPLAY

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    drawSky();

    drawSunMoon();

    drawGround();

    drawHouse();

    drawTrees();drawPond();

    drawCloud();

    drawBird();


    glutSwapBuffers();
}


// UPDATE

void update(int value)
{
    // Cloud movement
    cloudX += 0.15f;

    if (cloudX > 50)
        cloudX = -60;


    // Bird movement
    birdX += 0.25f;

    if (birdX > 50)
        birdX = -60;


    // Automatic day/night
    timerValue += 0.02f;

    if (timerValue > 10)
    {
        nightMode = !nightMode;
        timerValue = 0;
    }


    glutPostRedisplay();

    glutTimerFunc(20, update, 0);
}


// INITIALIZATION

void init()
{
    glClearColor(0, 0, 0, 1);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(-50, 50, -50, 50);

    glMatrixMode(GL_MODELVIEW);
}


// MAIN

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 600);

    glutCreateWindow("Simple Day Night Scenario");

    init();

    glutDisplayFunc(display);

    glutTimerFunc(20, update, 0);

    glutMainLoop();

    return 0;
}
