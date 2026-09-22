#include <windows.h>
#include <GL/glut.h>

// ======================================================
// BOAT
// ======================================================

void drawBoat()
{
    // ==================================================
    // LOWER BLACK BOAT BODY
    // ==================================================
    glColor3f(0.02f, 0.02f, 0.02f);

    glBegin(GL_POLYGON);

        glVertex2f(-8.5f, -5.0f);
        glVertex2f( 8.5f, -5.0f);
        glVertex2f( 6.3f, -7.2f);
        glVertex2f(-6.3f, -7.2f);

    glEnd();


    // ==================================================
    // SHADED BROWN RECTANGULAR COVER
    // ==================================================

    // Top light layer
    glBegin(GL_QUADS);

        glColor3f(0.88f, 0.62f, 0.38f);
        glVertex2f(-4.0f, -3.0f);

        glColor3f(0.88f, 0.62f, 0.38f);
        glVertex2f( 4.0f, -3.0f);

        glColor3f(0.72f, 0.44f, 0.24f);
        glVertex2f( 4.0f, -3.7f);

        glColor3f(0.72f, 0.44f, 0.24f);
        glVertex2f(-4.0f, -3.7f);

    glEnd();


    // Middle layer
    glBegin(GL_QUADS);

        glColor3f(0.72f, 0.44f, 0.24f);
        glVertex2f(-4.0f, -3.7f);

        glColor3f(0.72f, 0.44f, 0.24f);
        glVertex2f( 4.0f, -3.7f);

        glColor3f(0.58f, 0.32f, 0.15f);
        glVertex2f( 4.0f, -4.4f);

        glColor3f(0.58f, 0.32f, 0.15f);
        glVertex2f(-4.0f, -4.4f);

    glEnd();


    // Bottom dark layer
    glBegin(GL_QUADS);

        glColor3f(0.58f, 0.32f, 0.15f);
        glVertex2f(-4.0f, -4.4f);

        glColor3f(0.58f, 0.32f, 0.15f);
        glVertex2f( 4.0f, -4.4f);

        glColor3f(0.38f, 0.18f, 0.07f);
        glVertex2f( 4.0f, -5.0f);

        glColor3f(0.38f, 0.18f, 0.07f);
        glVertex2f(-4.0f, -5.0f);

    glEnd();


    // ==================================================
    // MAIN MAST + TOP ROD
    // ==================================================
    glColor3f(0.05f, 0.05f, 0.05f);
    glLineWidth(2.5f);

    glBegin(GL_LINES);

        // Mast lower part
        glVertex2f(0.2f, -3.0f);
        glVertex2f(0.2f, -1.7f);

        // Mast upper extension
        glVertex2f(0.2f, 7.5f);
        glVertex2f(0.2f, 8.8f);

        // Top horizontal rod
        glVertex2f(-4.8f, 7.5f);
        glVertex2f( 5.5f, 7.5f);

    glEnd();


    // ==================================================
    // YELLOW SHADED SAIL
    // Filled using triangles
    // ==================================================

    float centerX = 1.0f;
    float centerY = 2.5f;


    glBegin(GL_TRIANGLES);


        // ==================================================
        // LEFT UPPER PART
        // ==================================================

        glColor3f(1.0f, 0.94f, 0.20f);

        glVertex2f(centerX, centerY);
        glVertex2f(-4.5f, 7.5f);
        glVertex2f(-3.8f, 6.3f);


        glColor3f(1.0f, 0.92f, 0.16f);

        glVertex2f(centerX, centerY);
        glVertex2f(-3.8f, 6.3f);
        glVertex2f(-3.2f, 4.8f);


        glColor3f(1.0f, 0.90f, 0.12f);

        glVertex2f(centerX, centerY);
        glVertex2f(-3.2f, 4.8f);
        glVertex2f(-3.0f, 3.0f);


        glColor3f(1.0f, 0.88f, 0.08f);

        glVertex2f(centerX, centerY);
        glVertex2f(-3.0f, 3.0f);
        glVertex2f(-3.0f, 1.3f);


        glColor3f(1.0f, 0.86f, 0.05f);

        glVertex2f(centerX, centerY);
        glVertex2f(-3.0f, 1.3f);
        glVertex2f(-3.3f, -0.5f);


        glColor3f(1.0f, 0.84f, 0.02f);

        glVertex2f(centerX, centerY);
        glVertex2f(-3.3f, -0.5f);
        glVertex2f(-3.7f, -2.8f);


        // ==================================================
        // BOTTOM CURVED PART
        // ==================================================

        glColor3f(1.0f, 0.83f, 0.00f);

        glVertex2f(centerX, centerY);
        glVertex2f(-3.7f, -2.8f);
        glVertex2f(-2.5f, -2.3f);


        glVertex2f(centerX, centerY);
        glVertex2f(-2.5f, -2.3f);
        glVertex2f(-1.2f, -1.9f);


        glVertex2f(centerX, centerY);
        glVertex2f(-1.2f, -1.9f);
        glVertex2f(0.2f, -1.7f);


        glVertex2f(centerX, centerY);
        glVertex2f(0.2f, -1.7f);
        glVertex2f(1.5f, -1.7f);


        glVertex2f(centerX, centerY);
        glVertex2f(1.5f, -1.7f);
        glVertex2f(2.2f, -2.0f);


        glVertex2f(centerX, centerY);
        glVertex2f(2.2f, -2.0f);
        glVertex2f(2.6f, -2.6f);


        // ==================================================
        // RIGHT SIDE
        // ==================================================

        glColor3f(1.0f, 0.81f, 0.00f);

        glVertex2f(centerX, centerY);
        glVertex2f(2.6f, -2.6f);
        glVertex2f(3.6f, -1.3f);


        glColor3f(1.0f, 0.83f, 0.01f);

        glVertex2f(centerX, centerY);
        glVertex2f(3.6f, -1.3f);
        glVertex2f(4.4f, 0.1f);


        glColor3f(1.0f, 0.85f, 0.03f);

        glVertex2f(centerX, centerY);
        glVertex2f(4.4f, 0.1f);
        glVertex2f(5.0f, 1.8f);


        glColor3f(1.0f, 0.87f, 0.05f);

        glVertex2f(centerX, centerY);
        glVertex2f(5.0f, 1.8f);
        glVertex2f(5.3f, 3.4f);


        glColor3f(1.0f, 0.89f, 0.08f);

        glVertex2f(centerX, centerY);
        glVertex2f(5.3f, 3.4f);
        glVertex2f(5.4f, 5.1f);


        glColor3f(1.0f, 0.91f, 0.12f);

        glVertex2f(centerX, centerY);
        glVertex2f(5.4f, 5.1f);
        glVertex2f(5.3f, 6.5f);


        glColor3f(1.0f, 0.93f, 0.16f);

        glVertex2f(centerX, centerY);
        glVertex2f(5.3f, 6.5f);
        glVertex2f(5.2f, 7.5f);


        // ==================================================
        // TOP CLOSING PART
        // ==================================================

        glColor3f(1.0f, 0.95f, 0.22f);

        glVertex2f(centerX, centerY);
        glVertex2f(5.2f, 7.5f);
        glVertex2f(-4.5f, 7.5f);


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

    drawBoat();

    glutSwapBuffers();
}


// ======================================================
// INITIALIZATION
// ======================================================

void init()
{
    glClearColor(
        1.0f,
        1.0f,
        1.0f,
        1.0f
    );

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(
        -10,
        10,
        -10,
        10
    );

    glMatrixMode(GL_MODELVIEW);
}


// ======================================================
// MAIN
// ======================================================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB
    );

    glutInitWindowSize(
        900,
        700
    );

    glutInitWindowPosition(
        100,
        50
    );

    glutCreateWindow(
        "Shaded Village Sail Boat"
    );

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
