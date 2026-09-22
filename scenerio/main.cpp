#include <windows.h>
#include <GL/glut.h>
#include <cmath>

// =========================
// Basic Drawing Functions
// =========================

void box(float x1, float y1,
         float x2, float y2,
         float x3, float y3,
         float x4, float y4,
         float xf, float yf)
{
    glBegin(GL_POLYGON);
        glVertex2f(x1 + xf, y1 + yf);
        glVertex2f(x2 + xf, y2 + yf);
        glVertex2f(x3 + xf, y3 + yf);
        glVertex2f(x4 + xf, y4 + yf);
    glEnd();
}

void rectangle(float x1, float y1, float x2, float y2)
{
    glBegin(GL_POLYGON);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
}

void triangle(float x1, float y1,
              float x2, float y2,
              float x3, float y3)
{
    glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();
}

void circle(float cx, float cy, float r)
{
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);

        for (int i = 0; i <= 360; i++)
        {
            float angle = i * 3.1416f / 180.0f;
            glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
        }
    glEnd();
}

// =========================
// Building
// =========================

void building()
{
    // Main building body
    glColor3ub(70, 130, 180);
    box(-6, 6, 6, 6, 6, -6, -6, -6, -10, 0);

    // Roof
    glColor3ub(150, 60, 40);
    triangle(-16, 6, -10, 9, -4, 6);

    // Door
    glColor3ub(120, 70, 30);
    box(-1, -3, 1, -3, 0.96, -6, -1, -6, -10, 0);

    // Door knob
    glColor3ub(255, 220, 0);
    box(0.55, -4.6, 0.75, -4.6, 0.75, -4.8, 0.55, -4.8, -10, 0);

    // Windows
    glColor3ub(255, 230, 70);

    for (int row = 0; row < 5; row++)
    {
        float yShift = -2 * row;

        // Left windows
        box(-4, 5, -2, 5, -2, 4, -4, 4, -10, yShift);

        // Right windows
        box(-4, 5, -2, 5, -2, 4, -4, 4, -4, yShift);
    }

    // Window borders only
    glColor3ub(0, 0, 0);
    glLineWidth(2);

    for (int row = 0; row < 5; row++)
    {
        float yShift = -2 * row;

        // Left window border
        glBegin(GL_LINE_LOOP);
            glVertex2f(-14, 5 + yShift);
            glVertex2f(-12, 5 + yShift);
            glVertex2f(-12, 4 + yShift);
            glVertex2f(-14, 4 + yShift);
        glEnd();

        // Right window border
        glBegin(GL_LINE_LOOP);
            glVertex2f(-8, 5 + yShift);
            glVertex2f(-6, 5 + yShift);
            glVertex2f(-6, 4 + yShift);
            glVertex2f(-8, 4 + yShift);
        glEnd();
    }

    // Building outline
    glColor3ub(0, 0, 0);
    glLineWidth(3);

    glBegin(GL_LINE_LOOP);
        glVertex2f(-16, 6);
        glVertex2f(-4, 6);
        glVertex2f(-4, -6);
        glVertex2f(-16, -6);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(-16, 6);
        glVertex2f(-10, 9);
        glVertex2f(-4, 6);
    glEnd();
}

// =========================
// Triangle Tree
// =========================

void tree()
{
    // Tree trunk
    glColor3ub(120, 65, 20);
    rectangle(7.0, -6.5, 7.8, -4.0);

    // Bottom green triangle
    glColor3ub(0, 140, 0);
    triangle(4.8, -4.0, 10.0, -4.0, 7.4, -0.8);

    // Middle green triangle
    glColor3ub(0, 150, 0);
    triangle(5.0, -2.0, 9.8, -2.0, 7.4, 1.2);

    // Top green triangle
    glColor3ub(0, 130, 0);
    triangle(5.2, 0.0, 9.6, 0.0, 7.4, 3.3);
}

// =========================
// Lamppost
// =========================

void lamppost()
{
    // Pole
    glColor3ub(55, 55, 55);
    rectangle(1.8, -6, 2.1, 2.0);

    // Pole highlight
    glColor3ub(120, 120, 120);
    rectangle(1.88, -6, 1.95, 2.0);

    // Base
    glColor3ub(80, 80, 80);
    rectangle(1.4, -6.2, 2.5, -5.7);
    rectangle(1.55, -5.7, 2.35, -5.2);

    // Lamp connector
    glColor3ub(70, 70, 70);
    rectangle(1.65, 1.8, 2.25, 2.2);

    // Lamp glass
    glColor3ub(255, 190, 40);
    glBegin(GL_POLYGON);
        glVertex2f(1.25, 2.2);
        glVertex2f(2.65, 2.2);
        glVertex2f(2.35, 3.6);
        glVertex2f(1.55, 3.6);
    glEnd();

    // Lamp roof
    glColor3ub(90, 90, 90);
    glBegin(GL_POLYGON);
        glVertex2f(1.1, 3.6);
        glVertex2f(2.8, 3.6);
        glVertex2f(2.4, 4.2);
        glVertex2f(1.5, 4.2);
    glEnd();

    // Top cap
    glColor3ub(90, 90, 90);
    circle(1.95, 4.45, 0.25);

    // Lamp outline
    glColor3ub(0, 0, 0);
    glLineWidth(3);

    glBegin(GL_LINE_LOOP);
        glVertex2f(1.25, 2.2);
        glVertex2f(2.65, 2.2);
        glVertex2f(2.35, 3.6);
        glVertex2f(1.55, 3.6);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(1.1, 3.6);
        glVertex2f(2.8, 3.6);
        glVertex2f(2.4, 4.2);
        glVertex2f(1.5, 4.2);
    glEnd();
}

// =========================
// Car
// =========================

void car()
{
    // Main car body
    glColor3ub(0, 220, 0);

    glBegin(GL_POLYGON);
        glVertex2f(-2.5, -9.0);
        glVertex2f(5.5, -9.0);
        glVertex2f(5.5, -7.0);
        glVertex2f(4.5, -7.0);
        glVertex2f(3.0, -5.8);
        glVertex2f(-0.5, -5.8);
        glVertex2f(-2.0, -7.0);
        glVertex2f(-2.5, -7.0);
    glEnd();

    // Car window
    glColor3ub(0, 200, 255);

    glBegin(GL_POLYGON);
        glVertex2f(-0.8, -6.9);
        glVertex2f(3.8, -6.9);
        glVertex2f(2.7, -6.1);
        glVertex2f(0.1, -6.1);
    glEnd();

    // Wheels
    glColor3ub(0, 0, 0);
    circle(-0.5, -9.0, 0.75);
    circle(3.6, -9.0, 0.75);

    glColor3ub(180, 180, 180);
    circle(-0.5, -9.0, 0.45);
    circle(3.6, -9.0, 0.45);
}

// =========================
// Road and Sky
// =========================

void road()
{
    // Road
    glColor3ub(45, 45, 45);
    rectangle(-20, -10, 20, -6.5);

    // Road divider
    glColor3ub(255, 255, 255);
    for (float x = -18; x < 20; x += 5)
    {
        rectangle(x, -8.4, x + 2.5, -8.1);
    }
}

void skyObjects()
{
    // Moon
    glColor3ub(240, 240, 180);
    circle(13.5, 8.0, 1.0);

    // Stars
    glColor3ub(255, 255, 255);
    circle(-18, 8, 0.08);
    circle(-2, 7.5, 0.08);
    circle(5, 8.5, 0.08);
    circle(10, 6.8, 0.08);
    circle(17, 5.8, 0.08);
}

// =========================
// Display
// =========================

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    skyObjects();
    building();
    tree();
    lamppost();
    road();
    car();

    glFlush();
}

// =========================
// Main
// =========================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("City Scenario with Triangle Tree");

    gluOrtho2D(-20, 20, -11, 11);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
