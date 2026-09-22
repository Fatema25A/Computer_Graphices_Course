#include<windows.h>
#include <GL/glut.h>
#include <cmath>

#define PI 3.1415926f

// ==========================================================
// BASIC DRAWING FUNCTIONS
// ==========================================================

void drawLine(float x1, float y1,
              float x2, float y2,
              float r, float g, float b,
              float width = 2.0f)
{
    glColor3f(r, g, b);
    glLineWidth(width);

    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

    glLineWidth(1.0f);
}

void drawCircle(float cx, float cy, float radius,
                float r, float g, float b)
{
    glColor3f(r, g, b);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(cx, cy);

    for (int i = 0; i <= 100; i++)
    {
        float angle = 2.0f * PI * i / 100.0f;

        glVertex2f(
            cx + radius * cos(angle),
            cy + radius * sin(angle)
        );
    }

    glEnd();
}

void drawRectangle(float left, float bottom,
                   float right, float top,
                   float r, float g, float b)
{
    glColor3f(r, g, b);

    glBegin(GL_QUADS);

    glVertex2f(left, bottom);
    glVertex2f(right, bottom);
    glVertex2f(right, top);
    glVertex2f(left, top);

    glEnd();
}

void drawRectangleBorder(float left, float bottom,
                         float right, float top)
{
    glColor3f(0.05f, 0.05f, 0.05f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);

    glVertex2f(left, bottom);
    glVertex2f(right, bottom);
    glVertex2f(right, top);
    glVertex2f(left, top);

    glEnd();

    glLineWidth(1.0f);
}

// ==========================================================
// BACKGROUND
// ==========================================================

void drawBackground()
{
    glColor3f(0.88f, 0.95f, 0.98f);

    glBegin(GL_QUADS);

    glVertex2f(-7.2f, -2.8f);
    glVertex2f(7.2f, -2.8f);
    glVertex2f(7.2f, 4.8f);
    glVertex2f(-7.2f, 4.8f);

    glEnd();
}

// ==========================================================
// WATER
// ==========================================================

void drawWater()
{
    glColor3f(0.15f, 0.65f, 0.85f);

    glBegin(GL_QUADS);

    glVertex2f(-7.2f, -2.8f);
    glVertex2f(7.2f, -2.8f);
    glVertex2f(7.2f, -2.1f);
    glVertex2f(-7.2f, -2.1f);

    glEnd();

    // Simple water lines
    drawLine(-7.0f, -2.35f, -3.5f, -2.35f,
             0.90f, 1.00f, 1.00f, 2.0f);

    drawLine(-2.5f, -2.50f, 1.0f, -2.50f,
             0.90f, 1.00f, 1.00f, 2.0f);

    drawLine(2.0f, -2.30f, 6.5f, -2.30f,
             0.90f, 1.00f, 1.00f, 2.0f);
}

// ==========================================================
// LOWER RED PART OF THE SHIP
// ==========================================================

void drawLowerHull()
{
    /*
        Exact GeoGebra measurements:

        A = (-6.92, -2.54)
        B = ( 6.92, -2.54)

        F = (-5.32, -1.10)
        G = (-4.90, -1.33)
        H = ( 3.41, -1.27)
        I = (-4.17, -1.76)
        J = ( 3.45, -1.71)

        Segment measurements:

        i = Segment(F,G) = 0.48
        j = Segment(G,H) = 8.31
        k = Segment(G,I) = 0.85
        l = Segment(I,J) = 7.62
        m = Segment(H,J) = 0.44
    */

    glColor3f(0.68f, 0.08f, 0.04f);

    glBegin(GL_POLYGON);

    glVertex2f(-5.32f, -1.10f); // F
    glVertex2f(-4.90f, -1.33f); // G
    glVertex2f(-4.17f, -1.76f); // I
    glVertex2f(-6.92f, -2.54f); // A
    glVertex2f( 6.92f, -2.54f); // B
    glVertex2f( 3.45f, -1.71f); // J
    glVertex2f( 3.41f, -1.27f); // H

    glEnd();

    // Upper bright-red section
    glColor3f(0.92f, 0.15f, 0.07f);

    glBegin(GL_POLYGON);

    glVertex2f(-5.32f, -1.10f); // F
    glVertex2f(-4.90f, -1.33f); // G
    glVertex2f( 3.41f, -1.27f); // H
    glVertex2f( 3.60f, -0.80f); // E
    glVertex2f(-4.60f, -0.78f); // D
    glVertex2f(-5.45f, -0.58f); // C

    glEnd();

    // Hull borders
    drawLine(-5.32f, -1.10f, -4.90f, -1.33f,
             0.10f, 0.10f, 0.10f);

    drawLine(-4.90f, -1.33f, 3.41f, -1.27f,
             0.10f, 0.10f, 0.10f);

    drawLine(-4.17f, -1.76f, 3.45f, -1.71f,
             0.10f, 0.10f, 0.10f);

    drawLine(-6.92f, -2.54f, 6.92f, -2.54f,
             0.10f, 0.10f, 0.10f);
}

// ==========================================================
// MAIN BLUE HULL
// ==========================================================

void drawBlueHull()
{
    /*
        Exact GeoGebra measurements:

        C = (-5.45, -0.58)
        D = (-4.60, -0.78)
        E = ( 3.60, -0.80)

        F = (-5.32, -1.10)
        H = ( 3.41, -1.27)

        K = ( 4.49, 0.64)
        L = (-5.50, 0.00)
        M = (-4.61, -0.10)
        N = ( 1.24, -0.09)
        O = ( 2.15, 0.61)

        Segments:

        f = Segment(C,D) = 0.88
        g = Segment(D,E) = 8.19
        h = Segment(C,F) = 0.53
        p = Segment(L,C) = 0.58
        q = Segment(L,M) = 0.90
        r = Segment(M,N) = 5.85
        s = Segment(N,O) = 1.15
        t = Segment(O,K) = 2.34
    */

    glColor3f(0.02f, 0.22f, 0.36f);

    glBegin(GL_POLYGON);

    glVertex2f(-5.50f,  0.00f); // L
    glVertex2f(-4.61f, -0.10f); // M
    glVertex2f( 1.24f, -0.09f); // N
    glVertex2f( 2.15f,  0.61f); // O
    glVertex2f( 4.49f,  0.64f); // K
    glVertex2f( 3.60f, -0.80f); // E
    glVertex2f(-4.60f, -0.78f); // D
    glVertex2f(-5.45f, -0.58f); // C

    glEnd();

    // Borders
    drawLine(-5.50f, 0.00f, -5.45f, -0.58f,
             0.05f, 0.05f, 0.05f);

    drawLine(-5.50f, 0.00f, -4.61f, -0.10f,
             0.05f, 0.05f, 0.05f);

    drawLine(-4.61f, -0.10f, 1.24f, -0.09f,
             0.05f, 0.05f, 0.05f);

    drawLine(1.24f, -0.09f, 2.15f, 0.61f,
             0.05f, 0.05f, 0.05f);

    drawLine(2.15f, 0.61f, 4.49f, 0.64f,
             0.05f, 0.05f, 0.05f);

    drawLine(4.49f, 0.64f, 3.60f, -0.80f,
             0.05f, 0.05f, 0.05f);
}

// ==========================================================
// WHITE UPPER DECK
// ==========================================================

void drawWhiteDeck()
{
    /*
        Exact measurements:

        P = (-5.43, 0.57)
        Q = (-4.66, 0.62)
        R = (-0.58, 0.60)
        S = (-0.48, 1.17)
        T = ( 2.29, 1.19)
        U = ( 2.32, 0.62)

        Segment lengths:

        a  = Segment(P,L) = 0.58
        b  = Segment(P,Q) = 0.77
        c  = Segment(Q,M) = 0.72
        d  = Segment(Q,R) = 4.08
        e  = Segment(S,R) = 0.58
        f1 = Segment(S,T) = 2.77
        g1 = Segment(T,U) = 0.57
    */

    glColor3f(0.93f, 0.92f, 0.82f);

    glBegin(GL_POLYGON);

    glVertex2f(-5.43f, 0.57f); // P
    glVertex2f(-4.66f, 0.62f); // Q
    glVertex2f(-0.58f, 0.60f); // R
    glVertex2f(-0.48f, 1.17f); // S
    glVertex2f( 2.29f, 1.19f); // T
    glVertex2f( 2.32f, 0.62f); // U
    glVertex2f( 2.15f, 0.61f); // O
    glVertex2f(-5.50f, 0.00f); // L

    glEnd();

    drawLine(-5.43f, 0.57f, -4.66f, 0.62f,
             0.08f, 0.08f, 0.08f);

    drawLine(-4.66f, 0.62f, -0.58f, 0.60f,
             0.08f, 0.08f, 0.08f);

    drawLine(-0.48f, 1.17f, 2.29f, 1.19f,
             0.08f, 0.08f, 0.08f);

    drawLine(2.29f, 1.19f, 2.32f, 0.62f,
             0.08f, 0.08f, 0.08f);
}

// ==========================================================
// BOW AND CRANE
// ==========================================================

void drawBowAndCrane()
{
    /*
        Exact measurements:

        V = (3.50, 2.50)
        W = (3.43, 0.63)
        Z = (3.49, 2.16)
        A1 = (3.22, 2.21)
        K = (4.49, 0.64)

        h1 = Segment(V,W) = 1.87
        i1 = Segment(Z,K) = 1.82
        j1 = Segment(A1,Z) = 0.27
    */

    // Mast
    drawLine(
        3.43f, 0.63f,   // W
        3.50f, 2.50f,   // V
        0.08f, 0.08f, 0.08f,
        5.0f
    );

    // Crane diagonal
    drawLine(
        3.49f, 2.16f,   // Z
        4.49f, 0.64f,   // K
        0.08f, 0.08f, 0.08f,
        2.0f
    );

    // Small upper arm
    drawLine(
        3.22f, 2.21f,   // A1
        3.49f, 2.16f,   // Z
        0.08f, 0.08f, 0.08f,
        3.0f
    );

    // Top mast point
    drawCircle(3.50f, 2.50f, 0.035f,
               0.95f, 0.80f, 0.10f);
}

// ==========================================================
// RED BUILDING ON THE DECK
// ==========================================================

void drawRedBuilding()
{
    /*
        Exact coordinates:

        B1 = (-5.36, 0.78)
        C1 = (-0.72, 0.76)
        D1 = (-0.63, 1.17)

        J1 = (-5.31, 1.08)
        K1 = (-0.72, 1.04)

        t1 = Segment(J1,B1) = 0.30
        a1 = Segment(J1,K1) = 4.60
        l1 = Segment(B1,C1) = 4.64
    */

    // Lower red body
    glColor3f(0.82f, 0.10f, 0.06f);

    glBegin(GL_QUADS);

    glVertex2f(-5.36f, 0.78f); // B1
    glVertex2f(-0.72f, 0.76f); // C1
    glVertex2f(-0.72f, 1.04f); // K1
    glVertex2f(-5.31f, 1.08f); // J1

    glEnd();

    drawRectangleBorder(
        -5.36f, 0.76f,
        -0.72f, 1.08f
    );

    // Large upper structure
    /*
        L1 = (-3.64, 2.17)
        M1 = (-3.61, 0.77)

        N1 = (-1.25, 2.18)
        O1 = (-1.30, 0.78)

        b1 = Segment(L1,M1) = 1.40
        c1 = Segment(L1,N1) = 2.39
        d1 = Segment(N1,O1) = 1.40
    */

    glColor3f(0.88f, 0.18f, 0.08f);

    glBegin(GL_QUADS);

    glVertex2f(-3.61f, 0.77f); // M1
    glVertex2f(-1.30f, 0.78f); // O1
    glVertex2f(-1.25f, 2.18f); // N1
    glVertex2f(-3.64f, 2.17f); // L1

    glEnd();

    drawLine(-3.64f, 2.17f, -1.25f, 2.18f,
             0.08f, 0.08f, 0.08f);

    drawLine(-3.64f, 2.17f, -3.61f, 0.77f,
             0.08f, 0.08f, 0.08f);

    drawLine(-1.25f, 2.18f, -1.30f, 0.78f,
             0.08f, 0.08f, 0.08f);
}

// ==========================================================
// TOP RED ROOF
// ==========================================================

void drawTopRoof()
{
    /*
        Exact coordinates:

        P1 = (-3.89, 2.53)
        Q1 = (-1.19, 2.53)
        R1 = (-3.89, 2.76)
        S1 = (-1.21, 2.77)

        e1 = Segment(L1,P1) = 0.44
        f2 = Segment(P1,Q1) = 2.70
        g2 = Segment(Q1,N1) = 0.35
        h2 = Segment(P1,R1) = 0.23
        i2 = Segment(R1,S1) = 2.68
        j2 = Segment(S1,Q1) = 0.24
    */

    glColor3f(0.72f, 0.05f, 0.03f);

    glBegin(GL_QUADS);

    glVertex2f(-3.89f, 2.53f); // P1
    glVertex2f(-1.19f, 2.53f); // Q1
    glVertex2f(-1.21f, 2.77f); // S1
    glVertex2f(-3.89f, 2.76f); // R1

    glEnd();

    drawRectangleBorder(
        -3.89f, 2.53f,
        -1.19f, 2.77f
    );
}

// ==========================================================
// BRIDGE WINDOWS
// ==========================================================

void drawBridgeWindows()
{
    // Blue window strip
    drawRectangle(
        -5.10f, 1.35f,
        -1.35f, 1.90f,
        0.15f, 0.66f, 0.75f
    );

    // Vertical separators
    drawLine(-4.50f, 1.35f, -4.50f, 1.90f,
             0.92f, 0.92f, 0.80f, 4.0f);

    drawLine(-3.85f, 1.35f, -3.85f, 1.90f,
             0.92f, 0.92f, 0.80f, 4.0f);

    drawLine(-3.15f, 1.35f, -3.15f, 1.90f,
             0.92f, 0.92f, 0.80f, 4.0f);

    drawLine(-2.45f, 1.35f, -2.45f, 1.90f,
             0.92f, 0.92f, 0.80f, 4.0f);

    drawLine(-1.75f, 1.35f, -1.75f, 1.90f,
             0.92f, 0.92f, 0.80f, 4.0f);

    drawRectangleBorder(
        -5.10f, 1.35f,
        -1.35f, 1.90f
    );
}

// ==========================================================
// UPPER YELLOW CHIMNEY
// ==========================================================

void drawYellowChimney()
{
    /*
        Exact measurements:

        B2 = (-1.49, 2.81)
        C2 = (-1.49, 3.33)
        D2 = (-0.89, 3.33)
        E2 = (-0.82, 0.78)

        q2 = Segment(B2,C2) = 0.53
        r2 = Segment(C2,D2) = 0.60
        s2 = Segment(D2,E2) = 2.55
    */

    glColor3f(0.96f, 0.68f, 0.16f);

    glBegin(GL_QUADS);

    glVertex2f(-1.49f, 2.81f); // B2
    glVertex2f(-0.84f, 2.81f);
    glVertex2f(-0.89f, 3.33f); // D2
    glVertex2f(-1.49f, 3.33f); // C2

    glEnd();

    // Red chimney top
    drawRectangle(
        -1.49f, 3.26f,
        -0.89f, 3.33f,
        0.70f, 0.04f, 0.02f
    );

    drawRectangleBorder(
        -1.49f, 2.81f,
        -0.89f, 3.33f
    );
}

// ==========================================================
// TALL CENTRAL FUNNEL
// ==========================================================

void drawTallFunnel()
{
    /*
        Exact coordinates:

        T1 = (-2.23, 4.41)
        U1 = (-2.25, 2.70)

        k2 = Segment(T1,U1) = 1.72

        V1 = (-2.53, 3.93)
        W1 = (-2.48, 3.20)
        Z1 = (-2.04, 3.20)
        A2 = (-1.95, 3.92)

        l2 = Segment(V1,W1) = 0.73
        m2 = Segment(W1,Z1) = 0.44
        n2 = Segment(A2,Z1) = 0.73
        p2 = Segment(V1,A2) = 0.58
    */

    // Lower blue shaft
    drawRectangle(
        -2.35f, 2.70f,
        -2.10f, 3.20f,
        0.05f, 0.30f, 0.40f
    );

    // Upper black funnel
    glColor3f(0.10f, 0.10f, 0.08f);

    glBegin(GL_QUADS);

    glVertex2f(-2.48f, 3.20f); // W1
    glVertex2f(-2.04f, 3.20f); // Z1
    glVertex2f(-1.95f, 3.92f); // A2
    glVertex2f(-2.53f, 3.93f); // V1

    glEnd();

    // Central pipe to top
    drawLine(
        -2.25f, 2.70f, // U1
        -2.23f, 4.41f, // T1
        0.08f, 0.08f, 0.08f,
        5.0f
    );
}

// ==========================================================
// RED AND BLUE CABINS
// ==========================================================

void drawMiddleCabins()
{
    /*
        Red cabin:

        B3 = (-0.16, 0.92)
        C3 = (-0.16, 0.65)
        D3 = ( 0.98, 0.67)
        E3 = ( 0.96, 0.93)

        l3 = Segment(B3,C3) = 0.27
        m3 = Segment(C3,D3) = 1.14
        n3 = Segment(D3,E3) = 0.26
        p3 = Segment(B3,E3) = 1.12
    */

    drawRectangle(
        -0.16f, 0.65f,
        0.98f, 0.93f,
        0.84f, 0.12f, 0.06f
    );

    drawRectangleBorder(
        -0.16f, 0.65f,
        0.98f, 0.93f
    );

    /*
        Upper small cabin:

        F3 = (1.55, 0.90)
        G3 = (1.57, 0.59)
        H3 = (1.92, 0.64)
        I3 = (1.95, 0.92)

        q3 = Segment(F3,G3) = 0.31
        r3 = Segment(G3,H3) = 0.36
        s3 = Segment(F3,I3) = 0.40
        t3 = Segment(I3,H3) = 0.29
    */

    glColor3f(0.20f, 0.67f, 0.76f);

    glBegin(GL_QUADS);

    glVertex2f(1.57f, 0.59f); // G3
    glVertex2f(1.92f, 0.64f); // H3
    glVertex2f(1.95f, 0.92f); // I3
    glVertex2f(1.55f, 0.90f); // F3

    glEnd();

    drawLine(1.55f, 0.90f, 1.57f, 0.59f,
             0.05f, 0.05f, 0.05f);

    drawLine(1.57f, 0.59f, 1.92f, 0.64f,
             0.05f, 0.05f, 0.05f);

    drawLine(1.92f, 0.64f, 1.95f, 0.92f,
             0.05f, 0.05f, 0.05f);
}

// ==========================================================
// ROUND WINDOWS ON THE SHIP
// ==========================================================

void drawRoundWindows()
{
    /*
        O2 = (2.54, 0.31)
        P2 = (2.65, 0.22)

        c3 = Circle(O2,P2)

        Radius:
        sqrt((2.65-2.54)^2 + (0.22-0.31)^2)
        approximately 0.142
    */
    drawCircle(
        2.54f, 0.31f,
        0.142f,
        0.92f, 0.93f, 0.72f
    );

    /*
        Q2 = (2.97, 0.32)
        R2 = (2.97, 0.19)

        d3 = Circle(Q2,R2)
        radius = 0.13
    */
    drawCircle(
        2.97f, 0.32f,
        0.13f,
        0.92f, 0.93f, 0.72f
    );

    /*
        S2 = (3.41, 0.32)
        T2 = (3.41, 0.19)

        e3 = Circle(S2,T2)
        radius = 0.13
    */
    drawCircle(
        3.41f, 0.32f,
        0.13f,
        0.92f, 0.93f, 0.72f
    );

    /*
        U2 = (3.94, 0.35)
        V2 = (3.87, 0.21)

        k3 = Circle(U2,V2)

        Radius:
        sqrt((3.87-3.94)^2 + (0.21-0.35)^2)
        approximately 0.157
    */
    drawCircle(
        3.94f, 0.35f,
        0.157f,
        0.92f, 0.93f, 0.72f
    );

    // Dark centres
    drawCircle(2.54f, 0.31f, 0.045f,
               0.08f, 0.18f, 0.32f);

    drawCircle(2.97f, 0.32f, 0.045f,
               0.08f, 0.18f, 0.32f);

    drawCircle(3.41f, 0.32f, 0.045f,
               0.08f, 0.18f, 0.32f);

    drawCircle(3.94f, 0.35f, 0.045f,
               0.08f, 0.18f, 0.32f);
}

// ==========================================================
// SMALL RECTANGULAR WINDOWS
// ==========================================================

void drawSmallWindow(float left, float bottom,
                     float right, float top)
{
    drawRectangle(
        left, bottom,
        right, top,
        0.94f, 0.88f, 0.58f
    );

    drawRectangleBorder(
        left, bottom,
        right, top
    );

    drawCircle(
        (left + right) / 2.0f,
        (bottom + top) / 2.0f,
        0.025f,
        0.10f, 0.20f, 0.32f
    );
}

void drawPassengerWindows()
{
    /*
        Exact GeoGebra rectangle:

        V4 = (-5.16, 0.39)
        W4 = (-4.97, 0.38)
        Z4 = (-4.95, 0.13)
        A5 = (-5.16, 0.15)

        b5 = Segment(V4,W4) = 0.19
        c5 = Segment(W4,Z4) = 0.25
        d5 = Segment(Z4,A5) = 0.21
        e5 = Segment(A5,V4) = 0.24
    */
    drawSmallWindow(
        -5.16f, 0.13f,
        -4.95f, 0.39f
    );

    /*
        Exact rectangle:

        R4 = (-4.62, 0.41)
        S4 = (-4.41, 0.41)
        T4 = (-4.39, 0.18)
        U4 = (-4.59, 0.18)

        r5 = 0.20
        s5 = 0.23
        t5 = 0.20
        a5 = 0.23
    */
    drawSmallWindow(
        -4.62f, 0.18f,
        -4.39f, 0.41f
    );

    /*
        N4 = (-3.89, 0.41)
        O4 = (-3.70, 0.40)
        P4 = (-3.69, 0.18)
        Q4 = (-3.90, 0.18)
    */
    drawSmallWindow(
        -3.90f, 0.18f,
        -3.69f, 0.41f
    );

    /*
        J4 = (-3.35, 0.42)
        K4 = (-3.16, 0.42)
        L4 = (-3.15, 0.17)
        M4 = (-3.36, 0.17)
    */
    drawSmallWindow(
        -3.36f, 0.17f,
        -3.15f, 0.42f
    );

    /*
        F4 = (-2.82, 0.42)
        G4 = (-2.63, 0.42)
        H4 = (-2.62, 0.18)
        I4 = (-2.81, 0.18)
    */
    drawSmallWindow(
        -2.82f, 0.18f,
        -2.62f, 0.42f
    );

    /*
        B4 = (-1.72, 0.42)
        C4 = (-1.53, 0.42)
        D4 = (-1.53, 0.18)
        E4 = (-1.73, 0.17)
    */
    drawSmallWindow(
        -1.73f, 0.17f,
        -1.53f, 0.42f
    );

    /*
        B5 = (-1.86, 2.04)
        C5 = (-1.66, 2.04)
        D5 = (-1.66, 1.89)
        E5 = (-1.85, 1.88)
    */
    drawSmallWindow(
        -1.86f, 1.88f,
        -1.66f, 2.04f
    );

    /*
        F5 = (-2.35, 2.02)
        G5 = (-2.35, 1.87)
        H5 = (-2.14, 1.87)
        I5 = (-2.14, 2.02)
    */
    drawSmallWindow(
        -2.35f, 1.87f,
        -2.14f, 2.02f
    );

    /*
        J5 = (-2.85, 2.03)
        K5 = (-2.66, 2.02)
        L5 = (-2.66, 1.88)
        M5 = (-2.85, 1.89)
    */
    drawSmallWindow(
        -2.85f, 1.88f,
        -2.66f, 2.03f
    );

    /*
        N5 = (-3.35, 2.03)
        O5 = (-3.17, 2.03)
        P5 = (-3.17, 1.89)
        Q5 = (-3.35, 1.89)
    */
    drawSmallWindow(
        -3.35f, 1.89f,
        -3.17f, 2.03f
    );
}

// ==========================================================
// DISPLAY FUNCTION
// ==========================================================

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    drawWater();

    // Draw objects from back to front
    drawLowerHull();
    drawBlueHull();
    drawWhiteDeck();

    drawRedBuilding();
    drawTopRoof();
    drawBridgeWindows();

    drawTallFunnel();
    drawYellowChimney();

    drawMiddleCabins();
    drawPassengerWindows();

    drawBowAndCrane();
    drawRoundWindows();

    glFlush();
}

// ==========================================================
// WINDOW RESIZE
// ==========================================================

void reshape(int width, int height)
{
    if (height == 0)
    {
        height = 1;
    }

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /*
        Coordinate range based on the GeoGebra graph.

        Main x range:
        approximately -7 to +7

        Main y range:
        approximately -2.8 to +4.8
    */
    gluOrtho2D(
        -7.2, 7.2,
        -2.8, 4.8
    );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// ==========================================================
// INITIALIZATION
// ==========================================================

void initialize()
{
    glClearColor(
        0.88f,
        0.95f,
        0.98f,
        1.0f
    );

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

// ==========================================================
// MAIN FUNCTION
// ==========================================================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_SINGLE | GLUT_RGB
    );

    glutInitWindowSize(1400, 750);
    glutInitWindowPosition(50, 50);

    glutCreateWindow(
        "Ship Using GeoGebra Measurements"
    );

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
