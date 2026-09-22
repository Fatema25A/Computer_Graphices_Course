#include <windows.h>
#include <GL/glut.h>

// =========================
// Draw 4-point polygon / box
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

// =========================
// Draw triangle
// =========================
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

// =========================
// Building function
// =========================
void building()
{
    // =========================
    // Main building body
    // A(-6,6), B(6,6), D(6,-6), C(-6,-6)
    // =========================
    glColor3ub(70, 130, 180);   // Steel blue
    box(-6, 6,   6, 6,   6, -6,   -6, -6,   0, 0);

    // =========================
    // Roof
    // A(-6,6), E(0,9), B(6,6)
    // =========================
    glColor3ub(150, 60, 40);    // Dark red/brown roof
    triangle(-6, 6, 0, 9, 6, 6);

    // =========================
    // Door
    // R(-1,-3), S(1,-3), U(0.96,-6), T(-1,-6)
    // =========================
    glColor3ub(120, 70, 30);    // Brown door
    box(-1, -3,   1, -3,   0.96, -6,   -1, -6,   0, 0);

    // Door knob
    glColor3ub(255, 220, 0);
    box(0.55, -4.6,   0.75, -4.6,   0.75, -4.8,   0.55, -4.8,   0, 0);

    // =========================
    // Windows
    // One window measurement:
    // N(-4,5), O(-2,5), Q(-2,4), P(-4,4)
    //
    // 5 windows left side
    // 5 windows right side
    // =========================
    glColor3ub(255, 230, 70);   // Yellow windows

    for (int row = 0; row < 5; row++)
    {
        float yShift = -2 * row;

        // Left windows
        box(-4, 5,   -2, 5,   -2, 4,   -4, 4,   0, yShift);

        // Right windows
        box(-4, 5,   -2, 5,   -2, 4,   -4, 4,   6, yShift);
    }

    // =========================
    // Window outer borders only
    // No middle lines inside windows
    // =========================
    glColor3ub(0, 0, 0);
    glLineWidth(2);

    for (int row = 0; row < 5; row++)
    {
        float yShift = -2 * row;

        // Left window border
        glBegin(GL_LINE_LOOP);
            glVertex2f(-4, 5 + yShift);
            glVertex2f(-2, 5 + yShift);
            glVertex2f(-2, 4 + yShift);
            glVertex2f(-4, 4 + yShift);
        glEnd();

        // Right window border
        glBegin(GL_LINE_LOOP);
            glVertex2f(2, 5 + yShift);
            glVertex2f(4, 5 + yShift);
            glVertex2f(4, 4 + yShift);
            glVertex2f(2, 4 + yShift);
        glEnd();
    }

    // =========================
    // Building outline
    // =========================
    glColor3ub(0, 0, 0);
    glLineWidth(3);

    // Body outline
    glBegin(GL_LINE_LOOP);
        glVertex2f(-6, 6);
        glVertex2f(6, 6);
        glVertex2f(6, -6);
        glVertex2f(-6, -6);
    glEnd();

    // Roof outline
    glBegin(GL_LINE_LOOP);
        glVertex2f(-6, 6);
        glVertex2f(0, 9);
        glVertex2f(6, 6);
    glEnd();

    // Door outline
    glBegin(GL_LINE_LOOP);
        glVertex2f(-1, -3);
        glVertex2f(1, -3);
        glVertex2f(0.96, -6);
        glVertex2f(-1, -6);
    glEnd();
}

// =========================
// Display function
// =========================
void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Black background
    glClear(GL_COLOR_BUFFER_BIT);

    building();

    glFlush();
}

// =========================
// Main function
// =========================
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Building with 10 Windows");

    gluOrtho2D(-10, 10, -8, 10);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
