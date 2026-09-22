#include <windows.h>
#include <GL/glut.h>
#include <math.h>


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




void drawSky()
{
    glBegin(GL_QUADS);

    if (nightMode)
    {
        glColor3ub(26, 46, 89);
        glVertex2f(-100, 20);

        glColor3ub(26, 46, 89);
        glVertex2f(100, 20);

        glColor3ub(3, 8, 31);
        glVertex2f(100, 100);

        glColor3ub(3, 8, 31);
        glVertex2f(-100, 100);
    }
    else
    {
        glColor3ub(166, 224, 255);
        glVertex2f(-100, 20);

        glColor3ub(166, 224, 255);
        glVertex2f(100, 20);

        glColor3ub(38, 128, 230);
        glVertex2f(100, 100);

        glColor3ub(38, 128, 230);
        glVertex2f(-100, 100);
    }

    glEnd();
}

void drawSun()
{
    if (nightMode)
    {
        glColor3ub(230, 230, 230); // Moon
        circle(sunX, 80, 7);
    }
    else
    {
        glColor3ub(255, 255, 0); // Sun
        circle(sunX, 80, 7);
    }
}



void cloud()
{
    if (nightMode)
    {
        glColor3ub(56, 69, 97);

        circle(2, 1, 5);
        circle(8, 2, 6);
        circle(14, 1, 7);
        circle(20, 1, 5);

        glColor3ub(97, 110, 140);

        circle(0, 3, 5);
        circle(6, 5, 6);
        circle(13, 5, 7);
        circle(19, 3, 5);

        glColor3ub(148, 158, 184);

        circle(5, 7, 4);
        circle(11, 9, 5);
        circle(17, 7, 4);
    }
    else
    {
        glColor3ub(184, 209, 235);

        circle(2, 1, 5);
        circle(7, 1, 6);
        circle(13, 0, 7);
        circle(19, 1, 6);

        glColor3ub(224, 237, 250);

        circle(0, 3, 5);
        circle(5, 5, 6);
        circle(11, 5, 7);
        circle(17, 4, 7);
        circle(22, 3, 5);

        glColor3ub(255, 255, 255);

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



void bird()
{
    glColor3ub(13, 13, 13);

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

    glPushMatrix();
    glTranslatef(birdX, 0, 0);
    glTranslatef(-70, 67, 0);
    bird();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(birdX, 0, 0);
    glTranslatef(-55, 73, 0);
    bird();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(birdX, 0, 0);
    glTranslatef(-40, 65, 0);
    bird();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(birdX, 0, 0);
    glTranslatef(-25, 76, 0);
    bird();
    glPopMatrix();
}



void drawGrass()
{
    if (nightMode)
    {
        glColor3ub(20, 64, 20);
    }
    else
    {
        glColor3ub(51, 166, 46);
    }

    rectangle(-100, -100, 100, 25);
}




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

        glColor3ub(26, 77, 128);
        glVertex2f(-100, -25);

        glColor3ub(26, 77, 128);
        glVertex2f(100, -20);


        glColor3ub(5, 26, 56);
        glVertex2f(100, -60);

        glColor3ub(5, 26, 56);
        glVertex2f(-100, -65);
    }
    else
    {

        glColor3ub(77, 191, 242);
        glVertex2f(-100, -25);

        glColor3ub(77, 191, 242);
        glVertex2f(100, -20);


        glColor3ub(13, 89, 191);
        glVertex2f(100, -60);

        glColor3ub(13, 89, 191);
        glVertex2f(-100, -65);
    }

    glEnd();


    if (nightMode)
        glColor3ub(140, 191, 242);
    else
        glColor3ub(217, 242, 255);

    glLineWidth(2);

    drawWave(-95, -55, -34);
    drawWave(-40, 5, -42);
    drawWave(20, 70, -50);
}

void drawPond()
{
    glColor3ub(26,153,204);

    glPushMatrix();

    glTranslatef(60,2,0);

    glScalef(1.8f,0.7f,1);

    circle(0,0,12);

    glPopMatrix();
}



void villageHouse()
{

    glBegin(GL_QUADS);

    glColor3ub(140, 77, 46);
    glVertex2f(0, 0);
    glVertex2f(30, 0);

    glColor3ub(209, 143, 97);
    glVertex2f(30, 20);
    glVertex2f(0, 20);

    glEnd();



    glBegin(GL_QUADS);

    glColor3ub(89, 89, 89);
    glVertex2f(-3, 20);

    glColor3ub(158, 158, 158);
    glVertex2f(3, 31);
    glVertex2f(27, 31);

    glColor3ub(89, 89, 89);
    glVertex2f(34, 20);

    glEnd();



    glColor3ub(97, 51, 26);

    glBegin(GL_QUADS);

    glVertex2f(11, 0);
    glVertex2f(19, 0);
    glVertex2f(19, 14);
    glVertex2f(11, 14);

    glEnd();



    glBegin(GL_QUADS);

    glColor3ub(46, 20, 8);
    glVertex2f(12, 0);
    glVertex2f(18, 0);

    glColor3ub(107, 56, 26);
    glVertex2f(18, 13);
    glVertex2f(12, 13);

    glEnd();



    glColor3ub(31, 15, 5);
    glLineWidth(2.0f);

    glBegin(GL_LINES);

    glVertex2f(15, 0);
    glVertex2f(15, 13);

    glEnd();



    glPointSize(4.0f);
    glColor3ub(217, 166, 51);

    glBegin(GL_POINTS);

    glVertex2f(14.3f, 6);
    glVertex2f(15.7f, 6);

    glEnd();



    glColor3ub(97, 51, 26);

    glBegin(GL_QUADS);

    glVertex2f(3, 7);
    glVertex2f(9, 7);
    glVertex2f(9, 14);
    glVertex2f(3, 14);

    glEnd();



    glBegin(GL_QUADS);

    glColor3ub(97, 51, 26);
    glVertex2f(4, 8);
    glVertex2f(8, 8);

    glColor3ub(173, 107, 61);
    glVertex2f(8, 13);
    glVertex2f(4, 13);

    glEnd();



    glColor3ub(56, 28, 13);
    glLineWidth(1.5f);

    glBegin(GL_LINES);

    glVertex2f(6, 8);
    glVertex2f(6, 13);

    glVertex2f(4, 10.5f);
    glVertex2f(8, 10.5f);

    glEnd();



    glColor3ub(97, 51, 26);

    glBegin(GL_QUADS);

    glVertex2f(21, 7);
    glVertex2f(27, 7);
    glVertex2f(27, 14);
    glVertex2f(21, 14);

    glEnd();



    glBegin(GL_QUADS);

    glColor3ub(97, 51, 26);
    glVertex2f(22, 8);
    glVertex2f(26, 8);

    glColor3ub(173, 107, 61);
    glVertex2f(26, 13);
    glVertex2f(22, 13);

    glEnd();



    glColor3ub(56, 28, 13);
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

    glBegin(GL_QUADS);

    glColor3ub(184, 153, 102);
    glVertex2f(0, 0);
    glVertex2f(30, 0);

    glColor3ub(242, 209, 148);
    glVertex2f(30, 20);
    glVertex2f(0, 20);

    glEnd();



    glBegin(GL_TRIANGLES);

    glColor3ub(71, 74, 82);
    glVertex2f(-6, 20);

    glColor3ub(128, 130, 138);
    glVertex2f(15, 34);

    glColor3ub(87, 89, 97);
    glVertex2f(15, 20);

    glEnd();



    glBegin(GL_TRIANGLES);

    glColor3ub(128, 130, 138);
    glVertex2f(15, 34);

    glColor3ub(71, 74, 82);
    glVertex2f(36, 20);

    glColor3ub(87, 89, 97);
    glVertex2f(15, 20);

    glEnd();



    glColor3ub(38, 41, 46);

    glBegin(GL_QUADS);

    glVertex2f(-6, 20);
    glVertex2f(36, 20);
    glVertex2f(35.5f, 19);
    glVertex2f(-5.5f, 19);

    glEnd();



    glBegin(GL_QUADS);

    glColor3ub(77, 31, 5);
    glVertex2f(1, 0);

    glColor3ub(122, 51, 10);
    glVertex2f(2.5f, 0);

    glColor3ub(133, 59, 13);
    glVertex2f(2.5f, 20);

    glColor3ub(77, 31, 5);
    glVertex2f(1, 20);

    glEnd();



    glBegin(GL_QUADS);

    glColor3ub(77, 31, 5);
    glVertex2f(27.5f, 0);

    glColor3ub(122, 51, 10);
    glVertex2f(29, 0);

    glColor3ub(133, 59, 13);
    glVertex2f(29, 20);

    glColor3ub(77, 31, 5);
    glVertex2f(27.5f, 20);

    glEnd();



    glColor3ub(122, 77, 31);

    glBegin(GL_QUADS);

    glVertex2f(11, 0);
    glVertex2f(19, 0);
    glVertex2f(19, 15);
    glVertex2f(11, 15);

    glEnd();



    glBegin(GL_QUADS);

    glColor3ub(56, 54, 48);
    glVertex2f(12, 0);
    glVertex2f(18, 0);

    glColor3ub(87, 79, 69);
    glVertex2f(18, 14);
    glVertex2f(12, 14);

    glEnd();



    glBegin(GL_QUADS);

    glColor3ub(92, 33, 3);
    glVertex2f(15, 1);

    glColor3ub(143, 64, 8);
    glVertex2f(18, 2);

    glColor3ub(148, 69, 10);
    glVertex2f(18, 13);

    glColor3ub(97, 36, 3);
    glVertex2f(15, 12);

    glEnd();



    glColor3ub(107, 43, 5);
    rectangle(21, 6, 27, 12);



    glColor3ub(209, 199, 168);
    rectangle(22, 7, 26, 11);



    glColor3ub(64, 51, 38);

    glLineWidth(1.0f);

    glBegin(GL_LINES);

    glVertex2f(23, 7);
    glVertex2f(23, 11);

    glVertex2f(24, 7);
    glVertex2f(24, 11);

    glVertex2f(25, 7);
    glVertex2f(25, 11);

    glEnd();



    glColor3ub(128, 51, 5);

    glBegin(GL_QUADS);

    glVertex2f(19.5f, 6.5f);
    glVertex2f(21, 7);
    glVertex2f(21, 11.5f);
    glVertex2f(19.5f, 11);

    glEnd();



    glBegin(GL_QUADS);

    glVertex2f(27, 7);
    glVertex2f(28.5f, 6.5f);
    glVertex2f(28.5f, 11);
    glVertex2f(27, 11.5f);

    glEnd();



    glBegin(GL_QUADS);

    glColor3ub(122, 117, 107);
    glVertex2f(0, -3);
    glVertex2f(30, -3);

    glColor3ub(163, 156, 140);
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
    glColor3ub(89, 46, 13);
    rectangle(-2, 0, 2, 20);

    glColor3ub(13, 128, 26);

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

void drawBigTree(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);
    glScalef(1.3f, 1.3f, 1.0f);

    tree();

    glPopMatrix();
}



void coconutTree()
{

    glColor3ub(115, 64, 18);

    glBegin(GL_QUADS);

    glVertex2f(-2, 0);
    glVertex2f(2, 0);
    glVertex2f(1, 35);
    glVertex2f(-1, 35);

    glEnd();


    glColor3ub(13, 140, 26);

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



    glColor3ub(89, 51, 13);

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



void bananaTree()
{

    glColor3ub(77, 140, 26);
    rectangle(-1, 0, 1, 20);


    glColor3ub(38, 166, 31);

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


    glColor3ub(255, 204, 13);
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



void bamboo()
{
    glColor3ub(51, 153, 26);
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



void riceField()
{
    glColor3ub(140, 191, 26);
    rectangle(0, 0, 55, 23);

    glColor3ub(230, 204, 26);

    glBegin(GL_LINES);


    glVertex2f(3, 3);   glVertex2f(3, 6);
    glVertex2f(7, 3);   glVertex2f(7, 6);
    glVertex2f(11, 3);  glVertex2f(11, 6);
    glVertex2f(15, 3);  glVertex2f(15, 6);
    glVertex2f(19, 3);  glVertex2f(19, 6);
    glVertex2f(23, 3);  glVertex2f(23, 6);
    glVertex2f(27, 3);  glVertex2f(27, 6);
    glVertex2f(31, 3);  glVertex2f(31, 6);
    glVertex2f(35, 3);  glVertex2f(35, 6);
    glVertex2f(39, 3);  glVertex2f(39, 6);
    glVertex2f(43, 3);  glVertex2f(43, 6);
    glVertex2f(47, 3);  glVertex2f(47, 6);
    glVertex2f(51, 3);  glVertex2f(51, 6);


    glVertex2f(3, 8);   glVertex2f(3, 11);
    glVertex2f(7, 8);   glVertex2f(7, 11);
    glVertex2f(11, 8);  glVertex2f(11, 11);
    glVertex2f(15, 8);  glVertex2f(15, 11);
    glVertex2f(19, 8);  glVertex2f(19, 11);
    glVertex2f(23, 8);  glVertex2f(23, 11);
    glVertex2f(27, 8);  glVertex2f(27, 11);
    glVertex2f(31, 8);  glVertex2f(31, 11);
    glVertex2f(35, 8);  glVertex2f(35, 11);
    glVertex2f(39, 8);  glVertex2f(39, 11);
    glVertex2f(43, 8);  glVertex2f(43, 11);
    glVertex2f(47, 8);  glVertex2f(47, 11);
    glVertex2f(51, 8);  glVertex2f(51, 11);


    glVertex2f(3, 13);   glVertex2f(3, 16);
    glVertex2f(7, 13);   glVertex2f(7, 16);
    glVertex2f(11, 13);  glVertex2f(11, 16);
    glVertex2f(15, 13);  glVertex2f(15, 16);
    glVertex2f(19, 13);  glVertex2f(19, 16);
    glVertex2f(23, 13);  glVertex2f(23, 16);
    glVertex2f(27, 13);  glVertex2f(27, 16);
    glVertex2f(31, 13);  glVertex2f(31, 16);
    glVertex2f(35, 13);  glVertex2f(35, 16);
    glVertex2f(39, 13);  glVertex2f(39, 16);
    glVertex2f(43, 13);  glVertex2f(43, 16);
    glVertex2f(47, 13);  glVertex2f(47, 16);
    glVertex2f(51, 13);  glVertex2f(51, 16);


    glVertex2f(3, 18);   glVertex2f(3, 21);
    glVertex2f(7, 18);   glVertex2f(7, 21);
    glVertex2f(11, 18);  glVertex2f(11, 21);
    glVertex2f(15, 18);  glVertex2f(15, 21);
    glVertex2f(19, 18);  glVertex2f(19, 21);
    glVertex2f(23, 18);  glVertex2f(23, 21);
    glVertex2f(27, 18);  glVertex2f(27, 21);
    glVertex2f(31, 18);  glVertex2f(31, 21);
    glVertex2f(35, 18);  glVertex2f(35, 21);
    glVertex2f(39, 18);  glVertex2f(39, 21);
    glVertex2f(43, 18);  glVertex2f(43, 21);
    glVertex2f(47, 18);  glVertex2f(47, 21);
    glVertex2f(51, 18);  glVertex2f(51, 21);

    glEnd();
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
    glColor3ub(89, 56, 20);
    rectangle(0, 0, 35, 20);

    glColor3ub(26, 179, 38);

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



void drawRoad()
{
    glColor3ub(153,115,64);

    glBegin(GL_POLYGON);

    glVertex2f(-15, 25);
    glVertex2f(5, 25);
    glVertex2f(35, -25);
    glVertex2f(-25, -25);

    glEnd();
}



void drawFootpath()
{
    glColor3ub(191,166,102);

    glBegin(GL_POLYGON);

    glVertex2f(55, 15);
    glVertex2f(60, 15);
    glVertex2f(80, -20);
    glVertex2f(70, -20);

    glEnd();
}




void bridge()
{
    glColor3ub(102, 51, 20);


    rectangle(0, 0, 33, 5);

    glLineWidth(3);


    glBegin(GL_LINES);

    glVertex2f(2, -1);
    glVertex2f(2, 7);

    glVertex2f(7, -1);
    glVertex2f(7, 7);

    glVertex2f(12, -1);
    glVertex2f(12, 7);

    glVertex2f(17, -1);
    glVertex2f(17, 7);

    glVertex2f(22, -1);
    glVertex2f(22, 7);

    glVertex2f(27, -1);
    glVertex2f(27, 7);

    glVertex2f(32, -1);
    glVertex2f(32, 7);

    glEnd();
}

void drawBridge()
{
    glPushMatrix();

    glTranslatef(55, -28, 0);

    bridge();

    glPopMatrix();
}



void drawBoat()
{
    glPushMatrix();


    glTranslatef(boatX, 0, 0);
    glTranslatef(0, -30, 0);


    glScalef(2.2f, 2.2f, 1.0f);



    glColor3ub(5, 5, 5);

    glBegin(GL_POLYGON);

    glVertex2f(-8.5f, -5.0f);
    glVertex2f(8.5f, -5.0f);
    glVertex2f(6.3f, -7.2f);
    glVertex2f(-6.3f, -7.2f);

    glEnd();



    glBegin(GL_QUADS);

    glColor3ub(224, 158, 97);
    glVertex2f(-4.0f, -3.0f);
    glVertex2f(4.0f, -3.0f);

    glColor3ub(184, 112, 61);
    glVertex2f(4.0f, -3.7f);
    glVertex2f(-4.0f, -3.7f);

    glEnd();



    glBegin(GL_QUADS);

    glColor3ub(184, 112, 61);
    glVertex2f(-4.0f, -3.7f);
    glVertex2f(4.0f, -3.7f);

    glColor3ub(148, 82, 38);
    glVertex2f(4.0f, -4.4f);
    glVertex2f(-4.0f, -4.4f);

    glEnd();



    glBegin(GL_QUADS);

    glColor3ub(148, 82, 38);
    glVertex2f(-4.0f, -4.4f);
    glVertex2f(4.0f, -4.4f);

    glColor3ub(97, 46, 18);
    glVertex2f(4.0f, -5.0f);
    glVertex2f(-4.0f, -5.0f);

    glEnd();



    glColor3ub(13, 13, 13);

    glLineWidth(2.5f);

    glBegin(GL_LINES);

    glVertex2f(0.2f, -3.0f);
    glVertex2f(0.2f, 8.8f);

    glVertex2f(-4.8f, 7.5f);
    glVertex2f(5.5f, 7.5f);

    glEnd();



    glBegin(GL_TRIANGLES);


    glColor3ub(255, 240, 51);

    glVertex2f(1.0f, 2.5f);
    glVertex2f(-4.5f, 7.5f);
    glVertex2f(-3.2f, 4.8f);


    glColor3ub(255, 224, 20);

    glVertex2f(1.0f, 2.5f);
    glVertex2f(-3.2f, 4.8f);
    glVertex2f(-3.0f, 1.3f);



    glColor3ub(255, 212, 0);

    glVertex2f(1.0f, 2.5f);
    glVertex2f(-3.0f, 1.3f);
    glVertex2f(-2.5f, -2.3f);


    glVertex2f(1.0f, 2.5f);
    glVertex2f(-2.5f, -2.3f);
    glVertex2f(0.2f, -1.7f);



    glColor3ub(255, 212, 3);

    glVertex2f(1.0f, 2.5f);
    glVertex2f(0.2f, -1.7f);
    glVertex2f(2.6f, -2.6f);


    glVertex2f(1.0f, 2.5f);
    glVertex2f(2.6f, -2.6f);
    glVertex2f(4.4f, 0.1f);



    glColor3ub(255, 227, 20);

    glVertex2f(1.0f, 2.5f);
    glVertex2f(4.4f, 0.1f);
    glVertex2f(5.4f, 5.1f);


    glColor3ub(255, 242, 56);

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

    glColor3ub(89, 41, 13);

    rectangle(0, 0, 25, 3);

    rectangle(2, -8, 4, 3);
    rectangle(9, -8, 11, 3);
    rectangle(16, -8, 18, 3);
    rectangle(23, -8, 25, 3);

    glPopMatrix();
}


void farmer()
{

    glColor3ub(166, 102, 64);
    circle(0, 0, 3);


    glColor3ub(217, 179, 51);
    rectangle(-5, 3, 5, 4);


    glColor3ub(51, 77, 204);
    rectangle(-3, -12, 3, -2);


    glColor3ub(38, 26, 20);

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

    glColor3ub(230, 230, 204);
    rectangle(0, 0, 14, 7);


    circle(15, 5, 4);


    glColor3ub(38, 26, 13);

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



void goat()
{

    glColor3ub(191, 179, 153);
    rectangle(0, 0, 9, 5);


    circle(10, 4, 2.5);


    glColor3ub(26, 26, 26);

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



void chicken()
{

    glColor3ub(255, 230, 191);
    circle(0, 0, 2.5);


    circle(2, 2, 1.5);


    glColor3ub(255, 0, 0);
    circle(2, 4, 0.5);
}

void drawChicken(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    chicken();

    glPopMatrix();
}



void duck()
{

    glColor3ub(255, 230, 38);
    circle(0, 0, 2.5);


    circle(2, 2, 1.5);


    glColor3ub(255, 115, 13);

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



void hayStack()
{
    glColor3ub(217, 166, 31);

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


void fence()
{
    glColor3ub(115, 64, 20);

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



void well()
{

    glColor3ub(128, 128, 128);
    rectangle(-6, 0, 6, 6);


    glColor3ub(51, 51, 51);

    glBegin(GL_LINES);

    glVertex2f(-5, 6);
    glVertex2f(-5, 16);

    glVertex2f(5, 6);
    glVertex2f(5, 16);

    glEnd();


    glColor3ub(115, 51, 13);
    rectangle(-7, 15, 7, 17);
}

void drawWell(float x, float y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    well();

    glPopMatrix();
}




void waterPump()
{
    glColor3ub(64, 115, 89);


    rectangle(0, 0, 3, 13);


    rectangle(3, 9, 9, 12);


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



void flower()
{

    glColor3ub(26, 179, 38);

    glBegin(GL_LINES);

    glVertex2f(0, 0);
    glVertex2f(0, 5);

    glEnd();



    glColor3ub(255, 51, 77);
    circle(0, 6, 1.3);
}


void drawFlowers()
{
    glPushMatrix();
    glTranslatef(-90, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-78, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-66, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-54, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-42, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(18, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(42, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(54, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(66, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(78, 12, 0);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(90, 12, 0);
    flower();
    glPopMatrix();
}

// BUSH

void bush()
{
    glColor3ub(26, 140, 26);

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



void fishingItems()
{

    glColor3ub(64, 38, 13);
    glLineWidth(2);

    glBegin(GL_LINES);

    glVertex2f(7, 5);
    glVertex2f(20, -13);

    glEnd();



    glColor3ub(230, 230, 230);

    glBegin(GL_LINES);

    glVertex2f(20, -13);
    glVertex2f(20, -23);

    glEnd();



    glColor3ub(77, 77, 77);

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



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();





    drawSky();
    drawSun();
    drawClouds();
    drawBirds();



    drawGrass();



    drawTree(-85, 18);
    drawCoconutTree(-67, 18);
    drawTree(82, 18);
    drawCoconutTree(93, 18);
    drawBamboo(65, 18);



    drawVillageHouse(-55, 20);
    drawTinHouse(-20, 20);
    drawVillageHouse(20, 20);



    drawBananaTree(54, 18);
    drawTree(72, 18);



    drawRiceField();
    drawVegetableField();



    drawRoad();
    drawFootpath();



    drawPond();



    drawFence();



    drawHayStack(70, 9);
    drawWell(10, 7);
    drawWaterPump(62, 7);
    drawBush(-75, 12);
    drawBush(88, 10);
    drawFlowers();



    drawFarmer();drawGoat(8, 5);
    drawCow(-10, 0);

    drawChicken(38, 7);
    drawChicken(43, 5);
    drawDuck(55, -2);
    drawDuck(61, 0);



    drawRiver();



    drawDock();
    drawBridge();
    drawFishingItems();
    drawBoat();



    drawTree(-85, -82);
    drawTree(-70, -76);
    drawTree(-55, -80);

    drawTree(65, -82);
    drawTree(82, -76);
    drawTree(92, -84);


    glutSwapBuffers();
}

void update(int value)
{
    sunX += 0.02f;
    if (sunX > 110) sunX = -110;

    cloudX1 += cloudSpeed;
    cloudX2 += cloudSpeed * 0.7f;
    if (cloudX1 > 200) cloudX1 = -100;
    if (cloudX2 > 200) cloudX2 = -100;

    birdX += 0.30f;
    if (birdX > 190) birdX = -100;

    if (boatMoving)
    {
        boatX += 0.15f;
        if (boatX > 120) boatX = -100;
    }

    farmerMove += 0.03f;
    if (farmerMove > 8) farmerMove = -8;

    animalMove += 0.015f;
    if (animalMove > 4) animalMove = -4;

    waveOffset += 1.0f;
    if (waveOffset > 1000) waveOffset = 0;

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

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




void handleMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        boatMoving = !boatMoving;
    }
}




void init()
{
    glClearColor(0.45f, 0.80f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-50, 50, -50, 50);   glScalef(0.5f, 0.5f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
}




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
