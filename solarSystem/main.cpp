#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

const float PI = 3.1415926f;


// ================= GLOBAL VARIABLES =================

float mercuryAngle = 0;
float venusAngle = 0;
float earthAngle = 0;
float marsAngle = 0;
float moonAngle = 0;

float speed = 1.0f;

bool animationRunning = true;

int viewingMode = 1;
int selectedPlanet = 0;


// ================= BASIC CIRCLE =================

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


// ================= ORBIT =================

void orbit(float radius)
{
    glColor3f(0.4f, 0.4f, 0.4f);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 100; i++)
    {
        float angle = 2.0f * PI * i / 100.0f;

        glVertex2f(
            radius * cos(angle),
            radius * sin(angle)
        );
    }

    glEnd();
}


// ================= SUN =================

void drawSun()
{
    glColor3f(1.0f, 0.7f, 0.0f);

    circle(0, 0, 7);
}


// ================= MERCURY =================

void drawMercury()
{
    glPushMatrix();

    glRotatef(mercuryAngle, 0, 0, 1);

    glTranslatef(12, 0, 0);

    if (selectedPlanet == 1)
        glColor3f(1, 1, 1);
    else
        glColor3f(0.6f, 0.6f, 0.6f);

    circle(0, 0, 2);

    glPopMatrix();
}


// ================= VENUS =================

void drawVenus()
{
    glPushMatrix();

    glRotatef(venusAngle, 0, 0, 1);

    glTranslatef(20, 0, 0);

    if (selectedPlanet == 2)
        glColor3f(1, 1, 1);
    else
        glColor3f(0.9f, 0.5f, 0.1f);

    circle(0, 0, 3);

    glPopMatrix();
}


// ================= EARTH =================

void earth()
{
    if (selectedPlanet == 3)
        glColor3f(1, 1, 1);
    else
        glColor3f(0.1f, 0.4f, 1.0f);

    circle(0, 0, 3.5f);


    // Moon orbit
    glColor3f(0.3f, 0.3f, 0.3f);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 50; i++)
    {
        float angle = 2.0f * PI * i / 50.0f;

        glVertex2f(
            6 * cos(angle),
            6 * sin(angle)
        );
    }

    glEnd();


    // Moon
    glPushMatrix();

    glRotatef(moonAngle, 0, 0, 1);
    glTranslatef(6, 0, 0);

    glColor3f(0.8f, 0.8f, 0.8f);

    circle(0, 0, 1.2f);

    glPopMatrix();
}


void drawEarth()
{
    glPushMatrix();

    glRotatef(earthAngle, 0, 0, 1);

    glTranslatef(30, 0, 0);

    earth();

    glPopMatrix();
}


// ================= MARS =================

void drawMars()
{
    glPushMatrix();

    glRotatef(marsAngle, 0, 0, 1);

    glTranslatef(42, 0, 0);

    if (selectedPlanet == 4)
        glColor3f(1, 1, 1);
    else
        glColor3f(0.8f, 0.2f, 0.1f);

    circle(0, 0, 3);

    glPopMatrix();
}


// ================= PLANET INFORMATION =================

void showPlanetInfo()
{
    if (selectedPlanet == 1)
        printf("Mercury: Closest planet to the Sun.\n");

    else if (selectedPlanet == 2)
        printf("Venus: Second planet from the Sun.\n");

    else if (selectedPlanet == 3)
        printf("Earth: Our planet. It has one Moon.\n");

    else if (selectedPlanet == 4)
        printf("Mars: Known as the Red Planet.\n");
}


// ================= SCENE =================

void drawSolarSystem()
{
    drawSun();


    // Orbits
    orbit(12);
    orbit(20);
    orbit(30);
    orbit(42);


    // Planets
    drawMercury();
    drawVenus();
    drawEarth();
    drawMars();
}


// ================= DISPLAY =================

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();


    // Viewing mode
    if (viewingMode == 2)
    {
        glScalef(1.3f, 1.3f, 1);
    }


    drawSolarSystem();


    glutSwapBuffers();
}


// ================= UPDATE =================

void update(int value)
{
    if (animationRunning)
    {
        mercuryAngle += 2.0f * speed;

        venusAngle += 1.5f * speed;

        earthAngle += 1.0f * speed;

        marsAngle += 0.7f * speed;

        moonAngle += 3.0f * speed;


        if (mercuryAngle > 360)
            mercuryAngle = 0;

        if (venusAngle > 360)
            venusAngle = 0;

        if (earthAngle > 360)
            earthAngle = 0;

        if (marsAngle > 360)
            marsAngle = 0;

        if (moonAngle > 360)
            moonAngle = 0;
    }


    glutPostRedisplay();

    glutTimerFunc(20, update, 0);
}


// ================= RESET =================

void resetSimulation()
{
    mercuryAngle = 0;
    venusAngle = 0;
    earthAngle = 0;
    marsAngle = 0;
    moonAngle = 0;

    speed = 1.0f;

    animationRunning = true;

    viewingMode = 1;

    selectedPlanet = 0;

    printf("Simulation Reset\n");
}


// ================= KEYBOARD =================

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        // Start / Pause
        case 's':
        case 'S':

            animationRunning = !animationRunning;

            break;


        // Increase speed
        case '+':

            speed += 0.2f;

            printf("Speed: %.1f\n", speed);

            break;


        // Decrease speed
        case '-':

            speed -= 0.2f;

            if (speed < 0.2f)
                speed = 0.2f;

            printf("Speed: %.1f\n", speed);

            break;


        // Change viewing mode
        case 'v':
        case 'V':

            if (viewingMode == 1)
                viewingMode = 2;

            else
                viewingMode = 1;

            break;


        // Mercury
        case '1':

            selectedPlanet = 1;

            showPlanetInfo();

            break;


        // Venus
        case '2':

            selectedPlanet = 2;

            showPlanetInfo();

            break;


        // Earth
        case '3':

            selectedPlanet = 3;

            showPlanetInfo();

            break;


        // Mars
        case '4':

            selectedPlanet = 4;

            showPlanetInfo();

            break;


        // Reset
        case 'r':
        case 'R':

            resetSimulation();

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
        animationRunning = !animationRunning;
    }
}


// ================= INITIALIZATION =================

void init()
{
    glClearColor(0.02f, 0.02f, 0.08f, 1);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(-55, 55, -55, 55);

    glMatrixMode(GL_MODELVIEW);
}


// ================= MAIN =================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 700);

    glutInitWindowPosition(100, 50);

    glutCreateWindow("Interactive Solar System");

    init();

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    glutMouseFunc(mouse);

    glutTimerFunc(20, update, 0);

    glutMainLoop();

    return 0;
}
