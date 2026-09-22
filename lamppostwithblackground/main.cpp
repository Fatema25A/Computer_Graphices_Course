#include<windows.h>
#include <GL/glut.h>
#include <cmath>

// =========================
// Basic drawing functions
// =========================

void drawPolygon(float x[], float y[], int n)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++)
    {
        glVertex2f(x[i], y[i]);
    }
    glEnd();
}

void drawRectangle(float x1, float y1, float x2, float y2)
{
    glBegin(GL_POLYGON);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void drawSemiCircle(float cx, float cy, float r)
{
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);

        for (int i = 0; i <= 180; i++)
        {
            float angle = i * 3.1416f / 180.0f;
            float x = cx + r * cos(angle);
            float y = cy + r * sin(angle);
            glVertex2f(x, y);
        }
    glEnd();
}

// =========================
// Display function
// =========================

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // =========================
    // Colors
    // =========================
    float gray[]       = {0.45f, 0.45f, 0.45f};
    float darkGray[]   = {0.22f, 0.22f, 0.22f};
    float lightGray[]  = {0.60f, 0.60f, 0.60f};
    float orange[]     = {1.0f, 0.45f, 0.05f};
    float yellow[]     = {1.0f, 0.78f, 0.05f};
    float outline[]    = {0.05f, 0.05f, 0.05f};

    // =====================================================
    // 1. Lamp glass section
    // =====================================================

    // Left orange glass
    // A(-2,3), I(-1,3), G(-0.42,1), E(-1,1)
    glColor3fv(orange);
    float leftGlassX[] = {-2.0f, -1.0f, -0.42f, -1.0f};
    float leftGlassY[] = { 3.0f,  3.0f,  1.0f,  1.0f};
    drawPolygon(leftGlassX, leftGlassY, 4);

    // Middle yellow glass
    // I(-1,3), J(1,3), H(0.42,1), G(-0.42,1)
    glColor3fv(yellow);
    float middleGlassX[] = {-1.0f, 1.0f, 0.42f, -0.42f};
    float middleGlassY[] = { 3.0f, 3.0f, 1.0f,   1.0f};
    drawPolygon(middleGlassX, middleGlassY, 4);

    // Right orange glass
    // J(1,3), B(2,3), F(1,1), H(0.42,1)
    glColor3fv(orange);
    float rightGlassX[] = {1.0f, 2.0f, 1.0f, 0.42f};
    float rightGlassY[] = {3.0f, 3.0f, 1.0f, 1.0f};
    drawPolygon(rightGlassX, rightGlassY, 4);

    // =====================================================
    // 2. Lamp top roof
    // A(-2,3), C(-1,4), D(1,4), B(2,3)
    // =====================================================

    glColor3fv(gray);
    float roofX[] = {-2.0f, -1.0f, 1.0f, 2.0f};
    float roofY[] = { 3.0f,  4.0f, 4.0f, 3.0f};
    drawPolygon(roofX, roofY, 4);

    // Semicircle cap on top
    // K(-0.38,4), L(0.46,4)
    glColor3fv(gray);
    drawSemiCircle(0.04f, 4.0f, 0.42f);

    // =====================================================
    // 3. Lamp outlines
    // =====================================================

    glColor3fv(outline);
    glLineWidth(4);

    // Outer lamp outline
    drawLine(-2.0f, 3.0f, -1.0f, 4.0f);   // A to C
    drawLine(-1.0f, 4.0f, 1.0f, 4.0f);    // C to D
    drawLine(1.0f, 4.0f, 2.0f, 3.0f);     // D to B
    drawLine(2.0f, 3.0f, 1.0f, 1.0f);     // B to F
    drawLine(1.0f, 1.0f, -1.0f, 1.0f);    // F to E
    drawLine(-1.0f, 1.0f, -2.0f, 3.0f);   // E to A

    // Inner glass frame
    drawLine(-1.0f, 3.0f, -0.42f, 1.0f);  // I to G
    drawLine(1.0f, 3.0f, 0.42f, 1.0f);    // J to H
    drawLine(-1.0f, 3.0f, 1.0f, 3.0f);    // I to J
    drawLine(-0.42f, 1.0f, 0.42f, 1.0f);  // G to H

    // Top roof outline
    drawLine(-2.0f, 3.0f, 2.0f, 3.0f);
    drawLine(-1.0f, 4.0f, 1.0f, 4.0f);

    // =====================================================
    // 4. Connector under lamp
    // O(-0.1439,1), P(0.1543,1)
    // =====================================================

    glColor3fv(darkGray);
    drawRectangle(-0.25f, 0.85f, 0.25f, 1.0f);

    glColor3fv(gray);
    drawRectangle(-0.16f, 0.62f, 0.16f, 0.85f);

    glColor3fv(outline);
    glLineWidth(3);
    drawLine(-0.25f, 0.85f, 0.25f, 0.85f);
    drawLine(-0.25f, 1.0f, 0.25f, 1.0f);

    // =====================================================
    // 5. Main pole
    // O(-0.1439,1), P(0.1543,1)
    // M(-0.1439,-4.0129), N(0.1995,-4.0251)
    // =====================================================

    glColor3fv(darkGray);
    float poleX[] = {-0.1439f, 0.1543f, 0.1995f, -0.1439f};
    float poleY[] = { 1.0f,    1.0f,   -4.025f, -4.012f};
    drawPolygon(poleX, poleY, 4);

    // Pole highlight
    glColor3fv(lightGray);
    glLineWidth(2);
    drawLine(-0.05f, 0.9f, -0.05f, -3.9f);

    // Pole outline
    glColor3fv(outline);
    glLineWidth(3);
    drawLine(-0.1439f, 1.0f, -0.1439f, -4.012f);
    drawLine(0.1543f, 1.0f, 0.1995f, -4.025f);

    // =====================================================
    // 6. Bottom base
    // R(-1.5687,-4.3900), M(-0.1439,-4.0129),
    // N(0.1995,-4.0251), S(1.5791,-4.4024)
    // =====================================================

    glColor3fv(gray);
    float baseTopX[] = {-1.5687f, -0.1439f, 0.1995f, 1.5791f};
    float baseTopY[] = {-4.3900f, -4.0129f, -4.0251f, -4.4024f};
    drawPolygon(baseTopX, baseTopY, 4);

    // Main base block
    glColor3fv(darkGray);
    float baseX[] = {-0.65f, 0.65f, 0.50f, -0.50f};
    float baseY[] = {-5.05f, -5.05f, -4.40f, -4.40f};
    drawPolygon(baseX, baseY, 4);

    // Inner base design
    glColor3fv(gray);
    float innerBaseX[] = {-0.22f, 0.22f, 0.12f, -0.12f};
    float innerBaseY[] = {-4.90f, -4.90f, -4.48f, -4.48f};
    drawPolygon(innerBaseX, innerBaseY, 4);

    // Bottom rectangle base
    glColor3fv(gray);
    drawRectangle(-0.85f, -5.25f, 0.85f, -5.05f);

    // Base outlines
    glColor3fv(outline);
    glLineWidth(3);

    drawLine(-1.5687f, -4.3900f, -0.1439f, -4.0129f);
    drawLine(-0.1439f, -4.0129f, 0.1995f, -4.0251f);
    drawLine(0.1995f, -4.0251f, 1.5791f, -4.4024f);
    drawLine(1.5791f, -4.4024f, -1.5687f, -4.3900f);

    glFlush();
}

// =========================
// Init function
// =========================

void init()
{
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Coordinate system based on your GeoGebra measurement
    gluOrtho2D(-3.0, 3.0, -5.4, 5.0);
}

// =========================
// Main function
// =========================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(600, 900);
    glutInitWindowPosition(100, 50);

    glutCreateWindow("Lamppost with Black Background");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
