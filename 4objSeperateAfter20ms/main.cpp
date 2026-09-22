#include<windows.h>
#include <GL/glut.h>

float moveLeft = 0.0f;
float moveRight = 0.0f;
float moveUp = 0.0f;
float moveDown = 0.0f;


// Object 1: Triangle
// A=(-0.8,-0.3)
// B=(-0.4,-0.3)
// C=(-0.6,0.2)

void object1()
{
    glPushMatrix();

    glTranslatef(moveLeft, 0.0f, 0.0f);

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.8f, -0.3f);
        glVertex2f(-0.4f, -0.3f);
        glVertex2f(-0.6f,  0.2f);
    glEnd();

    glPopMatrix();
}


// Object 2: Square
// D=(-0.2,-0.3)
// E=(0.2,-0.3)
// F=(0.2,0.1)
// G=(-0.2,0.1)

void object2()
{
    glPushMatrix();

    glTranslatef(moveRight, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.3f);
        glVertex2f( 0.2f, -0.3f);
        glVertex2f( 0.2f,  0.1f);
        glVertex2f(-0.2f,  0.1f);
    glEnd();

    glPopMatrix();
}


// Object 3: Triangle
// H=(0.4,-0.3)
// I=(0.8,-0.3)
// J=(0.6,0.2)

void object3()
{
    glPushMatrix();

    glTranslatef(0.0f, moveUp, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLES);
        glVertex2f(0.4f, -0.3f);
        glVertex2f(0.8f, -0.3f);
        glVertex2f(0.6f,  0.2f);
    glEnd();

    glPopMatrix();
}


// Object 4: Rectangle
// K=(-0.3,0.4)
// L=(0.3,0.4)
// M=(0.3,0.7)
// N=(-0.3,0.7)

void object4()
{
    glPushMatrix();

    glTranslatef(0.0f, moveDown, 0.0f);

    glColor3f(1.0f, 0.5f, 0.0f);

    glBegin(GL_QUADS);
        glVertex2f(-0.3f, 0.4f);
        glVertex2f( 0.3f, 0.4f);
        glVertex2f( 0.3f, 0.7f);
        glVertex2f(-0.3f, 0.7f);
    glEnd();

    glPopMatrix();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    object1();
    object2();
    object3();
    object4();

    glutSwapBuffers();
}


// Keyboard control
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        // A = Object 1 moves LEFT
        case 'a':
        case 'A':

            moveLeft -= 0.1f;

            if(moveLeft < -0.6f)
                moveLeft = 1.8f;

            break;


        // D = Object 2 moves RIGHT
        case 'd':
        case 'D':

            moveRight += 0.1f;

            if(moveRight > 1.2f)
                moveRight = -1.2f;

            break;


        // W = Object 3 moves UP
        case 'w':
        case 'W':

            moveUp += 0.1f;

            if(moveUp > 1.3f)
                moveUp = -1.2f;

            break;


        // S = Object 4 moves DOWN
        case 's':
        case 'S':

            moveDown -= 0.1f;

            if(moveDown < -1.7f)
                moveDown = 0.6f;

            break;
    }

    glutPostRedisplay();
}


void init()
{
    // White background
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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

    glutCreateWindow("Four Objects Keyboard Animation");

    init();

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
