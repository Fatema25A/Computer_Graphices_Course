#include <windows.h>
#include <GL/glut.h>
#include <math.h>

const float PI = 3.1415926f;

int currentScene = 1;

float cloudX = -50;
float birdX = -50;
float boatX = -40;

float cloudSpeed = 0.15f;

bool boatMoving = true;

float sceneTimer = 0;


// ================= BASIC SHAPES =================

void rectangle(float x1, float y1, float x2, float y2)
{
    glBegin(GL_QUADS);

    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);

    glEnd();
}


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


// ================= HOUSE =================

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
    glColor3f(0.5f, 0.8f, 1.0f);
    rectangle(2, 6, 6, 10);
}


void drawHouse(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    house();

    glPopMatrix();
}


// ================= TREE =================

void tree()
{
    glColor3f(0.4f, 0.2f, 0.05f);
    rectangle(-2, 0, 2, 15);

    glColor3f(0.0f, 0.5f, 0.1f);

    circle(0, 18, 7);
    circle(-5, 15, 5);
    circle(5, 15, 5);
}


void drawTree(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    tree();

    glPopMatrix();
}


// ================= CLOUD =================

void cloud()
{
    glColor3f(1, 1, 1);

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


// ================= BIRD =================

void bird()
{
    glColor3f(0, 0, 0);

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


// ================= BOAT =================

void boat()
{
    glColor3f(0.4f, 0.2f, 0.05f);

    glBegin(GL_POLYGON);

    glVertex2f(-8, 0);
    glVertex2f(8, 0);
    glVertex2f(5, -4);
    glVertex2f(-5, -4);

    glEnd();


    // Mast
    glColor3f(0.2f, 0.1f, 0.05f);

    glBegin(GL_LINES);

    glVertex2f(0, 0);
    glVertex2f(0, 12);

    glEnd();


    // Sail
    glColor3f(1.0f, 0.8f, 0.1f);

    glBegin(GL_TRIANGLES);

    glVertex2f(0, 11);
    glVertex2f(0, 2);
    glVertex2f(7, 5);

    glEnd();
}


void drawBoat()
{
    glPushMatrix();

    glTranslatef(boatX, -25, 0);

    boat();

    glPopMatrix();
}


// =================================================
//                  SCENARIO 1
//                   DAY VILLAGE
// =================================================

void scenario1()
{
    // Sky
    glColor3f(0.4f, 0.8f, 1.0f);
    rectangle(-50, 0, 50, 50);


    // Ground
    glColor3f(0.2f, 0.7f, 0.2f);
    rectangle(-50, -50, 50, 0);


    // Sun
    glColor3f(1, 1, 0);
    circle(30, 35, 5);


    // House
    drawHouse(-10, -10);


    // Trees
    drawTree(-35, -10);
    drawTree(-25, -10);
    drawTree(25, -10);
    drawTree(35, -10);


    // Cloud
    drawCloud();


    // Bird
    drawBird();
}


// =================================================
//                  SCENARIO 2
//                  NIGHT RIVER
// =================================================

void scenario2()
{
    // Night sky
    glColor3f(0.05f, 0.08f, 0.25f);
    rectangle(-50, -10, 50, 50);


    // Moon
    glColor3f(0.9f, 0.9f, 0.8f);
    circle(30, 35, 5);


    // Stars
    glColor3f(1, 1, 1);

    glPointSize(4);

    glBegin(GL_POINTS);

    glVertex2f(-35, 35);
    glVertex2f(-20, 42);
    glVertex2f(-5, 30);
    glVertex2f(10, 40);
    glVertex2f(20, 25);
    glVertex2f(40, 45);

    glEnd();


    // Ground
    glColor3f(0.05f, 0.25f, 0.08f);
    rectangle(-50, -15, 50, -10);


    // River
    glColor3f(0.05f, 0.3f, 0.6f);
    rectangle(-50, -50, 50, -15);


    // House
    drawHouse(-35, -10);


    // Tree
    drawTree(30, -10);


    // Moving boat
    drawBoat();
}


// ================= DISPLAY =================

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    if (currentScene == 1)
        scenario1();

    else
        scenario2();


    glutSwapBuffers();
}


// ================= ANIMATION =================

void update(int value)
{
    // Scenario 1 animations
    cloudX += cloudSpeed;

    if (cloudX > 50)
        cloudX = -60;


    birdX += 0.25f;

    if (birdX > 50)
        birdX = -60;


    // Scenario 2 animation
    if (boatMoving)
    {
        boatX += 0.15f;

        if (boatX > 50)
            boatX = -50;
    }


    // Automatic scenario change
    sceneTimer += 0.02f;

    if (sceneTimer > 10)
    {
        if (currentScene == 1)
            currentScene = 2;

        else
            currentScene = 1;

        sceneTimer = 0;
    }


    glutPostRedisplay();

    glutTimerFunc(20, update, 0);
}


// ================= KEYBOARD =================

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        // Scenario 1
        case '1':
            currentScene = 1;
            sceneTimer = 0;
            break;


        // Scenario 2
        case '2':
            currentScene = 2;
            sceneTimer = 0;
            break;


        // Switch scenario
        case ' ':

            if (currentScene == 1)
                currentScene = 2;

            else
                currentScene = 1;

            sceneTimer = 0;

            break;


        // Cloud speed
        case 'c':
        case 'C':

            if (currentScene == 1)
                cloudSpeed += 0.1f;

            break;


        // Start / stop boat
        case 'b':
        case 'B':

            if (currentScene == 2)
                boatMoving = !boatMoving;

            break;


        // Exit
        case 27:
            exit(0);
            break;
    }


    glutPostRedisplay();
}


// ================= MOUSE =================

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON &&
        state == GLUT_DOWN)
    {
        if (currentScene == 1)
            currentScene = 2;

        else
            currentScene = 1;

        sceneTimer = 0;

        glutPostRedisplay();
    }
}


// ================= INITIALIZATION =================

void init()
{
    glClearColor(0, 0, 0, 1);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(-50, 50, -50, 50);

    glMatrixMode(GL_MODELVIEW);
}


// ================= MAIN =================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 600);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("Two Merged Animated Scenarios");

    init();

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    glutMouseFunc(mouse);

    glutTimerFunc(20, update, 0);

    glutMainLoop();

    return 0;
}
