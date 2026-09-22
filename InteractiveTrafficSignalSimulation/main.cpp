#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

const float PI = 3.1415926f;

// --------------------------------------------------
// GLOBAL VARIABLES
// --------------------------------------------------

float car1X = -90.0f;
float car2X = 90.0f;

float car3Y = -90.0f;
float car4Y = 90.0f;

float carSpeed = 0.4f;

// 0 = Horizontal Green
// 1 = Vertical Green
int signalState = 0;

bool animationRunning = true;


// --------------------------------------------------
// BASIC SHAPES
// --------------------------------------------------

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


// --------------------------------------------------
// BACKGROUND
// --------------------------------------------------

void drawBackground()
{
    glColor3f(0.25f, 0.65f, 0.25f);

    rectangle(-100, -100, 100, 100);
}


// --------------------------------------------------
// ROAD
// --------------------------------------------------

void drawRoad()
{
    glColor3f(0.25f, 0.25f, 0.25f);

    // Horizontal road
    rectangle(-100, -25, 100, 25);

    // Vertical road
    rectangle(-25, -100, 25, 100);


    // Horizontal road divider
    glColor3f(1.0f, 1.0f, 1.0f);

    for (int x = -100; x < 100; x += 16)
    {
        rectangle(x, -1, x + 8, 1);
    }


    // Vertical road divider
    for (int y = -100; y < 100; y += 16)
    {
        rectangle(-1, y, 1, y + 8);
    }
}


// --------------------------------------------------
// STOP LINES
// --------------------------------------------------

void drawStopLines()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    // Left side
    rectangle(-32, -24, -30, -3);

    // Right side
    rectangle(30, 3, 32, 24);

    // Bottom side
    rectangle(3, -32, 24, -30);

    // Top side
    rectangle(-24, 30, -3, 32);
}


// --------------------------------------------------
// HORIZONTAL SIGNAL
// --------------------------------------------------

void horizontalSignal()
{
    // Pole
    glColor3f(0.15f, 0.15f, 0.15f);
    rectangle(-1, -12, 1, 0);

    // Box
    rectangle(-4, 0, 4, 18);


    // RED
    if (signalState == 1)
        glColor3f(1.0f, 0.0f, 0.0f);
    else
        glColor3f(0.25f, 0.0f, 0.0f);

    circle(0, 14, 2.5f);


    // YELLOW
    glColor3f(0.35f, 0.30f, 0.0f);
    circle(0, 9, 2.5f);


    // GREEN
    if (signalState == 0)
        glColor3f(0.0f, 1.0f, 0.0f);
    else
        glColor3f(0.0f, 0.25f, 0.0f);

    circle(0, 4, 2.5f);
}


void drawHorizontalSignal()
{
    glPushMatrix();

    glTranslatef(-38, 30, 0);

    horizontalSignal();

    glPopMatrix();
}


// --------------------------------------------------
// VERTICAL SIGNAL
// --------------------------------------------------

void verticalSignal()
{
    // Pole
    glColor3f(0.15f, 0.15f, 0.15f);
    rectangle(-1, -12, 1, 0);

    // Box
    rectangle(-4, 0, 4, 18);


    // RED
    if (signalState == 0)
        glColor3f(1.0f, 0.0f, 0.0f);
    else
        glColor3f(0.25f, 0.0f, 0.0f);

    circle(0, 14, 2.5f);


    // YELLOW
    glColor3f(0.35f, 0.30f, 0.0f);
    circle(0, 9, 2.5f);


    // GREEN
    if (signalState == 1)
        glColor3f(0.0f, 1.0f, 0.0f);
    else
        glColor3f(0.0f, 0.25f, 0.0f);

    circle(0, 4, 2.5f);
}


void drawVerticalSignal()
{
    glPushMatrix();

    glTranslatef(38, 30, 0);

    verticalSignal();

    glPopMatrix();
}


// --------------------------------------------------
// CAR
// --------------------------------------------------

void car(float r, float g, float b)
{
    // Main body
    glColor3f(r, g, b);
    rectangle(-10, -4, 10, 4);


    // Upper body
    glColor3f(r, g, b);

    glBegin(GL_QUADS);

    glVertex2f(-5, 4);
    glVertex2f(5, 4);
    glVertex2f(3, 9);
    glVertex2f(-3, 9);

    glEnd();


    // Windows
    glColor3f(0.55f, 0.85f, 1.0f);

    rectangle(-3.5f, 5, -0.5f, 8);
    rectangle(0.5f, 5, 3.5f, 8);


    // Wheels
    glColor3f(0.05f, 0.05f, 0.05f);

    circle(-6, -5, 2);
    circle(6, -5, 2);
}


// --------------------------------------------------
// CAR 1 - LEFT TO RIGHT
// --------------------------------------------------

void drawCar1()
{
    glPushMatrix();

    glTranslatef(car1X, -13, 0);

    car(0.90f, 0.10f, 0.10f);

    glPopMatrix();
}


// --------------------------------------------------
// CAR 2 - RIGHT TO LEFT
// --------------------------------------------------

void drawCar2()
{
    glPushMatrix();

    glTranslatef(car2X, 13, 0);

    glRotatef(180, 0, 0, 1);

    car(0.10f, 0.35f, 0.90f);

    glPopMatrix();
}


// --------------------------------------------------
// CAR 3 - BOTTOM TO TOP
// --------------------------------------------------

void drawCar3()
{
    glPushMatrix();

    glTranslatef(13, car3Y, 0);

    glRotatef(90, 0, 0, 1);

    car(0.95f, 0.65f, 0.05f);

    glPopMatrix();
}


// --------------------------------------------------
// CAR 4 - TOP TO BOTTOM
// --------------------------------------------------

void drawCar4()
{
    glPushMatrix();

    glTranslatef(-13, car4Y, 0);

    glRotatef(-90, 0, 0, 1);

    car(0.55f, 0.10f, 0.75f);

    glPopMatrix();
}


// --------------------------------------------------
// DISPLAY
// --------------------------------------------------

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    drawBackground();

    drawRoad();

    drawStopLines();


    drawHorizontalSignal();

    drawVerticalSignal();


    drawCar1();

    drawCar2();

    drawCar3();

    drawCar4();


    glutSwapBuffers();
}


// --------------------------------------------------
// UPDATE
// --------------------------------------------------

void update(int value)
{
    if (animationRunning)
    {
        // ------------------------------------------
        // CAR 1 : LEFT TO RIGHT
        // ------------------------------------------

        if (signalState == 0 || car1X > -40)
        {
            car1X += carSpeed;
        }
        else
        {
            if (car1X < -40)
            {
                car1X += carSpeed;

                if (car1X > -40)
                    car1X = -40;
            }
        }


        if (car1X > 110)
            car1X = -110;


        // ------------------------------------------
        // CAR 2 : RIGHT TO LEFT
        // ------------------------------------------

        if (signalState == 0 || car2X < 40)
        {
            car2X -= carSpeed;
        }
        else
        {
            if (car2X > 40)
            {
                car2X -= carSpeed;

                if (car2X < 40)
                    car2X = 40;
            }
        }


        if (car2X < -110)
            car2X = 110;


        // ------------------------------------------
        // CAR 3 : BOTTOM TO TOP
        // ------------------------------------------

        if (signalState == 1 || car3Y > -40)
        {
            car3Y += carSpeed;
        }
        else
        {
            if (car3Y < -40)
            {
                car3Y += carSpeed;

                if (car3Y > -40)
                    car3Y = -40;
            }
        }


        if (car3Y > 110)
            car3Y = -110;


        // ------------------------------------------
        // CAR 4 : TOP TO BOTTOM
        // ------------------------------------------

        if (signalState == 1 || car4Y < 40)
        {
            car4Y -= carSpeed;
        }
        else
        {
            if (car4Y > 40)
            {
                car4Y -= carSpeed;

                if (car4Y < 40)
                    car4Y = 40;
            }
        }


        if (car4Y < -110)
            car4Y = 110;
    }


    glutPostRedisplay();

    glutTimerFunc(20, update, 0);
}


// --------------------------------------------------
// KEYBOARD
// --------------------------------------------------

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
        // Horizontal road green
        case 'h':
        case 'H':

            signalState = 0;

            break;


        // Vertical road green
        case 'v':
        case 'V':

            signalState = 1;

            break;


        // Pause / Resume
        case 'p':
        case 'P':

            animationRunning = !animationRunning;

            break;


        // Increase speed
        case '+':

            carSpeed += 0.1f;

            if (carSpeed > 1.5f)
                carSpeed = 1.5f;

            break;


        // Decrease speed
        case '-':

            carSpeed -= 0.1f;

            if (carSpeed < 0.1f)
                carSpeed = 0.1f;

            break;


        // Exit
        case 27:

            exit(0);

            break;
    }


    glutPostRedisplay();
}


// --------------------------------------------------
// MOUSE
// --------------------------------------------------

void handleMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (signalState == 0)
            signalState = 1;
        else
            signalState = 0;
    }


    glutPostRedisplay();
}


// --------------------------------------------------
// INITIALIZATION
// --------------------------------------------------

void init()
{
    glClearColor(0.60f, 0.85f, 1.0f, 1.0f);


    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();


    gluOrtho2D(-100,100,-100,100);


    glMatrixMode(GL_MODELVIEW);
}


// --------------------------------------------------
// MAIN
// --------------------------------------------------

int main(int argc, char** argv)
{
    glutInit(&argc, argv);


    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB
    );


    glutInitWindowSize(900, 700);

    glutInitWindowPosition(100, 50);


    glutCreateWindow(
        "Interactive Traffic Signal Simulation"
    );


    init();


    glutDisplayFunc(display);

    glutKeyboardFunc(handleKeypress);

    glutMouseFunc(handleMouse);


    glutTimerFunc(20,update,0);


    glutMainLoop();


    return 0;
}
