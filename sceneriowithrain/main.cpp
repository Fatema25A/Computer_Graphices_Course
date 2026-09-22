#include <windows.h>
#include <GL/glut.h>
#include <math.h>

float rainY = 0.0f;
float waterLevel = -1.0f;


// Draw Circle
void circle(float cx, float cy, float r)
{
    glBegin(GL_POLYGON);

    for (int i = 0; i < 100; i++)
    {
        float angle = 2.0f * 3.1416f * i / 100;

        float x = r * cos(angle);
        float y = r * sin(angle);

        glVertex2f(cx + x, cy + y);
    }

    glEnd();
}


// Curvy Cloud
void cloud()
{
    glColor3f(0.5f, 0.5f, 0.5f);

    circle(-0.55f, 0.75f, 0.18f);
    circle(-0.35f, 0.82f, 0.22f);
    circle(-0.10f, 0.78f, 0.20f);

    circle(0.15f, 0.80f, 0.22f);
    circle(0.40f, 0.75f, 0.18f);
    circle(0.60f, 0.80f, 0.20f);

    // Bottom part of cloud
    glBegin(GL_QUADS);

        glVertex2f(-0.70f, 0.65f);
        glVertex2f( 0.75f, 0.65f);
        glVertex2f( 0.75f, 0.78f);
        glVertex2f(-0.70f, 0.78f);

    glEnd();
}


// Rain
void rain()
{
    glColor3f(0.0f, 0.4f, 1.0f);

    glLineWidth(2.0f);

    glBegin(GL_LINES);

        glVertex2f(-0.8f, 0.65f + rainY);
        glVertex2f(-0.8f, 0.50f + rainY);

        glVertex2f(-0.6f, 0.60f + rainY);
        glVertex2f(-0.6f, 0.45f + rainY);

        glVertex2f(-0.4f, 0.70f + rainY);
        glVertex2f(-0.4f, 0.55f + rainY);

        glVertex2f(-0.2f, 0.65f + rainY);
        glVertex2f(-0.2f, 0.50f + rainY);

        glVertex2f(0.0f, 0.70f + rainY);
        glVertex2f(0.0f, 0.55f + rainY);

        glVertex2f(0.2f, 0.60f + rainY);
        glVertex2f(0.2f, 0.45f + rainY);

        glVertex2f(0.4f, 0.70f + rainY);
        glVertex2f(0.4f, 0.55f + rainY);

        glVertex2f(0.6f, 0.60f + rainY);
        glVertex2f(0.6f, 0.45f + rainY);

        glVertex2f(0.8f, 0.70f + rainY);
        glVertex2f(0.8f, 0.55f + rainY);

    glEnd();
}


// Ground
void ground()
{
    glColor3f(0.3f, 0.7f, 0.2f);

    glBegin(GL_QUADS);

        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 1.0f, -0.65f);
        glVertex2f(-1.0f, -0.65f);

    glEnd();
}


// Tree
void tree(float x)
{
    // Trunk
    glColor3f(0.45f, 0.22f, 0.05f);

    glBegin(GL_QUADS);

        glVertex2f(x - 0.04f, -0.70f);
        glVertex2f(x + 0.04f, -0.70f);
        glVertex2f(x + 0.04f, -0.30f);
        glVertex2f(x - 0.04f, -0.30f);

    glEnd();


    // Leaves
    glColor3f(0.0f, 0.5f, 0.0f);

    circle(x, -0.20f, 0.16f);
    circle(x - 0.10f, -0.28f, 0.14f);
    circle(x + 0.10f, -0.28f, 0.14f);
}


// House
void house()
{
    // House body
    glColor3f(0.8f, 0.4f, 0.2f);

    glBegin(GL_QUADS);

        glVertex2f(-0.25f, -0.70f);
        glVertex2f( 0.25f, -0.70f);
        glVertex2f( 0.25f, -0.20f);
        glVertex2f(-0.25f, -0.20f);

    glEnd();


    // Roof
    glColor3f(0.7f, 0.1f, 0.1f);

    glBegin(GL_TRIANGLES);

        glVertex2f(-0.35f, -0.20f);
        glVertex2f( 0.35f, -0.20f);
        glVertex2f( 0.0f,   0.15f);

    glEnd();


    // Door
    glColor3f(0.3f, 0.15f, 0.0f);

    glBegin(GL_QUADS);

        glVertex2f(-0.08f, -0.70f);
        glVertex2f( 0.08f, -0.70f);
        glVertex2f( 0.08f, -0.40f);
        glVertex2f(-0.08f, -0.40f);

    glEnd();


    // Left Window
    glColor3f(0.6f, 0.9f, 1.0f);

    glBegin(GL_QUADS);

        glVertex2f(-0.20f, -0.35f);
        glVertex2f(-0.10f, -0.35f);
        glVertex2f(-0.10f, -0.25f);
        glVertex2f(-0.20f, -0.25f);

    glEnd();


    // Right Window
    glBegin(GL_QUADS);

        glVertex2f(0.10f, -0.35f);
        glVertex2f(0.20f, -0.35f);
        glVertex2f(0.20f, -0.25f);
        glVertex2f(0.10f, -0.25f);

    glEnd();
}


// Flood Water
void flood()
{
    glColor3f(0.0f, 0.3f, 0.8f);

    glBegin(GL_QUADS);

        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);

        glVertex2f( 1.0f, waterLevel);
        glVertex2f(-1.0f, waterLevel);

    glEnd();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    ground();

    // Trees
    tree(-0.75f);
    tree(0.70f);

    house();

    rain();

    cloud();

    // Draw water last so it covers the landscape
    flood();

    glutSwapBuffers();
}


void update(int value)
{
    // Rain movement
    rainY -= 0.05f;

    if (rainY < -1.7f)
    {
        rainY = 0.0f;
    }


    // Flood gradually rises
    waterLevel += 0.002f;

    // Restart flood
    if (waterLevel > 0.45f)
    {
        waterLevel = -1.0f;
    }


    glutPostRedisplay();

    // Update every 20 ms
    glutTimerFunc(20, update, 0);
}


void init()
{
    // Light gray-blue rainy sky
    glClearColor(0.65f, 0.75f, 0.85f, 1.0f);

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

    glutCreateWindow("Rain and Flood Scenario");

    init();

    glutDisplayFunc(display);

    glutTimerFunc(20, update, 0);

    glutMainLoop();

    return 0;
}
