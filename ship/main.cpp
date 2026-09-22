#include<windows.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

const float PI = 3.14159265358979323846f;

// ============================================================
// BASIC DRAWING FUNCTIONS
// ============================================================

void setColor(float red, float green, float blue)
{
    glColor3f(red, green, blue);
}

void drawLine(float x1,
              float y1,
              float x2,
              float y2,
              float width = 2.0f)
{
    glLineWidth(width);

    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawPolygon(const float points[][2], int totalPoints)
{
    glBegin(GL_POLYGON);

    for (int i = 0; i < totalPoints; i++)
    {
        glVertex2f(points[i][0], points[i][1]);
    }

    glEnd();
}

void drawPolygonOutline(const float points[][2],
                        int totalPoints,
                        float width = 2.0f)
{
    glLineWidth(width);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < totalPoints; i++)
    {
        glVertex2f(points[i][0], points[i][1]);
    }

    glEnd();
}

void drawRectangle(float left,
                   float bottom,
                   float right,
                   float top)
{
    glBegin(GL_QUADS);

    glVertex2f(left, bottom);
    glVertex2f(right, bottom);
    glVertex2f(right, top);
    glVertex2f(left, top);

    glEnd();
}

void drawRectangleOutline(float left,
                          float bottom,
                          float right,
                          float top,
                          float width = 2.0f)
{
    glLineWidth(width);

    glBegin(GL_LINE_LOOP);

    glVertex2f(left, bottom);
    glVertex2f(right, bottom);
    glVertex2f(right, top);
    glVertex2f(left, top);

    glEnd();
}

void drawCircle(float centerX,
                float centerY,
                float radius,
                int segments = 100)
{
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(centerX, centerY);

    for (int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * PI * i / segments;

        glVertex2f(
            centerX + radius * cos(angle),
            centerY + radius * sin(angle)
        );
    }

    glEnd();
}

void drawCircleOutline(float centerX,
                       float centerY,
                       float radius,
                       int segments = 100,
                       float width = 2.0f)
{
    glLineWidth(width);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < segments; i++)
    {
        float angle = 2.0f * PI * i / segments;

        glVertex2f(
            centerX + radius * cos(angle),
            centerY + radius * sin(angle)
        );
    }

    glEnd();
}

// ============================================================
// SEA
// ============================================================

void drawSea()
{
    // GeoGebra water area:
    // K2 = (-5.26, -1.76)
    // L2 = (-5.25, -1.93)
    // M2 = (4.30, -1.96)
    // N2 = (4.24, -1.71)

    float sea[][2] =
    {
        {-6.90f, -1.78f},
        {-5.26f, -1.76f},
        {-5.25f, -1.93f},
        { 4.30f, -1.96f},
        { 6.90f, -1.94f},
        { 6.90f, -2.15f},
        {-6.90f, -2.15f}
    };

    setColor(0.55f, 0.88f, 0.92f);
    drawPolygon(sea, 7);

    setColor(0.20f, 0.60f, 0.70f);
    drawPolygonOutline(sea, 7, 1.5f);
}

// ============================================================
// LOWER RED HULL
// ============================================================

void drawLowerRedHull()
{
    /*
        GeoGebra points:

        C = (-5.45, -0.58)
        D = (-4.60, -0.78)
        E = ( 3.60, -0.80)
        F = (-5.32, -1.10)
        G = (-4.90, -1.33)
        H = ( 3.41, -1.27)
        I = (-4.17, -1.76)
        J = ( 3.45, -1.71)
        K = ( 4.49,  0.64)

        h = Segment(C,F) = 0.53
        i = Segment(F,G) = 0.48
        j = Segment(G,H) = 8.31
        k = Segment(G,I) = 0.85
        l = Segment(I,J) = 7.62
        m = Segment(H,J) = 0.44
        n = Segment(K,H) = 2.20
    */

    float hull[][2] =
    {
        {-5.45f, -0.58f}, // C
        {-4.60f, -0.78f}, // D
        { 3.60f, -0.80f}, // E
        { 4.49f,  0.64f}, // K
        { 3.41f, -1.27f}, // H
        { 3.45f, -1.71f}, // J
        {-4.17f, -1.76f}, // I
        {-4.90f, -1.33f}, // G
        {-5.32f, -1.10f}  // F
    };

    setColor(0.82f, 0.08f, 0.05f);
    drawPolygon(hull, 9);

    setColor(0.08f, 0.08f, 0.08f);
    drawPolygonOutline(hull, 9, 3.0f);

    // Dark red lower strip
    float lowerStrip[][2] =
    {
        {-4.90f, -1.33f},
        { 3.41f, -1.27f},
        { 3.45f, -1.71f},
        {-4.17f, -1.76f}
    };

    setColor(0.35f, 0.03f, 0.02f);
    drawPolygon(lowerStrip, 4);

    setColor(0.08f, 0.05f, 0.05f);
    drawPolygonOutline(lowerStrip, 4, 2.0f);

    // Bright red horizontal highlight
    setColor(1.0f, 0.22f, 0.12f);
    drawLine(-5.28f, -1.08f, 3.52f, -1.07f, 3.0f);
}

// ============================================================
// BLUE HULL
// ============================================================

void drawBlueHull()
{
    /*
        GeoGebra points:

        L = (-5.50,  0.00)
        M = (-4.61, -0.10)
        N = ( 1.24, -0.09)
        O = ( 2.15,  0.61)
        K = ( 4.49,  0.64)
        E = ( 3.60, -0.80)
        D = (-4.60, -0.78)
        C = (-5.45, -0.58)

        p = Segment(L,C) = 0.58
        q = Segment(L,M) = 0.90
        r = Segment(M,N) = 5.85
        s = Segment(N,O) = 1.15
        t = Segment(O,K) = 2.34
    */

    float blueHull[][2] =
    {
        {-5.50f,  0.00f}, // L
        {-4.61f, -0.10f}, // M
        { 1.24f, -0.09f}, // N
        { 2.15f,  0.61f}, // O
        { 4.49f,  0.64f}, // K
        { 3.60f, -0.80f}, // E
        {-4.60f, -0.78f}, // D
        {-5.45f, -0.58f}  // C
    };

    setColor(0.02f, 0.24f, 0.40f);
    drawPolygon(blueHull, 8);

    setColor(0.03f, 0.08f, 0.12f);
    drawPolygonOutline(blueHull, 8, 3.0f);

    // Upper blue hull edge
    setColor(0.08f, 0.45f, 0.58f);

    drawLine(-5.50f, 0.00f, -4.61f, -0.10f, 2.0f);
    drawLine(-4.61f, -0.10f, 1.24f, -0.09f, 2.0f);
    drawLine(1.24f, -0.09f, 2.15f, 0.61f, 2.0f);
    drawLine(2.15f, 0.61f, 4.49f, 0.64f, 2.0f);
}

// ============================================================
// CREAM MAIN DECK
// ============================================================

void drawMainDeck()
{
    /*
        GeoGebra points:

        P = (-5.43, 0.57)
        Q = (-4.66, 0.62)
        R = (-0.58, 0.60)
        S = (-0.48, 1.17)
        T = ( 2.29, 1.19)
        U = ( 2.32, 0.62)

        a = Segment(P,L) = 0.58
        b = Segment(P,Q) = 0.77
        c = Segment(Q,M) = 0.72
        d = Segment(Q,R) = 4.08
        e = Segment(S,R) = 0.58
        f1 = Segment(S,T) = 2.77
        g1 = Segment(T,U) = 0.57
    */

    float deck[][2] =
    {
        {-5.43f, 0.57f}, // P
        {-4.66f, 0.62f}, // Q
        {-0.58f, 0.60f}, // R
        {-0.48f, 1.17f}, // S
        { 2.29f, 1.19f}, // T
        { 2.32f, 0.62f}, // U
        { 2.15f, 0.61f}, // O
        { 1.24f,-0.09f}, // N
        {-4.61f,-0.10f}, // M
        {-5.50f, 0.00f}  // L
    };

    setColor(0.91f, 0.80f, 0.57f);
    drawPolygon(deck, 10);

    setColor(0.10f, 0.10f, 0.10f);
    drawPolygonOutline(deck, 10, 2.5f);
}

// ============================================================
// SMALL WINDOW
// ============================================================

void drawSmallWindow(float left,
                     float right,
                     float top,
                     float bottom)
{
    setColor(0.72f, 0.84f, 0.86f);
    drawRectangle(left, bottom, right, top);

    setColor(0.08f, 0.12f, 0.14f);
    drawRectangleOutline(left, bottom, right, top, 1.5f);

    setColor(0.35f, 0.50f, 0.55f);
    drawLine(
        left + 0.03f,
        bottom + 0.02f,
        right - 0.03f,
        top - 0.02f,
        1.0f
    );
}

// ============================================================
// LOWER DECK WINDOWS
// ============================================================

void drawLowerDeckWindows()
{
    /*
        Window 1:
        V4 = (-5.16, 0.39)
        W4 = (-4.97, 0.38)
        Z4 = (-4.95, 0.13)
        A5 = (-5.16, 0.15)
    */
    drawSmallWindow(-5.16f, -4.95f, 0.39f, 0.13f);

    /*
        Window 2:
        R4 = (-4.62, 0.41)
        S4 = (-4.41, 0.41)
        T4 = (-4.39, 0.18)
        U4 = (-4.59, 0.18)
    */
    drawSmallWindow(-4.62f, -4.39f, 0.41f, 0.18f);

    /*
        Window 3:
        N4 = (-3.89, 0.41)
        O4 = (-3.70, 0.40)
        P4 = (-3.69, 0.18)
        Q4 = (-3.90, 0.18)
    */
    drawSmallWindow(-3.90f, -3.69f, 0.41f, 0.18f);

    /*
        Window 4:
        J4 = (-3.35, 0.42)
        K4 = (-3.16, 0.42)
        L4 = (-3.15, 0.17)
        M4 = (-3.36, 0.17)
    */
    drawSmallWindow(-3.36f, -3.15f, 0.42f, 0.17f);

    /*
        Window 5:
        F4 = (-2.82, 0.42)
        G4 = (-2.63, 0.42)
        H4 = (-2.62, 0.18)
        I4 = (-2.81, 0.18)
    */
    drawSmallWindow(-2.82f, -2.62f, 0.42f, 0.18f);

    /*
        Window 6:
        V3 = (-2.26, 0.42)
        W3 = (-2.08, 0.42)
        Z3 = (-2.07, 0.17)
        A4 = (-2.26, 0.17)
    */
    drawSmallWindow(-2.26f, -2.07f, 0.42f, 0.17f);

    /*
        Window 7:
        B4 = (-1.72, 0.42)
        C4 = (-1.53, 0.42)
        D4 = (-1.53, 0.18)
        E4 = (-1.73, 0.17)
    */
    drawSmallWindow(-1.73f, -1.53f, 0.42f, 0.17f);

    /*
        Window 8:
        R3 = (-0.67, 0.41)
        S3 = (-0.48, 0.42)
        T3 = (-0.47, 0.17)
        U3 = (-0.67, 0.17)
    */
    drawSmallWindow(-0.67f, -0.47f, 0.42f, 0.17f);

    /*
        Window 9:
        N3 = (-0.09, 0.44)
        O3 = ( 0.12, 0.44)
        P3 = ( 0.13, 0.16)
        Q3 = (-0.10, 0.16)
    */
    drawSmallWindow(-0.10f, 0.13f, 0.44f, 0.16f);
}

// ============================================================
// LOWER RED SUPERSTRUCTURE
// ============================================================

void drawLowerSuperstructure()
{
    /*
        B1 = (-5.36, 0.78)
        C1 = (-0.72, 0.76)
        D1 = (-0.63, 1.17)
        J1 = (-5.31, 1.08)
        K1 = (-0.72, 1.04)
    */

    float structure[][2] =
    {
        {-5.36f, 0.78f},
        {-0.72f, 0.76f},
        {-0.63f, 1.17f},
        {-5.31f, 1.08f}
    };

    setColor(0.84f, 0.10f, 0.07f);
    drawPolygon(structure, 4);

    setColor(0.10f, 0.08f, 0.08f);
    drawPolygonOutline(structure, 4, 2.5f);

    // Vertical panel lines
    setColor(0.35f, 0.05f, 0.04f);

    drawLine(-4.05f, 0.78f, -4.05f, 1.09f, 1.5f);
    drawLine(-2.60f, 0.77f, -2.60f, 1.12f, 1.5f);
    drawLine(-1.30f, 0.77f, -1.30f, 1.15f, 1.5f);
}

// ============================================================
// MAIN PASSENGER CABIN
// ============================================================

void drawPassengerCabin()
{
    /*
        L1 = (-3.64, 2.17)
        M1 = (-3.61, 0.77)
        N1 = (-1.25, 2.18)
        O1 = (-1.30, 0.78)

        P1 = (-3.89, 2.53)
        Q1 = (-1.19, 2.53)
        R1 = (-3.89, 2.76)
        S1 = (-1.21, 2.77)
    */

    // Cream cabin
    float cabin[][2] =
    {
        {-3.64f, 2.17f},
        {-1.25f, 2.18f},
        {-1.30f, 0.78f},
        {-3.61f, 0.77f}
    };

    setColor(0.91f, 0.80f, 0.57f);
    drawPolygon(cabin, 4);

    setColor(0.10f, 0.10f, 0.10f);
    drawPolygonOutline(cabin, 4, 2.5f);

    // Blue window strip
    float windowStrip[][2] =
    {
        {-3.64f, 2.17f},
        {-1.25f, 2.18f},
        {-1.19f, 2.53f},
        {-3.89f, 2.53f}
    };

    setColor(0.18f, 0.62f, 0.70f);
    drawPolygon(windowStrip, 4);

    setColor(0.08f, 0.12f, 0.14f);
    drawPolygonOutline(windowStrip, 4, 2.0f);

    // Window strip separators
    setColor(0.15f, 0.30f, 0.34f);

    drawLine(-3.45f, 2.17f, -3.45f, 2.50f, 1.5f);
    drawLine(-3.10f, 2.17f, -3.10f, 2.50f, 1.5f);
    drawLine(-2.75f, 2.17f, -2.75f, 2.50f, 1.5f);
    drawLine(-2.40f, 2.17f, -2.40f, 2.50f, 1.5f);
    drawLine(-2.05f, 2.17f, -2.05f, 2.50f, 1.5f);
    drawLine(-1.70f, 2.17f, -1.70f, 2.50f, 1.5f);
    drawLine(-1.35f, 2.17f, -1.35f, 2.50f, 1.5f);

    // Red roof
    float roof[][2] =
    {
        {-3.89f, 2.53f},
        {-1.19f, 2.53f},
        {-1.21f, 2.77f},
        {-3.89f, 2.76f}
    };

    setColor(0.83f, 0.08f, 0.05f);
    drawPolygon(roof, 4);

    setColor(0.08f, 0.08f, 0.08f);
    drawPolygonOutline(roof, 4, 2.5f);
}

// ============================================================
// UPPER SMALL WINDOWS
// ============================================================

void drawUpperSmallWindows()
{
    // B5, C5, D5, E5
    drawSmallWindow(-1.86f, -1.66f, 2.04f, 1.88f);

    // F5, G5, H5, I5
    drawSmallWindow(-2.35f, -2.14f, 2.02f, 1.87f);

    // J5, K5, L5, M5
    drawSmallWindow(-2.85f, -2.66f, 2.03f, 1.88f);

    // N5, O5, P5, Q5
    drawSmallWindow(-3.35f, -3.17f, 2.03f, 1.89f);
}

// ============================================================
// REAR RAILING
// ============================================================

void drawRearRailing()
{
    setColor(0.12f, 0.12f, 0.12f);

    drawLine(-5.30f, 1.62f, -3.60f, 1.62f, 1.8f);
    drawLine(-5.30f, 1.30f, -3.60f, 1.30f, 1.8f);

    drawLine(-5.30f, 1.30f, -5.30f, 1.62f, 1.3f);
    drawLine(-5.00f, 1.30f, -5.00f, 1.62f, 1.3f);
    drawLine(-4.70f, 1.30f, -4.70f, 1.62f, 1.3f);
    drawLine(-4.40f, 1.30f, -4.40f, 1.62f, 1.3f);
    drawLine(-4.10f, 1.30f, -4.10f, 1.62f, 1.3f);
    drawLine(-3.80f, 1.30f, -3.80f, 1.62f, 1.3f);
    drawLine(-3.60f, 1.30f, -3.60f, 1.62f, 1.3f);
}

// ============================================================
// CENTRAL CABIN
// ============================================================

void drawCentralCabin()
{
    /*
        E1 = (-0.51, 2.08)
        F1 = ( 0.45, 2.08)
        G1 = ( 0.45, 1.17)
        H1 = (-0.06, 2.08)
        I1 = (-0.03, 1.21)
    */

    // Red part
    float redPart[][2] =
    {
        {-0.51f, 2.08f},
        {-0.06f, 2.08f},
        {-0.03f, 1.21f},
        {-0.48f, 1.17f}
    };

    setColor(0.86f, 0.10f, 0.06f);
    drawPolygon(redPart, 4);

    setColor(0.08f, 0.08f, 0.08f);
    drawPolygonOutline(redPart, 4, 2.0f);

    // Blue part
    float bluePart[][2] =
    {
        {-0.06f, 2.08f},
        { 0.45f, 2.08f},
        { 0.45f, 1.17f},
        {-0.03f, 1.21f}
    };

    setColor(0.15f, 0.61f, 0.69f);
    drawPolygon(bluePart, 4);

    setColor(0.08f, 0.08f, 0.08f);
    drawPolygonOutline(bluePart, 4, 2.0f);
}

// ============================================================
// FRONT RAILING
// ============================================================

void drawFrontRailing()
{
    setColor(0.12f, 0.12f, 0.12f);

    drawLine(0.45f, 1.17f, 1.77f, 1.18f, 1.7f);
    drawLine(0.45f, 1.47f, 1.77f, 1.47f, 1.7f);

    drawLine(0.45f, 1.17f, 0.45f, 1.47f, 1.2f);
    drawLine(0.75f, 1.17f, 0.75f, 1.47f, 1.2f);
    drawLine(1.05f, 1.17f, 1.05f, 1.47f, 1.2f);
    drawLine(1.35f, 1.17f, 1.35f, 1.47f, 1.2f);
    drawLine(1.65f, 1.17f, 1.65f, 1.47f, 1.2f);
    drawLine(1.77f, 1.18f, 1.77f, 1.47f, 1.2f);
}

// ============================================================
// FRONT CABINS
// ============================================================

void drawFrontCabins()
{
    /*
        First cabin:
        B3 = (-0.16, 0.92)
        C3 = (-0.16, 0.65)
        D3 = ( 0.98, 0.67)
        E3 = ( 0.96, 0.93)
    */

    float firstCabin[][2] =
    {
        {-0.16f, 0.92f},
        { 0.96f, 0.93f},
        { 0.98f, 0.67f},
        {-0.16f, 0.65f}
    };

    setColor(0.88f, 0.85f, 0.73f);
    drawPolygon(firstCabin, 4);

    setColor(0.10f, 0.10f, 0.10f);
    drawPolygonOutline(firstCabin, 4, 2.0f);

    // Blue windows
    setColor(0.15f, 0.60f, 0.70f);
    drawRectangle(-0.08f, 0.70f, 0.10f, 0.86f);
    drawRectangle( 0.17f, 0.70f, 0.35f, 0.86f);

    /*
        Second cabin:
        F3 = (1.55, 0.90)
        G3 = (1.57, 0.59)
        H3 = (1.92, 0.64)
        I3 = (1.95, 0.92)
    */

    float secondCabin[][2] =
    {
        {1.55f, 0.90f},
        {1.95f, 0.92f},
        {1.92f, 0.64f},
        {1.57f, 0.59f}
    };

    setColor(0.88f, 0.85f, 0.73f);
    drawPolygon(secondCabin, 4);

    setColor(0.10f, 0.10f, 0.10f);
    drawPolygonOutline(secondCabin, 4, 2.0f);

    setColor(0.15f, 0.60f, 0.70f);
    drawRectangle(1.61f, 0.66f, 1.74f, 0.84f);
}

// ============================================================
// CHIMNEY
// ============================================================

void drawChimney()
{
    /*
        B2 = (-1.49, 2.81)
        C2 = (-1.49, 3.33)
        D2 = (-0.89, 3.33)
        E2 = (-0.82, 0.78)
    */

    float chimney[][2] =
    {
        {-1.49f, 2.81f},
        {-1.49f, 3.33f},
        {-0.89f, 3.33f},
        {-0.86f, 2.79f}
    };

    setColor(0.95f, 0.58f, 0.14f);
    drawPolygon(chimney, 4);

    setColor(0.08f, 0.08f, 0.08f);
    drawPolygonOutline(chimney, 4, 2.5f);

    // Dark chimney top
    setColor(0.50f, 0.04f, 0.02f);
    drawRectangle(-1.49f, 3.23f, -0.89f, 3.33f);
}

// ============================================================
// MAIN MAST
// ============================================================

void drawMainMast()
{
    /*
        T1 = (-2.23, 4.41)
        U1 = (-2.25, 2.70)
        V1 = (-2.53, 3.93)
        W1 = (-2.48, 3.20)
        Z1 = (-2.04, 3.20)
        A2 = (-1.95, 3.92)
    */

    setColor(0.08f, 0.08f, 0.08f);

    // Main vertical mast
    drawLine(-2.23f, 2.70f, -2.23f, 4.41f, 4.0f);

    // Mast cabin
    float mastCabin[][2] =
    {
        {-2.53f, 3.93f},
        {-1.95f, 3.92f},
        {-2.04f, 3.20f},
        {-2.48f, 3.20f}
    };

    setColor(0.72f, 0.76f, 0.74f);
    drawPolygon(mastCabin, 4);

    setColor(0.08f, 0.08f, 0.08f);
    drawPolygonOutline(mastCabin, 4, 2.5f);

    drawLine(-2.49f, 3.50f, -2.00f, 3.50f, 2.0f);

    // Red top light
    setColor(0.90f, 0.10f, 0.06f);
    drawCircle(-2.23f, 4.41f, 0.035f);
}

// ============================================================
// FRONT MAST
// ============================================================

void drawFrontMast()
{
    /*
        V = (3.50, 2.50)
        W = (3.43, 0.63)
        Z = (3.49, 2.16)
        A1 = (3.22, 2.21)
        K = (4.49, 0.64)
    */

    setColor(0.08f, 0.08f, 0.08f);

    // Vertical mast
    drawLine(3.43f, 0.63f, 3.50f, 2.50f, 4.0f);

    // Small top arm
    drawLine(3.22f, 2.21f, 3.49f, 2.16f, 3.0f);

    // Diagonal support
    drawLine(3.49f, 2.16f, 4.49f, 0.64f, 2.0f);

    // Top red light
    setColor(0.90f, 0.10f, 0.05f);
    drawCircle(3.50f, 2.50f, 0.035f);
}

// ============================================================
// PORTHOLES
// ============================================================

void drawPorthole(float centerX, float centerY)
{
    /*
        Circle equation:
        (x - h)^2 + (y - k)^2 = 0.02

        Radius = square root of 0.02
    */

    float radius = sqrt(0.02f);

    // Dark outer border
    setColor(0.03f, 0.10f, 0.14f);
    drawCircle(centerX, centerY, radius);

    // Cream inside
    setColor(0.88f, 0.88f, 0.68f);
    drawCircle(centerX, centerY, radius * 0.68f);

    setColor(0.02f, 0.08f, 0.10f);
    drawCircleOutline(centerX, centerY, radius, 80, 2.0f);

    // Small highlight
    setColor(1.0f, 1.0f, 0.90f);
    drawCircle(
        centerX - 0.035f,
        centerY + 0.035f,
        0.02f
    );
}

void drawPortholes()
{
    /*
        c3: Circle(O2,P2)
        O2 = (2.54, 0.31)
    */
    drawPorthole(2.54f, 0.31f);

    /*
        d3: Circle(Q2,R2)
        Q2 = (2.97, 0.32)
    */
    drawPorthole(2.97f, 0.32f);

    /*
        e3: Circle(S2,T2)
        S2 = (3.41, 0.32)
    */
    drawPorthole(3.41f, 0.32f);

    /*
        k3: Circle(U2,V2)
        U2 = (3.94, 0.35)
    */
    drawPorthole(3.94f, 0.35f);
}

// ============================================================
// BOW ANCHOR
// ============================================================

void drawBowAnchor()
{
    /*
        J3 = (3.21, -0.42)
        K3 = (3.51, -0.41)
        L3 = (3.17, -1.14)
        M3 = (2.83, -1.12)
    */

    float anchor[][2] =
    {
        {3.21f, -0.42f},
        {3.51f, -0.41f},
        {3.17f, -1.14f},
        {2.83f, -1.12f}
    };

    setColor(0.70f, 0.74f, 0.74f);
    drawPolygon(anchor, 4);

    setColor(0.05f, 0.07f, 0.08f);
    drawPolygonOutline(anchor, 4, 2.0f);

    setColor(0.03f, 0.04f, 0.04f);
    drawCircle(3.21f, -0.53f, 0.07f);
}

// ============================================================
// EXTRA SHIP LINES
// ============================================================

void drawShipDetails()
{
    setColor(0.10f, 0.10f, 0.10f);

    // Main long deck line
    drawLine(-5.43f, 0.57f, 2.32f, 0.62f, 2.0f);

    // Upper deck line
    drawLine(-5.31f, 1.08f, -0.63f, 1.17f, 2.0f);

    // Supports near center
    drawLine(-0.82f, 0.78f, -0.82f, 1.60f, 2.0f);
    drawLine(-1.27f, 0.78f, -1.27f, 1.60f, 2.0f);
}

// ============================================================
// COMPLETE SHIP
// ============================================================

void drawShip()
{
    drawSea();

    drawLowerRedHull();
    drawBlueHull();

    drawMainDeck();
    drawLowerDeckWindows();

    drawLowerSuperstructure();

    drawPassengerCabin();
    drawUpperSmallWindows();

    drawRearRailing();

    drawCentralCabin();
    drawFrontRailing();
    drawFrontCabins();

    drawChimney();

    drawMainMast();
    drawFrontMast();

    drawPortholes();
    drawBowAnchor();

    drawShipDetails();
}

// ============================================================
// DISPLAY
// ============================================================

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawShip();

    glutSwapBuffers();
}

// ============================================================
// CORRECTED RESHAPE FUNCTION
// PRESERVES THE GEOGEBRA ASPECT RATIO
// ============================================================

void reshape(int width, int height)
{
    if (height == 0)
    {
        height = 1;
    }

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float windowAspect =
        static_cast<float>(width) /
        static_cast<float>(height);

    /*
        Original GeoGebra visible coordinate range:

        X-axis: approximately -7.2 to 7.2
        Y-axis: approximately -2.7 to 4.7
    */

    const float left   = -7.2f;
    const float right  =  7.2f;
    const float bottom = -2.7f;
    const float top    =  4.7f;

    float worldWidth = right - left;
    float worldHeight = top - bottom;

    float worldAspect = worldWidth / worldHeight;

    float centerX = (left + right) / 2.0f;
    float centerY = (bottom + top) / 2.0f;

    if (windowAspect > worldAspect)
    {
        /*
            The window is wider than the GeoGebra coordinate area.

            Keep the vertical range unchanged and increase the
            visible horizontal range.
        */

        float newWidth = worldHeight * windowAspect;
        float halfWidth = newWidth / 2.0f;

        glOrtho(
            centerX - halfWidth,
            centerX + halfWidth,
            bottom,
            top,
            -1.0f,
            1.0f
        );
    }
    else
    {
        /*
            The window is taller than the GeoGebra coordinate area.

            Keep the horizontal range unchanged and increase the
            visible vertical range.
        */

        float newHeight = worldWidth / windowAspect;
        float halfHeight = newHeight / 2.0f;

        glOrtho(
            left,
            right,
            centerY - halfHeight,
            centerY + halfHeight,
            -1.0f,
            1.0f
        );
    }

    glMatrixMode(GL_MODELVIEW);
}

// ============================================================
// KEYBOARD
// ============================================================

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
        case 'q':
        case 'Q':
            exit(0);
            break;
    }
}

// ============================================================
// INITIALIZATION
// ============================================================

void initialize()
{
    // Light background similar to the reference image
    glClearColor(0.94f, 0.95f, 0.97f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

// ============================================================
// MAIN
// ============================================================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB
    );

    // Wide window matching the reference ship image
    glutInitWindowSize(1500, 750);
    glutInitWindowPosition(50, 50);

    glutCreateWindow(
        "Cargo Ship - GeoGebra Measurement"
    );

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
