#include <windows.h>
#include <GL/glut.h>

// ======================================================
// BASIC RECTANGLE
// ======================================================
void rectangle(float x1, float y1, float x2, float y2)
{
    glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
}

// ======================================================
// DRAW HOUSE
// ======================================================
void drawHouse()
{
    // ==================================================
    // MAIN WALL - SHADED CREAM
    // ==================================================
    glBegin(GL_QUADS);

        // Bottom slightly darker
        glColor3f(0.78f, 0.64f, 0.38f);
        glVertex2f(-34.0f, -15.0f);

        glColor3f(0.78f, 0.64f, 0.38f);
        glVertex2f(34.0f, -15.0f);

        // Top lighter
        glColor3f(0.96f, 0.80f, 0.48f);
        glVertex2f(34.0f, 17.0f);

        glColor3f(0.96f, 0.80f, 0.48f);
        glVertex2f(-34.0f, 17.0f);

    glEnd();


    // ==================================================
    // WALL CENTER LIGHT SHADE
    // ==================================================
    glBegin(GL_QUADS);

        glColor3f(0.90f, 0.74f, 0.44f);
        glVertex2f(-32.0f, -15.0f);

        glColor3f(0.90f, 0.74f, 0.44f);
        glVertex2f(32.0f, -15.0f);

        glColor3f(1.0f, 0.86f, 0.58f);
        glVertex2f(28.0f, 16.0f);

        glColor3f(1.0f, 0.86f, 0.58f);
        glVertex2f(-28.0f, 16.0f);

    glEnd();


    // ==================================================
    // LEFT WOODEN POST
    // ==================================================
    glBegin(GL_QUADS);

        glColor3f(0.35f, 0.13f, 0.02f);
        glVertex2f(-35.0f, -15.5f);

        glColor3f(0.48f, 0.20f, 0.04f);
        glVertex2f(-32.2f, -15.5f);

        glColor3f(0.55f, 0.25f, 0.05f);
        glVertex2f(-32.2f, 17.0f);

        glColor3f(0.35f, 0.13f, 0.02f);
        glVertex2f(-35.0f, 17.0f);

    glEnd();


    // ==================================================
    // RIGHT WOODEN POST
    // ==================================================
    glBegin(GL_QUADS);

        glColor3f(0.35f, 0.13f, 0.02f);
        glVertex2f(32.2f, -15.5f);

        glColor3f(0.52f, 0.22f, 0.04f);
        glVertex2f(35.0f, -15.5f);

        glColor3f(0.55f, 0.25f, 0.05f);
        glVertex2f(35.0f, 17.0f);

        glColor3f(0.35f, 0.13f, 0.02f);
        glVertex2f(32.2f, 17.0f);

    glEnd();


    // ==================================================
    // CLEAN SHADED TIN ROOF - NO STRIPS
    // ==================================================

    // LEFT HALF
    glBegin(GL_TRIANGLES);

        glColor3f(0.26f, 0.27f, 0.30f);
        glVertex2f(-45.0f, 17.0f);

        glColor3f(0.48f, 0.49f, 0.52f);
        glVertex2f(0.0f, 40.0f);

        glColor3f(0.32f, 0.33f, 0.36f);
        glVertex2f(0.0f, 17.0f);

    glEnd();

    // RIGHT HALF
    glBegin(GL_TRIANGLES);

        glColor3f(0.48f, 0.49f, 0.52f);
        glVertex2f(0.0f, 40.0f);

        glColor3f(0.26f, 0.27f, 0.30f);
        glVertex2f(45.0f, 17.0f);

        glColor3f(0.32f, 0.33f, 0.36f);
        glVertex2f(0.0f, 17.0f);

    glEnd();


    // ==================================================
    // ROOF BOTTOM EDGE
    // ==================================================
    glColor3f(0.14f, 0.15f, 0.17f);

    glBegin(GL_QUADS);

        glVertex2f(-45.0f, 17.0f);
        glVertex2f(45.0f, 17.0f);
        glVertex2f(44.2f, 15.8f);
        glVertex2f(-44.2f, 15.8f);

    glEnd();


    // ==================================================
    // DOOR FRAME
    // ==================================================
    glColor3f(0.50f, 0.32f, 0.14f);
    rectangle(-8.0f, -15.0f, 8.0f, 13.5f);


    // ==================================================
    // DOOR OPENING
    // ==================================================
    glBegin(GL_QUADS);

        glColor3f(0.25f, 0.23f, 0.20f);
        glVertex2f(-6.5f, -15.0f);

        glColor3f(0.25f, 0.23f, 0.20f);
        glVertex2f(6.5f, -15.0f);

        glColor3f(0.35f, 0.32f, 0.27f);
        glVertex2f(6.5f, 12.0f);

        glColor3f(0.35f, 0.32f, 0.27f);
        glVertex2f(-6.5f, 12.0f);

    glEnd();


    // ==================================================
    // DARK LOWER INSIDE
    // ==================================================
    glColor3f(0.20f, 0.21f, 0.20f);
    rectangle(-6.5f, -15.0f, 6.5f, -8.0f);


    // ==================================================
    // OPEN WOODEN DOOR
    // ==================================================
    glBegin(GL_QUADS);

        glColor3f(0.38f, 0.14f, 0.01f);
        glVertex2f(1.5f, -13.5f);

        glColor3f(0.55f, 0.23f, 0.02f);
        glVertex2f(6.0f, -12.0f);

        glColor3f(0.58f, 0.26f, 0.03f);
        glVertex2f(6.0f, 10.0f);

        glColor3f(0.40f, 0.15f, 0.01f);
        glVertex2f(1.5f, 8.5f);

    glEnd();


    // ==================================================
    // DOOR OUTLINE
    // ==================================================
    glColor3f(0.15f, 0.07f, 0.01f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);

        glVertex2f(1.5f, -13.5f);
        glVertex2f(6.0f, -12.0f);
        glVertex2f(6.0f, 10.0f);
        glVertex2f(1.5f, 8.5f);

    glEnd();


    // ==================================================
    // DOOR HANDLE
    // ==================================================
    glColor3f(0.35f, 0.35f, 0.32f);
    glPointSize(5.0f);

    glBegin(GL_POINTS);
        glVertex2f(2.2f, -1.0f);
    glEnd();


    // ==================================================
    // RIGHT WINDOW MAIN FRAME
    // ==================================================
    glColor3f(0.40f, 0.15f, 0.02f);
    rectangle(17.0f, -2.0f, 29.0f, 9.5f);


    // ==================================================
    // WINDOW TOP WOOD
    // ==================================================
    glColor3f(0.48f, 0.20f, 0.03f);
    rectangle(16.0f, 9.5f, 30.0f, 11.0f);


    // ==================================================
    // WINDOW BOTTOM WOOD
    // ==================================================
    rectangle(16.0f, -3.5f, 30.0f, -2.0f);


    // ==================================================
    // WINDOW INNER LIGHT PANEL
    // ==================================================
    glColor3f(0.80f, 0.78f, 0.67f);
    rectangle(19.0f, 0.0f, 27.0f, 8.0f);


    // ==================================================
    // WINDOW BARS
    // ==================================================
    glColor3f(0.25f, 0.24f, 0.21f);
    glLineWidth(1.5f);

    glBegin(GL_LINES);

        glVertex2f(20.2f, 0.0f);
        glVertex2f(20.2f, 8.0f);

        glVertex2f(21.7f, 0.0f);
        glVertex2f(21.7f, 8.0f);

        glVertex2f(23.2f, 0.0f);
        glVertex2f(23.2f, 8.0f);

        glVertex2f(24.7f, 0.0f);
        glVertex2f(24.7f, 8.0f);

        glVertex2f(26.2f, 0.0f);
        glVertex2f(26.2f, 8.0f);

    glEnd();


    // ==================================================
    // LEFT WINDOW SHUTTER
    // ==================================================
    glColor3f(0.48f, 0.19f, 0.02f);

    glBegin(GL_QUADS);

        glVertex2f(14.0f, -1.0f);
        glVertex2f(17.0f, 0.0f);
        glVertex2f(17.0f, 8.5f);
        glVertex2f(14.0f, 7.5f);

    glEnd();


    // Left shutter inner panels
    glColor3f(0.38f, 0.14f, 0.01f);
    rectangle(14.7f, 4.0f, 16.3f, 7.0f);
    rectangle(14.7f, 0.3f, 16.3f, 3.3f);


    // ==================================================
    // RIGHT WINDOW SHUTTER
    // ==================================================
    glColor3f(0.48f, 0.19f, 0.02f);

    glBegin(GL_QUADS);

        glVertex2f(29.0f, 0.0f);
        glVertex2f(32.0f, -1.0f);
        glVertex2f(32.0f, 7.5f);
        glVertex2f(29.0f, 8.5f);

    glEnd();


    // Right shutter inner panels
    glColor3f(0.38f, 0.14f, 0.01f);
    rectangle(29.7f, 4.0f, 31.3f, 7.0f);
    rectangle(29.7f, 0.3f, 31.3f, 3.3f);


    // ==================================================
    // FRONT VERANDA
    // ==================================================
    glBegin(GL_QUADS);

        glColor3f(0.57f, 0.54f, 0.48f);
        glVertex2f(-37.5f, -18.5f);

        glColor3f(0.57f, 0.54f, 0.48f);
        glVertex2f(37.5f, -18.5f);

        glColor3f(0.72f, 0.68f, 0.60f);
        glVertex2f(37.5f, -15.0f);

        glColor3f(0.72f, 0.68f, 0.60f);
        glVertex2f(-37.5f, -15.0f);

    glEnd();


    // ==================================================
    // VERANDA FRONT WALL
    // ==================================================
    glBegin(GL_QUADS);

        glColor3f(0.32f, 0.30f, 0.28f);
        glVertex2f(-37.5f, -24.0f);

        glColor3f(0.32f, 0.30f, 0.28f);
        glVertex2f(37.5f, -24.0f);

        glColor3f(0.50f, 0.48f, 0.44f);
        glVertex2f(37.5f, -18.5f);

        glColor3f(0.50f, 0.48f, 0.44f);
        glVertex2f(-37.5f, -18.5f);

    glEnd();


    // ==================================================
    // FRONT STAIRS - TOP STEP
    // ==================================================
    glBegin(GL_QUADS);

        glColor3f(0.68f, 0.65f, 0.59f);
        glVertex2f(-8.0f, -20.0f);

        glVertex2f(8.0f, -20.0f);

        glColor3f(0.78f, 0.75f, 0.69f);
        glVertex2f(6.5f, -18.0f);

        glVertex2f(-6.5f, -18.0f);

    glEnd();


    // ==================================================
    // FRONT STAIRS - MIDDLE STEP
    // ==================================================
    glColor3f(0.66f, 0.63f, 0.57f);

    glBegin(GL_QUADS);

        glVertex2f(-9.0f, -23.0f);
        glVertex2f(9.0f, -23.0f);
        glVertex2f(8.0f, -20.0f);
        glVertex2f(-8.0f, -20.0f);

    glEnd();


    // ==================================================
    // FRONT STAIRS - BOTTOM STEP
    // ==================================================
    glColor3f(0.58f, 0.56f, 0.52f);

    glBegin(GL_QUADS);

        glVertex2f(-10.0f, -26.0f);
        glVertex2f(10.0f, -26.0f);
        glVertex2f(9.0f, -23.0f);
        glVertex2f(-9.0f, -23.0f);

    glEnd();
}

// ======================================================
// DISPLAY
// ======================================================
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawHouse();

    glutSwapBuffers();
}

// ======================================================
// INITIALIZATION
// ======================================================
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-55.0, 55.0, -35.0, 48.0);

    glMatrixMode(GL_MODELVIEW);
}

// ======================================================
// MAIN
// ======================================================
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 650);
    glutInitWindowPosition(100, 50);

    glutCreateWindow("Village House");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
