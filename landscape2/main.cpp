#include<windows.h>
#include <GL/glut.h>
#include <cmath>

#define PI 3.14159265358979323846f

// ============================================================
// BASIC DRAWING FUNCTIONS
// ============================================================

// Draw a filled circle using its centre and radius.
void drawCircle(float centerX, float centerY, float radius,
                float red, float green, float blue)
{
    glColor3f(red, green, blue);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(centerX, centerY);

    for (int i = 0; i <= 120; i++)
    {
        float angle = 2.0f * PI * i / 120.0f;

        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);

        glVertex2f(x, y);
    }

    glEnd();
}

// Draw a straight segment between two GeoGebra points.
void drawSegment(float x1, float y1,
                 float x2, float y2,
                 float red, float green, float blue,
                 float width)
{
    glColor3f(red, green, blue);
    glLineWidth(width);

    glBegin(GL_LINES);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glEnd();

    glLineWidth(1.0f);
}

// Draw a filled rotated ellipse.
void drawRotatedEllipse(float centerX, float centerY,
                        float radiusA, float radiusB,
                        float angleDegree,
                        float red, float green, float blue)
{
    float angleRotation = angleDegree * PI / 180.0f;

    glColor3f(red, green, blue);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(centerX, centerY);

    for (int i = 0; i <= 150; i++)
    {
        float angle = 2.0f * PI * i / 150.0f;

        float localX = radiusA * cos(angle);
        float localY = radiusB * sin(angle);

        float x =
            centerX +
            localX * cos(angleRotation) -
            localY * sin(angleRotation);

        float y =
            centerY +
            localX * sin(angleRotation) +
            localY * cos(angleRotation);

        glVertex2f(x, y);
    }

    glEnd();
}

// ============================================================
// SKY
// ============================================================

void drawSky()
{
    glBegin(GL_QUADS);

    // Bottom sky colour
    glColor3f(0.12f, 0.72f, 0.92f);
    glVertex2f(-10.0f, -6.0f);
    glVertex2f(13.5f, -6.0f);

    // Top sky colour
    glColor3f(0.04f, 0.58f, 0.88f);
    glVertex2f(13.5f, 12.0f);
    glVertex2f(-10.0f, 12.0f);

    glEnd();
}

// ============================================================
// CLOUD 1: LEFT CLOUD
// Exact measurements from K3, L3, M3, N3 and O3
// ============================================================

void drawLeftCloud()
{
    /*
       GeoGebra:
       K3 = (-6.15, 6.30)
       c4 = Circle(K3, 0.5341273759694235)
    */
    drawCircle(
        -6.15f, 6.30f,
        0.5341273759694235f,
        1.0f, 1.0f, 1.0f
    );

    /*
       GeoGebra:
       L3 = (-5.51, 6.25)
       d4 = Circle(L3, 0.5077695293832583)
    */
    drawCircle(
        -5.51f, 6.25f,
        0.5077695293832583f,
        1.0f, 1.0f, 1.0f
    );

    /*
       GeoGebra:
       M3 = (-5.21, 5.84)
       e4 = Circle(M3, 0.5349157431598349)
    */
    drawCircle(
        -5.21f, 5.84f,
        0.5349157431598349f,
        1.0f, 1.0f, 1.0f
    );

    /*
       GeoGebra:
       N3 = (-6.72, 5.81)
       f4 = Circle(N3, 0.45511896590639667)
    */
    drawCircle(
        -6.72f, 5.81f,
        0.45511896590639667f,
        1.0f, 1.0f, 1.0f
    );

    /*
       GeoGebra:
       O3 = (-5.99, 5.69)
       g4 = Circle(O3, 0.3833032202130376)
    */
    drawCircle(
        -5.99f, 5.69f,
        0.3833032202130376f,
        1.0f, 1.0f, 1.0f
    );
}

// ============================================================
// CLOUD 2: MIDDLE CLOUD
// Exact measurements from F3, G3, H3, I3 and J3
// ============================================================

void drawMiddleCloud()
{
    /*
       GeoGebra:
       F3 = (4.97, 5.45)
       p3 = Circle(F3, 0.5639593536917924)
    */
    drawCircle(
        4.97f, 5.45f,
        0.5639593536917924f,
        1.0f, 1.0f, 1.0f
    );

    /*
       GeoGebra:
       G3 = (5.55, 5.45)
       q3 = Circle(G3, 0.4313166556863977)
    */
    drawCircle(
        5.55f, 5.45f,
        0.4313166556863977f,
        1.0f, 1.0f, 1.0f
    );

    /*
       GeoGebra:
       H3 = (5.73, 5.04)
       r3 = Circle(H3, 0.525271009872025)
    */
    drawCircle(
        5.73f, 5.04f,
        0.525271009872025f,
        1.0f, 1.0f, 1.0f
    );

    /*
       GeoGebra:
       I3 = (4.33, 5.06)
       s3 = Circle(I3, 0.5448839700902541)
    */
    drawCircle(
        4.33f, 5.06f,
        0.5448839700902541f,
        1.0f, 1.0f, 1.0f
    );

    /*
       GeoGebra:
       J3 = (4.93, 4.89)
       t3 = Circle(J3, 0.44951443976738154)
    */
    drawCircle(
        4.93f, 4.89f,
        0.44951443976738154f,
        1.0f, 1.0f, 1.0f
    );
}

// ============================================================
// CLOUD 3: RIGHT CLOUD
// Exact measurements from P3, Q3, R3, S3 and T3
// ============================================================

void drawRightCloud()
{
    /*
       GeoGebra:
       P3 = (10.43, 4.10)
       h4 = Circle(P3, 0.6179872607917782)
    */
    drawCircle(
        10.43f, 4.10f,
        0.6179872607917782f,
        1.0f, 1.0f, 1.0f
    );

    /*
       GeoGebra:
       Q3 = (11.13, 4.16)
       k4 = Circle(Q3, 0.34783216491731783)
    */
    drawCircle(
        11.13f, 4.16f,
        0.34783216491731783f,
        1.0f, 1.0f, 1.0f
    );

    /*
       GeoGebra:
       R3 = (9.77, 3.57)
       p4 = Circle(R3, 0.49528182171319846)
    */
    drawCircle(
        9.77f, 3.57f,
        0.49528182171319846f,
        1.0f, 1.0f, 1.0f
    );

    /*
       GeoGebra:
       S3 = (11.09, 3.49)
       q4 = Circle(S3, 0.5655033328377035)
    */
    drawCircle(
        11.09f, 3.49f,
        0.5655033328377035f,
        1.0f, 1.0f, 1.0f
    );

    /*
       GeoGebra:
       T3 = (10.42, 3.44)
       r4 = Circle(T3, 0.43006721012365057)
    */
    drawCircle(
        10.42f, 3.44f,
        0.43006721012365057f,
        1.0f, 1.0f, 1.0f
    );
}

// ============================================================
// BACK LEFT DARK HILL
// ============================================================

void drawDarkLeftHill()
{
    /*
       Exact GeoGebra hill points:

       U3 = (-9.03, -4.55)
       V3 = (-5.81, -2.25)
       W3 = (-3.19, 0.55)

       Upper boundary points:

       G4 = (-9.00, 0.00)
       H4 = (-7.53, 1.10)
       I4 = (-5.73, 1.58)
    */

    glColor3f(0.02f, 0.28f, 0.07f);

    glBegin(GL_POLYGON);

    glVertex2f(-10.0f, -6.0f);

    glVertex2f(-10.0f, -0.50f);

    glVertex2f(-9.00f, 0.00f);      // G4
    glVertex2f(-7.53f, 1.10f);      // H4
    glVertex2f(-5.73f, 1.58f);      // I4
    glVertex2f(-3.19f, 0.55f);      // W3
    glVertex2f(-5.81f, -2.25f);     // V3
    glVertex2f(-9.03f, -4.55f);     // U3

    glEnd();
}

// ============================================================
// MAIN GREEN HILL
// Exact upper hill coordinates
// ============================================================

void drawMainHill()
{
    /*
       Exact GeoGebra upper-hill measurements:

       G4 = (-9.00, 0.00)
       H4 = (-7.53, 1.10)
       I4 = (-5.73, 1.58)
       W3 = (-3.19, 0.55)
       Z3 = (-1.32, 2.18)
       A4 = (1.18, 2.75)
       B4 = (2.46, 2.38)
       C4 = (4.76, 0.89)
       D4 = (6.61, -0.72)
       E4 = (10.19, -3.14)
       F4 = (12.60, -3.93)

       Segment lengths from GeoGebra:

       j4 = Segment(G4,H4) = 1.83
       l4 = Segment(H4,I4) = 1.86
       m4 = Segment(I4,W3) = 2.74
       j3 = Segment(W3,Z3) = 2.48
       l3 = Segment(Z3,A4) = 2.56
       m3 = Segment(A4,B4) = 1.33
       n3 = Segment(B4,C4) = 2.74
       a3 = Segment(C4,D4) = 2.44
       b3 = Segment(D4,E4) = 4.33
       i4 = Segment(E4,F4) = 2.54
    */

    glColor3f(0.35f, 0.86f, 0.05f);

    glBegin(GL_POLYGON);

    glVertex2f(-9.00f, 0.00f);      // G4
    glVertex2f(-7.53f, 1.10f);      // H4
    glVertex2f(-5.73f, 1.58f);      // I4
    glVertex2f(-3.19f, 0.55f);      // W3
    glVertex2f(-1.32f, 2.18f);      // Z3
    glVertex2f(1.18f, 2.75f);       // A4
    glVertex2f(2.46f, 2.38f);       // B4
    glVertex2f(4.76f, 0.89f);       // C4
    glVertex2f(6.61f, -0.72f);      // D4
    glVertex2f(10.19f, -3.14f);     // E4
    glVertex2f(12.60f, -3.93f);     // F4

    glVertex2f(13.50f, -4.20f);
    glVertex2f(13.50f, -6.00f);
    glVertex2f(-9.00f, -6.00f);

    glEnd();
}

// ============================================================
// FRONT LIGHT-GREEN ELLIPSE
// Exact GeoGebra ellipse defined by C3, D3 and E3
// ============================================================

void drawFrontEllipse()
{
    /*
       GeoGebra:

       C3 = (-5.00, -2.00)
       D3 = (5.22, -1.88)
       E3 = (1.46, 1.02)

       k3 = Ellipse(C3, D3, E3)

       C3 and D3 are the two focus points.
       E3 is a point on the ellipse.

       Calculated from these exact GeoGebra points:

       centre = midpoint of C3 and D3
              = (0.11, -1.94)

       major radius a = 5.939745
       minor radius b = 3.027354
       rotation angle = 0.672718 degrees

       GeoGebra displayed equation:

       146.29x² - 10.15xy + 564.01y²
       - 51.85x + 2187.13y = 3033.08
    */

    drawRotatedEllipse(
        0.11f, -1.94f,
        5.939745f,
        3.027354f,
        0.672718f,
        0.55f, 0.93f, 0.10f
    );
}

// ============================================================
// LARGE LEFT TREE
// ============================================================

void drawLargeLeftTree()
{
    // Draw trunks first so leaves appear over them.

    /*
       GeoGebra:
       W2 = (-7.60, -2.76)
       Z2 = (-7.56, -4.28)

       b2 = Segment(W2,Z2) = 1.53
    */
    drawSegment(
        -7.60f, -2.76f,
        -7.56f, -4.28f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       GeoGebra:
       A3 = (-7.31, -2.81)
       B3 = (-7.30, -4.28)

       g3 = Segment(A3,B3) = 1.47
    */
    drawSegment(
        -7.31f, -2.81f,
        -7.30f, -4.28f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       GeoGebra:
       Z2 = (-7.56, -4.28)
       B3 = (-7.30, -4.28)

       h3 = Segment(Z2,B3) = 0.25
    */
    drawSegment(
        -7.56f, -4.28f,
        -7.30f, -4.28f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       S2 = (-7.44, -1.67)
       c3 = Circle(S2, 0.7583021690557658)
    */
    drawCircle(
        -7.44f, -1.67f,
        0.7583021690557658f,
        0.06f, 0.40f, 0.07f
    );

    /*
       T2 = (-7.70, -1.49)
       d3 = Circle(T2, 0.2656948056388394)
    */
    drawCircle(
        -7.70f, -1.49f,
        0.2656948056388394f,
        0.54f, 0.87f, 0.12f
    );

    /*
       U2 = (-7.96, -2.22)
       e3 = Circle(U2, 0.6497742659148906)
    */
    drawCircle(
        -7.96f, -2.22f,
        0.6497742659148906f,
        0.15f, 0.58f, 0.08f
    );

    /*
       V2 = (-6.90, -2.21)
       f3 = Circle(V2, 0.7264148979564938)
    */
    drawCircle(
        -6.90f, -2.21f,
        0.7264148979564938f,
        0.22f, 0.68f, 0.10f
    );
}

// ============================================================
// TREE NEAR x = -4.4
// ============================================================

void drawTreeMinusFour()
{
    /*
       O2 = (-4.42, 0.08)
       P2 = (-4.43, -0.57)

       n2 = Segment(O2,P2) = 0.65
    */
    drawSegment(
        -4.42f, 0.08f,
        -4.43f, -0.57f,
        0.43f, 0.22f, 0.05f,
        4.0f
    );

    /*
       Q2 = (-4.29, 0.09)
       R2 = (-4.31, -0.55)

       t2 = Segment(Q2,R2) = 0.65
    */
    drawSegment(
        -4.29f, 0.09f,
        -4.31f, -0.55f,
        0.43f, 0.22f, 0.05f,
        4.0f
    );

    /*
       P2 = (-4.43, -0.57)
       R2 = (-4.31, -0.55)

       a2 = Segment(P2,R2) = 0.12
    */
    drawSegment(
        -4.43f, -0.57f,
        -4.31f, -0.55f,
        0.43f, 0.22f, 0.05f,
        4.0f
    );

    /*
       K2 = (-4.36, 0.59)
       p2 = Circle(K2, 0.3401082782315724)
    */
    drawCircle(
        -4.36f, 0.59f,
        0.3401082782315724f,
        0.05f, 0.39f, 0.06f
    );

    /*
       L2 = (-4.61, 0.33)
       q2 = Circle(L2, 0.31515826186251233)
    */
    drawCircle(
        -4.61f, 0.33f,
        0.31515826186251233f,
        0.18f, 0.60f, 0.08f
    );

    /*
       M2 = (-4.13, 0.35)
       r2 = Circle(M2, 0.30613829114167074)
    */
    drawCircle(
        -4.13f, 0.35f,
        0.30613829114167074f,
        0.23f, 0.69f, 0.10f
    );

    /*
       N2 = (-4.48, 0.67)
       s2 = Circle(N2, 0.12047508078255101)
    */
    drawCircle(
        -4.48f, 0.67f,
        0.12047508078255101f,
        0.60f, 0.91f, 0.20f
    );
}

// ============================================================
// TREE NEAR x = -2
// ============================================================

void drawTreeMinusTwo()
{
    /*
       G2 = (-2.07, 2.46)
       H2 = (-2.02, 1.62)

       k2 = Segment(G2,H2) = 0.84
    */
    drawSegment(
        -2.07f, 2.46f,
        -2.02f, 1.62f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       I2 = (-1.88, 2.46)
       J2 = (-1.89, 1.65)

       l2 = Segment(I2,J2) = 0.81
    */
    drawSegment(
        -1.88f, 2.46f,
        -1.89f, 1.65f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       H2 = (-2.02, 1.62)
       J2 = (-1.89, 1.65)

       m2 = Segment(H2,J2) = 0.13
    */
    drawSegment(
        -2.02f, 1.62f,
        -1.89f, 1.65f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       F = (-2.00, 3.00)
       f = Circle(F, 0.4101593445272619)
    */
    drawCircle(
        -2.00f, 3.00f,
        0.4101593445272619f,
        0.05f, 0.40f, 0.06f
    );

    /*
       G = (-2.33, 2.76)
       g = Circle(G, 0.39981474331923067)
    */
    drawCircle(
        -2.33f, 2.76f,
        0.39981474331923067f,
        0.16f, 0.59f, 0.08f
    );

    /*
       H = (-1.63, 2.82)
       h = Circle(H, 0.44124095347121517)
    */
    drawCircle(
        -1.63f, 2.82f,
        0.44124095347121517f,
        0.24f, 0.69f, 0.10f
    );
}

// ============================================================
// CENTRAL TREE
// ============================================================

void drawCenterTree()
{
    /*
       C2 = (0.35, 2.90)
       D2 = (0.36, 2.06)

       h2 = Segment(C2,D2) = 0.84
    */
    drawSegment(
        0.35f, 2.90f,
        0.36f, 2.06f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       F2 = (0.53, 2.87)
       E2 = (0.53, 2.06)

       j2 = Segment(F2,E2) = 0.81
    */
    drawSegment(
        0.53f, 2.87f,
        0.53f, 2.06f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       D2 = (0.36, 2.06)
       E2 = (0.53, 2.06)

       i2 = Segment(D2,E2) = 0.17
    */
    drawSegment(
        0.36f, 2.06f,
        0.53f, 2.06f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       C = (0.46, 3.67)
       c = Circle(C, 0.45797575352346026)
    */
    drawCircle(
        0.46f, 3.67f,
        0.45797575352346026f,
        0.05f, 0.40f, 0.06f
    );

    /*
       D = (0.14, 3.35)
       d = Circle(D, 0.4962965630077528)
    */
    drawCircle(
        0.14f, 3.35f,
        0.4962965630077528f,
        0.17f, 0.60f, 0.08f
    );

    /*
       E = (0.75, 3.32)
       e = Circle(E, 0.49861654923364995)
    */
    drawCircle(
        0.75f, 3.32f,
        0.49861654923364995f,
        0.24f, 0.69f, 0.10f
    );
}

// ============================================================
// TREE NEAR x = 2.8
// ============================================================

void drawTreeTwo()
{
    /*
       W1 = (2.80, 1.60)
       Z1 = (2.80, 0.97)

       a1 = Segment(W1,Z1) = 0.63
    */
    drawSegment(
        2.80f, 1.60f,
        2.80f, 0.97f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       B2 = (2.96, 1.66)
       A2 = (2.93, 0.97)

       g2 = Segment(B2,A2) = 0.70
    */
    drawSegment(
        2.96f, 1.66f,
        2.93f, 0.97f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       Z1 = (2.80, 0.97)
       A2 = (2.93, 0.97)

       b1 = Segment(Z1,A2) = 0.14
    */
    drawSegment(
        2.80f, 0.97f,
        2.93f, 0.97f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       I = (2.86, 2.24)
       k = Circle(I, 0.42630207352655636)
    */
    drawCircle(
        2.86f, 2.24f,
        0.42630207352655636f,
        0.05f, 0.40f, 0.06f
    );

    /*
       J = (2.60, 1.90)
       p = Circle(J, 0.3641375074150842)
    */
    drawCircle(
        2.60f, 1.90f,
        0.3641375074150842f,
        0.17f, 0.60f, 0.08f
    );

    /*
       K = (3.18, 1.96)
       q = Circle(K, 0.3708636032889819)
    */
    drawCircle(
        3.18f, 1.96f,
        0.3708636032889819f,
        0.24f, 0.69f, 0.10f
    );
}

// ============================================================
// TREE NEAR x = 5
// ============================================================

void drawTreeFive()
{
    /*
       A = (5.03, -0.08)
       B = (5.00, -0.40)

       t4 = Segment(A,B) = 0.32
    */
    drawSegment(
        5.03f, -0.08f,
        5.00f, -0.40f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       M4 = (5.12, -0.14)
       N4 = (5.11, -0.40)

       a4 = Segment(M4,N4) = 0.26
    */
    drawSegment(
        5.12f, -0.14f,
        5.11f, -0.40f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       B = (5.00, -0.40)
       N4 = (5.11, -0.40)

       b4 = Segment(B,N4) = 0.11
    */
    drawSegment(
        5.00f, -0.40f,
        5.11f, -0.40f,
        0.43f, 0.22f, 0.05f,
        5.0f
    );

    /*
       L = (5.02, 0.28)
       r = Circle(L, 0.35965464157469684)
    */
    drawCircle(
        5.02f, 0.28f,
        0.35965464157469684f,
        0.05f, 0.40f, 0.06f
    );

    /*
       M = (4.78, 0.02)
       s = Circle(M, 0.2692403847859041)
    */
    drawCircle(
        4.78f, 0.02f,
        0.2692403847859041f,
        0.17f, 0.60f, 0.08f
    );

    /*
       N = (5.32, 0.07)
       t = Circle(N, 0.28884840791065365)
    */
    drawCircle(
        5.32f, 0.07f,
        0.28884840791065365f,
        0.24f, 0.69f, 0.10f
    );
}

// ============================================================
// TREE NEAR x = 8
// ============================================================

void drawTreeEight()
{
    /*
       G1 = (8.06, -1.88)
       H1 = (8.08, -2.31)

       m = Segment(G1,H1) = 0.43
    */
    drawSegment(
        8.06f, -1.88f,
        8.08f, -2.31f,
        0.43f, 0.22f, 0.05f,
        4.0f
    );

    /*
       I1 = (8.19, -1.86)
       J1 = (8.17, -2.34)

       n = Segment(I1,J1) = 0.48
    */
    drawSegment(
        8.19f, -1.86f,
        8.17f, -2.34f,
        0.43f, 0.22f, 0.05f,
        4.0f
    );

    /*
       H1 = (8.08, -2.31)
       J1 = (8.17, -2.34)

       a = Segment(H1,J1) = 0.10
    */
    drawSegment(
        8.08f, -2.31f,
        8.17f, -2.34f,
        0.43f, 0.22f, 0.05f,
        4.0f
    );

    /*
       O = (8.12, -1.40)
       c1 = Circle(O, 0.3206863838092459)
    */
    drawCircle(
        8.12f, -1.40f,
        0.3206863838092459f,
        0.05f, 0.40f, 0.06f
    );

    /*
       P = (7.88, -1.61)
       d1 = Circle(P, 0.3238016655596222)
    */
    drawCircle(
        7.88f, -1.61f,
        0.3238016655596222f,
        0.17f, 0.60f, 0.08f
    );

    /*
       Q = (8.33, -1.64)
       e1 = Circle(Q, 0.2804415258165292)
    */
    drawCircle(
        8.33f, -1.64f,
        0.2804415258165292f,
        0.24f, 0.69f, 0.10f
    );

    /*
       V = (8.03, -1.40)
       p1 = Circle(V, 0.11595378541805104)
    */
    drawCircle(
        8.03f, -1.40f,
        0.11595378541805104f,
        0.60f, 0.91f, 0.20f
    );
}

// ============================================================
// TREE NEAR x = 9.4
// ============================================================

void drawTreeNine()
{
    /*
       C1 = (9.40, -1.80)
       D1 = (9.40, -2.20)

       i = Segment(C1,D1) = 0.40
    */
    drawSegment(
        9.40f, -1.80f,
        9.40f, -2.20f,
        0.43f, 0.22f, 0.05f,
        4.0f
    );

    /*
       E1 = (9.49, -1.84)
       F1 = (9.50, -2.21)

       j = Segment(E1,F1) = 0.37
    */
    drawSegment(
        9.49f, -1.84f,
        9.50f, -2.21f,
        0.43f, 0.22f, 0.05f,
        4.0f
    );

    /*
       D1 = (9.40, -2.20)
       F1 = (9.50, -2.21)

       l = Segment(D1,F1) = 0.10
    */
    drawSegment(
        9.40f, -2.20f,
        9.50f, -2.21f,
        0.43f, 0.22f, 0.05f,
        4.0f
    );

    /*
       R = (9.44, -1.47)
       f1 = Circle(R, 0.23362644993880557)
    */
    drawCircle(
        9.44f, -1.47f,
        0.23362644993880557f,
        0.05f, 0.40f, 0.06f
    );

    /*
       S = (9.26, -1.62)
       g1 = Circle(S, 0.20665563784944865)
    */
    drawCircle(
        9.26f, -1.62f,
        0.20665563784944865f,
        0.17f, 0.60f, 0.08f
    );

    /*
       T = (9.59, -1.65)
       h1 = Circle(T, 0.21478996576743564)
    */
    drawCircle(
        9.59f, -1.65f,
        0.21478996576743564f,
        0.24f, 0.69f, 0.10f
    );

    /*
       U = (9.37, -1.41)
       k1 = Circle(U, 0.08945371428331048)
    */
    drawCircle(
        9.37f, -1.41f,
        0.08945371428331048f,
        0.60f, 0.91f, 0.20f
    );
}

// ============================================================
// TREE NEAR x = 11
// ============================================================

void drawTreeEleven()
{
    /*
       K1 = (10.94, -2.30)
       L1 = (10.96, -2.63)

       b = Segment(K1,L1) = 0.33
    */
    drawSegment(
        10.94f, -2.30f,
        10.96f, -2.63f,
        0.43f, 0.22f, 0.05f,
        4.0f
    );

    /*
       M1 = (11.01, -2.30)
       N1 = (11.01, -2.63)

       i1 = Segment(M1,N1) = 0.33
    */
    drawSegment(
        11.01f, -2.30f,
        11.01f, -2.63f,
        0.43f, 0.22f, 0.05f,
        4.0f
    );

    /*
       L1 = (10.96, -2.63)
       N1 = (11.01, -2.63)

       j1 = Segment(L1,N1) = 0.05
    */
    drawSegment(
        10.96f, -2.63f,
        11.01f, -2.63f,
        0.43f, 0.22f, 0.05f,
        4.0f
    );

    /*
       W = (10.98, -2.03)
       q1 = Circle(W, 0.1701914943302079)
    */
    drawCircle(
        10.98f, -2.03f,
        0.1701914943302079f,
        0.05f, 0.40f, 0.06f
    );

    /*
       Z = (10.87, -2.16)
       r1 = Circle(Z, 0.16838465620616216)
    */
    drawCircle(
        10.87f, -2.16f,
        0.16838465620616216f,
        0.17f, 0.60f, 0.08f
    );

    /*
       A1 = (11.10, -2.16)
       s1 = Circle(A1, 0.1680167617413357)
    */
    drawCircle(
        11.10f, -2.16f,
        0.1680167617413357f,
        0.24f, 0.69f, 0.10f
    );

    /*
       B1 = (10.92, -1.97)
       t1 = Circle(B1, 0.06364258289509535)
    */
    drawCircle(
        10.92f, -1.97f,
        0.06364258289509535f,
        0.60f, 0.91f, 0.20f
    );
}

// ============================================================
// TREE NEAR x = 12
// ============================================================

void drawTreeTwelve()
{
    /*
       S1 = (12.05, -2.67)
       T1 = (12.05, -2.99)

       l1 = Segment(S1,T1) = 0.32
    */
    drawSegment(
        12.05f, -2.67f,
        12.05f, -2.99f,
        0.43f, 0.22f, 0.05f,
        4.0f
    );

    /*
       U1 = (12.10, -2.68)
       V1 = (12.10, -2.98)

       m1 = Segment(U1,V1) = 0.31
    */
    drawSegment(
        12.10f, -2.68f,
        12.10f, -2.98f,
        0.43f, 0.22f, 0.05f,
        4.0f
    );

    /*
       O1 = (12.09, -2.43)
       c2 = Circle(O1, 0.16549140713808003)
    */
    drawCircle(
        12.09f, -2.43f,
        0.16549140713808003f,
        0.05f, 0.40f, 0.06f
    );

    /*
       P1 = (11.98, -2.55)
       d2 = Circle(P1, 0.14062165084379408)
    */
    drawCircle(
        11.98f, -2.55f,
        0.14062165084379408f,
        0.17f, 0.60f, 0.08f
    );

    /*
       Q1 = (12.19, -2.56)
       e2 = Circle(Q1, 0.14565556267549326)
    */
    drawCircle(
        12.19f, -2.56f,
        0.14565556267549326f,
        0.24f, 0.69f, 0.10f
    );

    /*
       R1 = (12.02, -2.38)
       f2 = Circle(R1, 0.059988347020236796)
    */
    drawCircle(
        12.02f, -2.38f,
        0.059988347020236796f,
        0.60f, 0.91f, 0.20f
    );
}

// ============================================================
// DISPLAY
// ============================================================

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Objects must be drawn from back to front.

    drawSky();

    // Clouds are behind the landscape.
    drawLeftCloud();
    drawMiddleCloud();
    drawRightCloud();

    // Hills
    drawDarkLeftHill();
    drawMainHill();

    // Front light-green ellipse
    drawFrontEllipse();

    // Trees
    drawLargeLeftTree();
    drawTreeMinusFour();
    drawTreeMinusTwo();
    drawCenterTree();
    drawTreeTwo();
    drawTreeFive();
    drawTreeEight();
    drawTreeNine();
    drawTreeEleven();
    drawTreeTwelve();

    glFlush();
}

// ============================================================
// WINDOW RESHAPE
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

    /*
       Coordinate range selected to contain the complete
       GeoGebra landscape:

       x approximately from -10 to 13.5
       y approximately from -6 to 12
    */
    gluOrtho2D(-10.0, 13.5, -6.0, 12.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// ============================================================
// INITIALIZATION
// ============================================================

void initialize()
{
    glClearColor(0.12f, 0.72f, 0.92f, 1.0f);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

// ============================================================
// MAIN FUNCTION
// ============================================================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1200, 750);
    glutInitWindowPosition(50, 50);

    glutCreateWindow(
        "GeoGebra Landscape Using Exact Measurements"
    );

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
