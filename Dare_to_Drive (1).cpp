#include <iostream>
#include <stdlib.h>
#include <math.h>
#include<GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include<string>
#include<sstream>
#define CTRL_COUNT 100

using namespace std;


//Initializes 3D rendering
void initRendering()
{
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glClearColor(0.0, 0.6, 0.0, 0.0);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}


int score = 0, level = 1;
float _angle = 0.0, speed = 0.025;
bool collide = 0;
float dividerX = 0.0, dividerY = 1, move_div=0.0,mov=7,mov_building=8.0;
float cr_m_L_R=0.0,cr_m_U_D=-0.3;
float oppX[10], oppY[10];

bool collision()
{
    for(int i = 0; i<10; i++)
    {
        if(oppX[i] == cr_m_L_R && oppY[i] < cr_m_U_D + 0.2 && oppY[i] > cr_m_U_D - 0.2)
        {
                collide = 1;
                return true;
        }
    }
    return false;
}

void oppPos()
{
    for(int i = 0; i<5; i++)
    {
        if(rand() % 2 == 0)
        {
            oppX[i] = 0.0;
        }
        else
        {
            oppX[i] = 0.5;
        }
    }
    oppY[0] = -1.2;
    oppY[1] = -2.2;
    oppY[2] = -3.2;
    oppY[3] = -4.2;
    oppY[4] = -5.2;
    oppY[5] = -6.2;
    oppY[6] = -7.2;
    oppY[7] = -8.2;
    oppY[8] = -9.2;
    oppY[9] = -10.2;
}

void divider()//black patch drawn in middle of road
 {
       //glRotatef(5, -1.0, 0.0, 0.0);
        glTranslatef(0.0, move_div, 0.1);


    for(int i = 0; i <= 80; i++)
    {
          glColor3f(0, 0, 0);

        glBegin(GL_POLYGON);
        glVertex2f(dividerX  - 0.03, dividerY *0.15*i-0.05);
        glVertex2f(dividerX  + 0.03, dividerY *0.15*i-0.05);
        glVertex2f(dividerX  + 0.03, dividerY*0.15*i+0.05);
        glVertex2f(dividerX  - 0.03, dividerY *0.15*i+0.05);


        glEnd();

    }

    for(int i = 0; i <= 80; i++)
    {
        glColor3f(1, 1, 1);
        glBegin(GL_POLYGON);
        glVertex2f(dividerX  - 0.65, dividerY *0.15*i-0.05);
        glVertex2f(dividerX  - 0.6, dividerY *0.15*i-0.05);
        glVertex2f(dividerX  - 0.6, dividerY*0.15*i+0.05);
        glVertex2f(dividerX  - 0.65, dividerY *0.15*i+0.05);
        glEnd();
        dividerX -0.1;

    }
    for(int i = 0; i <= 80; i++)
    {
        glColor3f(1, 1, 1);
        glBegin(GL_POLYGON);
        glVertex2f(dividerX  + 0.65, dividerY *0.15*i-0.05);
        glVertex2f(dividerX  + 0.6, dividerY *0.15*i-0.05);
        glVertex2f(dividerX  + 0.6, dividerY*0.15*i+0.05);
        glVertex2f(dividerX  + 0.65, dividerY *0.15*i+0.05);
        glEnd();
        dividerX -0.1;

    }

    glLoadIdentity();
 }

void Specialkey(int key, int x, int y)
 {
 switch(key)
 {
 case GLUT_KEY_UP:
 {
       if(cr_m_U_D <7)
       {
             cr_m_U_D+=0.03;
       }
            break;
 }
 case GLUT_KEY_DOWN:
 {
       if(cr_m_U_D >-0.2)
       {
             cr_m_U_D-=0.03;
       }
            break;
 }
 case GLUT_KEY_LEFT:cr_m_L_R = 0.0;
        break;
 case GLUT_KEY_RIGHT:cr_m_L_R = 0.5;
        break;
 }

    glutPostRedisplay();

 }

void car()
 {
      glPushMatrix();

      glTranslatef(cr_m_L_R, cr_m_U_D,0.0);

      glPushMatrix();
      glTranslatef(-0.25, 0.1,0.55);
      glColor3f(0.3,0.8,0.6);
      glScalef(0.9,1.3,0.3);
      glutSolidCube(0.3);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-0.25, 0.03,0.64);
      glColor3f(0.8,0.0,0.0);
      glScalef(0.9,0.7,0.3);
      glutSolidCube(0.3);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-0.25, 0.0,0.7);
      glColor3f(0.0,0.0,0.0);
      glScalef(0.7,0.2,0.08);
      glutSolidCube(0.3);
      glPopMatrix();

//Tires
      glColor3f(0.1,0.1,0.1);
      glPushMatrix();
      glTranslatef(-0.1, 0.2,0.54);
      glRotatef(90,0.0,1.0,0.0);
      glRotatef(_angle,0.0,0.0,1.0);

      glutWireTorus(0.017,0.04,40,40);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-0.4, 0.2,0.54);
      glRotatef(90,0.0,1.0,0.0);
      glRotatef(_angle,0.0,0.0,1.0);

      glutWireTorus(0.017,0.04,40,40);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-0.4, -0.05,0.54);
      glRotatef(90,0.0,1.0,0.0);
      glRotatef(_angle,0.0,0.0,1.0);

      glutWireTorus(0.017,0.04,40,40);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-0.1, -0.05,0.54);
      glRotatef(90,0.0,1.0,0.0);
      glRotatef(_angle,0.0,0.0,1.0);

      glutWireTorus(0.017,0.04,40,40);
      glPopMatrix();

      glPopMatrix();
 }

 void obstecal()
 {
        glPushMatrix();
        glTranslatef(-0.25, 0.1,0.55);
        glColor3f(0.3,0.0,0.6);
        glScalef(0.9,1.3,0.3);
        glutSolidCube(0.3);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.25, 0.03,0.64);
        glColor3f(0.4,0.0,0.5);
        glScalef(0.9,0.7,0.3);
        glutSolidCube(0.3);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.25, 0.0,0.7);
        glColor3f(0.0,0.0,0.0);
        glScalef(0.7,0.2,0.08);
        glutSolidCube(0.3);
        glPopMatrix();

//Tires
      glColor3f(0.1,0.1,0.1);
      glPushMatrix();
      glTranslatef(-0.1, 0.2,0.54);
      glRotatef(90,0.0,1.0,0.0);
      glRotatef(_angle,0.0,0.0,1.0);

      glutWireTorus(0.017,0.04,40,40);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-0.4, 0.2,0.54);
      glRotatef(90,0.0,1.0,0.0);
      glRotatef(_angle,0.0,0.0,1.0);

      glutWireTorus(0.017,0.04,40,40);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-0.4, -0.05,0.54);
      glRotatef(90,0.0,1.0,0.0);
      glRotatef(_angle,0.0,0.0,1.0);

      glutWireTorus(0.017,0.04,40,40);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-0.1, -0.05,0.54);
      glRotatef(90,0.0,1.0,0.0);
      glRotatef(_angle,0.0,0.0,1.0);

      glutWireTorus(0.017,0.04,40,40);
      glPopMatrix();
 }

 void Horizon()
 {
	glPushMatrix();
	glTranslatef(0.0, 0.9, -7.0);

      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_POLYGON);
	glVertex2f(-6.5, 2.9);
      glVertex2f(-6.5, 3.8);
      glVertex2f(-5.7, 3.8);
      glVertex2f(-5.7, 2.9);
      glEnd();

      glColor3f(0.6, 0.8, 0.2);
      glBegin(GL_POLYGON);
	glVertex2f(-6.6, 2.9);
      glVertex2f(-6.6, 3.6);
      glVertex2f(-7.1, 3.6);
      glVertex2f(-7.1, 2.9);
      glEnd();

      glColor3f(0.3, 0.0, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(-5.2, 2.9);
      glVertex2f(-5.2, 3.6);
      glVertex2f(-4.7, 3.6);
      glVertex2f(-4.7, 2.9);
      glEnd();

      glColor3f(0.8, 0.4, 0.0);
      glBegin(GL_POLYGON);
	glVertex2f(-4.7, 2.9);
      glVertex2f(-4.7, 3.8);
      glVertex2f(-4.0, 3.8);
      glVertex2f(-4.0, 2.9);
      glEnd();

      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_POLYGON);
	glVertex2f(-4.0, 2.9);
      glVertex2f(-4.0, 3.4);
      glVertex2f(-3.5, 3.4);
      glVertex2f(-3.5, 2.9);
      glEnd();
      glColor3f(0.0, 0.5, 1.0);
      glBegin(GL_POLYGON);
	glVertex2f(-3.5, 2.9);
      glVertex2f(-3.5, 3.5);
      glVertex2f(-3.0, 3.5);
      glVertex2f(-3.0, 2.9);
      glEnd();

      glColor3f(1.0, 0.0, 0.8);
      glBegin(GL_POLYGON);
	glVertex2f(-2.5, 2.9);
      glVertex2f(-2.5, 3.8);
      glVertex2f(-1.7, 3.8);
      glVertex2f(-1.7, 2.9);
      glEnd();

      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_POLYGON);
	glVertex2f(-2.5, 3.05);
      glVertex2f(-2.75, 3.3);
      glVertex2f(-2.75, 3.3);
      glVertex2f(-3.0, 3.05);
      glEnd();
      glColor3f(1.0, 0.8, 0.2);
      glBegin(GL_POLYGON);
	glVertex2f(-2.9, 2.9);
      glVertex2f(-2.9, 3.1);
      glVertex2f(-2.6, 3.1);
      glVertex2f(-2.6, 2.9);
      glEnd();

      glColor3f(0.6, 0.0, 0.0);
      glBegin(GL_POLYGON);
	glVertex2f(-1.7, 2.9);
      glVertex2f(-1.7, 3.6);
      glVertex2f(-1.2, 3.6);
      glVertex2f(-1.2, 2.9);
      glEnd();

      glColor3f(0.0, 0.8, 0.0);
      glBegin(GL_POLYGON);
	glVertex2f(-1.2, 2.9);
      glVertex2f(-1.2, 3.2);
      glVertex2f(-0.8, 3.2);
      glVertex2f(-0.8, 2.9);
      glEnd();

      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_POLYGON);
	glVertex2f(6.5, 2.9);
      glVertex2f(6.5, 3.8);
      glVertex2f(5.7, 3.8);
      glVertex2f(5.7, 2.9);
      glEnd();

      glColor3f(0.4, 0.0, 0.2);
      glBegin(GL_POLYGON);
	glVertex2f(6.6, 2.9);
      glVertex2f(6.6, 3.6);
      glVertex2f(7.1, 3.6);
      glVertex2f(7.1, 2.9);
      glEnd();

      glColor3f(1.0, 0.8, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(5.2, 2.9);
      glVertex2f(5.2, 3.6);
      glVertex2f(4.7, 3.6);
      glVertex2f(4.7, 2.9);
      glEnd();

      glColor3f(0.8, 0.8, 0.8);
      glBegin(GL_POLYGON);
	glVertex2f(4.7, 2.9);
      glVertex2f(4.7, 3.8);
      glVertex2f(4.0, 3.8);
      glVertex2f(4.0, 2.9);
      glEnd();

      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_POLYGON);
	glVertex2f(4.0, 2.9);
      glVertex2f(4.0, 3.4);
      glVertex2f(3.5, 3.4);
      glVertex2f(3.5, 2.9);
      glEnd();
      glColor3f(1.0, 0.8, 0.2);
      glBegin(GL_POLYGON);
	glVertex2f(3.5, 2.9);
      glVertex2f(3.5, 3.5);
      glVertex2f(3.0, 3.5);
      glVertex2f(3.0, 2.9);
      glEnd();

      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_POLYGON);
	glVertex2f(2.5, 3.05);
      glVertex2f(2.75, 3.3);
      glVertex2f(2.75, 3.3);
      glVertex2f(3.0, 3.05);
      glEnd();
      glColor3f(1.0, 0.0, 0.0);
      glBegin(GL_POLYGON);
	glVertex2f(2.9, 2.9);
      glVertex2f(2.9, 3.1);
      glVertex2f(2.6, 3.1);
      glVertex2f(2.6, 2.9);
      glEnd();

      glColor3f(0.0, 0.4, 0.8);
      glBegin(GL_POLYGON);
	glVertex2f(2.5, 2.9);
      glVertex2f(2.5, 3.8);
      glVertex2f(1.7, 3.8);
      glVertex2f(1.7, 2.9);
      glEnd();

      glColor3f(0.5, 0.5, 0.5);
      glBegin(GL_POLYGON);
	glVertex2f(1.7, 2.9);
      glVertex2f(1.7, 3.6);
      glVertex2f(1.2, 3.6);
      glVertex2f(1.2, 2.9);
      glEnd();
      glColor3f(1.0, 1.0, 0.2);
      glBegin(GL_POLYGON);
	glVertex2f(1.2, 2.9);
      glVertex2f(1.2, 3.4);
      glVertex2f(0.8, 3.4);
      glVertex2f(0.8, 2.9);
      glEnd();

      glColor3f(0.8, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-9.0, 2.9);
	glVertex2f(-9.0, 5.0);
      glVertex2f(9.0, 2.9);
      glVertex2f(9.0, 5.0);
      glEnd();

      glColor3f(0.6, 0.3, 0.0);
	glBegin(GL_POLYGON);
      glVertex2f(-9.0, 2.9);
      glVertex2f(-9.0, 2.8);
      glVertex2f(-0.55, 2.8);
      glVertex2f(-0.55, 2.9);
      glEnd();
      glBegin(GL_POLYGON);
      glVertex2f(9.0, 2.9);
      glVertex2f(9.0, 2.8);
      glVertex2f(0.55, 2.8);
      glVertex2f(0.55, 2.9);
      glEnd();
      glPopMatrix();
}

void Road()
{
	glPushMatrix();
	glBegin(GL_QUADS);
      glColor3f(0.5,0.5,0.5);
      glVertex2f(-0.7, -0.2);
      glVertex2f(0.7, -0.2);
      glVertex2f(0.7, 12);
      glVertex2f(-0.7,12);
      glEnd();
      divider();
      glPopMatrix();
}

void Buildings()
{
      glTranslatef(0.0,mov_building,0.0);
            glPushMatrix();
            glTranslatef(-1.5,0.8,0.0);
            glPushMatrix();
            glColor3f(0.25,0.25,0.25);
            glScalef(1.5,2.8,3.5);
            glutSolidCube(0.3);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0.0,0.0,0.0);
            glTranslatef(0.2,0.3,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,-0.3);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,0.6);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glPopMatrix();
            glPopMatrix();

/*
            glPushMatrix();
            glTranslatef(-1.5,4.8,0.0);
            glPushMatrix();
            glColor3f(0.1,0.0,0.2);
            glScalef(1.5,2.8,3.5);
            glutSolidCube(0.3);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0.0,0.0,0.0);
            glTranslatef(0.2,0.3,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,-0.3);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,0.6);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-1.5,9.8,0.0);
            glPushMatrix();
            glColor3f(0.6,0.3,0.0);
            glScalef(1.5,2.8,3.5);
            glutSolidCube(0.3);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0.0,0.0,0.0);
            glTranslatef(0.2,0.3,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,-0.3);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,0.6);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-1.5,13.8,0.0);
            glPushMatrix();
            glColor3f(1.0,0.2,0.2);
            glScalef(1.5,2.8,3.5);
            glutSolidCube(0.3);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0.0,0.0,0.0);
            glTranslatef(0.2,0.3,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,-0.3);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,0.6);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-1.5,18.8,0.0);
            glPushMatrix();
            glColor3f(0.8,0.6,0.0);
            glScalef(1.5,2.8,3.5);
            glutSolidCube(0.3);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0.0,0.0,0.0);
            glTranslatef(0.2,0.3,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,-0.3);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,0.6);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glPopMatrix();
            glPopMatrix();
*/
            glPushMatrix();
            glTranslatef(1.5,0.8,0.0);
            glPushMatrix();
            glColor3f(0.0,0.6,0.6);
            glScalef(1.5,2.8,3.5);
            glutSolidCube(0.3);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0.0,0.0,0.0);
            glTranslatef(-0.2,0.3,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,-0.3);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,0.6);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glPopMatrix();
            glPopMatrix();
}
            /*
            glPushMatrix();
            glTranslatef(1.5,4.8,0.0);
            glPushMatrix();
            glColor3f(0.8,0.8,0.0);
            glScalef(1.5,2.8,3.5);
            glutSolidCube(0.3);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0.0,0.0,0.0);
            glTranslatef(-0.2,0.3,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,-0.3);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,0.6);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(1.5,9.8,0.0);
            glPushMatrix();
            glColor3f(0.4,0.4,0.0);
            glScalef(1.5,2.8,3.5);
            glutSolidCube(0.3);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0.0,0.0,0.0);
            glTranslatef(-0.2,0.3,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,-0.3);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,0.6);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(1.5,13.8,0.0);
            glPushMatrix();
            glColor3f(0.4,0.0,0.4);
            glScalef(1.5,2.8,3.5);
            glutSolidCube(0.3);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0.0,0.0,0.0);
            glTranslatef(-0.2,0.3,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,-0.3);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,0.6);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(1.5,18.8,0.0);
            glPushMatrix();
            glColor3f(0.87,0.87,0.87);
            glScalef(1.5,2.8,3.5);
            glutSolidCube(0.3);
            glPopMatrix();
            glPushMatrix();
            glColor3f(0.0,0.0,0.0);
            glTranslatef(-0.2,0.3,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,-0.3);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.5,0.0);
            glutSolidCube(0.1);
            glTranslatef(0.0,0.0,0.6);
            glutSolidCube(0.1);
            glTranslatef(0.0,-0.5,0.0);
            glutSolidCube(0.1);
            glPopMatrix();
            glPopMatrix();

}
*/
void rendertext(float x,float y, string strings)
{

    glColor3f(0.0,0.0,0.0);
    glRasterPos2d(x,y);
    glDisable(GL_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    for(int i=0;i<=strings.length();i++)
      {
         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,(int)strings[i]);
      }
    glEnable(GL_TEXTURE);
    glEnable(GL_TEXTURE_2D);

}

 void update1(int i)
 {
    exit(0);
 }

void score_display()
{
    glutTimerFunc(3000,update1,0);
}
//Draws the 3D scene
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

        if(collision())
        {
            glTranslatef(0.0, 0.0, -2.2);
            glClearColor(0.5,0.5,0.5,1.0);
            glPushMatrix();
            string sf="Game Over";
            rendertext(-0.2,0.0,sf);
            glPopMatrix();
            glPushMatrix();
            sf="Score";
            rendertext(-0.2,-0.1,sf);
            glPopMatrix();
            glPushMatrix();
            stringstream ss;
            ss << score;
            sf=ss.str();
            rendertext(0.0,-0.1,sf);
            glPopMatrix();
            glutDisplayFunc(score_display);
            glutIdleFunc(score_display);
        }
        else
        {
            glTranslatef(0.0, -0.9, -2.2);

            glPushMatrix();
            glTranslatef(0.0, 0.0, -2.2);
            string sf="Score :";
            rendertext(-2.5,2.0,sf);
            glPopMatrix();
            score++;
            glPushMatrix();
            glTranslatef(0.0,0.0, -2.2);
            stringstream ss;
            ss << score;
            sf=ss.str();
            rendertext(-2.0,2.0,sf);
            glPopMatrix();
            if(score%350 == 0)
            {
                speed +=0.0015;
                level += 1;
            }
            glPushMatrix();
            glTranslatef(0.0, -0.08, -2.2);
            sf="Level :";
            rendertext(-2.5,2.0,sf);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0.0,-0.08, -2.2);
            stringstream sl;
            sl << level;
            sf=sl.str();
            rendertext(-2.0,2.0,sf);
            glPopMatrix();
            Horizon();
            glRotatef(65, -1.0, 0.0, 0.0);
            Road();
             for(int i = 0; i < 10; i++)
            {
                oppY[i] -= speed;
                if (oppY[i] <= -10.2)
                {
                    oppY[i] = 7;
                    if(rand() % 2 == 0)
                    {
                        oppX[i] = 0.0;
                    }
                    else
                    {
                        oppX[i] = 0.5;
                    }
                }
                glPushMatrix();
                glTranslatef(oppX[i], oppY[i],0.0);
                obstecal();
                glPopMatrix();
            }
            car();
            Buildings();
        }
        glutSwapBuffers();
}

void update(int value)
 {

	_angle += 5.0f;
	if (_angle > 360)
    {
		_angle -= 360;
	}

	move_div = move_div - speed;
    if(move_div <- 0.9)
    {
        move_div = 0;
    }
     mov_building = mov_building - 0.08;
      if(mov_building<-6)
        {
              mov_building = 7.5;
        }

        glutPostRedisplay();
        glutTimerFunc(25, update, 0);

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(100,100);

	glutCreateWindow("Project");
	oppPos();
	initRendering();
    glutDisplayFunc(drawScene);

	glutReshapeFunc(handleResize);
    glutSpecialFunc(Specialkey);
	glutIdleFunc(drawScene);

	glutTimerFunc(25, update, 0);
     glutMainLoop();

	return 0;
}








