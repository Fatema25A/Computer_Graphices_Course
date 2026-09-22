#include <windows.h>
#include <GL/glut.h>
#include <math.h>

// GLOBAL VARIABLES
float waveOffset = 0.0f;
float sunX = -80.0f;
float cloudX1 = 0.0f;
float cloudX2 = 0.0f;
float birdX = 0.0f;
float boatX = 0.0f;

float farmerMove = 0.0f;
float animalMove = 0.0f;

float cloudSpeed = 0.15f;

bool boatMoving = true;
bool nightMode = false;

const float PI = 3.1415926f;


// BASIC SHAPES

void circle(float cx, float cy, float r)
{
    glBegin(GL_POLYGON);

    for (int i = 0; i < 100; i++)
    {
        float angle = 2.0f * PI * i / 100.0f;

        glVertex2f(
            cx + r * cos(angle),
            cy + r * sin(angle)
        );
    }

    glEnd();
}


void rectangle(float x1, float y1, float x2, float y2)
{
    glBegin(GL_QUADS);

    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);

    glEnd();
}


// SKY

void drawSky()
{
    glBegin(GL_QUADS);

    if (nightMode)
    {
        glColor3f(0.10f, 0.18f, 0.35f);
        glVertex2f(-100, 20);

        glColor3f(0.10f, 0.18f, 0.35f);
        glVertex2f(100, 20);

        glColor3f(0.01f, 0.03f, 0.12f);
        glVertex2f(100, 100);

        glColor3f(0.01f, 0.03f, 0.12f);
        glVertex2f(-100, 100);
    }
    else
    {
        glColor3f(0.65f, 0.88f, 1.0f);
        glVertex2f(-100, 20);

        glColor3f(0.65f, 0.88f, 1.0f);
        glVertex2f(100, 20);

        glColor3f(0.15f, 0.50f, 0.90f);
        glVertex2f(100, 100);

        glColor3f(0.15f, 0.50f, 0.90f);
        glVertex2f(-100, 100);
    }

    glEnd();
}
void drawSun()
{
    if (nightMode)
    {
        glColor3f(0.9f, 0.9f, 0.9f); // Moon
        circle(sunX, 80, 7);
    }
    else
    {
        glColor3f(1.0f, 1.0f, 0.0f); // Sun
        circle(sunX, 80, 7);
    }
}

// CLOUD

void cloud()
{
    if (nightMode)
    {
        glColor3f(0.22f, 0.27f, 0.38f);

        circle(2, 1, 5);
        circle(8, 2, 6);
        circle(14, 1, 7);
        circle(20, 1, 5);

        glColor3f(0.38f, 0.43f, 0.55f);

        circle(0, 3, 5);
        circle(6, 5, 6);
        circle(13, 5, 7);
        circle(19, 3, 5);

        glColor3f(0.58f, 0.62f, 0.72f);

        circle(5, 7, 4);
        circle(11, 9, 5);
        circle(17, 7, 4);
    }
    else
    {
        glColor3f(0.72f, 0.82f, 0.92f);

        circle(2, 1, 5);
        circle(7, 1, 6);
        circle(13, 0, 7);
        circle(19, 1, 6);

        glColor3f(0.88f, 0.93f, 0.98f);

        circle(0, 3, 5);
        circle(5, 5, 6);
        circle(11, 5, 7);
        circle(17, 4, 7);
        circle(22, 3, 5);

        glColor3f(1.0f, 1.0f, 1.0f);

        circle(5, 7, 4);
        circle(10, 9, 5);
        circle(15, 9, 5);
        circle(19, 7, 4);
    }
}

void drawClouds()
{
    glPushMatrix();
    glTranslatef(cloudX1, 0, 0);
    glTranslatef(-80, 72, 0);
    cloud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(cloudX2, 0, 0);
    glTranslatef(-20, 85, 0);
    cloud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(cloudX1, 0, 0);
    glTranslatef(50, 67, 0);
    cloud();
    glPopMatrix();
}

// BIRD

void bird()
{
    glColor3f(0.05f, 0.05f, 0.05f);

    glLineWidth(2);

    glBegin(GL_LINES);

    glVertex2f(0, 0);
    glVertex2f(3, 2);

    glVertex2f(3, 2);
    glVertex2f(6, 0);

    glEnd();
}
void drawBirds()
{
    // Bird 1
    glPushMatrix();
    glTranslatef(birdX, 0, 0);
    glTranslatef(-70, 67, 0);
    bird();
    glPopMatrix();

    // Bird 2
    glPushMatrix();
    glTranslatef(birdX, 0, 0);
    glTranslatef(-55, 73, 0);
    bird();
    glPopMatrix();

    // Bird 3
    glPushMatrix();
    glTranslatef(birdX, 0, 0);
    glTranslatef(-40, 65, 0);
    bird();
    glPopMatrix();

    // Bird 4
    glPushMatrix();
    glTranslatef(birdX, 0, 0);
    glTranslatef(-25, 76, 0);
    bird();
    glPopMatrix();
}

// GRASS

void drawGrass()
{
    if (nightMode)
    {
        glColor3f(0.08f, 0.25f, 0.08f);
    }
    else
    {
        glColor3f(0.20f, 0.65f, 0.18f);
    }

    rectangle(-100, -100, 100, 25);
}


// CURVY WAVE

void wave(float startX, float endX)
{
    glBegin(GL_LINE_STRIP);

    for (float x = startX; x <= endX; x++)
    {
        float y = sin((x + waveOffset) * 0.18f);
        glVertex2f(x, y);
    }

    glEnd();
}
void drawWave(float startX, float endX, float yPos)
{
    glPushMatrix();

    glTranslatef(0, yPos, 0);

    wave(startX, endX);

    glPopMatrix();
}

void drawRiver()
{
    glBegin(GL_POLYGON);

    if (nightMode)
    {
        // Top side lighter
        glColor3f(0.10f, 0.30f, 0.50f);
        glVertex2f(-100, -25);

        glColor3f(0.10f, 0.30f, 0.50f);
        glVertex2f(100, -20);

        // Bottom side darker
        glColor3f(0.02f, 0.10f, 0.22f);
        glVertex2f(100, -60);

        glColor3f(0.02f, 0.10f, 0.22f);
        glVertex2f(-100, -65);
    }
    else
    {
        // Top side lighter
        glColor3f(0.30f, 0.75f, 0.95f);
        glVertex2f(-100, -25);

        glColor3f(0.30f, 0.75f, 0.95f);
        glVertex2f(100, -20);

        // Bottom side darker
        glColor3f(0.05f, 0.35f, 0.75f);
        glVertex2f(100, -60);

        glColor3f(0.05f, 0.35f, 0.75f);
        glVertex2f(-100, -65);
    }

    glEnd();

    // Wave color
    if (nightMode)
        glColor3f(0.55f, 0.75f, 0.95f);
    else
        glColor3f(0.85f, 0.95f, 1.0f);

    glLineWidth(2);

    drawWave(-95, -55, -34);
    drawWave(-40, 5, -42);
    drawWave(20, 70, -50);
}
void drawPond()
{
    glColor3f(0.10f,0.60f,0.80f);

    glPushMatrix();

    glTranslatef(60,2,0);

    glScalef(1.8f,0.7f,1);

    circle(0,0,12);

    glPopMatrix();
}

// VILLAGE HOUSE

void villageHouse()
{
    // Main wall
    glBegin(GL_QUADS);

    glColor3f(0.55f, 0.30f, 0.18f);
    glVertex2f(0, 0);
    glVertex2f(30, 0);

    glColor3f(0.82f, 0.56f, 0.38f);
    glVertex2f(30, 20);
    glVertex2f(0, 20);

    glEnd();


    // Roof
    glBegin(GL_QUADS);

    glColor3f(0.35f, 0.35f, 0.35f);
    glVertex2f(-3, 20);

    glColor3f(0.62f, 0.62f, 0.62f);
    glVertex2f(3, 31);
    glVertex2f(27, 31);

    glColor3f(0.35f, 0.35f, 0.35f);
    glVertex2f(34, 20);

    glEnd();


    // Gate frame
    glColor3f(0.38f, 0.20f, 0.10f);

    glBegin(GL_QUADS);

    glVertex2f(11, 0);
    glVertex2f(19, 0);
    glVertex2f(19, 14);
    glVertex2f(11, 14);

    glEnd();


    // Gate
    glBegin(GL_QUADS);

    glColor3f(0.18f, 0.08f, 0.03f);
    glVertex2f(12, 0);
    glVertex2f(18, 0);

    glColor3f(0.42f, 0.22f, 0.10f);
    glVertex2f(18, 13);
    glVertex2f(12, 13);

    glEnd();


    // Gate center
    glColor3f(0.12f, 0.06f, 0.02f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);

    glVertex2f(15, 0);
    glVertex2f(15, 13);

    glEnd();


    // Gate handles
    glPointSize(4.0f);
    glColor3f(0.85f, 0.65f, 0.20f);

    glBegin(GL_POINTS);

    glVertex2f(14.3f, 6);
    glVertex2f(15.7f, 6);

    glEnd();


    // Left window frame
    glColor3f(0.38f, 0.20f, 0.10f);

    glBegin(GL_QUADS);

    glVertex2f(3, 7);
    glVertex2f(9, 7);
    glVertex2f(9, 14);
    glVertex2f(3, 14);

    glEnd();


    // Left window
    glBegin(GL_QUADS);

    glColor3f(0.38f, 0.20f, 0.10f);
    glVertex2f(4, 8);
    glVertex2f(8, 8);

    glColor3f(0.68f, 0.42f, 0.24f);
    glVertex2f(8, 13);
    glVertex2f(4, 13);

    glEnd();


    // Left window cross
    glColor3f(0.22f, 0.11f, 0.05f);
    glLineWidth(1.5f);

    glBegin(GL_LINES);

    glVertex2f(6, 8);
    glVertex2f(6, 13);

    glVertex2f(4, 10.5f);
    glVertex2f(8, 10.5f);

    glEnd();


    // Right window frame
    glColor3f(0.38f, 0.20f, 0.10f);

    glBegin(GL_QUADS);

    glVertex2f(21, 7);
    glVertex2f(27, 7);
    glVertex2f(27, 14);
    glVertex2f(21, 14);

    glEnd();


    // Right window
    glBegin(GL_QUADS);

    glColor3f(0.38f, 0.20f, 0.10f);
    glVertex2f(22, 8);
    glVertex2f(26, 8);

    glColor3f(0.68f, 0.42f, 0.24f);
    glVertex2f(26, 13);
    glVertex2f(22, 13);

    glEnd();


    // Right window cross
    glColor3f(0.22f, 0.11f, 0.05f);
    glLineWidth(1.5f);

    glBegin(GL_LINES);

    glVertex2f(24, 8);
    glVertex2f(24, 13);

    glVertex2f(22, 10.5f);
    glVertex2f(26, 10.5f);

    glEnd();
}

void drawVillageHouse(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    villageHouse();

    glPopMatrix();
}
void tinHouse()
{
    // Main wall
    glBegin(GL_QUADS);

    glColor3f(0.72f, 0.60f, 0.40f);
    glVertex2f(0, 0);
    glVertex2f(30, 0);

    glColor3f(0.95f, 0.82f, 0.58f);
    glVertex2f(30, 20);
    glVertex2f(0, 20);

    glEnd();


    // Left roof
    glBegin(GL_TRIANGLES);

    glColor3f(0.28f, 0.29f, 0.32f);
    glVertex2f(-6, 20);

    glColor3f(0.50f, 0.51f, 0.54f);
    glVertex2f(15, 34);

    glColor3f(0.34f, 0.35f, 0.38f);
    glVertex2f(15, 20);

    glEnd();


    // Right roof
    glBegin(GL_TRIANGLES);

    glColor3f(0.50f, 0.51f, 0.54f);
    glVertex2f(15, 34);

    glColor3f(0.28f, 0.29f, 0.32f);
    glVertex2f(36, 20);

    glColor3f(0.34f, 0.35f, 0.38f);
    glVertex2f(15, 20);

    glEnd();


    // Roof edge
    glColor3f(0.15f, 0.16f, 0.18f);

    glBegin(GL_QUADS);

    glVertex2f(-6, 20);
    glVertex2f(36, 20);
    glVertex2f(35.5f, 19);
    glVertex2f(-5.5f, 19);

    glEnd();


    // Left post
    glBegin(GL_QUADS);

    glColor3f(0.30f, 0.12f, 0.02f);
    glVertex2f(1, 0);

    glColor3f(0.48f, 0.20f, 0.04f);
    glVertex2f(2.5f, 0);

    glColor3f(0.52f, 0.23f, 0.05f);
    glVertex2f(2.5f, 20);

    glColor3f(0.30f, 0.12f, 0.02f);
    glVertex2f(1, 20);

    glEnd();


    // Right post
    glBegin(GL_QUADS);

    glColor3f(0.30f, 0.12f, 0.02f);
    glVertex2f(27.5f, 0);

    glColor3f(0.48f, 0.20f, 0.04f);
    glVertex2f(29, 0);

    glColor3f(0.52f, 0.23f, 0.05f);
    glVertex2f(29, 20);

    glColor3f(0.30f, 0.12f, 0.02f);
    glVertex2f(27.5f, 20);

    glEnd();


    // Door frame
    glColor3f(0.48f, 0.30f, 0.12f);

    glBegin(GL_QUADS);

    glVertex2f(11, 0);
    glVertex2f(19, 0);
    glVertex2f(19, 15);
    glVertex2f(11, 15);

    glEnd();


    // Door opening
    glBegin(GL_QUADS);

    glColor3f(0.22f, 0.21f, 0.19f);
    glVertex2f(12, 0);
    glVertex2f(18, 0);

    glColor3f(0.34f, 0.31f, 0.27f);
    glVertex2f(18, 14);
    glVertex2f(12, 14);

    glEnd();


    // Open wooden door
    glBegin(GL_QUADS);

    glColor3f(0.36f, 0.13f, 0.01f);
    glVertex2f(15, 1);

    glColor3f(0.56f, 0.25f, 0.03f);
    glVertex2f(18, 2);

    glColor3f(0.58f, 0.27f, 0.04f);
    glVertex2f(18, 13);

    glColor3f(0.38f, 0.14f, 0.01f);
    glVertex2f(15, 12);

    glEnd();


    // Right window frame
    glColor3f(0.42f, 0.17f, 0.02f);
    rectangle(21, 6, 27, 12);


    // Window inner
    glColor3f(0.82f, 0.78f, 0.66f);
    rectangle(22, 7, 26, 11);


    // Window bars
    glColor3f(0.25f, 0.20f, 0.15f);

    glLineWidth(1.0f);

    glBegin(GL_LINES);

    glVertex2f(23, 7);
    glVertex2f(23, 11);

    glVertex2f(24, 7);
    glVertex2f(24, 11);

    glVertex2f(25, 7);
    glVertex2f(25, 11);

    glEnd();


    // Left shutter
    glColor3f(0.50f, 0.20f, 0.02f);

    glBegin(GL_QUADS);

    glVertex2f(19.5f, 6.5f);
    glVertex2f(21, 7);
    glVertex2f(21, 11.5f);
    glVertex2f(19.5f, 11);

    glEnd();


    // Right shutter
    glBegin(GL_QUADS);

    glVertex2f(27, 7);
    glVertex2f(28.5f, 6.5f);
    glVertex2f(28.5f, 11);
    glVertex2f(27, 11.5f);

    glEnd();


    // Front veranda
    glBegin(GL_QUADS);

    glColor3f(0.48f, 0.46f, 0.42f);
    glVertex2f(0, -3);
    glVertex2f(30, -3);

    glColor3f(0.64f, 0.61f, 0.55f);
    glVertex2f(30, 0);
    glVertex2f(0, 0);

    glEnd();
}
void drawTinHouse(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    tinHouse();

    glPopMatrix();
}
void tree()
{
    // Trunk
    glColor3f(0.35f, 0.18f, 0.05f);
    rectangle(-2, 0, 2, 20);

    // Leaves
    glColor3f(0.05f, 0.50f, 0.10f);

    circle(0, 25, 9);
    circle(-7, 22, 7);
    circle(7, 22, 7);
}
void drawTree(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    tree();

    glPopMatrix();
}
 //COCONUT TREE

void coconutTree()
{
    // Trunk
    glColor3f(0.45f, 0.25f, 0.07f);

    glBegin(GL_QUADS);

    glVertex2f(-2, 0);
    glVertex2f(2, 0);
    glVertex2f(1, 35);
    glVertex2f(-1, 35);

    glEnd();


    // Leaves
    glColor3f(0.05f, 0.55f, 0.10f);

    glBegin(GL_TRIANGLES);

    glVertex2f(0, 35);
    glVertex2f(-18, 30);
    glVertex2f(-3, 38);

    glVertex2f(0, 35);
    glVertex2f(18, 30);
    glVertex2f(3, 38);

    glVertex2f(0, 35);
    glVertex2f(-10, 45);
    glVertex2f(2, 38);

    glVertex2f(0, 35);
    glVertex2f(10, 45);
    glVertex2f(-2, 38);

    glEnd();


    // Coconuts
    glColor3f(0.35f, 0.20f, 0.05f);

    circle(-3, 34, 2);
    circle(3, 34, 2);
}
void drawCoconutTree(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    coconutTree();

    glPopMatrix();
}

// BANANA TREE

void bananaTree()
{
    // Trunk
    glColor3f(0.30f, 0.55f, 0.10f);
    rectangle(-1, 0, 1, 20);

    // Leaves
    glColor3f(0.15f, 0.65f, 0.12f);

    glBegin(GL_TRIANGLES);

    glVertex2f(0, 18);
    glVertex2f(-12, 25);
    glVertex2f(-2, 20);

    glVertex2f(0, 18);
    glVertex2f(12, 25);
    glVertex2f(2, 20);

    glVertex2f(0, 20);
    glVertex2f(-8, 32);
    glVertex2f(0, 23);

    glVertex2f(0, 20);
    glVertex2f(8, 32);
    glVertex2f(0, 23);

    glEnd();

    // Bananas
    glColor3f(1.0f, 0.8f, 0.05f);
    circle(2, 15, 1.5);
    circle(4, 14, 1.5);
    circle(3, 12, 1.5);
}
void drawBananaTree(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    bananaTree();

    glPopMatrix();
}

// BAMBOO

void bamboo()
{
    glColor3f(0.20f, 0.60f, 0.10f);
    glLineWidth(3);

    glBegin(GL_LINES);

    glVertex2f(0, 0);
    glVertex2f(2, 35);

    glVertex2f(3, 0);
    glVertex2f(5, 35);

    glVertex2f(6, 0);
    glVertex2f(8, 35);

    glVertex2f(9, 0);
    glVertex2f(11, 35);

    glVertex2f(12, 0);
    glVertex2f(14, 35);

    glEnd();
}
void drawBamboo(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    bamboo();

    glPopMatrix();
}

// RICE FIELD

void riceField()
{
    glColor3f(0.55f, 0.75f, 0.10f);
    rectangle(0, 0, 55, 23);

    glColor3f(0.90f, 0.80f, 0.10f);

    for (int x = 3; x < 55; x += 4)
    {
        for (int y = 3; y < 22; y += 5)
        {
            glBegin(GL_LINES);

            glVertex2f(x, y);
            glVertex2f(x, y + 3);

            glEnd();
        }
    }
}

void drawRiceField()
{
    glPushMatrix();

    glTranslatef(-100, -15, 0);

    riceField();

    glPopMatrix();
}
void vegetableField()
{
    glColor3f(0.35f, 0.22f, 0.08f);
    rectangle(0, 0, 35, 20);

    glColor3f(0.10f, 0.70f, 0.15f);

    for (int x = 3; x < 35; x += 5)
    {
        circle(x, 10, 2);
        circle(x, 15, 2);
    }
}

void drawVegetableField()
{
    glPushMatrix();

    glTranslatef(20, -15, 0);

    vegetableField();

    glPopMatrix();
}

// ROAD

void drawRoad()
{
    glColor3f(
        0.60f,
        0.45f,
        0.25f
    );


    glBegin(GL_POLYGON);

    glVertex2f(-15, 25);
    glVertex2f(5, 25);
    glVertex2f(35, -25);
    glVertex2f(-25, -25);

    glEnd();
}


// FOOTPATH

void drawFootpath()
{
    glColor3f(0.75f,0.65f,0.40f);


    glBegin(GL_POLYGON);

    glVertex2f(55, 15);
    glVertex2f(60, 15);
    glVertex2f(80, -20);
    glVertex2f(70, -20);

    glEnd();
}


// WOODEN BRIDGE

void bridge()
{
    glColor3f(0.40f, 0.20f, 0.08f);

    // Main bridge body
    rectangle(0, 0, 33, 5);

    glLineWidth(3);

    // Vertical wooden bars
    for (int x = 2; x < 33; x += 5)
    {
        glBegin(GL_LINES);

        glVertex2f(x, -1);
        glVertex2f(x, 7);

        glEnd();
    }
}

void drawBridge()
{
    glPushMatrix();

    glTranslatef(55, -28, 0);

    bridge();

    glPopMatrix();
}


// BOAT
void drawBoat()
{
    glPushMatrix();

    // Move entire boat
    glTranslatef(boatX, 0, 0);
    glTranslatef(0, -30, 0);

    // Make entire boat bigger
    glScalef(2.2f, 2.2f, 1.0f);


    // BLACK BOAT BODY
    glColor3f(0.02f, 0.02f, 0.02f);

    glBegin(GL_POLYGON);

    glVertex2f(-8.5f, -5.0f);
    glVertex2f(8.5f, -5.0f);
    glVertex2f(6.3f, -7.2f);
    glVertex2f(-6.3f, -7.2f);

    glEnd();


    // BROWN BOAT BODY - TOP
    glBegin(GL_QUADS);

    glColor3f(0.88f, 0.62f, 0.38f);
    glVertex2f(-4.0f, -3.0f);
    glVertex2f(4.0f, -3.0f);

    glColor3f(0.72f, 0.44f, 0.24f);
    glVertex2f(4.0f, -3.7f);
    glVertex2f(-4.0f, -3.7f);

    glEnd();


    // BROWN BOAT BODY - MIDDLE
    glBegin(GL_QUADS);

    glColor3f(0.72f, 0.44f, 0.24f);
    glVertex2f(-4.0f, -3.7f);
    glVertex2f(4.0f, -3.7f);

    glColor3f(0.58f, 0.32f, 0.15f);
    glVertex2f(4.0f, -4.4f);
    glVertex2f(-4.0f, -4.4f);

    glEnd();


    // BROWN BOAT BODY - BOTTOM
    glBegin(GL_QUADS);

    glColor3f(0.58f, 0.32f, 0.15f);
    glVertex2f(-4.0f, -4.4f);
    glVertex2f(4.0f, -4.4f);

    glColor3f(0.38f, 0.18f, 0.07f);
    glVertex2f(4.0f, -5.0f);
    glVertex2f(-4.0f, -5.0f);

    glEnd();


    // MAST
    glColor3f(0.05f, 0.05f, 0.05f);

    glLineWidth(2.5f);

    glBegin(GL_LINES);

    glVertex2f(0.2f, -3.0f);
    glVertex2f(0.2f, 8.8f);

    glVertex2f(-4.8f, 7.5f);
    glVertex2f(5.5f, 7.5f);

    glEnd();


    // SAIL
    glBegin(GL_TRIANGLES);

    // Left upper
    glColor3f(1.0f, 0.94f, 0.20f);

    glVertex2f(1.0f, 2.5f);
    glVertex2f(-4.5f, 7.5f);
    glVertex2f(-3.2f, 4.8f);


    glColor3f(1.0f, 0.88f, 0.08f);

    glVertex2f(1.0f, 2.5f);
    glVertex2f(-3.2f, 4.8f);
    glVertex2f(-3.0f, 1.3f);


    // Left lower
    glColor3f(1.0f, 0.83f, 0.00f);

    glVertex2f(1.0f, 2.5f);
    glVertex2f(-3.0f, 1.3f);
    glVertex2f(-2.5f, -2.3f);


    glVertex2f(1.0f, 2.5f);
    glVertex2f(-2.5f, -2.3f);
    glVertex2f(0.2f, -1.7f);


    // Right lower
    glColor3f(1.0f, 0.83f, 0.01f);

    glVertex2f(1.0f, 2.5f);
    glVertex2f(0.2f, -1.7f);
    glVertex2f(2.6f, -2.6f);


    glVertex2f(1.0f, 2.5f);
    glVertex2f(2.6f, -2.6f);
    glVertex2f(4.4f, 0.1f);


    // Right upper
    glColor3f(1.0f, 0.89f, 0.08f);

    glVertex2f(1.0f, 2.5f);
    glVertex2f(4.4f, 0.1f);
    glVertex2f(5.4f, 5.1f);


    glColor3f(1.0f, 0.95f, 0.22f);

    glVertex2f(1.0f, 2.5f);
    glVertex2f(5.4f, 5.1f);
    glVertex2f(5.2f, 7.5f);


    glVertex2f(1.0f, 2.5f);
    glVertex2f(5.2f, 7.5f);
    glVertex2f(-4.5f, 7.5f);

    glEnd();


    glPopMatrix();
}
void drawDock()
{
    glPushMatrix();

    glTranslatef(-55, -30, 0);

    glColor3f(0.35f, 0.16f, 0.05f);

    rectangle(0, 0, 25, 3);

    rectangle(2, -8, 4, 3);
    rectangle(9, -8, 11, 3);
    rectangle(16, -8, 18, 3);
    rectangle(23, -8, 25, 3);

    glPopMatrix();
}


void farmer()
{
    // Head
    glColor3f(0.65f, 0.40f, 0.25f);
    circle(0, 0, 3);

    // Hat
    glColor3f(0.85f, 0.70f, 0.20f);
    rectangle(-5, 3, 5, 4);

    // Body
    glColor3f(0.20f, 0.30f, 0.80f);
    rectangle(-3, -12, 3, -2);

    // Legs
    glColor3f(0.15f, 0.10f, 0.08f);

    glBegin(GL_LINES);

    glVertex2f(-2, -12);
    glVertex2f(-4, -19);

    glVertex2f(2, -12);
    glVertex2f(4, -19);

    glEnd();
}
void drawFarmer()
{
    glPushMatrix();

    glTranslatef(farmerMove, 0, 0);
    glTranslatef(-32, 3, 0);

    farmer();

    glPopMatrix();
}

void cow()
{
    // Body
    glColor3f(0.9f, 0.9f, 0.8f);
    rectangle(0, 0, 14, 7);

    // Head
    circle(15, 5, 4);

    // Legs
    glColor3f(0.15f, 0.10f, 0.05f);

    glBegin(GL_LINES);

    glVertex2f(3, 0);
    glVertex2f(3, -6);

    glVertex2f(11, 0);
    glVertex2f(11, -6);

    glEnd();
}
void drawCow(float x, float y)
{
    glPushMatrix();

    glTranslatef(animalMove, 0, 0);
    glTranslatef(x, y, 0);

    cow();

    glPopMatrix();
}

// GOAT

void goat()
{
    // Body
    glColor3f(0.75f, 0.70f, 0.60f);
    rectangle(0, 0, 9, 5);

    // Head
    circle(10, 4, 2.5);

    // Legs
    glColor3f(0.10f, 0.10f, 0.10f);

    glBegin(GL_LINES);

    glVertex2f(2, 0);
    glVertex2f(1, -5);

    glVertex2f(7, 0);
    glVertex2f(8, -5);

    glEnd();
}
void drawGoat(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    goat();

    glPopMatrix();
}

// CHICKEN

void chicken()
{
    // Body
    glColor3f(1.0f, 0.90f, 0.75f);
    circle(0, 0, 2.5);

    // Head
    circle(2, 2, 1.5);

    // Comb
    glColor3f(1, 0, 0);
    circle(2, 4, 0.5);
}
void drawChicken(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    chicken();

    glPopMatrix();
}

// DUCK

void duck()
{
    // Body
    glColor3f(1.0f, 0.9f, 0.15f);
    circle(0, 0, 2.5);

    // Head
    circle(2, 2, 1.5);

    // Beak
    glColor3f(1.0f, 0.45f, 0.05f);

    glBegin(GL_TRIANGLES);

    glVertex2f(3, 2);
    glVertex2f(6, 1);
    glVertex2f(3, 0);

    glEnd();
}
void drawDuck(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    duck();

    glPopMatrix();
}

// HAY STACK

void hayStack()
{
    glColor3f(0.85f, 0.65f, 0.12f);

    glBegin(GL_TRIANGLES);

    glVertex2f(-8, 0);
    glVertex2f(0, 18);
    glVertex2f(8, 0);

    glEnd();

    rectangle(-7, -3, 7, 3);
}
void drawHayStack(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    hayStack();

    glPopMatrix();
}

// FENCE

void fence()
{
    glColor3f(0.45f, 0.25f, 0.08f);

    rectangle(1, 10, 2, 20);
    rectangle(6, 10, 7, 20);
    rectangle(11, 10, 12, 20);
    rectangle(16, 10, 17, 20);
    rectangle(21, 10, 22, 20);
    rectangle(26, 10, 27, 20);
    rectangle(31, 10, 32, 20);

    rectangle(0, 13, 33, 15);
    rectangle(0, 17, 33, 19);
}
void drawFence()
{
    glPushMatrix();

    glTranslatef(24, 0, 0);

    fence();

    glPopMatrix();
}
// WELL

void well()
{
    // Well body
    glColor3f(0.50f, 0.50f, 0.50f);
    rectangle(-6, 0, 6, 6);

    // Side posts
    glColor3f(0.2f, 0.2f, 0.2f);

    glBegin(GL_LINES);

    glVertex2f(-5, 6);
    glVertex2f(-5, 16);

    glVertex2f(5, 6);
    glVertex2f(5, 16);

    glEnd();

    // Top wood
    glColor3f(0.45f, 0.20f, 0.05f);
    rectangle(-7, 15, 7, 17);
}
void drawWell(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    well();

    glPopMatrix();
}


// WATER PUMP
void waterPump()
{
    glColor3f(0.25f, 0.45f, 0.35f);

    // Main body
    rectangle(0, 0, 3, 13);

    // Spout
    rectangle(3, 9, 9, 12);

    // Handle
    glLineWidth(3);

    glBegin(GL_LINES);

    glVertex2f(1, 12);
    glVertex2f(-4, 18);

    glEnd();
}
void drawWaterPump(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    waterPump();

    glPopMatrix();
}


// FLOWERS

void flower()
{
    // Stem
    glColor3f(0.1f, 0.7f, 0.15f);

    glBegin(GL_LINES);

    glVertex2f(0, 0);
    glVertex2f(0, 5);

    glEnd();

    // Flower
    glColor3f(1.0f, 0.2f, 0.3f);
    circle(0, 6, 1.3);
}
void drawFlowers()
{
    for (int x = -90; x <= 90; x += 12)
    {
        glPushMatrix();

        glTranslatef(x, 12, 0);

        flower();

        glPopMatrix();
    }
}
// BUSH

void bush()
{
    glColor3f(0.10f, 0.55f, 0.10f);

    circle(0, 0, 5);
    circle(5, 1, 5);
    circle(-5, 1, 5);
}
void drawBush(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    bush();

    glPopMatrix();
}

// FISHING ROD AND NET
void fishingItems()
{
    // Fishing rod
    glColor3f(0.25f, 0.15f, 0.05f);
    glLineWidth(2);

    glBegin(GL_LINES);

    glVertex2f(7, 5);
    glVertex2f(20, -13);

    glEnd();


    // Fishing line
    glColor3f(0.9f, 0.9f, 0.9f);

    glBegin(GL_LINES);

    glVertex2f(20, -13);
    glVertex2f(20, -23);

    glEnd();


    // Net
    glColor3f(0.3f, 0.3f, 0.3f);

    glBegin(GL_LINE_LOOP);

    glVertex2f(0, 0);
    glVertex2f(8, 0);
    glVertex2f(5, -10);
    glVertex2f(3, -10);

    glEnd();
}
void drawFishingItems()
{
    glPushMatrix();

    glTranslatef(35, -25, 0);

    fishingItems();

    glPopMatrix();
}



// DISPLAY

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(0.5f, 0.5f, 1.0f);


    // SKY
    drawSky();
    drawSun();
    drawClouds();
    drawBirds();


    // LAND
    drawGrass();


    // BACKGROUND TREES
    drawTree(-85, 18);
    drawCoconutTree(-67, 18);
    drawTree(82, 18);
    drawCoconutTree(93, 18);
    drawBamboo(65, 18);


    // HOUSES
    drawVillageHouse(-55, 20);
    drawTinHouse(-20, 20);
    drawVillageHouse(20, 20);


    // PLANTS
    drawBananaTree(54, 18);
    drawTree(72, 18);


    // FIELDS
    drawRiceField();
    drawVegetableField();


    // ROAD
    drawRoad();
    drawFootpath();


    // POND
    drawPond();


    // FENCE
    drawFence();


    // OTHER VILLAGE OBJECTS
    drawHayStack(70, 9);
    drawWell(10, 7);
    drawWaterPump(62, 7);
    drawBush(-75, 12);
    drawBush(88, 10);
    drawFlowers();


    // FARMER AND ANIMALS
    drawFarmer();
    drawCow(-10, 0);
    drawGoat(8, 5);
    drawChicken(38, 7);
    drawChicken(43, 5);
    drawDuck(55, -2);
    drawDuck(61, 0);


    // RIVER
    drawRiver();


    // RIVER OBJECTS
    drawDock();
    drawBridge();
    drawBoat();
    drawFishingItems();


    glutSwapBuffers();
}

void update(int value)
{
    // Sun movement
    sunX += 0.02f;

    if (sunX > 110)
        sunX = -110;


    // Cloud movement
    cloudX1 += cloudSpeed;
    cloudX2 += cloudSpeed * 0.7f;

    if (cloudX1 > 200)
        cloudX1 = -100;

    if (cloudX2 > 200)
        cloudX2 = -100;


    // Bird movement
    birdX += 0.30f;

    if (birdX > 190)
        birdX = -100;


    // Boat movement
    if (boatMoving)
    {
        boatX += 0.15f;

        if (boatX > 120)
            boatX = -100;
    }


    // Farmer movement
    farmerMove += 0.03f;

    if (farmerMove > 8)
        farmerMove = -8;


    // Animal movement
    animalMove += 0.015f;

    if (animalMove > 4)
        animalMove = -4;


    // River waves
    waveOffset += 1.0f;

    if (waveOffset > 1000.0f)
        waveOffset = 0.0f;


    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

// KEYBOARD

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'n':
        case 'N':
            nightMode = !nightMode;
            break;

        case 'c':
        case 'C':
            cloudSpeed += 0.10f;

            if (cloudSpeed > 1.5f)
                cloudSpeed = 1.5f;

            break;

        case 'r':
        case 'R':
            cloudSpeed = 0.15f;
            break;

        case 27:
            exit(0);
            break;
    }

    glutPostRedisplay();
}


// MOUSE

void handleMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        boatMoving = !boatMoving;
    }
}


// INITIALIZATION

void init()
{
    glClearColor(0.45f, 0.80f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-50, 50, -50, 50);

    glMatrixMode(GL_MODELVIEW);
}


// MAIN

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(100, 50);

    glutCreateWindow("Beautiful Village Scene - OpenGL");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(handleMouse);

    glutTimerFunc(20, update, 0);

    glutMainLoop();

    return 0;
}
