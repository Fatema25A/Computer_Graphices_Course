#include <windows.h>
#include <GL/glut.h>
#include <math.h>

bool natureView=true;
bool villageFair=false;
bool smartCity=false;
bool villageScene=false;

class NatureView{

public:
float _moveCloud=0.0f;
float _moveBoat=0.0f;
float _moveSmallBoat=0.0f;
float angle=0.0f;
float moveCarLeft=0.0f;
float moveCarRight=0.0f;
float boatSpeed=0.4f;
float carSpeed=0.6f;
bool rainOn = false;
bool nightMode = false;
float downSun = 0.0f;
float upMoon=0.0f;

#define MAX_RAIN 150

float rainX[MAX_RAIN];
float rainY[MAX_RAIN];
float rainSpeed[MAX_RAIN];


void circle(float r, float g, float b, float radius, float xc, float yc)//g01
{
    glMatrixMode(GL_MODELVIEW);

    glBegin(GL_POLYGON);

    for(int i = 0; i < 200; i++)
    {
        glColor3ub(r, g, b);

        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;

        float x = radius * cos(A);
        float y = radius * sin(A);

        glVertex2f(x + xc, y + yc);
    }

    glEnd();
}

void initRain()//g02
{
    for(int i = 0; i < MAX_RAIN; i++)
    {
        rainX[i] = -50 + (rand() % 100);
        rainY[i] = -10 + (rand() % 60);
        rainSpeed[i] = 0.3f + (rand() % 20) / 100.0f;
    }
}

void rain()//g03
{
    if(!rainOn)
        return;

    glColor3ub(190, 225, 255);

    glBegin(GL_LINES);

    for(int i = 0; i < MAX_RAIN; i++)
    {
        glVertex2f(rainX[i], rainY[i]);
        glVertex2f(rainX[i] - 0.5f, rainY[i] - 2.5f);
    }

    glEnd();
}

void rainySkyEffect()//g04
{
    if(!rainOn)
        return;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.25f, 0.30f, 0.35f, 0.25f);

    glBegin(GL_QUADS);
    glVertex2f(-50, 50);
    glVertex2f(50, 50);
    glVertex2f(50, -50);
    glVertex2f(-50, -50);
    glEnd();

    glDisable(GL_BLEND);
}

void updateRain(int a)//g05
{
    if(rainOn)
    {
        for(int i = 0; i < MAX_RAIN; i++)
        {
            rainY[i] -= rainSpeed[i];

            if(rainY[i] < -50)
            {
                rainY[i] = 50;
                rainX[i] = -50 + (rand() % 100);
            }
        }

        glutPostRedisplay();
    }

    //glutTimerFunc(20, updateRain, 0);
}

void sky()//g06
{
    if(rainOn)
        glColor3ub(70, 80, 100);
    else
        glColor3ub(30, 170, 235);
    if(nightMode&& upMoon>=20){
        glColor3ub(0,0,0);
    }
    glBegin(GL_QUADS);

    glVertex2f(-50, -50);
    glVertex2f(50, -50);
    glVertex2f(50, 50);
    glVertex2f(-50, 50);

    glEnd();
}


void sun()//g07
{
    glColor3ub(255, 205, 25);

    glBegin(GL_TRIANGLES);

    glVertex2f(29, 26);
    glVertex2f(31, 26);
    glVertex2f(30, 31);

    glVertex2f(29, 16);
    glVertex2f(31, 16);
    glVertex2f(30, 12);

    glVertex2f(35, 20);
    glVertex2f(35, 22);
    glVertex2f(39, 21);

    glVertex2f(25, 20);
    glVertex2f(25, 22);
    glVertex2f(21, 21);

    glVertex2f(33, 24);
    glVertex2f(35, 26);
    glVertex2f(37, 29);

    glVertex2f(27, 24);
    glVertex2f(25, 26);
    glVertex2f(23, 29);

    glVertex2f(33, 18);
    glVertex2f(35, 16);
    glVertex2f(37, 13);

    glVertex2f(27, 18);
    glVertex2f(25, 16);
    glVertex2f(23, 13);

    glEnd();

    circle(255, 210, 40, 4, 30, 21);
}
void moon(){//g08
        circle(255, 255, 255, 4, -30, 21);
}
void star(){//g09
    if(nightMode && upMoon>=20){
    circle(255, 255, 255, 0.5, -25, 46);
    circle(255, 255, 255, 0.5, -15, 44);
    circle(255, 255, 255, 0.5, -15, 47);
    circle(255, 255, 255, 0.5, 20, 45);
    circle(255, 255, 255, 0.5, -21, 41);
    circle(255, 255, 255, 0.5, -23, 43);
    circle(255, 255, 255, 0.5, 23, 41);
    circle(255, 255, 255, 0.5, -24, 45);
    circle(255, 255, 255, 0.5, -44, 45);
    circle(255, 255, 255, 0.5, 45, 45);
    circle(255, 255, 255, 0.5, -49, 45);
    circle(255, 255, 255, 0.5, 47, 45);
    circle(255, 255, 255, 0.5, -36, 45);
    circle(255, 255, 255, 0.5, 33, 45);
    circle(255, 255, 255, 0.5, -44, 35);
    circle(255, 255, 255, 0.5, 45, 25);
    circle(255, 255, 255, 0.5, -49, 36);
    circle(255, 255, 255, 0.5, 47, 18);
    circle(255, 255, 255, 0.5, -36, 28);
    circle(255, 255, 255, 0.5, 33, 33);
    circle(255, 255, 255, 0.5, 10, 45);
    circle(255, 255, 255, 0.5, -10, 45);
    circle(255, 255, 255, 0.5, 13, 45);
    circle(255, 255, 255, 0.5, -14, 35);
    circle(255, 255, 255, 0.5, 5, 25);
    circle(255, 255, 255, 0.5, -4, 36);
    circle(255, 255, 255, 0.5, 2, 18);
    circle(255, 255, 255, 0.5, 0, 28);
    circle(255, 255, 255, 0.5, -7, 33);
    circle(255, 255, 255, 0.5, -14, 36);
    circle(255, 255, 255, 0.5, 10, 18);
    circle(255, 255, 255, 0.5, -3, 28);
    circle(255, 255, 255, 0.5, 18, 33);
    circle(255, 255, 255, 0.5, 17, 45);
    circle(255, 255, 255, 0.5, -19, 45);
    circle(255, 255, 255, 0.5, -21, 45);
    circle(255, 255, 255, 0.5, -15, 35);
    circle(255, 255, 255, 0.5, 28, 25);
    circle(255, 255, 255, 0.5, -24, 36);
    circle(255, 255, 255, 0.5, 26, 18);
    circle(255, 255, 255, 0.5, -9, 28);
    circle(255, 255, 255, 0.5, -7, 33);
    circle(255, 255, 255, 0.5, -44, 25);
    circle(255, 255, 255, 0.5, -34, 36);
    circle(255, 255, 255, 0.5, -36, 18);
    circle(255, 255, 255, 0.5, -29, 28);
    circle(255, 255, 255, 0.5, -37, 33);
    circle(255, 255, 255, 0.5, 26, 18);
    circle(255, 255, 255, 0.5, -15, 15);
    circle(255, 255, 255, 0.5, -13, 10);
    circle(255, 255, 255, 0.5, -20, 20);
    circle(255, 255, 255, 0.5, -24, 16);
    circle(255, 255, 255, 0.5, -18, 28);
    circle(255, 255, 255, 0.5, -29, 28);
    circle(255, 255, 255, 0.5, -17, 23);

    }
}
void cloud1()//g10
{
    circle(255, 255, 255, 4, -34, 33);
    circle(255, 255, 255, 5, -30, 35);
    circle(255, 255, 255, 4, -26, 33);
    //circle(255, 255, 255, 4, -38, 33);

    glColor3ub(255, 255, 255);

    glBegin(GL_QUADS);

    glVertex2f(-38, 29);
    glVertex2f(-22, 29);
    glVertex2f(-22, 33);
    glVertex2f(-38, 33);

    glEnd();
}

void cloud2()//g11
{
    circle(255, 255, 255, 3, -11, 28);
    circle(255, 255, 255, 4, -8, 30);
    circle(255, 255, 255, 3, -5, 28);
    circle(255, 255, 255, 3, -14, 28);

    glColor3ub(255, 255, 255);

    glBegin(GL_QUADS);

    glVertex2f(-14, 25);
    glVertex2f(-2, 25);
    glVertex2f(-2, 28);
    glVertex2f(-14, 28);

    glEnd();
}

void cloud3()//g12
{
    circle(255, 255, 255, 3, -27, 23);
    circle(255, 255, 255, 3, -25, 25);
    circle(255, 255, 255, 3, -22, 23);
    circle(255, 255, 255, 3, -29, 23);

    glColor3ub(255, 255, 255);

    glBegin(GL_QUADS);

    glVertex2f(-29, 20);
    glVertex2f(-20, 20);
    glVertex2f(-20, 23);
    glVertex2f(-29, 23);

    glEnd();
}

void cloud4()//g13
{
    //circle(255, 255, 255, 3, 19, 38);
    circle(255, 255, 255, 4, 22, 40);
    circle(255, 255, 255, 3, 25, 38);
    circle(255, 255, 255, 3, 16, 38);

    glColor3ub(255, 255, 255);

    glBegin(GL_QUADS);

    glVertex2f(16, 35);
    glVertex2f(28, 35);
    glVertex2f(28, 38);
    glVertex2f(16, 38);

    glEnd();
}

void cloud5()//g14
{
    circle(255, 255, 255, 3, 40, 33);
    circle(255, 255, 255, 4, 42, 35);
    circle(255, 255, 255, 3, 45, 33);
    //circle(255, 255, 255, 3, 37, 33);

    glColor3ub(255, 255, 255);

    glBegin(GL_QUADS);

    glVertex2f(37, 30);
    glVertex2f(48, 30);
    glVertex2f(48, 33);
    glVertex2f(37, 33);

    glEnd();
}

void clouds()//g15
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    //glTranslatef(_moveCloud, 0.0f, 0.0f);
    cloud1();
    cloud2();
    cloud3();
    cloud4();
    cloud5();
    glPopMatrix();

}



void mountain1()//g16
{


    if(nightMode && upMoon >= 20)
        glColor3ub(16, 48, 32);
    else
        glColor3ub(90, 80, 150);
    glBegin(GL_TRIANGLES);
    glVertex2f(-17, 0);
    glVertex2f(-10, 13);
    glVertex2f(-3, 0);
    glEnd();
}

void mountain2()//g17
{

    if(nightMode && upMoon >= 20)
        glColor3ub(16, 48, 32);
    else
        glColor3ub(80, 75, 145);

    glBegin(GL_TRIANGLES);
    glVertex2f(-8, 0);
    glVertex2f(0, 10);
    glVertex2f(9, 0);
    glEnd();
}

void mountain3()//g18
{

    if(nightMode && upMoon >= 20)
        glColor3ub(16, 48, 32);
    else
        glColor3ub(85, 80, 150);
    glBegin(GL_TRIANGLES);
    glVertex2f(8, 0);
    glVertex2f(18, 9);
    glVertex2f(28, 0);
    glEnd();
}

void snowMountain1()//g19
{

    if(nightMode && upMoon >= 20)
        glColor3ub(36, 38, 36);
    else
        glColor3ub(90, 80, 150);
    glBegin(GL_TRIANGLES);
    glVertex2f(-17, 0);
    glVertex2f(-10, 13);
    glVertex2f(-3, 0);
    glEnd();

    if(nightMode && upMoon >= 20)
        glColor3ub(193, 201, 193);
    else
        glColor3ub(245,245,245);

    glBegin(GL_TRIANGLES);
    glVertex2f(-12, 9);
    glVertex2f(-10, 13);
    glVertex2f(-8, 9);
    glEnd();
}

void snowMountain2()//g20
{


    if(nightMode && upMoon >= 20)
        glColor3ub(36, 38, 36);
    else
        glColor3ub(80, 75, 145);
    glBegin(GL_TRIANGLES);
    glVertex2f(-8, 0);
    glVertex2f(0, 10);
    glVertex2f(9, 0);
    glEnd();

    if(nightMode && upMoon >= 20)
        glColor3ub(193, 201, 193);
    else
        glColor3ub(245,245,245);
    glBegin(GL_TRIANGLES);
    glVertex2f(-3, 6);
    glVertex2f(0, 10);
    glVertex2f(3, 6);
    glEnd();
}

void snowMountain3()//g21
{
    if(nightMode && upMoon >= 20)
        glColor3ub(36, 38, 36);
    else
        glColor3ub(90, 80, 150);

    glBegin(GL_TRIANGLES);
    glVertex2f(8, 0);
    glVertex2f(18, 9);
    glVertex2f(28, 0);
    glEnd();


     if(nightMode && upMoon >= 20)
        glColor3ub(193, 201, 193);
    else
        glColor3ub(245,245,245);

    glBegin(GL_TRIANGLES);
    //glColor3ub(245,245,245);
    glVertex2f(16, 6);
    glVertex2f(18, 9);
    glVertex2f(21, 6);
    glEnd();
}

void gMountain1()//g22
{


    if(nightMode && upMoon >= 20)
        glColor3ub(16, 48, 32);
    else
        glColor3ub(20, 110, 50);
    glBegin(GL_TRIANGLES);
    glVertex2f(-50, 0);
    glVertex2f(-50, 20);
    glVertex2f(-30, 0);
    glEnd();
}

void gMountain2()//g23
{


    if(nightMode && upMoon >= 20)
        glColor3ub(16, 48, 32);
    else
        glColor3ub(10, 75, 35);
    glBegin(GL_TRIANGLES);
    glVertex2f(-45, 0);
    glVertex2f(-40, 15);
    glVertex2f(-30, 0);
    glEnd();
}

void gMountain3()//g24
{


    if(nightMode && upMoon >= 20)
        glColor3ub(16, 48, 32);
    else
        glColor3ub(25, 115, 50);
    glBegin(GL_TRIANGLES);
    glVertex2f(-40, 0);
    glVertex2f(-32, 15);
    glVertex2f(-22, 0);
    glEnd();
}

void gMountain4()//g25
{


    if(nightMode && upMoon >= 20)
        glColor3ub(16, 48, 32);
    else
        glColor3ub(10, 75, 35);
    glBegin(GL_TRIANGLES);
    glVertex2f(-35, 0);
    glVertex2f(-25, 12);
    glVertex2f(-15, 0);
    glEnd();
}

void gMountain5()//g26
{

    if(nightMode && upMoon >= 20)
        glColor3ub(16, 48, 32);
    else
        glColor3ub(20, 110, 50);
    glBegin(GL_TRIANGLES);
    glVertex2f(22, 0);
    glVertex2f(32, 13);
    glVertex2f(42, 0);
    glEnd();
}

void gMountain6()//g27
{


    if(nightMode && upMoon >= 20)
        glColor3ub(16, 48, 32);
    else
        glColor3ub(10, 75, 35);
    glBegin(GL_QUADS);
    glVertex2f(28, 0);
    glVertex2f(40, 15);
    glVertex2f(50, 17);
    glVertex2f(50, 0);
    glEnd();
}

void gMountain7()//g28
{


    if(nightMode && upMoon >= 20)
        glColor3ub(16, 48, 32);
    else
        glColor3ub(20, 110, 50);
    glBegin(GL_TRIANGLES);
    glVertex2f(38, 0);
    glVertex2f(48, 16);
    glVertex2f(50, 14);
    glEnd();
}
void waterFall(){//g29
    glBegin(GL_TRIANGLES);
    if(nightMode && upMoon>=20)
       glColor3ub(5, 100, 110);
    else
       glColor3ub(55, 200, 240);
    glVertex2f(-38, 0);
    glVertex2f(-35, 0);
    glVertex2f(-27.8, 8.7);
    glEnd();
}
void river(){//g30

    if(nightMode && upMoon>=20)
       glColor3ub(5, 100, 110);
    else
       glColor3ub(55, 200, 240);
    glBegin(GL_POLYGON);
    glVertex2f(-50, 0);
    glVertex2f(50, 0);
    glVertex2f(50, -14);
    glVertex2f(-50, -14);

    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(35, -14);
    glVertex2f(50, -14);
    glVertex2f(50, -32);


    glEnd();


}

void boat(){//g31
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glBegin(GL_QUADS);
    glColor3ub(156, 102, 25);
    glVertex2f(-34,-6);
    glVertex2f(-30, -10);
    glVertex2f(-16, -10);
    glVertex2f(-12, -6);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(94, 72, 35);
    glVertex2f(-34,-6);
    glVertex2f(-12, -6);
    glVertex2f(-24, -8);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(156, 102, 25);
    glVertex2f(-24,-3);
    glVertex2f(-19, -3);
    glVertex2f(-19, -7);
    glVertex2f(-24, -8);

    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(43, 25, 2);
    glVertex2f(-26,-3);
    glVertex2f(-24, -3);
    glVertex2f(-24, -6);
    glVertex2f(-26, -6);

    glEnd();
    glPopMatrix();
}
void boat2(){//g32
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glBegin(GL_QUADS);
    glColor3ub(156, 102, 25);
    glVertex2f(-5,-1);
    glVertex2f(1, -1);
    glVertex2f(0, -2);
    glVertex2f(-4, -2);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(94, 72, 35);
    glVertex2f(-5,-1);
    glVertex2f(1, -1);
    glVertex2f(-2, -1.5);
    glEnd();
    glPopMatrix();

}

void standBoat(){//g33
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glBegin(GL_QUADS);
    glColor3ub(156, 102, 25);
    glVertex2f(-4,-12);
    glVertex2f(4, -12);
    glVertex2f(6, -10);
    glVertex2f(-6, -10);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(94, 72, 35);
    glVertex2f(6,-10);
    glVertex2f(-6, -10);
    glVertex2f(0, -11);
    glEnd();
    glPopMatrix();

}
void boatGhat(){//g34
    glBegin(GL_QUADS);
    glColor3ub(156, 102, 25);
    glVertex2f(-5.5,-14);
    glVertex2f(-5.5, -12.5+3);
    glVertex2f(-6, -12.5+3);
    glVertex2f(-6, -14);

    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(156, 102, 25);
    glVertex2f(-0.5,-12.5+3);
    glVertex2f(0, -12.5+3);
    glVertex2f(0, -14);
    glVertex2f(-0.5, -14);

    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(156, 102, 25);
    glVertex2f(-5.5,-13);
    glVertex2f(0, -13);
    glVertex2f(0, -14);
    glVertex2f(-6, -14);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(94, 72, 35);
    glVertex2f(0,-12.5);
    glVertex2f(0, -13);
    glVertex2f(6, -10);
    glEnd();
    glPopMatrix();
}

void boat3(){//g35
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glBegin(GL_QUADS);
    glColor3ub(240, 191, 117);
    glVertex2f(32,-8+3);
    glVertex2f(36, -4+3);
    glVertex2f(18, -4+3);
    glVertex2f(22, -8+3);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(94, 72, 35);
    glVertex2f(18,-4+3);
    glVertex2f(36, -4+3);
    glVertex2f(27, -6+3);
    glEnd();
    glPopMatrix();

}
void smallBoat(){//g36
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    boat2();
    boat3();
    glPopMatrix();
}
void ground()//g37
{
    if(nightMode && upMoon>=20)
       glColor3ub(7, 61, 27);
    else
       glColor3ub(80, 150, 70);

    glBegin(GL_QUADS);

    glVertex2f(-50, -50);
    glVertex2f(50, -50);
    glVertex2f(50, 0);
    glVertex2f(-50, 0);

    glEnd();
}
void windowLight()//g38
{
    if(nightMode && upMoon >= 20.0f)
        glColor3ub(255, 220, 80);
    else
        glColor3ub(189, 242, 240);
}
void building1()//g39
{

    glBegin(GL_QUADS);
    glColor3ub(190, 150, 110);
    glVertex2f(-47,-6);
    glVertex2f(-38,-6);
    glVertex2f(-38,-30);
    glVertex2f(-47,-30);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3ub(140, 50, 40);
    glVertex2f(-48,-6);
    glVertex2f(-37,-6);
    glVertex2f(-42.5,-1);
    glEnd();

    //left window
    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(-45.5,-11);
    glVertex2f(-43,-11);
    glVertex2f(-43,-8);
    glVertex2f(-45.5,-8);
    glEnd();


    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(-41.5,-11);
    glVertex2f(-39,-11);
    glVertex2f(-39,-8);
    glVertex2f(-41.5,-8);
    glEnd();

    //left window
    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(-45.5,-17);
    glVertex2f(-43,-17);
    glVertex2f(-43,-14);
    glVertex2f(-45.5,-14);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(-41.5,-17);
    glVertex2f(-39,-17);
    glVertex2f(-39,-14);
    glVertex2f(-41.5,-14);
    glEnd();

    //door
    glBegin(GL_QUADS);
    glColor3ub(90,55,30);
    glVertex2f(-44,-30);
    glVertex2f(-41,-30);
    glVertex2f(-41,-23);
    glVertex2f(-44,-23);
    glEnd();
}


void building2()//g40
{

    glBegin(GL_QUADS);
    glColor3ub(170, 180, 190);
    glVertex2f(-35,-10);
    glVertex2f(-27,-10);
    glVertex2f(-27,-30);
    glVertex2f(-35,-30);
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(80,80,90);
    glVertex2f(-36,-10);
    glVertex2f(-26,-10);
    glVertex2f(-27,-7);
    glVertex2f(-35,-7);
    glEnd();

    //windows
    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(-33.5,-14);
    glVertex2f(-31.5,-14);
    glVertex2f(-31.5,-12);
    glVertex2f(-33.5,-12);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(-30.5,-14);
    glVertex2f(-28.5,-14);
    glVertex2f(-28.5,-12);
    glVertex2f(-30.5,-12);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(-33.5,-19);
    glVertex2f(-31.5,-19);
    glVertex2f(-31.5,-17);
    glVertex2f(-33.5,-17);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(-30.5,-19);
    glVertex2f(-28.5,-19);
    glVertex2f(-28.5,-17);
    glVertex2f(-30.5,-17);
    glEnd();

    //door
    glBegin(GL_QUADS);
    glColor3ub(80,55,40);
    glVertex2f(-33,-30);
    glVertex2f(-30,-30);
    glVertex2f(-30,-24);
    glVertex2f(-33,-24);
    glEnd();
}


void building3()//g41
{

    glBegin(GL_QUADS);
    glColor3ub(200, 120, 90);
    glVertex2f(-24,-7);
    glVertex2f(-14,-7);
    glVertex2f(-14,-30);
    glVertex2f(-24,-30);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3ub(100,50,40);
    glVertex2f(-25,-7);
    glVertex2f(-13,-7);
    glVertex2f(-19,-2);
    glEnd();

    //windows
    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(-22,-12);
    glVertex2f(-19.5,-12);
    glVertex2f(-19.5,-9);
    glVertex2f(-22,-9);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(-18.5,-12);
    glVertex2f(-16,-12);
    glVertex2f(-16,-9);
    glVertex2f(-18.5,-9);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(-22,-18);
    glVertex2f(-19.5,-18);
    glVertex2f(-19.5,-15);
    glVertex2f(-22,-15);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(-18.5,-18);
    glVertex2f(-16,-18);
    glVertex2f(-16,-15);
    glVertex2f(-18.5,-15);
    glEnd();

    //door
    glBegin(GL_QUADS);
    glColor3ub(85,50,30);
    glVertex2f(-20.5,-30);
    glVertex2f(-17.5,-30);
    glVertex2f(-17.5,-22);
    glVertex2f(-20.5,-22);
    glEnd();
}



void building4()//g42
{

    glBegin(GL_QUADS);
    glColor3ub(220, 170, 100);
    glVertex2f(5+5,-9);
    glVertex2f(15+5,-9);
    glVertex2f(15+5,-30);
    glVertex2f(5+5,-30);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3ub(155,55,40);
    glVertex2f(4+5,-9);
    glVertex2f(16+5,-9);
    glVertex2f(10+5,-3);
    glEnd();

    //windows
    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(7+5,-14);
    glVertex2f(9.5+5,-14);
    glVertex2f(9.5+5,-11);
    glVertex2f(7+5,-11);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(10.5+5,-14);
    glVertex2f(13+5,-14);
    glVertex2f(13+5,-11);
    glVertex2f(10.5+5,-11);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(7+5,-20);
    glVertex2f(9.5+5,-20);
    glVertex2f(9.5+5,-17);
    glVertex2f(7+5,-17);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(10.5+5,-20);
    glVertex2f(13+5,-20);
    glVertex2f(13+5,-17);
    glVertex2f(10.5+5,-17);
    glEnd();

    //door
    glBegin(GL_QUADS);
    glColor3ub(85,50,30);
    glVertex2f(8.5+5,-30);
    glVertex2f(11.5+5,-30);
    glVertex2f(11.5+5,-23);
    glVertex2f(8.5+5,-23);
    glEnd();
}


void building5()//g43
{

    glBegin(GL_QUADS);
    glColor3ub(165, 165, 180);
    glVertex2f(20+5,-5);
    glVertex2f(31+5,-5);
    glVertex2f(31+5,-30);
    glVertex2f(20+5,-30);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(70,70,80);
    glVertex2f(19+5,-5);
    glVertex2f(32+5,-5);
    glVertex2f(31+5,-2);
    glVertex2f(20+5,-2);
    glEnd();

    //windows
    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(22+5,-10);
    glVertex2f(24.5+5,-10);
    glVertex2f(24.5+5,-7);
    glVertex2f(22+5,-7);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(26.5+5,-10);
    glVertex2f(29+5,-10);
    glVertex2f(29+5,-7);
    glVertex2f(26.5+5,-7);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(22+5,-16);
    glVertex2f(24.5+5,-16);
    glVertex2f(24.5+5,-13);
    glVertex2f(22+5,-13);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(26.5+5,-16);
    glVertex2f(29+5,-16);
    glVertex2f(29+5,-13);
    glVertex2f(26.5+5,-13);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(22+5,-22);
    glVertex2f(24.5+5,-22);
    glVertex2f(24.5+5,-19);
    glVertex2f(22+5,-19);
    glEnd();

    glBegin(GL_QUADS);
    windowLight();
    glVertex2f(26.5+5,-22);
    glVertex2f(29+5,-22);
    glVertex2f(29+5,-19);
    glVertex2f(26.5+5,-19);
    glEnd();

    //door
    glBegin(GL_QUADS);
    glColor3ub(80,55,40);
    glVertex2f(24+5,-30);
    glVertex2f(27+5,-30);
    glVertex2f(27+5,-24);
    glVertex2f(24+5,-24);
    glEnd();
}


void road()//g44
{
    glColor3ub(43, 43, 43);

    glBegin(GL_QUADS);

    glVertex2f(-50, -32);
    glVertex2f(50, -32);
    glVertex2f(50, -50);
    glVertex2f(-50, -50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(97, 53, 5);
    glVertex2f(-50, -42);
    glVertex2f(50, -42);
    glVertex2f(50, -38.5);
    glVertex2f(-50, -38.5);

    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255,255,255);
    glPointSize(5);
    glVertex2f(-50,-35);
    glVertex2f(50,-35);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(255,255,255);
    glPointSize(5);
    glVertex2f(-50,-46);
    glVertex2f(50,-46);
    glEnd();
}

void wheel1(float xc,float yc,float radius)//g45
{
    float x=radius/2;
    glPointSize(4);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(xc,yc,0);
	glRotatef(angle, 0.0f, 0.0f,1.0f);
	glTranslatef(-xc,-yc,0);
	circle(0,0,0,radius,xc,yc);
	circle(255,255,255,x,xc,yc);
	glPopMatrix();
}

void wheel2(float xc,float yc,float radius)//g46
{
    float x=radius/2;
    glPointSize(4);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(xc,yc,0);
	glRotatef(angle, 0.0f, 0.0f,1.0f);
	glTranslatef(-xc,-yc,0);
	circle(0,0,0,radius,xc,yc);
	circle(255,255,255,x,xc,yc);
	glPopMatrix();
}

void privateCar(){//g47

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3ub(235, 41, 2);
    glVertex2f(49, -45);
    glVertex2f(38, -45);
    glVertex2f(38, -47);
    glVertex2f(49, -47);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(235, 41, 2);
    glVertex2f(39, -45);
    glVertex2f(48, -45);
    glVertex2f(46, -43);
    glVertex2f(41, -43);
    glEnd();
    //window
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(40, -44.5);
    glVertex2f(41, -43.5);
    glVertex2f(43, -43.5);
    glVertex2f(43, -44.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(44, -43.5);
    glVertex2f(45.5, -43.5);
    glVertex2f(46.5, -44.5);
    glVertex2f(44, -44.5);
    glEnd();

    //headlight
    glBegin(GL_QUADS);
    glColor3ub(230, 255, 166);
    glVertex2f(38, -45.5);
    glVertex2f(38, -46);
    glVertex2f(38.5, -46);
    glVertex2f(38.5, -45.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(156, 0, 35);
    glVertex2f(48.5, -45.5);
    glVertex2f(48.5, -46);
    glVertex2f(49, -46);
    glVertex2f(49, -45.5);
    glEnd();


    wheel1(40,-47,1);
    wheel2(47,-47,1);

    //light on/of
    if(nightMode && upMoon>=20){
        glBegin(GL_TRIANGLES);
        glColor3ub(248, 255, 117);
        glVertex2f(31, -45);
        glVertex2f(31, -47);
        glVertex2f(38, -45.5);
        glEnd();
    }
    glPopMatrix();
}
void privateCar2(){//g48

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3ub(51, 32, 232);
    glVertex2f(49-20, -45);
    glVertex2f(38-20, -45);
    glVertex2f(38-20, -47);
    glVertex2f(49-20, -47);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(51, 32, 232);
    glVertex2f(39-20, -45);
    glVertex2f(48-20, -45);
    glVertex2f(46-20, -43);
    glVertex2f(41-20, -43);
    glEnd();
    //window
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(40-20, -44.5);
    glVertex2f(41-20, -43.5);
    glVertex2f(43-20, -43.5);
    glVertex2f(43-20, -44.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(44-20, -43.5);
    glVertex2f(45.5-20, -43.5);
    glVertex2f(46.5-20, -44.5);
    glVertex2f(44-20, -44.5);
    glEnd();

    //headlight
    glBegin(GL_QUADS);
    glColor3ub(230, 255, 166);
    glVertex2f(38-20, -45.5);
    glVertex2f(38-20, -46);
    glVertex2f(38.5-20, -46);
    glVertex2f(38.5-20, -45.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(156, 0, 35);
    glVertex2f(48.5-20, -45.5);
    glVertex2f(48.5-20, -46);
    glVertex2f(49-20, -46);
    glVertex2f(49-20, -45.5);
    glEnd();

    wheel1(40-20,-47,1);
    wheel2(47-20,-47,1);
    //light on/of
    if(nightMode && upMoon>=20){
        glBegin(GL_TRIANGLES);
        glColor3ub(248, 255, 117);
        glVertex2f(31-20, -45);
        glVertex2f(31-20, -47);
        glVertex2f(38-20, -45.5);
        glEnd();
    }
    glPopMatrix();
}

void privateCar3(){//g49

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3ub(200, 76, 245);
    glVertex2f(49-50, -45);
    glVertex2f(38-50, -45);
    glVertex2f(38-50, -47);
    glVertex2f(49-50, -47);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(200, 76, 245);
    glVertex2f(39-50, -45);
    glVertex2f(48-50, -45);
    glVertex2f(46-50, -43);
    glVertex2f(41-50, -43);
    glEnd();
    //window
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(40-50, -44.5);
    glVertex2f(41-50, -43.5);
    glVertex2f(43-50, -43.5);
    glVertex2f(43-50, -44.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(44-50, -43.5);
    glVertex2f(45.5-50, -43.5);
    glVertex2f(46.5-50, -44.5);
    glVertex2f(44-50, -44.5);
    glEnd();

    //headlight
    glBegin(GL_QUADS);
    glColor3ub(230, 255, 166);
    glVertex2f(38-50, -45.5);
    glVertex2f(38-50, -46);
    glVertex2f(38.5-50, -46);
    glVertex2f(38.5-50, -45.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(156, 0, 35);
    glVertex2f(48.5-50, -45.5);
    glVertex2f(48.5-50, -46);
    glVertex2f(49-50, -46);
    glVertex2f(49-50, -45.5);
    glEnd();

    wheel1(40-50,-47,1);
    wheel2(47-50,-47,1);
    if(nightMode && upMoon>=20){
        glBegin(GL_TRIANGLES);
        glColor3ub(248, 255, 117);
        glVertex2f(31-50, -45);
        glVertex2f(31-50, -47);
        glVertex2f(38-50, -45.5);
        glEnd();
    }
    glPopMatrix();
}
void privateCar4(){//g50

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3ub(173, 171, 49);
    glVertex2f(49+20, -45);
    glVertex2f(38+20, -45);
    glVertex2f(38+20, -47);
    glVertex2f(49+20, -47);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(173, 171, 49);
    glVertex2f(39+20, -45);
    glVertex2f(48+20, -45);
    glVertex2f(46+20, -43);
    glVertex2f(41+20, -43);
    glEnd();
    //window
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(40+20, -44.5);
    glVertex2f(41+20, -43.5);
    glVertex2f(43+20, -43.5);
    glVertex2f(43+20, -44.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(44+20, -43.5);
    glVertex2f(45.5+20, -43.5);
    glVertex2f(46.5+20, -44.5);
    glVertex2f(44+20, -44.5);
    glEnd();

    //headlight
    glBegin(GL_QUADS);
    glColor3ub(230, 255, 166);
    glVertex2f(38+20, -45.5);
    glVertex2f(38+20, -46);
    glVertex2f(38.5+20, -46);
    glVertex2f(38.5+20, -45.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(156, 0, 35);
    glVertex2f(48.5+20, -45.5);
    glVertex2f(48.5+20, -46);
    glVertex2f(49+20, -46);
    glVertex2f(49+20, -45.5);
    glEnd();

    wheel1(40+20,-47,1);
    wheel2(47+20,-47,1);
    if(nightMode && upMoon>=20){
        glBegin(GL_TRIANGLES);
        glColor3ub(248, 255, 117);
        glVertex2f(31+20, -45);
        glVertex2f(31+20, -47);
        glVertex2f(38+20, -45.5);
        glEnd();
    }
    glPopMatrix();
}
//right len
void miniBus(){//g51

    glBegin(GL_QUADS);
    glColor3ub(156, 0, 35);
    glVertex2f(-46, -34);
    glVertex2f(-46, -37);
    glVertex2f(-40,-37);
    glVertex2f(-40,-34);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(156, 0, 35);
    glVertex2f(-40, -34);
    glVertex2f(-38.7,-36);
    glVertex2f(-38.7,-37);

    glVertex2f(-40,-37);
    glEnd();

    ///window
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(-39, -36);
    glVertex2f(-40.5, -36);
    glVertex2f(-41,-34.5);
    glVertex2f(-40,-34.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(-41.5, -34.5);
    glVertex2f(-41.5, -36);
    glVertex2f(-42.5,-36);
    glVertex2f(-42.5,-34.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(-45.5, -36);
    glVertex2f(-45.5, -34.5);
    glVertex2f(-44.5,-34.5);
    glVertex2f(-44.5,-36);
    glEnd();

    ///door

    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(-43, -37+1);
    glVertex2f(-44, -37+1);
    glVertex2f(-44,-35+0.5);
    glVertex2f(-43,-35+0.5);
    glEnd();

    wheel1(-45,-37,0.6);
    wheel2(-40.5,-37,0.6);
    if(nightMode && upMoon>=20){
        glBegin(GL_TRIANGLES);
        glColor3ub(248, 255, 117);
        glVertex2f(-38.5, -36.5);
        glVertex2f(-34, -36);
        glVertex2f(-34, -37.5);
        glEnd();
    }


}
void privateCarRight(){//g52

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3ub(6, 122, 156);
    glVertex2f(49, -45+10);
    glVertex2f(38, -45+10);
    glVertex2f(38, -47+10);
    glVertex2f(49, -47+10);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(6, 122, 156);
    glVertex2f(39, -45+10);
    glVertex2f(48, -45+10);
    glVertex2f(46, -43+10);
    glVertex2f(41, -43+10);
    glEnd();
    //window
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(40, -44.5+10);
    glVertex2f(41, -43.5+10);
    glVertex2f(43, -43.5+10);
    glVertex2f(43, -44.5+10);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(44, -43.5+10);
    glVertex2f(45.5, -43.5+10);
    glVertex2f(46.5, -44.5+10);
    glVertex2f(44, -44.5+10);
    glEnd();

    //headlight
    glBegin(GL_QUADS);
    glColor3ub(156, 0, 35);
    glVertex2f(38, -45.5+10);
    glVertex2f(38, -46+10);
    glVertex2f(38.5, -46+10);
    glVertex2f(38.5, -45.5+10);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(230, 255, 166);
    glVertex2f(48.5, -45.5+10);
    glVertex2f(48.5, -46+10);
    glVertex2f(49, -46+10);
    glVertex2f(49, -45.5+10);
    glEnd();

    wheel1(40,-47+10,1);
    wheel2(47,-47+10,1);
    if(nightMode && upMoon>=20){
        glBegin(GL_TRIANGLES);
        glColor3ub(248, 255, 117);
        glVertex2f(56, -45+10);
        glVertex2f(56, -47+10);
        glVertex2f(49, -45.5+10);
        glEnd();
    }
    glPopMatrix();
}

void privateCarRight1(){//g53

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3ub(5, 105, 81);
    glVertex2f(49-30, -45+10);
    glVertex2f(38-30, -45+10);
    glVertex2f(38-30, -47+10);
    glVertex2f(49-30, -47+10);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(5, 105, 81);
    glVertex2f(39-30, -45+10);
    glVertex2f(48-30, -45+10);
    glVertex2f(46-30, -43+10);
    glVertex2f(41-30,-43+10);
    glEnd();
    //window
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(40-30, -44.5+10);
    glVertex2f(41-30, -43.5+10);
    glVertex2f(43-30, -43.5+10);
    glVertex2f(43-30, -44.5+10);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(44-30, -43.5+10);
    glVertex2f(45.5-30, -43.5+10);
    glVertex2f(46.5-30, -44.5+10);
    glVertex2f(44-30, -44.5+10);
    glEnd();

    //headlight
    glBegin(GL_QUADS);
    glColor3ub(156, 0, 35);
    glVertex2f(38-30, -45.5+10);
    glVertex2f(38-30, -46+10);
    glVertex2f(38.5-30, -46+10);
    glVertex2f(38.5-30, -45.5+10);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(230, 255, 166);
    glVertex2f(48.5-30, -45.5+10);
    glVertex2f(48.5-30, -46+10);
    glVertex2f(49-30,-46+10);
    glVertex2f(49-30,-45.5+10);
    glEnd();

    wheel1(40-30,-47+10,1);
    wheel2(47-30,-47+10,1);

    if(nightMode && upMoon>=20){
        glBegin(GL_TRIANGLES);
        glColor3ub(248, 255, 117);
        glVertex2f(56-30, -45+10);
        glVertex2f(56-30, -47+10);
        glVertex2f(49-30, -45.5+10);
        glEnd();
    }
    glPopMatrix();
}


void sideRoad(){//g54
    glColor3ub(43, 43, 43);

    glBegin(GL_QUADS);

    glVertex2f(-6,-14);
    glVertex2f(0, -14);
    glVertex2f(0,-32);
    glVertex2f(-6,-32);
    glEnd();

}

void standCar(){//g55

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3ub(97, 81, 237);
    glVertex2f(-4, -28+3);
    glVertex2f(-2, -28+3);
    glVertex2f(-2, -30+3);
    glVertex2f(-4, -30+3);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(97, 81, 237);
    glVertex2f(-2, -28+3);
    glVertex2f(-2, -30+3);
    glVertex2f(-1, -31+3);
    glVertex2f(-1, -27+3);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(97, 81, 237);
    glVertex2f(-1, -27+3);
    glVertex2f(-3, -27+3);
    glVertex2f(-3, -26+4);
    glVertex2f(-1, -26+4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(97, 81, 237);
    glVertex2f(-3, -31+3);
    glVertex2f(-1, -31+3);
    glVertex2f(-1, -32-1+2);
    glVertex2f(-3, -32-1+2);
    glEnd();

    //glass
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(-4, -28+3);
    glVertex2f(-2,-28+3);
    glVertex2f(-1,-27+3);
    glVertex2f(-3, -27+3);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(-4, -30+3);
    glVertex2f(-2, -30+3);
    glVertex2f(-1, -31+3);
    glVertex2f(-3,-31+3);
    glEnd();
    //window
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(-1.2, -28.5+3);
    glVertex2f(-1.8,-28.5+3);
    glVertex2f(-1.8,-28+3);
    glVertex2f(-1.2, -27.7+3);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(189, 242, 240);
    glVertex2f(-1.8, -29+3);
    glVertex2f(-1.3, -29+3);
    glVertex2f(-1.3, -30.25+3);
    glVertex2f(-1.8,-29.7+3);
    glEnd();


    wheel1(-1,-31+3,0.27);
    wheel2(-1,-27+3,0.27);
    glPopMatrix();
}

void treeSqureNight()//g56
{
    if(nightMode && upMoon >= 20)
        glColor3ub(70, 45, 30);
    else
        glColor3ub(171, 118, 77);
}

void treeLeafNight()//g57
{
    if(nightMode && upMoon >= 20)
        glColor3ub(7, 61, 27);
    else
        glColor3ub(22, 184, 29);
}
void treeR1(){//g58
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(-8,-29);
    glVertex2f(-8, -26);
    glVertex2f(-7,-26);
    glVertex2f(-7,-29);
    glEnd();

    treeLeafNight();
    glBegin(GL_TRIANGLES);
    glVertex2f(-10,-26);
    glVertex2f(-5, -26);
    glVertex2f(-7.5,-24);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-9.5,-25);
    glVertex2f(-5.5, -25);
    glVertex2f(-7.5,-23);
    glEnd();
}
void treeR2(){//g59
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(-8,-29+7);
    glVertex2f(-8, -26+7);
    glVertex2f(-7,-26+7);
    glVertex2f(-7,-29+7);
    glEnd();

    treeLeafNight();
    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(-10,-26+7);
    glVertex2f(-5, -26+7);
    glVertex2f(-7.5,-24+7);
    glEnd();

    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(-9.5,-25+7);
    glVertex2f(-5.5, -25+7);
    glVertex2f(-7.5,-23+7);
    glEnd();
}
void treeR3(){//g60
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(-8+9,-29+7);
    glVertex2f(-8+9, -26+7);
    glVertex2f(-7+9,-26+7);
    glVertex2f(-7+9,-29+7);
    glEnd();

    treeLeafNight();
    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(-10+9,-26+7);
    glVertex2f(-5+9, -26+7);
    glVertex2f(-7.5+9,-24+7);
    glEnd();

    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(-9.5+9,-25+7);
    glVertex2f(-5.5+9, -25+7);
    glVertex2f(-7.5+9,-23+7);
    glEnd();
}
void treeR4(){//g61
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(-8+9,-29);
    glVertex2f(-8+9, -26);
    glVertex2f(-7+9,-26);
    glVertex2f(-7+9,-29);
    glEnd();

    treeLeafNight();
    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(-10+9,-26);
    glVertex2f(-5+9, -26);
    glVertex2f(-7.5+9,-24);
    glEnd();

    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(-9.5+9,-25);
    glVertex2f(-5.5+9, -25);
    glVertex2f(-7.5+9,-23);
    glEnd();
}

void treeMR1(){//g62
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(-12,-28);
    glVertex2f(-11, -28);
    glVertex2f(-11,-31);
    glVertex2f(-12,-31);
    glEnd();

    treeLeafNight();
    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(-9,-28);
    glVertex2f(-11.5, -26);
    glVertex2f(-14,-28);
    glEnd();

    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(-13.5,-27);
    glVertex2f(-9.5, -27);
    glVertex2f(-11.5,-25);
    glEnd();
}

void treeMR2(){//g63
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(-12-6,-28);
    glVertex2f(-11-6, -28);
    glVertex2f(-11-6,-31);
    glVertex2f(-12-6,-31);
    glEnd();

    glBegin(GL_TRIANGLES);
    treeLeafNight();
    glVertex2f(-9-6,-28);
    glVertex2f(-11.5-6, -26);
    glVertex2f(-14-6,-28);
    glEnd();

    glBegin(GL_TRIANGLES);
    treeLeafNight();
    glVertex2f(-13.5-6,-27);
    glVertex2f(-9.5-6, -27);
    glVertex2f(-11.5-6,-25);
    glEnd();
}
void treeMR3(){//g100
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(-12-12,-28);
    glVertex2f(-11-12, -28);
    glVertex2f(-11-12,-31);
    glVertex2f(-12-12,-31);
    glEnd();

    glBegin(GL_TRIANGLES);
    treeLeafNight();
    glVertex2f(-9-12,-28);
    glVertex2f(-11.5-12, -26);
    glVertex2f(-14-12,-28);
    glEnd();

    glBegin(GL_TRIANGLES);
    treeLeafNight();
    glVertex2f(-13.5-12,-27);
    glVertex2f(-9.5-12, -27);
    glVertex2f(-11.5-12,-25);
    glEnd();
}

void treeMR4(){//g64
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(-12-18,-28);
    glVertex2f(-11-18, -28);
    glVertex2f(-11-18,-31);
    glVertex2f(-12-18,-31);
    glEnd();

    treeLeafNight();
    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(-9-18,-28);
    glVertex2f(-11.5-18, -26);
    glVertex2f(-14-18,-28);
    glEnd();

    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(-13.5-18,-27);
    glVertex2f(-9.5-18, -27);
    glVertex2f(-11.5-18,-25);
    glEnd();
}

void treeMR5(){//g65
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(-12-24,-28);
    glVertex2f(-11-24, -28);
    glVertex2f(-11-24,-31);
    glVertex2f(-12-24,-31);
    glEnd();

    treeLeafNight();
    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(-9-24,-28);
    glVertex2f(-11.5-24, -26);
    glVertex2f(-14-24,-28);
    glEnd();

    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(-13.5-24,-27);
    glVertex2f(-9.5-24, -27);
    glVertex2f(-11.5-24,-25);
    glEnd();
}
void treeMR6(){//g66
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(-12-30,-28);
    glVertex2f(-11-30, -28);
    glVertex2f(-11-30,-31);
    glVertex2f(-12-30,-31);
    glEnd();

    glBegin(GL_TRIANGLES);
    treeLeafNight();
    glVertex2f(-9-30,-28);
    glVertex2f(-11.5-30, -26);
    glVertex2f(-14-30,-28);
    glEnd();

    glBegin(GL_TRIANGLES);
    treeLeafNight();
    glVertex2f(-13.5-30,-27);
    glVertex2f(-9.5-30, -27);
    glVertex2f(-11.5-30,-25);
    glEnd();
}
void treeMR7(){//g67
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(-12-36,-28);
    glVertex2f(-11-36, -28);
    glVertex2f(-11-36,-31);
    glVertex2f(-12-36,-31);
    glEnd();

    glBegin(GL_TRIANGLES);
    treeLeafNight();
    glVertex2f(-9-36,-28);
    glVertex2f(-11.5-36, -26);
    glVertex2f(-14-36,-28);
    glEnd();

    glBegin(GL_TRIANGLES);
    treeLeafNight();
    glVertex2f(-13.5-36,-27);
    glVertex2f(-9.5-36, -27);
    glVertex2f(-11.5-36,-25);
    glEnd();
}
void treeMRL1(){//g68
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(3,-28);
    glVertex2f(4, -28);
    glVertex2f(4,-31);
    glVertex2f(3,-31);
    glEnd();

    treeLeafNight();
    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(6,-28);
    glVertex2f(3.5, -26);
    glVertex2f(1,-28);
    glEnd();

    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(1.5,-27);
    glVertex2f(5.5, -27);
    glVertex2f(3.5,-25);
    glEnd();
}

void treeMRL2(){//g69
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(3+7,-28);
    glVertex2f(4+7, -28);
    glVertex2f(4+7,-31);
    glVertex2f(3+7,-31);
    glEnd();

    treeLeafNight();
    glBegin(GL_TRIANGLES);
   // glColor3ub(22, 184, 29);
    glVertex2f(6+7,-28);
    glVertex2f(3.5+7, -26);
    glVertex2f(1+7,-28);
    glEnd();

    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(1.5+7,-27);
    glVertex2f(5.5+7, -27);
    glVertex2f(3.5+7,-25);
    glEnd();
}

void treeMRL3(){//g70
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(3+14,-28);
    glVertex2f(4+14, -28);
    glVertex2f(4+14,-31);
    glVertex2f(3+14,-31);
    glEnd();

    treeLeafNight();
    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(6+14,-28);
    glVertex2f(3.5+14, -26);
    glVertex2f(1+14,-28);
    glEnd();

    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(1.5+14,-27);
    glVertex2f(5.5+14, -27);
    glVertex2f(3.5+14,-25);
    glEnd();
}

void treeMRL4(){//g71
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(3+21,-28);
    glVertex2f(4+21, -28);
    glVertex2f(4+21,-31);
    glVertex2f(3+21,-31);
    glEnd();

    treeLeafNight();
    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(6+21,-28);
    glVertex2f(3.5+21, -26);
    glVertex2f(1+21,-28);
    glEnd();

    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(1.5+21,-27);
    glVertex2f(5.5+21, -27);
    glVertex2f(3.5+21,-25);
    glEnd();
}

void treeMRL5(){//g72
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(3+28,-28);
    glVertex2f(4+28, -28);
    glVertex2f(4+28,-31);
    glVertex2f(3+28,-31);
    glEnd();

    glBegin(GL_TRIANGLES);
    treeLeafNight();
    glVertex2f(6+28,-28);
    glVertex2f(3.5+28, -26);
    glVertex2f(1+28,-28);
    glEnd();

    glBegin(GL_TRIANGLES);
    treeLeafNight();
    glVertex2f(1.5+28,-27);
    glVertex2f(5.5+28, -27);
    glVertex2f(3.5+28,-25);
    glEnd();
}

void treeMRL6(){//g73
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(3+35,-28);
    glVertex2f(4+35, -28);
    glVertex2f(4+35,-31);
    glVertex2f(3+35,-31);
    glEnd();

    treeLeafNight();
    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(6+35,-28);
    glVertex2f(3.5+35, -26);
    glVertex2f(1+35,-28);
    glEnd();

    glBegin(GL_TRIANGLES);
   // glColor3ub(22, 184, 29);
    glVertex2f(1.5+35,-27);
    glVertex2f(5.5+35, -27);
    glVertex2f(3.5+35,-25);
    glEnd();
}
void treeMRL7(){//g74
    glBegin(GL_QUADS);
    treeSqureNight();
    glVertex2f(3+42,-28);
    glVertex2f(4+42, -28);
    glVertex2f(4+42,-31);
    glVertex2f(3+42,-31);
    glEnd();

    treeLeafNight();
    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(6+42,-28);
    glVertex2f(3.5+42, -26);
    glVertex2f(1+42,-28);
    glEnd();

    glBegin(GL_TRIANGLES);
    //glColor3ub(22, 184, 29);
    glVertex2f(1.5+42,-27);
    glVertex2f(5.5+42, -27);
    glVertex2f(3.5+42,-25);
    glEnd();
}
 ///animation

void movingCloude()//g75
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(_moveCloud,0.0,0);
    clouds();
    glPopMatrix();
}
void updateCloud(int a)//g76
{
    if(!rainOn)
    {
        _moveCloud += 0.1f;

        if(_moveCloud > 100)
            _moveCloud = -100;
    }

    //_moveCloud+=0.02f;
    glutPostRedisplay();
    //glutTimerFunc(20, updateCloud, 0);

}
void movingBoat()//g77
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(_moveBoat,0.0,0);
    boat();
    glPopMatrix();
}
void updateBoat(int a)//g78
{
    _moveBoat+=boatSpeed;
    glutPostRedisplay();
    //glutTimerFunc(20, updateBoat, 0);
    if(_moveBoat>70)
    {
        _moveBoat=-40;
    }
}
void movingSmallBoat()//g79
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(_moveSmallBoat,0.0,0);
    smallBoat();
    glPopMatrix();
}
void updateSmallBoat(int a)//g80
{
    _moveSmallBoat-=boatSpeed;
    glutPostRedisplay();
    //glutTimerFunc(20, updateSmallBoat, 0);
    if(_moveSmallBoat<-70)
    {
        _moveSmallBoat=40;
    }
}

void updateWheelRotation(int a)//g81
{
    angle+=2.0f;
    glutPostRedisplay();
    //glutTimerFunc(20, updateWheelRotation, 0);
}
void movingVehicleRight()//g82
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(moveCarRight,0.0,0);
    miniBus();
    privateCarRight();
    privateCarRight1();
    glPopMatrix();
}
void updateVehicleRight(int a)//g83
{
    moveCarRight+=carSpeed;
    glutPostRedisplay();
    //glutTimerFunc(20, updateVehicleRight, 0);
    if(moveCarRight>95)
    {
        moveCarRight=-70;
    }
}
void movingPrivateCar()//g84
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(moveCarLeft,0.0,0);
    privateCar();
    privateCar2();
    privateCar3();
    privateCar4();
    glPopMatrix();
}
void updatePrivateCar(int a)//g85
{
    moveCarLeft-=carSpeed;
    glutPostRedisplay();
    //glutTimerFunc(20, updatePrivateCar, 0);
    if(moveCarLeft<-90)
    {
        moveCarLeft=49;
    }
}
void movingSun(){//g86
    if(nightMode){
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0,downSun,0);
        sun();
        glPopMatrix();
    }
}
void updateSun(int a){//g87
     if(nightMode)
    {
        if(downSun > -50.0f)
        {
            downSun -= 0.2f;
        }
    }

    glutPostRedisplay();
    //glutTimerFunc(20, updateSun, 0);

}
void movingMoon()//g88
{
    if(nightMode)
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        glTranslatef(0.0f, upMoon, 0.0f);

        moon();

        glPopMatrix();
    }
}
void updateMoon(int a)//g89
{
    if(nightMode)
    {
        if(upMoon < 20.0f)
        {
            upMoon += 0.2f;
        }
    }

    glutPostRedisplay();
    //glutTimerFunc(20, updateMoon, 0);
}
void display()//g90
{
    glClearColor(0, 0, 0, 1);

    glClear(GL_COLOR_BUFFER_BIT);

    sky();

    star();
    if(!rainOn && !nightMode)
     {
        sun();
     }
    if(nightMode)
     {
         movingSun();
         movingMoon();
     }

    mountain1();
    mountain2();
    mountain3();

    snowMountain1();
    snowMountain2();
    snowMountain3();

    gMountain1();
    gMountain2();
    gMountain3();
    gMountain4();
    gMountain5();
    gMountain6();
    gMountain7();
    waterFall();

    ground();

    road();

    sideRoad();
    standCar();

    river();
    standBoat();
    boatGhat();


    ///animation

    movingCloude();
    movingSmallBoat();
    movingBoat();
    movingPrivateCar();
    movingVehicleRight();

    rainySkyEffect();
    rain();

    //house
    building1();
    building2();
    building3();
    building4();
    building5();

    //tree
    treeR1();
    treeR2();
    treeR3();
    treeR4();
    treeMR1();
    treeMR2();
    treeMR3();
    treeMR4();
    treeMR5();
    treeMR6();
    treeMR7();
    treeMRL1();
    treeMRL2();
    treeMRL3();
    treeMRL4();
    treeMRL5();
    treeMRL6();
    treeMRL7();



    glutSwapBuffers();
    glFlush();
}

void handleKeypress(unsigned char key, int x, int y)//g91
{
    if(key == 'r' || key == 'R')
    {
        rainOn = !rainOn;
    }
    if(key=='b' || key=='B'){
        rainOn=false;
        nightMode=false;
        downSun=0.0f;
        upMoon=0.0f;
    }
    if(key=='n' || key=='N'){
        nightMode=true;
    }

    glutPostRedisplay();
}
void handleMouse(int button, int state, int x, int y) {//g92
    if (button == GLUT_LEFT_BUTTON)
	   {
	      carSpeed += 0.1f;
          boatSpeed+=0.1f;
       }
    if (button == GLUT_RIGHT_BUTTON)
	{
	    carSpeed=0.0f;
	    boatSpeed=0.0f;

	}
    glutPostRedisplay();
}

};

class VillageFair{
public:


float boatMove1 = -50.0f;
float boatMove2 = -20.0f;
float boatMove3 = 20.0f;
float _angle1 = 0.0f;
float moveCloud=0.0f;
float moveFanush=0.0;
float boatSpeed=0.2f;
float fanushSpeed=0.2;
bool boatAnimation = true;
bool ferrisAnimation = true;

void circle(float radius, float xc, float yc,
            float r, float g, float b)   //s001
{
    glBegin(GL_POLYGON);

    for(int i=0;i<200;i++)
    {
        glColor3ub(r,g,b);

        float pi=3.1416;
        float A=(i*2*pi)/200;

        float x = radius * cos(A);
        float y = radius * sin(A);

        glVertex2f(x+xc,y+yc);
    }

    glEnd();
}
void feeriWhile(float radius, float xc, float yc,
            float r, float g, float b) //s002
{
    glPointSize(3);
    glBegin(GL_POINTS);

    for(int i=0;i<200;i++)
    {
        glColor3ub(r,g,b);

        float pi=3.1416;
        float A=(i*2*pi)/200;

        float x = radius * cos(A);
        float y = radius * sin(A);

        glVertex2f(x+xc,y+yc);
    }

    glEnd();
}



void Sky()//s003
{
    glColor3ub(5, 10, 30);

    glBegin(GL_QUADS);

    glVertex2f(-50, 0);
    glVertex2f(50, 0);
    glVertex2f(50, 50);
    glVertex2f(-50, 50);

    glEnd();
}
void star(){//s004
    circle(0.5, -45, 45, 255, 255, 255);
    circle(0.4, -38, 40, 255, 255, 255);
    circle(0.6, -30, 46, 255, 255, 255);
    circle(0.4, -22, 42, 255, 255, 255);
    circle(0.5, -12, 47, 255, 255, 255);

    circle(0.5, -2, 43, 255, 255, 255);
    circle(0.4, 8, 47, 255, 255, 255);
    circle(0.6, 18, 42, 255, 255, 255);
    circle(0.4, 28, 46, 255, 255, 255);
    circle(0.5, 38, 41, 255, 255, 255);
    circle(0.6, 46, 47, 255, 255, 255);
    circle(0.4, -45, 35, 255, 255, 255);
    circle(0.5, -40, 30, 255, 255, 255);
    circle(0.3, -34, 37, 255, 255, 255);
    circle(0.5, -28, 32, 255, 255, 255);
    circle(0.3, 3, 37, 255, 255, 255);
    circle(0.5, 28, 32, 255, 255, 255);
    circle(0.3, 10, 10, 255, 255, 255);
    circle(0.5, 18, 22, 255, 255, 255);
    circle(0.3, 3, 10, 255, 255, 255);
    circle(0.5, 16, 12, 255, 255, 255);
    circle(0.3, 0, 20, 255, 255, 255);
    circle(0.5, 0, 23, 255, 255, 255);
    circle(0.3, 3, 23, 255, 255, 255);
    circle(0.5, 0, 19, 255, 255, 255);
    circle(0.5, -10, 12, 255, 255, 255);
    circle(0.3, -11, 21, 255, 255, 255);
    circle(0.5, -10, 28, 255, 255, 255);
    circle(0.3, 7, 23, 255, 255, 255);
    circle(0.5, 0, 39, 255, 255, 255);

}

void Sun()//s005
{
    circle(7.203, 29.86, 42.06, 210, 215, 225);
}



void Cloud1()//s006
{
    circle(4,-35,38,255,255,255);
    circle(5,-30,39,255,255,255);
    circle(4,-25,38,255,255,255);

    glColor3ub(255,255,255);

    glBegin(GL_QUADS);

    glVertex2f(-39,35);
    glVertex2f(-21,35);
    glVertex2f(-21,38);
    glVertex2f(-39,38);

    glEnd();
}



void Cloud2()//s007
{
    circle(4,5,43,255,255,255);
    circle(5,10,44,255,255,255);
    circle(4,15,43,255,255,255);

    glColor3ub(255,255,255);

    glBegin(GL_QUADS);

    glVertex2f(1,40);
    glVertex2f(19,40);
    glVertex2f(19,43);
    glVertex2f(1,43);

    glEnd();
}
void cloud3(){//s008
    circle(3,4+24,43,255,255,255);
    circle(2,5+24,43,255,255,255);
    circle(5,10+24,44,255,255,255);
    circle(3,15+24,43,255,255,255);

    glColor3ub(255,255,255);

    glBegin(GL_QUADS);

    glVertex2f(1+25,40);
    glVertex2f(19+25,40);
    glVertex2f(19+23,43);
    glVertex2f(1+23,43);

    glEnd();
}
void clouds(){//s009
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(moveCloud,0.0,0);
    Cloud1();
    Cloud2();
    cloud3();
    glPopMatrix();
}



void Grass()//s010
{
    glColor3ub(60, 170, 50);

    glBegin(GL_QUADS);

    glVertex2f(-50, -50);
    glVertex2f(50, -50);
    glVertex2f(50, 0);
    glVertex2f(-50, 0);

    glEnd();
}



void Mountains()//s011
{


    glColor3ub(20, 45, 25);

    glBegin(GL_TRIANGLES);

    glVertex2f(-50, 5);
    glVertex2f(-35, 15);
    glVertex2f(-20, 5);

    glVertex2f(-35, 5);
    glVertex2f(-18, 20);
    glVertex2f(0, 5);

    glVertex2f(-5, 5);
    glVertex2f(12, 14);
    glVertex2f(30, 5);

    glVertex2f(20, 5);
    glVertex2f(38, 19);
    glVertex2f(50, 5);

    glEnd();

    glColor3ub(25, 65, 30);

    glBegin(GL_TRIANGLES);

    glVertex2f(-50, 5);
    glVertex2f(-25, 9);
    glVertex2f(-5, 5);

    glVertex2f(-25, 5);
    glVertex2f(-5, 13);
    glVertex2f(15, 5);

    glVertex2f(5, 5);
    glVertex2f(25, 11);
    glVertex2f(50, 5);

    glEnd();
}



void River()//s012
{
    glColor3ub(40, 90, 150);

    glBegin(GL_QUADS);

    glVertex2f(-50, -50);
    glVertex2f(50, -50);
    glVertex2f(50, -44);
    glVertex2f(-50, -44);

    glEnd();


    glColor3ub(60, 120, 180);

    glBegin(GL_QUADS);

    glVertex2f(-50, -44);
    glVertex2f(50, -44);
    glVertex2f(50, -41);
    glVertex2f(-50, -41);

    glEnd();


    glColor3ub(120, 170, 210);

    glLineWidth(2);

    glBegin(GL_LINES);

    glVertex2f(-45, -47);
    glVertex2f(-35, -47);

    glVertex2f(-20, -46);
    glVertex2f(-8, -46);

    glVertex2f(5, -48);
    glVertex2f(18, -48);

    glVertex2f(25, -45.5);
    glVertex2f(38, -45.5);

    glVertex2f(-40, -43);
    glVertex2f(-28, -43);

    glVertex2f(-10, -42.5);
    glVertex2f(3, -42.5);

    glVertex2f(15, -43);
    glVertex2f(28, -43);

    glVertex2f(33, -42);
    glVertex2f(46, -42);

    glEnd();
}


void Path()//s013
{
    glColor3ub(180, 140, 90);

    glBegin(GL_POLYGON);

    glVertex2f(-42, -12);
    glVertex2f(-30, -14);
    glVertex2f(-15, -13);
    glVertex2f(0, -10);
    glVertex2f(15, -9);
    glVertex2f(30, -10);
    glVertex2f(42, -12);
    glVertex2f(45, -16);
    glVertex2f(40, -22);
    glVertex2f(25, -24);
    glVertex2f(10, -25);
    glVertex2f(-5, -25);
    glVertex2f(-20, -24);
    glVertex2f(-35, -22);
    glVertex2f(-45, -18);

    glEnd();
}



void Stall1()//s014
{
    glColor3ub(200, 60, 130);

    glBegin(GL_QUADS);

    glVertex2f(-47, -26);
    glVertex2f(-30, -26);
    glVertex2f(-30, -18);
    glVertex2f(-47, -18);

    glEnd();


    glColor3ub(220, 100, 160);

    glBegin(GL_QUADS);

    glVertex2f(-47, -18);
    glVertex2f(-30, -18);
    glVertex2f(-30, -16);
    glVertex2f(-47, -16);

    glEnd();


    glColor3ub(30, 140, 210);

    glBegin(GL_QUADS);

    glVertex2f(-46, -16);
    glVertex2f(-31, -16);
    glVertex2f(-31, -7);
    glVertex2f(-46, -7);

    glEnd();


    glColor3ub(20, 50, 160);

    glBegin(GL_POLYGON);

    glVertex2f(-48, -7);
    glVertex2f(-29, -7);
    glVertex2f(-31, -3);
    glVertex2f(-47, -3);

    glEnd();


    glColor3ub(40, 40, 40);

    glLineWidth(3);

    glBegin(GL_LINES);

    glVertex2f(-46.5, -16);
    glVertex2f(-46.5, -7);

    glVertex2f(-30.5, -16);
    glVertex2f(-30.5, -7);

    glEnd();


    circle(0.6, -42, -14.5, 255, 50, 50);
    circle(0.6, -40, -14.5, 50, 220, 80);
    circle(0.6, -38, -14.5, 255, 210, 40);
    circle(0.6, -36, -14.5, 180, 50, 200);
}



void Stall2()//s015
{
    glColor3ub(120, 30, 140);

    glBegin(GL_TRIANGLES);

    glVertex2f(13, -3);
    glVertex2f(22, 5);
    glVertex2f(31, -3);

    glEnd();


    glColor3ub(230, 230, 240);

    glBegin(GL_QUADS);

    glVertex2f(14, -13);
    glVertex2f(30, -13);
    glVertex2f(30, -3);
    glVertex2f(14, -3);

    glEnd();


    glColor3ub(150, 80, 180);

    glBegin(GL_QUADS);

    glVertex2f(14, -17);
    glVertex2f(30, -17);
    glVertex2f(30, -13);
    glVertex2f(14, -13);

    glEnd();


    circle(0.9, 17, -6, 255, 80, 40);
    circle(0.9, 22, -6, 255, 210, 40);
    circle(0.9, 27, -6, 40, 180, 240);

    circle(0.9, 19, -9, 240, 60, 120);
    circle(0.9, 25, -9, 50, 200, 80);
}



void FerrisWheel()//s016
{
    glPushMatrix();
    glTranslatef(-18, 1, 0);


    glRotatef(_angle1, 0, 0, 1);


    glTranslatef(18, -1, 0);

    glColor3ub(70,70,70);
    glBegin(GL_LINES);
    glColor3ub(255,200,0);
    glPointSize(3);
    glVertex2f(-18,1);
    glVertex2f(-24-1,0);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255,200,0);
    glPointSize(3);
    glVertex2f(-18,1);
    glVertex2f(-12+1,0);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(255,200,0);
    glPointSize(3);
    glVertex2f(-18,1);
    glVertex2f(-18,-5-1);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255,200,0);
    glPointSize(3);
    glVertex2f(-18,1);
    glVertex2f(-18,7+1);
    glEnd();

    //canin
    glBegin(GL_QUADS);

    glColor3ub(255,200,0);
    glVertex2f(-19.5,-5-1);
    glVertex2f(-16.5,-5-1);
    glVertex2f(-16.5,-7-1);
    glVertex2f(-19.5,-7-1);
    glBegin(GL_QUADS);

    glColor3ub(255,200,0);
    glVertex2f(-11,1);
    glVertex2f(-8,1);
    glVertex2f(-8,-1.5);
    glVertex2f(-11,-1.5);

    glColor3ub(255,200,0);
    glVertex2f(-11-17,1);
    glVertex2f(-8-17,1);
    glVertex2f(-8-17,-1.5);
    glVertex2f(-11-17,-1.5);
    glColor3ub(255,200,0);
    glVertex2f(-19.5,-5+15);
    glVertex2f(-16.5,-5+15);
    glVertex2f(-16.5,-7+15);
    glVertex2f(-19.5,-7+15);
    glBegin(GL_QUADS);


    glEnd();


    glColor3ub(50,50,50);

    circle(1.5,-18,1,255,200,0);


    feeriWhile (6,-18,1,255,200,0);

    glPopMatrix();
}

void feeriBase(){//s017
     glBegin(GL_QUADS);

    glVertex2f(-20,1);
    glVertex2f(-19,1);
    glVertex2f(-21,-12);
    glVertex2f(-22,-12);

    glEnd();

    glBegin(GL_QUADS);

    glVertex2f(-17,1);
    glVertex2f(-16,1);
    glVertex2f(-14,-12);
    glVertex2f(-15,-12);

    glEnd();
    glBegin(GL_QUADS);

    glColor3ub(70,70,70);
    glVertex2f(-24,-11);
    glVertex2f(-12,-11);
    glVertex2f(-12,-13);
    glVertex2f(-24,-13);

    glEnd();
}

void FairTent()//s018
{

    glColor3ub(220, 60, 120);

    glBegin(GL_QUADS);

    glVertex2f(28, -27);
    glVertex2f(48, -27);
    glVertex2f(48, -13);
    glVertex2f(28, -13);

    glEnd();




    glColor3ub(100, 40, 180);

    glBegin(GL_TRIANGLES);

    glVertex2f(26, -13);
    glVertex2f(38, -3);
    glVertex2f(50, -13);

    glEnd();



    glColor3ub(255, 190, 30);

    glBegin(GL_TRIANGLES);

    glVertex2f(31, -13);
    glVertex2f(38, -3);
    glVertex2f(35, -13);

    glEnd();



    glColor3ub(40, 190, 220);

    glBegin(GL_TRIANGLES);

    glVertex2f(38, -3);
    glVertex2f(46, -13);
    glVertex2f(42, -13);

    glEnd();


    glColor3ub(255, 190, 30);

    glBegin(GL_QUADS);

    glVertex2f(28, -27);
    glVertex2f(32, -27);
    glVertex2f(32, -13);
    glVertex2f(28, -13);

    glEnd();



    glColor3ub(40, 180, 220);

    glBegin(GL_QUADS);

    glVertex2f(44, -27);
    glVertex2f(48, -27);
    glVertex2f(48, -13);
    glVertex2f(44, -13);

    glEnd();



    glColor3ub(60, 30, 90);

    glBegin(GL_QUADS);

    glVertex2f(35, -27);
    glVertex2f(41, -27);
    glVertex2f(41, -16);
    glVertex2f(35, -16);

    glEnd();


    glColor3ub(255, 50, 50);

    glBegin(GL_TRIANGLES);

    glVertex2f(38, -3);
    glVertex2f(42, 0);
    glVertex2f(38, -1);

    glEnd();

}





void tree5()//s019
{


    glColor3ub(110, 60, 20);

    glBegin(GL_QUADS);

    glVertex2f(-7, -38);
    glVertex2f(-4, -38);
    glVertex2f(-4, -29);
    glVertex2f(-7, -29);

    glEnd();


    glColor3ub(15, 110, 35);

    glBegin(GL_TRIANGLES);

    glVertex2f(-11, -30);
    glVertex2f(-5.5, -21);
    glVertex2f(0, -30);

    glEnd();


    glColor3ub(30, 145, 45);

    glBegin(GL_TRIANGLES);

    glVertex2f(-10, -26);
    glVertex2f(-5.5, -18);
    glVertex2f(-1, -26);

    glEnd();
}





void Bench(float x, float y)//s020
{
    glPushMatrix();

    glTranslatef(x, y, 0);


    glColor3ub(120, 70, 30);

    glBegin(GL_QUADS);

    glVertex2f(-5, 0);
    glVertex2f(5, 0);
    glVertex2f(5, 2);
    glVertex2f(-5, 2);

    glEnd();

    glColor3ub(150, 80, 35);

    glBegin(GL_QUADS);

    glVertex2f(-5, 2);
    glVertex2f(5, 2);
    glVertex2f(5, 5);
    glVertex2f(-5, 5);

    glEnd();


    glColor3ub(70, 70, 70);

    glBegin(GL_QUADS);

    glVertex2f(-4, 0);
    glVertex2f(-3, 0);
    glVertex2f(-3, -4);
    glVertex2f(-4, -4);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(3, 0);
    glVertex2f(4, 0);
    glVertex2f(4, -4);
    glVertex2f(3, -4);

    glEnd();

    glPopMatrix();
}



void House1()//s021
{
    glColor3ub(180, 120, 70);

    glBegin(GL_QUADS);

    glVertex2f(-45, 2);
    glVertex2f(-35, 2);
    glVertex2f(-35, 9);
    glVertex2f(-45, 9);

    glEnd();


    glColor3ub(130, 50, 30);

    glBegin(GL_TRIANGLES);

    glVertex2f(-47, 9);
    glVertex2f(-40, 14);
    glVertex2f(-33, 9);

    glEnd();

    glColor3ub(70, 40, 25);

    glBegin(GL_QUADS);

    glVertex2f(-41, 2);
    glVertex2f(-38, 2);
    glVertex2f(-38, 6);
    glVertex2f(-41, 6);

    glEnd();
}



void House2()//s022
{
    glColor3ub(200, 150, 80);

    glBegin(GL_QUADS);

    glVertex2f(-27, 2);
    glVertex2f(-17, 2);
    glVertex2f(-17, 10);
    glVertex2f(-27, 10);

    glEnd();

    glColor3ub(150, 60, 35);

    glBegin(GL_TRIANGLES);

    glVertex2f(-29, 10);
    glVertex2f(-22, 15);
    glVertex2f(-15, 10);

    glEnd();


    glColor3ub(70, 40, 25);

    glBegin(GL_QUADS);

    glVertex2f(-24, 2);
    glVertex2f(-21, 2);
    glVertex2f(-21, 6);
    glVertex2f(-24, 6);

    glEnd();
}


void House3()//s023
{
    glColor3ub(190, 130, 70);

    glBegin(GL_QUADS);

    glVertex2f(5, 2);
    glVertex2f(15, 2);
    glVertex2f(15, 9);
    glVertex2f(5, 9);

    glEnd();


    glColor3ub(130, 50, 35);

    glBegin(GL_TRIANGLES);

    glVertex2f(3, 9);
    glVertex2f(10, 14);
    glVertex2f(17, 9);

    glEnd();


    glColor3ub(70, 40, 25);

    glBegin(GL_QUADS);

    glVertex2f(8, 2);
    glVertex2f(11, 2);
    glVertex2f(11, 6);
    glVertex2f(8, 6);

    glEnd();
}




void House4()//s024
{
    glColor3ub(180, 120, 75);

    glBegin(GL_QUADS);

    glVertex2f(25, 2);
    glVertex2f(36, 2);
    glVertex2f(36, 9);
    glVertex2f(25, 9);

    glEnd();


    glColor3ub(145, 55, 30);

    glBegin(GL_TRIANGLES);

    glVertex2f(23, 9);
    glVertex2f(30.5, 15);
    glVertex2f(38, 9);

    glEnd();


    glColor3ub(70, 40, 25);

    glBegin(GL_QUADS);

    glVertex2f(28, 2);
    glVertex2f(31, 2);
    glVertex2f(31, 6);
    glVertex2f(28, 6);

    glEnd();
}



void tree1()//s025
{

    glColor3ub(100, 55, 20);

    glBegin(GL_QUADS);

    glVertex2f(-33, 1);
    glVertex2f(-31, 1);
    glVertex2f(-31, 7);
    glVertex2f(-33, 7);

    glEnd();


    glColor3ub(20, 100, 35);

    glBegin(GL_TRIANGLES);

    glVertex2f(-37, 7);
    glVertex2f(-32, 14);
    glVertex2f(-27, 7);

    glEnd();


    glColor3ub(30, 140, 45);

    glBegin(GL_TRIANGLES);

    glVertex2f(-36, 10);
    glVertex2f(-32, 17);
    glVertex2f(-28, 10);

    glEnd();
}



void tree2()//s026
{

    glColor3ub(100, 55, 20);

    glBegin(GL_QUADS);

    glVertex2f(-12, 1);
    glVertex2f(-10, 1);
    glVertex2f(-10, 7);
    glVertex2f(-12, 7);

    glEnd();



    glColor3ub(20, 105, 35);

    glBegin(GL_TRIANGLES);

    glVertex2f(-16, 7);
    glVertex2f(-11, 14);
    glVertex2f(-6, 7);

    glEnd();

    glColor3ub(30, 145, 45);

    glBegin(GL_TRIANGLES);

    glVertex2f(-15, 10);
    glVertex2f(-11, 17);
    glVertex2f(-7, 10);

    glEnd();
}

void tree3()//s027
{
    glColor3ub(100, 55, 20);

    glBegin(GL_QUADS);

    glVertex2f(18, 1);
    glVertex2f(20, 1);
    glVertex2f(20, 7);
    glVertex2f(18, 7);

    glEnd();


    glColor3ub(20, 105, 35);

    glBegin(GL_TRIANGLES);

    glVertex2f(14, 7);
    glVertex2f(19, 14);
    glVertex2f(24, 7);

    glEnd();


    glColor3ub(30, 145, 45);

    glBegin(GL_TRIANGLES);

    glVertex2f(15, 10);
    glVertex2f(19, 17);
    glVertex2f(23, 10);

    glEnd();
}


void tree4()//s028
{

    glColor3ub(100, 55, 20);

    glBegin(GL_QUADS);

    glVertex2f(39, 1);
    glVertex2f(41, 1);
    glVertex2f(41, 7);
    glVertex2f(39, 7);

    glEnd();

    glColor3ub(20, 105, 35);

    glBegin(GL_TRIANGLES);

    glVertex2f(35, 7);
    glVertex2f(40, 14);
    glVertex2f(45, 7);

    glEnd();

    glColor3ub(30, 145, 45);

    glBegin(GL_TRIANGLES);

    glVertex2f(36, 10);
    glVertex2f(40, 17);
    glVertex2f(44, 10);

    glEnd();
}

void VillageBackground()//s029
{

    glColor3ub(75, 125, 45);

    glBegin(GL_QUADS);

    glVertex2f(-50, -2);
    glVertex2f(50, -2);
    glVertex2f(50, 8);
    glVertex2f(-50, 8);

    glEnd();


    House1();
    House2();
    House3();
    House4();


    tree1();
    tree2();
    tree3();
    tree4();
}
void HotAirBalloon(float x,float y,float scale)//s030
{
    glPushMatrix();
    //glPushMatrix();
    glTranslatef(x,y, 0);
    glScalef(scale, scale, 1);

    circle(4, 0, 0, 230, 50, 50);
    circle(3.5, 0, -1, 240, 180, 40);

    glColor3ub(50, 50, 50);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2f(-1.5, -3.5);
    glVertex2f(-1, -6);
    glVertex2f(1.5, -3.5);
    glVertex2f(1, -6);
    glEnd();


    glColor3ub(130, 70, 30);
    glBegin(GL_QUADS);
    glVertex2f(-1.5, -6);
    glVertex2f(1.5, -6);
    glVertex2f(1.2, -8);
    glVertex2f(-1.2, -8);
    glEnd();
    glPopMatrix();

}
void Fanush(){//s031
    glPushMatrix();

    glTranslatef(moveFanush, 0, 0);
    HotAirBalloon(-15, 38, 1.2);
    HotAirBalloon(-40, 42, 0.8);
    HotAirBalloon(10, 42, 0.8);
    HotAirBalloon(40, 32, 0.8);
    glPopMatrix();
}
void Boat(float x, float y, float scale)//s032
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1);

    glColor3ub(100, 50, 20);
    glBegin(GL_POLYGON);
    glVertex2f(-4*2.5, 0);
    glVertex2f(4*2.5, 0);
    glVertex2f(3*2.5, -1.5*2.5);
    glVertex2f(-3*2.5, -1.5*2.5);
    glEnd();
    glColor3ub(40, 40, 40);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(0*2.5, 0*3);
    glVertex2f(0, 4*2.5);
    glEnd();

    glColor3ub(240, 240, 240);
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 0.5*2.5);
    glVertex2f(2.5*2.5, 2.0*2.5);
    glVertex2f(0, 3.8*2.5);
    glEnd();

    glPopMatrix();
}

void boats(){//s033

   Boat(boatMove1, -45, 1.5);
   Boat(boatMove2, -47, 1.2);
   Boat(boatMove3, -47, 1.2);

}


void Person(float x, float y,float z)//s034
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    circle(1.2, 0, 4, 255, 200, 150);

    circle(1.25, 0, 4.8, 50, 30, 20);

    glColor3ub(220, 60, z);

    glBegin(GL_QUADS);
    glVertex2f(-1.2, 3);
    glVertex2f(1.2, 3);
    glVertex2f(1.2, -2);
    glVertex2f(-1.2, -2);
    glEnd();

    glColor3ub(255, 200, 150);

    glBegin(GL_QUADS);
    glVertex2f(-1.2, 3);
    glVertex2f(-0.5, 2.8);
    glVertex2f(-1.8, -1);
    glVertex2f(-2.3, -0.8);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.5, 2.8);
    glVertex2f(1.2, 3);
    glVertex2f(2.3, -0.8);
    glVertex2f(1.8, -1);
    glEnd();


    glColor3ub(40, 40, 80);

    glBegin(GL_QUADS);
    glVertex2f(-1, -2);
    glVertex2f(0, -2);
    glVertex2f(-0.2, -6);
    glVertex2f(-1.2, -6);
    glEnd();


    glBegin(GL_QUADS);
    glVertex2f(0, -2);
    glVertex2f(1, -2);
    glVertex2f(1.2, -6);
    glVertex2f(0.2, -6);
    glEnd();

    glPopMatrix();
}
void men(){//s035
    Person(-45, -23,55);

    Person(-35, -30,20);
    Person(18, -13,150);
    Person(32, -24,255);
    Person(45, -24,111);
    Person(-15, -17,0);
    Person(-5, -10,90);
}

void chorki()//s036
{

    glColor3ub(220, 50, 50);

    glBegin(GL_TRIANGLES);
    glVertex2f(-8, 5);
    glVertex2f(8, 5);
    glVertex2f(0, 13);
    glEnd();


    glColor3ub(255, 200, 50);

    glBegin(GL_QUADS);
    glVertex2f(-8, 3);
    glVertex2f(8, 3);
    glVertex2f(8, 5);
    glVertex2f(-8, 5);
    glEnd();


    glColor3ub(100, 60, 30);

    glBegin(GL_QUADS);
    glVertex2f(-1, -10);
    glVertex2f(1, -10);
    glVertex2f(1, 4);
    glVertex2f(-1, 4);
    glEnd();


    glColor3ub(50, 150, 255);

    glBegin(GL_QUADS);
    glVertex2f(-6, -4);
    glVertex2f(-3, -4);
    glVertex2f(-3, 2);
    glVertex2f(-6, 2);
    glEnd();

    glColor3ub(255, 100, 150);

    glBegin(GL_QUADS);
    glVertex2f(3, -4);
    glVertex2f(6, -4);
    glVertex2f(6, 2);
    glVertex2f(3, 2);
    glEnd();

    circle(1.5, -4.5, 2, 50, 150, 255);
    circle(1.5, 4.5, 2, 255, 100, 150);


    glColor3ub(80, 80, 80);

    glBegin(GL_QUADS);
    glVertex2f(-9, -12);
    glVertex2f(9, -12);
    glVertex2f(7, -9);
    glVertex2f(-7, -9);
    glEnd();

}





void update(int value)//s037
{

    if(boatAnimation)
    {
        boatMove1 += boatSpeed;
        boatMove2 += boatSpeed;
        boatMove3 += boatSpeed;

        if(boatMove1 > 60)
            boatMove1 = -60;

        if(boatMove2 > 60)
            boatMove2 = -60;

        if(boatMove3 > 60)
            boatMove3 = -60;
    }


    if(ferrisAnimation)
    {
        _angle1 += 2.0f;

        if(_angle1 > 360)
            _angle1 -= 360;
    }

    moveFanush+=fanushSpeed;
    if(moveFanush>70){
        moveFanush=-70;
    }



    glutPostRedisplay();

    //glutTimerFunc(20, update, 0);
}

void updateCloud(int a){//s038
    moveCloud+=0.06f;

    glutPostRedisplay();
    //glutTimerFunc(20, updateCloud, 0);
    if(moveCloud>70){
        moveCloud=-80;
    }

}






void display()//s039
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(7.5);

    Sky();
    star();

    Sun();
    Grass();


    Mountains();

    VillageBackground();


    River();

    Path();

    FerrisWheel();
    feeriBase();
    clouds();

    Fanush();

    Stall1();

    Stall2();

    FairTent();

    Bench(-25, -26);

    Bench(32, -35);

    chorki();




    tree5();
    men();

    boats();


    glFlush();
}
void keyboard(unsigned char key, int x, int y)//s040
{
    switch(key)
    {
        case '1':
            boatAnimation = !boatAnimation;
            break;

        case '2':
            ferrisAnimation = !ferrisAnimation;
            break;

        case '0':
            boatAnimation = true;
            ferrisAnimation = true;
            break;
    }

    glutPostRedisplay();

}
void handleMouse(int button, int state, int x, int y) {//s041
    if (button == GLUT_LEFT_BUTTON)
	   {
          boatSpeed+=0.1f;
          fanushSpeed+=0.1f;
       }
    if (button == GLUT_RIGHT_BUTTON)
	{
	    boatSpeed=0.0f;
	    fanushSpeed=0.0f;

	}
    glutPostRedisplay();
}

};

class SmartCity{
public:

float carMove = -50.0f;
float carMove2 = -25;
float carMove3 = 50.0f;
int trafficState = 0;
int streetLight = 0;
float bicycleMove = -45.0f;
float bicycleMove1 = -25.0f;
float bicycleMove2 = -45.0f;

float vehicleSpeed = 0.5f;
bool nightMode = false;

void circle(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);

    for(int i = 0; i < 200; i++)
    {
        glColor3f(r, g, b);

        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;

        float x = radius * cos(A);
        float y = radius * sin(A);

        glVertex2f(x + xc, y + yc);
    }

    glEnd();
}




void sky() /////D1
{
    glBegin(GL_QUADS);

    if(nightMode)
    {
        // Dark Night Sky
        glColor3ub(10, 20, 50);
        glVertex2f(-50, 50);
        glVertex2f(50, 50);

        glColor3ub(25, 35, 75);
        glVertex2f(50, 20);
        glVertex2f(-50, 20);
    }
    else
    {
        // Day Sky
        glColor3ub(90, 170, 230);
        glVertex2f(-50, 50);
        glVertex2f(50, 50);

        glColor3ub(180, 225, 250);
        glVertex2f(50, 20);
        glVertex2f(-50, 20);
    }

    glEnd();
}

void airplane() //////D2
{
    // Body
    glColor3ub(255, 255, 255);

    glBegin(GL_POLYGON);
        glVertex2f(10, 35);
        glVertex2f(22, 35);
        glVertex2f(24, 36);
        glVertex2f(22, 37);
        glVertex2f(10, 37);
        glVertex2f(8, 36);
    glEnd();

    // Upper Wing
    glBegin(GL_POLYGON);
        glVertex2f(14, 37);
        glVertex2f(18, 43);
        glVertex2f(20, 43);
        glVertex2f(18, 37);
    glEnd();

    // Lower Wing
    glBegin(GL_POLYGON);
        glVertex2f(14, 35);
        glVertex2f(18, 29);
        glVertex2f(20, 29);
        glVertex2f(18, 35);
    glEnd();

    // Tail
    glBegin(GL_TRIANGLES);
        glVertex2f(10, 37);
        glVertex2f(8, 41);
        glVertex2f(13, 37);
    glEnd();
}


void Bird() ////D3
{

        glColor3ub(70, 50, 30);
    // =========================
    // BIRD 1
    // =========================

    glBegin(GL_TRIANGLES);

    glVertex2f(-10, 40);
    glVertex2f(-12.5, 41.5);
    glVertex2f(-11.5, 40);

    glVertex2f(-10, 40);
    glVertex2f(-7.5, 41.5);
    glVertex2f(-8.5, 40);

    glEnd();
}
void Bird1()    //////D4
{

        glColor3ub(70, 50, 30);


    glBegin(GL_TRIANGLES);

    // =========================
    // BIRD 2
    // =========================

    glBegin(GL_TRIANGLES);

    glVertex2f(0, 45);
    glVertex2f(-2.5, 46.5);
    glVertex2f(-1.5, 45);

    glVertex2f(0, 45);
    glVertex2f(2.5, 46.5);
    glVertex2f(1.5, 45);

    glEnd();
}
void Bird2() ////D5
{
 glColor3ub(70, 50, 30);


    glBegin(GL_TRIANGLES);
    // =========================
    // BIRD 3
    // =========================

    glBegin(GL_TRIANGLES);

    glVertex2f(12, 38);
    glVertex2f(9.5, 39.5);
    glVertex2f(10.5, 38);

    glVertex2f(12, 38);
    glVertex2f(14.5, 39.5);
    glVertex2f(13.5, 38);

    glEnd();
}
void Bird3() ////D6
{

 glColor3ub(70, 50, 30);


    glBegin(GL_TRIANGLES);

    // BIRD 4
    // =========================

    glBegin(GL_TRIANGLES);

    glVertex2f(22, 43);
    glVertex2f(19.5, 44.5);
    glVertex2f(20.5, 43);

    glVertex2f(22, 43);
    glVertex2f(24.5, 44.5);
    glVertex2f(23.5, 43);

    glEnd();
}









void Stars() /// D7
{
    glColor3ub(255, 255, 255);

    circle(0.25, -42, 44, 1, 1, 1);
    circle(0.20, -35, 38, 1, 1, 1);
    circle(0.25, -25, 45, 1, 1, 1);
    circle(0.20, -15, 40, 1, 1, 1);
    circle(0.25, -5, 46, 1, 1, 1);
    circle(0.20, 5, 40, 1, 1, 1);
    circle(0.25, 15, 45, 1, 1, 1);
    circle(0.20, 25, 37, 1, 1, 1);
    circle(0.25, 42, 45, 1, 1, 1);
}



// ROAD LINE


void RoadLine() ///////D8
{
   if(nightMode)
    glColor3ub(255, 220, 80);   // Night - Yellow
else
    glColor3ub(255, 255, 255);  // Day - White



    // LOWER HORIZONTAL ROAD


    glBegin(GL_QUADS);

    glVertex2f(-50, -14.5);
    glVertex2f(-42, -14.5);
    glVertex2f(-42, -15.5);
    glVertex2f(-50, -15.5);

    glVertex2f(-37, -14.5);
    glVertex2f(-29, -14.5);
    glVertex2f(-29, -15.5);
    glVertex2f(-37, -15.5);

    glVertex2f(-24, -14.5);
    glVertex2f(-16, -14.5);
    glVertex2f(-16, -15.5);
    glVertex2f(-24, -15.5);

    glVertex2f(-11, -14.5);
    glVertex2f(-3, -14.5);
    glVertex2f(-3, -15.5);
    glVertex2f(-11, -15.5);

    glVertex2f(3, -14.5);
    glVertex2f(11, -14.5);
    glVertex2f(11, -15.5);
    glVertex2f(3, -15.5);

    glVertex2f(16, -14.5);
    glVertex2f(24, -14.5);
    glVertex2f(24, -15.5);
    glVertex2f(16, -15.5);

    glVertex2f(29, -14.5);
    glVertex2f(37, -14.5);
    glVertex2f(37, -15.5);
    glVertex2f(29, -15.5);

    glVertex2f(42, -14.5);
    glVertex2f(50, -14.5);
    glVertex2f(50, -15.5);
    glVertex2f(42, -15.5);

    glEnd();



    // VERTICAL ROAD


    glBegin(GL_QUADS);



    glVertex2f(-0.5, 11);
    glVertex2f(0.5, 11);
    glVertex2f(0.5, 3);
    glVertex2f(-0.5, 3);

    glVertex2f(-0.5, 0);
    glVertex2f(0.5, 0);
    glVertex2f(0.5, -8);
    glVertex2f(-0.5, -8);

    glVertex2f(-0.5, -13);
    glVertex2f(0.5, -13);
    glVertex2f(0.5, -21);
    glVertex2f(-0.5, -21);

    glVertex2f(-0.5, -26);
    glVertex2f(0.5, -26);
    glVertex2f(0.5, -34);
    glVertex2f(-0.5, -34);

    glVertex2f(-0.5, -39);
    glVertex2f(0.5, -39);
    glVertex2f(0.5, -47);
    glVertex2f(-0.5, -47);

    glEnd();


    // -------------------------
    // UPPER HORIZONTAL ROAD
    // -------------------------

    glBegin(GL_QUADS);

    glVertex2f(-50, 14.5);
    glVertex2f(-42, 14.5);
    glVertex2f(-42, 15.5);
    glVertex2f(-50, 15.5);

    glVertex2f(-37, 14.5);
    glVertex2f(-29, 14.5);
    glVertex2f(-29, 15.5);
    glVertex2f(-37, 15.5);

    glVertex2f(-24, 14.5);
    glVertex2f(-16, 14.5);
    glVertex2f(-16, 15.5);
    glVertex2f(-24, 15.5);

    glVertex2f(-11, 14.5);
    glVertex2f(-3, 14.5);
    glVertex2f(-3, 15.5);
    glVertex2f(-11, 15.5);

    glVertex2f(3, 14.5);
    glVertex2f(11, 14.5);
    glVertex2f(11, 15.5);
    glVertex2f(3, 15.5);

    glVertex2f(16, 14.5);
    glVertex2f(24, 14.5);
    glVertex2f(24, 15.5);
    glVertex2f(16, 15.5);

    glVertex2f(29, 14.5);
    glVertex2f(37, 14.5);
    glVertex2f(37, 15.5);
    glVertex2f(29, 15.5);

    glVertex2f(42, 14.5);
    glVertex2f(50, 14.5);
    glVertex2f(50, 15.5);
    glVertex2f(42, 15.5);

    glEnd();
}


// =====================================================
// ROAD 1
// =====================================================

void Road()  ///////D9
{
    glColor3ub(55, 55, 60);

    glBegin(GL_QUADS);

    glVertex2f(-50, -10);
    glVertex2f(10, -10);
    glVertex2f(10, -20);
    glVertex2f(-50, -20);

    glEnd();
}


// =====================================================
// ROAD 2
// =====================================================

void Road2() //////D10
{
    glColor3ub(55, 55, 60);

    glBegin(GL_QUADS);

    glVertex2f(-10, 20);
    glVertex2f(10, 20);
    glVertex2f(10, -50);
    glVertex2f(-10, -50);

    glEnd();
}


// =====================================================
// ROAD 3
// =====================================================

void Road3() ///D11
{
    glColor3ub(55, 55, 60);

    glBegin(GL_QUADS);

    glVertex2f(-50, 10);
    glVertex2f(50, 10);
    glVertex2f(50, 20);
    glVertex2f(-50, 20);

    glEnd();
}

// car
// =====================================================


void RoadCar(float x, float y) ///////D12
{
    glPushMatrix();


    glTranslatef(x, y, 0);


    glColor3ub(30, 120, 220);

    glBegin(GL_QUADS);

    glVertex2f(-8, 15);
    glVertex2f(8, 15);
    glVertex2f(8, 19);
    glVertex2f(-8, 19);

    glEnd();



    glColor3ub(40, 90, 170);

    glBegin(GL_POLYGON);

    glVertex2f(-5, 19);
    glVertex2f(-3, 22);
    glVertex2f(4, 22);
    glVertex2f(6, 19);

    glEnd();



    glColor3ub(180, 225, 245);

    glBegin(GL_QUADS);


    glVertex2f(-2.5, 19.5);
    glVertex2f(0, 19.5);
    glVertex2f(0, 21.3);
    glVertex2f(-2, 21.3);


    glVertex2f(0.5, 19.5);
    glVertex2f(3.5, 19.5);
    glVertex2f(4.5, 21.3);
    glVertex2f(0.5, 21.3);

    glEnd();



    glColor3ub(255, 255, 150);

    glBegin(GL_QUADS);

    glVertex2f(7, 16.5);
    glVertex2f(8, 16.5);
    glVertex2f(8, 17.5);
    glVertex2f(7, 17.5);

    glEnd();



    circle(1.4, -4.5, 15, 0.05, 0.05, 0.05);
    circle(1.4, 4.5, 15, 0.05, 0.05, 0.05);

    circle(0.6, -4.5, 15, 0.7, 0.7, 0.7);
    circle(0.6, 4.5, 15, 0.7, 0.7, 0.7);

    glPopMatrix();
}
// =====================================================
// CAR 3
// =====================================================

void RoadCar3(float x, float y)  /////D13
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    // Body
    glColor3ub(220, 50, 50);

    glBegin(GL_QUADS);

    glVertex2f(-8, 15);
    glVertex2f(8, 15);
    glVertex2f(8, 19);
    glVertex2f(-8, 19);

    glEnd();

    // Roof
    glColor3ub(170, 40, 40);

    glBegin(GL_POLYGON);

    glVertex2f(-5, 19);
    glVertex2f(-3, 22);
    glVertex2f(4, 22);
    glVertex2f(6, 19);

    glEnd();

    // Windows
    glColor3ub(180, 225, 245);

    glBegin(GL_QUADS);

    glVertex2f(-2.5, 19.5);
    glVertex2f(0, 19.5);
    glVertex2f(0, 21.3);
    glVertex2f(-2, 21.3);

    glVertex2f(0.5, 19.5);
    glVertex2f(3.5, 19.5);
    glVertex2f(4.5, 21.3);
    glVertex2f(0.5, 21.3);

    glEnd();

    // Light
    glColor3ub(255, 255, 120);

    glBegin(GL_QUADS);

    glVertex2f(7, 16.5);
    glVertex2f(8, 16.5);
    glVertex2f(8, 17.5);
    glVertex2f(7, 17.5);

    glEnd();

    // Wheels
    circle(1.4, -4.5, 15, 0.05, 0.05, 0.05);
    circle(1.4, 4.5, 15, 0.05, 0.05, 0.05);

    circle(0.6, -4.5, 15, 0.7, 0.7, 0.7);
    circle(0.6, 4.5, 15, 0.7, 0.7, 0.7);

    glPopMatrix();
}





void update(int value)
{
    // =========================
// VEHICLE MOVEMENT
// =========================

// Road 1 car: left to right
carMove += vehicleSpeed;

if(carMove > 60)
{
    carMove = -60;
}
carMove2 += vehicleSpeed;
if(carMove2 > 60)
{
    carMove2 = -60;
}

// Road 2 car: right to left
carMove3 -= vehicleSpeed *0.7f;

if(carMove3 < -60)
{
    carMove3 = 60;
}



// Bicycle movement
bicycleMove += vehicleSpeed;

if(bicycleMove > 60)
{
    bicycleMove = -60;
}

bicycleMove1 += vehicleSpeed;

if(bicycleMove1 > 60)
{
    bicycleMove1 = -60;
}

bicycleMove2 += vehicleSpeed*2;

if(bicycleMove2 > 60)
{
    bicycleMove2 = -60;
}

    static int counter = 0;

    counter++;


    if(counter >= 100)
    {
        trafficState++;

        if(trafficState > 2)
        {
            trafficState = 0;
        }

        counter = 0;
    }

    //// street light
     streetLight++;

if(streetLight > 100)
{
    streetLight = 0;
}










    glutPostRedisplay();

    //glutTimerFunc(20, update, 0);
}




// =====================================================
// SMALL HOUSE
// =====================================================

void House2()  //////D14
{
    // Building
    glColor3ub(210, 210, 210);

    glBegin(GL_QUADS);

    glVertex2f(-19, 2.5);
    glVertex2f(-11, 2.5);
    glVertex2f(-11, 7);
    glVertex2f(-19, 7);

    glEnd();


    // Roof
    glColor3ub(60, 60, 60);

    glBegin(GL_QUADS);

    glVertex2f(-19.5, 7);
    glVertex2f(-10.5, 7);
    glVertex2f(-11.5, 8);
    glVertex2f(-18.5, 8);

    glEnd();


    // Window
   if(nightMode)
    glColor3ub(255, 220, 80);   // Window light
else
    glColor3ub(180, 220, 255);  // Day window

    glBegin(GL_QUADS);

    glVertex2f(-18, 4.5);
    glVertex2f(-15.5, 4.5);
    glVertex2f(-15.5, 6);
    glVertex2f(-18, 6);

    glVertex2f(-14.5, 4.5);
    glVertex2f(-12, 4.5);
    glVertex2f(-12, 6);
    glVertex2f(-14.5, 6);

    glEnd();


    // Door
    glColor3ub(100, 60, 30);

    glBegin(GL_QUADS);

    glVertex2f(-15, 2.5);
    glVertex2f(-13, 2.5);
    glVertex2f(-13, 4);
    glVertex2f(-15, 4);

    glEnd();
}




void House() //// D15
{
    // Main building
    glColor3ub(220, 190, 150);

    glBegin(GL_QUADS);

    glVertex2f(-48, -8);
    glVertex2f(-30, -8);
    glVertex2f(-30, 8);
    glVertex2f(-48, 8);

    glEnd();


    // Roof
    glColor3ub(100, 70, 50);

    glBegin(GL_QUADS);

    glVertex2f(-49, 8);
    glVertex2f(-29, 8);
    glVertex2f(-30, 10);
    glVertex2f(-48, 10);

    glEnd();


    // Windows
    if(nightMode)
    glColor3ub(255, 220, 80);
    else
    glColor3ub(70, 170, 220);

    glBegin(GL_QUADS);

    // Floor 1
    glVertex2f(-46, -6);
    glVertex2f(-42, -6);
    glVertex2f(-42, -2);
    glVertex2f(-46, -2);

    glVertex2f(-36, -6);
    glVertex2f(-32, -6);
    glVertex2f(-32, -2);
    glVertex2f(-36, -2);

    // Floor 2
    glVertex2f(-46, 0);
    glVertex2f(-42, 0);
    glVertex2f(-42, 4);
    glVertex2f(-46, 4);

    glVertex2f(-36, 0);
    glVertex2f(-32, 0);
    glVertex2f(-32, 4);
    glVertex2f(-36, 4);

    // Floor 3
    glVertex2f(-46, 5);
    glVertex2f(-42, 5);
    glVertex2f(-42, 7);
    glVertex2f(-46, 7);

    glVertex2f(-36, 5);
    glVertex2f(-32, 5);
    glVertex2f(-32, 7);
    glVertex2f(-36, 7);

    glEnd();


    // Door
    glColor3ub(100, 60, 30);

    glBegin(GL_QUADS);

    glVertex2f(-41, -8);
    glVertex2f(-37, -8);
    glVertex2f(-37, -2);
    glVertex2f(-41, -2);

    glEnd();
}




void Bench()  /////D16
{


    glColor3ub(139, 69, 19);

    // Seat
    glBegin(GL_QUADS);

    glVertex2f(-28, -7);
    glVertex2f(-20, -7);
    glVertex2f(-20, -6);
    glVertex2f(-28, -6);

    glEnd();


    // Backrest
    glBegin(GL_QUADS);

    glVertex2f(-28, -5);
    glVertex2f(-20, -5);
    glVertex2f(-20, -4);
    glVertex2f(-28, -4);

    glEnd();


    // Legs
    glColor3ub(70, 70, 70);

    glBegin(GL_QUADS);

    glVertex2f(-27, -8);
    glVertex2f(-26, -8);
    glVertex2f(-26, -7);
    glVertex2f(-27, -7);

    glVertex2f(-22, -8);
    glVertex2f(-21, -8);
    glVertex2f(-21, -7);
    glVertex2f(-22, -7);

    glEnd();




}




void Tree()  ////D17
{


    // Trunk
   if(nightMode)
    glColor3ub(15, 60, 20);     // Night
else
    glColor3ub(50, 140, 40);    // Day

    glBegin(GL_QUADS);

    glVertex2f(-49, -10);
    glVertex2f(-47.5, -10);
    glVertex2f(-47.5, -4);
    glVertex2f(-49, -4);

    glEnd();
}
void Tree1() ///D18
{


    // Leaves
    glColor3ub(34, 139, 34);

    glBegin(GL_TRIANGLES);

    glVertex2f(-50, -4);
    glVertex2f(-46.5, -4);
    glVertex2f(-48.25, 0);

    glVertex2f(-49.7, -2);
    glVertex2f(-46.8, -2);
    glVertex2f(-48.25, 2.5);

    glVertex2f(-49.4, 0);
    glVertex2f(-47.1, 0);
    glVertex2f(-48.25, 4.5);

    glEnd();




    // Trunk
    glColor3ub(30, 120, 50);

    glBegin(GL_QUADS);

    glVertex2f(-27, -1);
    glVertex2f(-25.5, -1);
    glVertex2f(-25.5, 4);
    glVertex2f(-27, 4);

    glEnd();


    // Leaves
    glColor3ub(34, 139, 34);

    glBegin(GL_TRIANGLES);

    glVertex2f(-29, 3);
    glVertex2f(-23.5, 3);
    glVertex2f(-26.25, 7);

    glVertex2f(-28.5, 5);
    glVertex2f(-24, 5);
    glVertex2f(-26.25, 9);

    glVertex2f(-28, 7);
    glVertex2f(-24.5, 7);
    glVertex2f(-26.25, 11);

    glEnd();

}

    // TREE 3
void Tree2() ////D19
{

    // Trunk
    glColor3ub(101, 67, 33);

    glBegin(GL_QUADS);

    glVertex2f(-17, -10);
    glVertex2f(-15.5, -10);
    glVertex2f(-15.5, -5);
    glVertex2f(-17, -5);

    glEnd();


    // Leaves
    glColor3ub(34, 139, 34);

    glBegin(GL_TRIANGLES);

    glVertex2f(-19, -5);
    glVertex2f(-13.5, -5);
    glVertex2f(-16.25, -1);

    glVertex2f(-18.5, -3);
    glVertex2f(-14, -3);
    glVertex2f(-16.25, 1);

    glVertex2f(-18, -1);
    glVertex2f(-14.5, -1);
    glVertex2f(-16.25, 3);

    glEnd();
}



// SCHOOL AREA///////////////////////////////////////////////////////////////////////////




void SchoolArea() /// D20
{
    if(nightMode)
    glColor3ub(20, 60, 25);     // Night grass
else
    glColor3ub(70, 160, 50);     // Day grass

    glBegin(GL_QUADS);

    // School er niche puro area
    glVertex2f(10, -20);
    glVertex2f(50, -20);
    glVertex2f(50, -50);
    glVertex2f(10, -50);

    glEnd();

}




// SMALL BUILDINGS -


void SmallBuildings() /// D21
{

    // Body
    glColor3ub(200, 200, 200);

    glBegin(GL_QUADS);

    glVertex2f(11, -10);
    glVertex2f(21, -10);
    glVertex2f(21, -2);
    glVertex2f(11, -2);

    glEnd();


    // Roof
    glColor3ub(60, 60, 60);

    glBegin(GL_QUADS);

    glVertex2f(10, -2);
    glVertex2f(22, -2);
    glVertex2f(20.5, 0);
    glVertex2f(11.5, 0);

    glEnd();


    // Window 1
   if(nightMode)
    glColor3ub(255, 220, 80);   // Window light
else
    glColor3ub(180, 220, 255);  // Day window

    glBegin(GL_QUADS);

    glVertex2f(12.5, -6);
    glVertex2f(16, -6);
    glVertex2f(16, -3.5);
    glVertex2f(12.5, -3.5);

    glEnd();


    // Window 2
    glBegin(GL_QUADS);

    glVertex2f(17, -6);
    glVertex2f(20, -6);
    glVertex2f(20, -3.5);
    glVertex2f(17, -3.5);

    glEnd();


    // Door
    glColor3ub(100, 60, 30);

    glBegin(GL_QUADS);

    glVertex2f(14.5, -10);
    glVertex2f(17.5, -10);
    glVertex2f(17.5, -6.5);
    glVertex2f(14.5, -6.5);

    glEnd();



    // RIGHT SMALL BUILDING



    glColor3ub(200, 200, 200);

    glBegin(GL_QUADS);

    glVertex2f(39, -10);
    glVertex2f(49, -10);
    glVertex2f(49, -2);
    glVertex2f(39, -2);

    glEnd();



    glColor3ub(60, 60, 60);

    glBegin(GL_QUADS);

    glVertex2f(38, -2);
    glVertex2f(50, -2);
    glVertex2f(48.5, 0);
    glVertex2f(39.5, 0);

    glEnd();



    glColor3ub(50, 150, 220);

    glBegin(GL_QUADS);

    glVertex2f(40.5, -6);
    glVertex2f(44, -6);
    glVertex2f(44, -3.5);
    glVertex2f(40.5, -3.5);

    glEnd();



    glBegin(GL_QUADS);

    glVertex2f(45, -6);
    glVertex2f(48, -6);
    glVertex2f(48, -3.5);
    glVertex2f(45, -3.5);

    glEnd();



    glColor3ub(100, 60, 30);

    glBegin(GL_QUADS);

    glVertex2f(42.5, -10);
    glVertex2f(45.5, -10);
    glVertex2f(45.5, -6.5);
    glVertex2f(42.5, -6.5);

    glEnd();
}





// =====================================================
// SCHOOL
// =====================================================
void School() //// D22
{


    glColor3ub(230, 100, 50);

    glBegin(GL_QUADS);

    glVertex2f(14, -7);
    glVertex2f(46, -7);
    glVertex2f(46, 7);
    glVertex2f(14, 7);

    glEnd();




    glColor3ub(220, 70, 40);

    glBegin(GL_QUADS);

    glVertex2f(14, -7);
    glVertex2f(22, -7);
    glVertex2f(22, 6);
    glVertex2f(14, 6);

    glEnd();



    glBegin(GL_QUADS);

    glVertex2f(38, -7);
    glVertex2f(46, -7);
    glVertex2f(46, 6);
    glVertex2f(38, 6);

    glEnd();




    glColor3ub(245, 95, 45);

    glBegin(GL_QUADS);

    glVertex2f(22, -7);
    glVertex2f(38, -7);
    glVertex2f(38, 6);
    glVertex2f(22, 6);

    glEnd();



    glColor3ub(70, 70, 75);

    glBegin(GL_QUADS);

    glVertex2f(13, 6);
    glVertex2f(47, 6);
    glVertex2f(43, 8);
    glVertex2f(17, 8);

    glEnd();



    glColor3ub(55, 55, 55);

    glBegin(GL_TRIANGLES);

    glVertex2f(26, 8);
    glVertex2f(34, 8);
    glVertex2f(30, 9.5);

    glEnd();




    glColor3ub(235, 80, 40);

    glBegin(GL_QUADS);

    glVertex2f(27, 6);
    glVertex2f(33, 6);
    glVertex2f(33, 10);
    glVertex2f(27, 10);

    glEnd();




    glColor3ub(255, 255, 255);

    circle(0.9, 30, 8, 1, 1, 1);

    glColor3ub(0, 0, 0);

    glBegin(GL_LINES);

    glVertex2f(30, 8);
    glVertex2f(30, 8.7);

    glVertex2f(30, 8);
    glVertex2f(30.6, 8);

    glEnd();





   if(nightMode)
    glColor3ub(255, 230, 80);   // Night window
else
    glColor3ub(180, 220, 255);  // Day window


    glBegin(GL_QUADS);

    glVertex2f(16, 1);
    glVertex2f(20, 1);
    glVertex2f(20, 4);
    glVertex2f(16, 4);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(23, 1);
    glVertex2f(27, 1);
    glVertex2f(27, 4);
    glVertex2f(23, 4);

    glEnd();



    glBegin(GL_QUADS);

    glVertex2f(33, 1);
    glVertex2f(37, 1);
    glVertex2f(37, 4);
    glVertex2f(33, 4);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(40, 1);
    glVertex2f(44, 1);
    glVertex2f(44, 4);
    glVertex2f(40, 4);

    glEnd();



    glBegin(GL_QUADS);

    glVertex2f(16, -5);
    glVertex2f(20, -5);
    glVertex2f(20, -2);
    glVertex2f(16, -2);

    glVertex2f(23, -5);
    glVertex2f(27, -5);
    glVertex2f(27, -2);
    glVertex2f(23, -2);

    glVertex2f(33, -5);
    glVertex2f(37, -5);
    glVertex2f(37, -2);
    glVertex2f(33, -2);

    glVertex2f(40, -5);
    glVertex2f(44, -5);
    glVertex2f(44, -2);
    glVertex2f(40, -2);

    glEnd();



    glColor3ub(70, 70, 70);

    glBegin(GL_QUADS);

    glVertex2f(27, -7);
    glVertex2f(33, -7);
    glVertex2f(33, -1);
    glVertex2f(27, -1);

    glEnd();



    glColor3ub(150, 220, 240);

    glBegin(GL_QUADS);

    glVertex2f(28, -4);
    glVertex2f(32, -4);
    glVertex2f(32, -2);
    glVertex2f(28, -2);

    glEnd();
}




// FOOTBALL GOAL POSTS




void FootballGoal()   ///// D23
{
    glColor3ub(245, 245, 245);



    glBegin(GL_QUADS);

    glVertex2f(23, -27);
    glVertex2f(24.2, -27);
    glVertex2f(24.2, -21);
    glVertex2f(23, -21);

    glEnd();



    glBegin(GL_QUADS);

    glVertex2f(35.8, -27);
    glVertex2f(37, -27);
    glVertex2f(37, -21);
    glVertex2f(35.8, -21);

    glEnd();



    glBegin(GL_QUADS);

    glVertex2f(23, -22.2);
    glVertex2f(37, -22.2);
    glVertex2f(37, -21);
    glVertex2f(23, -21);

    glEnd();


    // =================================================
    // BOTTOM GOAL
    // =================================================


    glBegin(GL_QUADS);

    glVertex2f(23, -49);
    glVertex2f(24.2, -49);
    glVertex2f(24.2, -43);
    glVertex2f(23, -43);

    glEnd();



    glBegin(GL_QUADS);

    glVertex2f(35.8, -49);
    glVertex2f(37, -49);
    glVertex2f(37, -43);
    glVertex2f(35.8, -43);

    glEnd();



    glBegin(GL_QUADS);

    glVertex2f(23, -44.2);
    glVertex2f(37, -44.2);
    glVertex2f(37, -43);
    glVertex2f(23, -43);

    glEnd();
}




// =====================================================
// SCHOOL TREES
// =====================================================

void SchoolTrees() ////D24
{
    // =================================================
    // TREE 1
    // =================================================

    // Trunk


    // Leaves
    glColor3ub(34, 139, 34);

    glBegin(GL_TRIANGLES);

    glVertex2f(9.5, 0);
    glVertex2f(13.7, 0);
    glVertex2f(11.6, 4);

    glVertex2f(9.8, 2);
    glVertex2f(13.4, 2);
    glVertex2f(11.6, 6);

    glEnd();
}
void SchoolTrees1() ////D25
{


    // =================================================
    // TREE 2
    // =================================================


    glColor3ub(34, 139, 34);

    glBegin(GL_TRIANGLES);

    glVertex2f(45.5, 0);
    glVertex2f(49.7, 0);
    glVertex2f(47.6, 4);

    glVertex2f(45.8, 2);
    glVertex2f(49.5, 2);
    glVertex2f(47.6, 6);

    glEnd();

}

void SchoolTrees2() ////D26
{


    // =================================================
    // TREE 3 - PLAYGROUND LEFT
    // =================================================

    glColor3ub(101, 67, 33);

    glBegin(GL_QUADS);

    glVertex2f(14, -48);
    glVertex2f(15.2, -48);
    glVertex2f(15.2, -41);
    glVertex2f(14, -41);

    glEnd();

    glColor3ub(34, 139, 34);

    glBegin(GL_TRIANGLES);

    glVertex2f(12.5, -41);
    glVertex2f(16.7, -41);
    glVertex2f(14.6, -37);

    glVertex2f(12.8, -39);
    glVertex2f(16.5, -39);
    glVertex2f(14.6, -35);

    glEnd();
}

void SchoolTrees3() ////D27
{


    // =================================================
    // TREE 4 - PLAYGROUND RIGHT
    // =================================================

    glColor3ub(101, 67, 33);

    glBegin(GL_QUADS);

    glVertex2f(44.8, -48);
    glVertex2f(46, -48);
    glVertex2f(46, -41);
    glVertex2f(44.8, -41);

    glEnd();

    glColor3ub(34, 139, 34);

    glBegin(GL_TRIANGLES);

    glVertex2f(43.3, -41);
    glVertex2f(47.5, -41);
    glVertex2f(45.4, -37);

    glVertex2f(43.5, -39);
    glVertex2f(47.3, -39);
    glVertex2f(45.4, -35);

    glEnd();
}












void ParkArea() /////D28
{
    // =================================================
    // PARK GREEN AREA
    // =================================================

  if(nightMode)
    glColor3ub(10, 40, 15);
else
    glColor3ub(70, 160, 50);

    glBegin(GL_QUADS);

    glVertex2f(-50, -50);
    glVertex2f(-10, -50);
    glVertex2f(-10, -20);
    glVertex2f(-50, -20);

    glEnd();
}

void FOUNTAINBASE() ///// D29
{

    // FOUNTAIN BASE
    // =================================================

    glColor3ub(130, 130, 135);

    glBegin(GL_QUADS);

    glVertex2f(-38, -38);
    glVertex2f(-22, -38);
    glVertex2f(-22, -34);
    glVertex2f(-38, -34);

    glEnd();

}

void FOUNTAINwater() //////D30
{
 glColor3ub(40, 160, 230);

    glBegin(GL_QUADS);

    glVertex2f(-37, -36);
    glVertex2f(-23, -36);
    glVertex2f(-25, -34.5);
    glVertex2f(-35, -34.5);

    glEnd();
}

    // =================================================
    // FOUNTAIN CENTER
    // =================================================
void FOUNTAINcenter() /////D31
{
    glColor3ub(150, 150, 150);

    glBegin(GL_QUADS);

    glVertex2f(-31, -36);
    glVertex2f(-29, -36);
    glVertex2f(-29, -29);
    glVertex2f(-31, -29);

    glEnd();

}
    // =================================================
    // FOUNTAIN WATER STREAM
    // =================================================
void FOUNTAINwaterstream()  ///// D32
{
    glColor3ub(100, 210, 255);

    glBegin(GL_LINES);

    glVertex2f(-30, -29);
    glVertex2f(-32, -34);

    glVertex2f(-30, -29);
    glVertex2f(-30, -34);

    glVertex2f(-30, -29);
    glVertex2f(-28, -34);

    glEnd();

}
    // =================================================
    // BENCH 1
    // =================================================
void Bench1()  //// D33
{
    glColor3ub(139, 69, 19);

    glBegin(GL_QUADS);

    // Seat
    glVertex2f(-47, -30);
    glVertex2f(-41, -30);
    glVertex2f(-41, -29);
    glVertex2f(-47, -29);

    // Back
    glVertex2f(-47, -28);
    glVertex2f(-41, -28);
    glVertex2f(-41, -27);
    glVertex2f(-47, -27);

    glEnd();


    // Legs
    glColor3ub(70, 70, 70);

    glBegin(GL_QUADS);

    glVertex2f(-46, -31);
    glVertex2f(-45.3, -31);
    glVertex2f(-45.3, -30);
    glVertex2f(-46, -30);

    glVertex2f(-42.5, -31);
    glVertex2f(-41.8, -31);
    glVertex2f(-41.8, -30);
    glVertex2f(-42.5, -30);

    glEnd();
}

void Bench2() //////D34
{
    // =================================================
    // BENCH 2
    // =================================================

    glColor3ub(160, 82, 45);

    glBegin(GL_QUADS);

    // Seat
    glVertex2f(-47, -43);
    glVertex2f(-41, -43);
    glVertex2f(-41, -42);
    glVertex2f(-47, -42);

    // Back
    glVertex2f(-47, -41);
    glVertex2f(-41, -41);
    glVertex2f(-41, -40);
    glVertex2f(-47, -40);

    glEnd();
}


    // =================================================
    // DUSTBIN 1
    // =================================================
void Dustbin()  /////D35
{
    glColor3ub(80, 80, 80);

    glBegin(GL_QUADS);

    glVertex2f(-19, -30);
    glVertex2f(-17, -30);
    glVertex2f(-17, -27);
    glVertex2f(-19, -27);

    glEnd();


    // Dustbin top
    glColor3ub(40, 40, 40);

    glBegin(GL_QUADS);

    glVertex2f(-19.3, -27);
    glVertex2f(-16.7, -27);
    glVertex2f(-16.7, -26.5);
    glVertex2f(-19.3, -26.5);

    glEnd();
}


    // =================================================
    // DUSTBIN 2
    // =================================================
void Dustbin2()  ////D36
{
    glColor3ub(80, 80, 80);

    glBegin(GL_QUADS);

    glVertex2f(-45, -47);
    glVertex2f(-43, -47);
    glVertex2f(-43, -44);
    glVertex2f(-45, -44);

    glEnd();
}


    // =================================================
    // FLOWER GARDEN 1
    // =================================================
void FlowerGerden()  /////D37
{
    glColor3ub(100, 60, 30);

    glBegin(GL_QUADS);

    glVertex2f(-20, -48);
    glVertex2f(-12, -48);
    glVertex2f(-12, -46);
    glVertex2f(-20, -46);

    glEnd();
}

void Flowers()  ////// D38
{
    // Flowers
    glColor3ub(255, 80, 80);

    circle(0.5, -19, -45.5, 1, 0, 0);
    circle(0.5, -17, -45.5, 1, 0, 0);
    circle(0.5, -15, -45.5, 1, 0, 0);
    circle(0.5, -13, -45.5, 1, 0, 0);


    // =================================================
    // FLOWER GARDEN 2
    // =================================================

    glColor3ub(100, 60, 30);

    glBegin(GL_QUADS);

    glVertex2f(-49, -24);
    glVertex2f(-42, -24);
    glVertex2f(-42, -22);
    glVertex2f(-49, -22);

    glEnd();
}

void flowers2()   ////// D39
{
    // Flowers
    glColor3ub(255, 220, 0);

    circle(0.5, -48, -21.5, 1, 1, 0);
    circle(0.5, -46, -21.5, 1, 1, 0);
    circle(0.5, -44, -21.5, 1, 1, 0);
}





// =====================================================
// LAMPPOST - ROAD 1
// =====================================================

void Lamppost1(float x, float y)  //// D40
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    // Pole
    glColor3ub(60, 60, 60);

    glBegin(GL_QUADS);

    glVertex2f(-0.4, 0);
    glVertex2f(0.4, 0);
    glVertex2f(0.4, 7);
    glVertex2f(-0.4, 7);

    glEnd();


    // Top horizontal arm
    glBegin(GL_QUADS);

    glVertex2f(0, 6.5);
    glVertex2f(2.5, 6.5);
    glVertex2f(2.5, 7.2);
    glVertex2f(0, 7.2);

    glEnd();


    // Lamp holder
    glColor3ub(40, 40, 40);

    glBegin(GL_QUADS);

    glVertex2f(2.2, 6);
    glVertex2f(3.2, 6);
    glVertex2f(3.2, 7);
    glVertex2f(2.2, 7);

    glEnd();


    // Base
    glColor3ub(45, 45, 45);

    glBegin(GL_QUADS);

    glVertex2f(-0.9, 0);
    glVertex2f(0.9, 0);
    glVertex2f(0.7, -0.7);
    glVertex2f(-0.7, -0.7);

    glEnd();

    glPopMatrix();
}


void Lamppost2(float x, float y)  /////D41
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    // =========================
    // POLE
    // =========================

    glColor3ub(60, 60, 60);

    glBegin(GL_QUADS);

    glVertex2f(-0.4, 0);
    glVertex2f(0.4, 0);
    glVertex2f(0.4, 7);
    glVertex2f(-0.4, 7);

    glEnd();


    // =========================
    // TOP ARM
    // =========================

    glBegin(GL_QUADS);

    glVertex2f(0, 6.5);
    glVertex2f(2.5, 6.5);
    glVertex2f(2.5, 7.2);
    glVertex2f(0, 7.2);

    glEnd();


    // =========================
    // LAMP HOLDER
    // =========================

    glColor3ub(40, 40, 40);

    glBegin(GL_QUADS);

    glVertex2f(2.2, 6);
    glVertex2f(3.2, 6);
    glVertex2f(3.2, 7);
    glVertex2f(2.2, 7);

    glEnd();


    // =========================
    // BASE
    // =========================

    glColor3ub(45, 45, 45);

    glBegin(GL_QUADS);

    glVertex2f(-0.9, 0);
    glVertex2f(0.9, 0);
    glVertex2f(0.7, -0.7);
    glVertex2f(-0.7, -0.7);

    glEnd();

    glPopMatrix();
}



//// traffic light
 // =====================================================
// TRAFFIC LIGHT
// =====================================================

void TrafficLight(float x, float y) ////D42
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    // =========================
    // POLE
    // =========================

    glColor3ub(50, 50, 50);

    glBegin(GL_QUADS);

    glVertex2f(-0.4, 0);
    glVertex2f(0.4, 0);
    glVertex2f(0.4, 7);
    glVertex2f(-0.4, 7);

    glEnd();


    // =========================
    // TRAFFIC LIGHT BOX
    // =========================

    glColor3ub(35, 35, 35);

    glBegin(GL_QUADS);

    glVertex2f(-1.5, 5);
    glVertex2f(1.5, 5);
    glVertex2f(1.5, 9);
    glVertex2f(-1.5, 9);

    glEnd();


    // =========================
    // TOP CAP
    // =========================

    glColor3ub(25, 25, 25);

    glBegin(GL_QUADS);

    glVertex2f(-1.7, 9);
    glVertex2f(1.7, 9);
    glVertex2f(1.4, 9.5);
    glVertex2f(-1.4, 9.5);

    glEnd();


    // =========================
    // BASE
    // =========================

    glColor3ub(40, 40, 40);

    glBegin(GL_QUADS);

    glVertex2f(-1, 0);
    glVertex2f(1, 0);
    glVertex2f(1, -0.7);
    glVertex2f(-1, -0.7);

    glEnd();


    glPopMatrix();
}



// BICYCLE WITH PERSON
// =====================================================

void BicyclePerson(float x, float y) /////D43
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    // =========================
    // BICYCLE WHEELS
    // =========================

    glColor3ub(30, 30, 30);

    circle(1.2, -3, 0, 0.05, 0.05, 0.05);
    circle(1.2, 3, 0, 0.05, 0.05, 0.05);

    // Wheel centers
    circle(0.3, -3, 0, 0.7, 0.7, 0.7);
    circle(0.3, 3, 0, 0.7, 0.7, 0.7);


    // =========================
    // BICYCLE FRAME
    // =========================

    glColor3ub(220, 40, 40);

    glBegin(GL_LINES);

    // Back triangle
    glVertex2f(-3, 0);
    glVertex2f(-1, 2);

    glVertex2f(-1, 2);
    glVertex2f(0, 0);

    glVertex2f(0, 0);
    glVertex2f(-3, 0);

    // Front triangle
    glVertex2f(-1, 2);
    glVertex2f(3, 0);

    glVertex2f(0, 0);
    glVertex2f(3, 0);

    // Handle
    glVertex2f(3, 0);
    glVertex2f(2.7, 2);

    glVertex2f(2.7, 2);
    glVertex2f(3.5, 2);

    // Seat
    glVertex2f(-1, 2);
    glVertex2f(-1.5, 2.3);

    glEnd();


    // =========================
    // PERSON BODY
    // =========================

    glColor3ub(30, 100, 200);

    glBegin(GL_QUADS);

    glVertex2f(-1.3, 3);
    glVertex2f(0.7, 3);
    glVertex2f(1, 5.5);
    glVertex2f(-0.7, 5.5);

    glEnd();


    // =========================
    // PERSON HEAD
    // =========================

    circle(0.9, 0.1, 6.5, 1.0, 0.75, 0.55);


    // =========================
    // PERSON LEGS
    // =========================

    glColor3ub(40, 40, 40);

    glBegin(GL_LINES);

    glVertex2f(-0.5, 3);
    glVertex2f(-1.5, 1);

    glVertex2f(0.5, 3);
    glVertex2f(1.5, 1);

    // =========================
    // PERSON ARMS
    // =========================

    glVertex2f(-0.5, 5);
    glVertex2f(2.5, 2.5);

    glVertex2f(0.7, 5);
    glVertex2f(2.7, 2.8);

    glEnd();


    glPopMatrix();
}

/// keyBoard
void handleKeypress(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'r':
        case 'R':
            vehicleSpeed += 0.5f;
            break;

        case 's':
        case 'S':
            vehicleSpeed = 0.0f;
             trafficState = 0;


            break;

        case 'n':
        case 'N':
            nightMode = !nightMode;
            break;
    }

    glutPostRedisplay();
}


//// mouse


 // =====================================================
// MOUSE INTERACTION
// Click Traffic Light = RED + STOP ALL VEHICLES
// =====================================================

void handleMouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Traffic light RED
        trafficState = 0;

        // Stop all vehicles
        vehicleSpeed = 0.0f;
    }

    glutPostRedisplay();
}




// =====================================================
// PERSON
// =====================================================

void Person(float x, float y) //////D44
{
    glPushMatrix();

    glTranslatef(x, y, 0);
 if(nightMode)
        circle(1.2, 0, 4, 0.863, 0.627, 0.471);
    else
        circle(1.2, 0, 4, 0.216, 0.392, 0.980);

    // HAIR
    if(nightMode)
        circle(1.25, 0, 4.8, 0.098, 0.078, 0.059);
    else
        circle(1.25, 0, 4.8, 0.196, 0.118, 0.196);

    // BODY
    if(nightMode)
        glColor3ub(0.471, 0.118, 0.275);
    else
        glColor3ub(0.863, 0.235, 0.471);

    glBegin(GL_QUADS);
        glVertex2f(-1.2, 3);
        glVertex2f(1.2, 3);
        glVertex2f(1.2, -2);
        glVertex2f(-1.2, -2);
    glEnd();

    // LEFT ARM
    glColor3ub(255, 200, 150);

    glBegin(GL_QUADS);
        glVertex2f(-1.2, 3);
        glVertex2f(-0.5, 2.8);
        glVertex2f(-1.8, -1);
        glVertex2f(-2.3, -0.8);
    glEnd();

    // RIGHT ARM
    glBegin(GL_QUADS);
        glVertex2f(0.5, 2.8);
        glVertex2f(1.2, 3);
        glVertex2f(2.3, -0.8);
        glVertex2f(1.8, -1);
    glEnd();

    // LEFT LEG
    glColor3ub(40, 40, 80);

    glBegin(GL_QUADS);
        glVertex2f(-1, -2);
        glVertex2f(0, -2);
        glVertex2f(-0.2, -6);
        glVertex2f(-1.2, -6);
    glEnd();

    // RIGHT LEG
    glBegin(GL_QUADS);
        glVertex2f(0, -2);
        glVertex2f(1, -2);
        glVertex2f(1.2, -6);
        glVertex2f(0.2, -6);
    glEnd();

    glPopMatrix();
}






// =====================================================
// DISPLAY
// =====================================================

void display()
{
    if(nightMode)
{
    // Night = Lights ON
    glClearColor(0.0, 0.0, 0.0, 1.0);
}
else
{
    // Day = Lights OFF
   glClearColor(0.65, 0.85, 0.95, 1.0);
}


    glClear(GL_COLOR_BUFFER_BIT);
    sky();
   if(nightMode)
{
    // Night
    circle(7.203, 29.86, 42.06, 230, 230, 230);
    Stars();
}
else
{
    // Day
    circle(4.68, -39.95, 44.41, 0.961, 0.961, 0.961);
    circle(3.83, -34.27, 42.61, 0.961, 0.961, 0.961);
    circle(4.71, -31.78, 39.70, 0.961, 0.961, 0.961);

    circle(7.203, 29.86, 42.06, 1.0, 0.706, 0.078);

    airplane();
    Bird();
    Bird1();
Bird2();
Bird3();
}




    Road();
    Road2();
    Road3();

    RoadLine();




    House();
    House2();

    Bench();

    Tree();

ParkArea();
FOUNTAINBASE();
FOUNTAINwater();
FOUNTAINcenter();
FOUNTAINwaterstream();

Bench1();
Bench2();

Dustbin();
Dustbin2();

FlowerGerden();
Flowers();

flowers2();
    // School area
    SchoolArea();

    // School building
    School();
    SmallBuildings();


  SchoolTrees();
  SchoolTrees1();
  SchoolTrees2();
  SchoolTrees3();




// LAMP POSTS

Lamppost1(-30, 20);
Lamppost2(20, 11);
Lamppost2(30, -20);
Lamppost2(-30, -10);
 RoadCar(carMove, 0);
      RoadCar(carMove2, 0);
   RoadCar3(carMove3, -3);


// =========================
// STREET LIGHT
// =========================

if(nightMode)
{
    // Night = Lights ON
    circle(0.769, -27.34, 26.61, 1.0, 1.0, 0.3);
    circle(0.746, 22.74, 17.51, 1.0, 1.0, 0.3);
}
else
{
    if(streetLight < 50)
{
    // Light OFF
    circle(0.769, -27.34, 26.61, 0.3, 0.3, 0.1);
    circle(0.746, 22.74, 17.51, 0.3, 0.3, 0.1);
}
else
{
    // Light ON - Yellow
    circle(0.769, -27.34, 26.61, 1.0, 1.0, 0.3);
    circle(0.746, 22.74, 17.51, 1.0, 1.0, 0.3);
}
}
// =========================
// STREET LIGHT
// =========================


TrafficLight(35, 20);


// =========================
// TRAFFIC LIGHTS
// =========================

// RED LIGHT
if(trafficState == 0)
{
    circle(0.616, 34.99, 28.27,
           1.0, 0.0, 0.0);
}
else
{
    circle(0.616, 34.99, 28.27,
           0.25, 0.0, 0.0);
}


// YELLOW LIGHT
if(trafficState == 1)
{
    circle(0.649, 35.001, 26.91,
           1.0, 1.0, 0.0);
}
else
{
    circle(0.649, 35.001, 26.91,
           0.25, 0.25, 0.0);
}


// GREEN LIGHT
if(trafficState == 2)
{
    circle(0.623, 35.001, 25.52,
           0.0, 1.0, 0.0);
}
else
{
    circle(0.623, 35.001, 25.52,
           0.0, 0.25, 0.0);
}


BicyclePerson(bicycleMove, -17);
BicyclePerson(bicycleMove1, -17);
BicyclePerson(bicycleMove2, -13);

Person(-25, 16);
Person(-35, 16);
Person(5, 3);
Person(-5, -30);
Person(25, 16);
Person(-25,-14);
Person(30,-39);
Tree1();
Tree2();

 FootballGoal();


    glFlush();
}

};

class VillageScene{
public:
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
    glClearColor(0, 0, 0, 1);

    glClear(GL_COLOR_BUFFER_BIT);


    //glScalef(0.5f, 0.5f, 1.0f);



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
    glFlush();
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
    //glutTimerFunc(20, update, 0);
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










};


///variable
NatureView natureview;
VillageFair villagefair;
SmartCity smartcity;
VillageScene villagescene;


void display()//m100
{
    if(natureView){
        natureview.display();
    }
    else if(villageFair){
        villagefair.display();
    }
    else if(smartCity){
        smartcity.display();
    }
    else if(villageScene){
        villagescene.display();
    }
}


void update(int value)//m101
{
    natureview.updateBoat(value);
    natureview.updateCloud(value);
    natureview.updateSmallBoat(value);
    natureview.updatePrivateCar(value);
    natureview.updateVehicleRight(value);
    natureview.updateMoon(value);
    natureview.updateSun(value);
    natureview.updateRain(value);
    natureview.updateWheelRotation(value);


    ///village fiar
    villagefair.update(value);
    villagefair.updateCloud(value);
    villagefair.update(value);

    ///smart city
    smartcity.update(value);

    ///village scene
    villagescene.update(value);




    glutPostRedisplay();

    glutTimerFunc(20,update,0);
}


void Handelkeypress(unsigned char key,int x,int y)//m102
{
    if(key=='6')
    {
        natureView=false;
        villageFair=true;
        smartCity=false;
        villageScene=false;

    }
    else if(key=='7')
    {
        villageFair=false;
        smartCity=true;
        natureView=false;
        villageScene=false;
    }
    else if(key=='8'){
        natureView=true;
        villageScene=false;
        villageFair=false;
        smartCity=false;

    }
    else if(key=='9'){
        villageScene=true;
        villageFair=false;
        smartCity=false;
        natureView=false;
    }

    if(natureView){
        natureview.handleKeypress(key,x,y);
    }
    else if(villageFair){
        villagefair.keyboard(key,x,y);
    }
    else if(smartCity){
        smartcity.handleKeypress(key,x,y);
    }
    else if(villageScene){
        villagescene.handleKeypress(key,x,y);
    }
    glutPostRedisplay();
}

void handleMouse(int button, int state, int x, int y) {//m103
    if (button == GLUT_LEFT_BUTTON)
	   {
          if(natureView){
               natureview.handleMouse(button,state,x,y);
          }
          if(villageFair){
               villagefair.handleMouse(button,state,x,y);
          }
          if(smartCity){
               smartcity.handleMouse(button,state,x,y);
          }
          if(villageScene){
               villagescene.handleMouse(button,state,x,y);
          }



       }
    if (button == GLUT_RIGHT_BUTTON)
	{
	     if(natureView){
               natureview.handleMouse(button,state,x,y);
          }
          if(villageFair){
               villagefair.handleMouse(button,state,x,y);
          }
          if(smartCity){
               smartcity.handleMouse(button,state,x,y);
          }
          if(villageScene){
               villagescene.handleMouse(button,state,x,y);
          }

	}
    glutPostRedisplay();
}

int main(int argc,char** argv)//m104
{
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1000, 560);

    glutCreateWindow("");

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(-50,50,-50,50);


    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();


    natureview.initRain();
    glutDisplayFunc(display);

    glutKeyboardFunc(Handelkeypress);
    glutMouseFunc(handleMouse);


    glutTimerFunc(20,update,0);


    glutMainLoop();

    return 0;
}
