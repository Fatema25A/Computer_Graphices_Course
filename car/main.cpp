#include<windows.h>
#include <GL/glut.h>
#include <cmath>

// Draw filled polygon
void drawPolygon(float x[], float y[], int n)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++)
    {
        glVertex2f(x[i], y[i]);
    }
    glEnd();
}

// Draw filled circle
void drawCircle(float cx, float cy, float r)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);

    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416f / 180;
        float x = cx + r * cos(angle);
        float y = cy + r * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // =========================
    // Main car body
    // Points:
    // F(-5,0), H(5,0), G(5,2), D(4,2),
    // B(2,3), A(-2,3), C(-4,2), E(-5,2)
    // =========================

    glColor3f(0.0f, 0.85f, 0.0f);   // Green

    float bodyX[] = {-5, 5, 5, 4, 2, -2, -4, -5};
    float bodyY[] = { 0, 0, 2, 2, 3,  3,  2,  2};

    drawPolygon(bodyX, bodyY, 8);

    // =========================
    // Car window
    // Points:
    // I(-3,2), J(-2,2.6), K(2.02,2.64), L(3,2)
    // =========================

    glColor3f(0.0f, 0.85f, 1.0f);   // Cyan / Blue window

    float windowX[] = {-3, -2, 2.02, 3};
    float windowY[] = { 2, 2.6, 2.64, 2};

    drawPolygon(windowX, windowY, 4);

    // =========================
    // Left wheel
    // Center: M(-2.48, 0)
    // Outer radius: 0.840
    // Inner radius: 0.660
    // =========================

    glColor3f(0.0f, 0.0f, 0.0f);      // Black outer wheel
    drawCircle(-2.48f, 0.0f, 0.840f);

    glColor3f(0.75f, 0.75f, 0.75f);   // Gray inner wheel
    drawCircle(-2.48f, 0.0f, 0.660f);

    // =========================
    // Right wheel
    // Center: N(2.54, 0)
    // Outer radius: 0.859
    // Inner radius: 0.683
    // =========================

    glColor3f(0.0f, 0.0f, 0.0f);      // Black outer wheel
    drawCircle(2.54f, 0.0f, 0.859f);

    glColor3f(0.75f, 0.75f, 0.75f);   // Gray inner wheel
    drawCircle(2.54f, 0.0f, 0.683f);

    glFlush();
}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   // White background

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Coordinate system according to your GeoGebra drawing
    gluOrtho2D(-6, 6, -2, 5);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Car Drawing Using OpenGL");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
