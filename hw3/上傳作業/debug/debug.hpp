#pragma once
#include <GL/glut.h>
#include<iostream>
#include<cmath> 
/*----------------------------------------------------------
 * Procedure to initialize the working environment.
 */
float   eyeDx=0.0, eyeDy=0.0, eyeDz=0.0;
float   eyeAngx=0.0, eyeAngy=0.0, eyeAngz=0.0;
double  Eye[3]={0.0, 0.0, 30.0}, Focus[3]={0.0, 0.0, 0.0}, 
        Vup[3]={0.0, 1.0, 0.0};

float   u[3][3]={{1.0,0.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0}};
float   eye[3];
float   cv, sv; /* cos(5.0) and sin(5.0) */
// #include <../robot/robot.hpp>
void draw_axes() {
  glPushMatrix();
  glScaled(1, 1, 1);
  GLUquadricObj *sphere = gluNewQuadric();
  GLUquadricObj *cylind = gluNewQuadric();

  /*----Draw a white sphere to represent the original-----*/
  glColor3f(0.9, 0.9, 0.9);

  gluSphere(sphere, 2.0, /* radius=2.0 */
            12,          /* composing of 12 slices*/
            12);         /* composing of 8 stacks */

  /*----Draw three axes in colors, yellow, meginta, and cyan--*/
  /* Draw Z axis  */
  glColor3f(0.0, 0.95, 0.95);
  gluCylinder(cylind, 0.5, 0.5, /* radius of top and bottom circle */
              10.0,             /* height of the cylinder */
              12,               /* use 12-side polygon approximating circle*/
              3);               /* Divide it into 3 sections */

  /* Draw Y axis */
  glPushMatrix();
  glRotatef(-90.0, 1.0, 0.0, 0.0); /*Rotate about x by -90', z becomes y */
  glColor3f(0.95, 0.0, 0.95);
  gluCylinder(cylind, 0.5, 0.5, /* radius of top and bottom circle */
              10.0,             /* height of the cylinder */
              12,               /* use 12-side polygon approximating circle*/
              3);               /* Divide it into 3 sections */
  glPopMatrix();

  /* Draw X axis */
  glColor3f(0.95, 0.95, 0.0);
  glPushMatrix();
  glRotatef(90.0, 0.0, 1.0, 0.0); /*Rotate about y  by 90', x becomes z */
  gluCylinder(cylind, 0.5, 0.5,   /* radius of top and bottom circle */
              10.0,               /* height of the cylinder */
              12,                 /* use 12-side polygon approximating circle*/
              3);                 /* Divide it into 3 sections */
  glPopMatrix();
  /*-- Restore the original modelview matrix --*/
  glPopMatrix();
}



void draw_Perspective(float fovy, float aspect, float near, float far) {
  glPushMatrix();
  glTranslated(eye[0], eye[1], eye[2]);
  GLdouble *m = new GLdouble[16];
  m[0] = u[0][0];
  m[1] = u[0][1];
  m[2] = u[0][2];
  m[3] = 0.0;
  m[4] = u[1][0];
  m[5] = u[1][1];
  m[6] = u[1][2];
  m[7] = 0.0;
  m[8] = u[2][0];
  m[9] = u[2][1];
  m[10] = u[2][2];
  m[11] = 0.0;
  m[12] = 0.0;
  m[13] = 0.0;
  m[14] = 0.0;
  m[15] = 1.0;
  glMultMatrixd(m);
  // glRotated(90, 1, 0, 0);
  // glTranslated(0, -10, 0);
  // float fovx = fovy * aspect;
  draw_axes();
  float top = near * tan(fovy * M_PI / 360.0) ;
  float bottom = -top;
  float right = top * aspect;
  float left = -right;
  float ftop = far * tan(fovy * M_PI / 360.0);
  float fbottom = -ftop;
  float fright = ftop * aspect;
  float fleft = -fright;
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  {
  glBegin(GL_QUADS);

  glVertex3f(left, bottom, -near);
  glVertex3f(right, bottom, -near);
  glVertex3f(right, top, -near);
  glVertex3f(left, top, -near);

  glVertex3f(fleft, fbottom, -far);
  glVertex3f(fright, fbottom, -far);
  glVertex3f(fright, ftop, -far);
  glVertex3f(fleft, ftop, -far);

  glVertex3f(left, bottom, -near);
  glVertex3f(right, bottom, -near);
  glVertex3f(fright, fbottom, -far);
  glVertex3f(fleft, fbottom, -far);

  glVertex3f(left, top, -near);
  glVertex3f(right, top, -near);
  glVertex3f(fright, ftop, -far);
  glVertex3f(fleft, ftop, -far);

  glVertex3f(left, bottom, -near);
  glVertex3f(left, top, -near);
  glVertex3f(fleft, ftop, -far);
  glVertex3f(fleft, fbottom, -far);

  glVertex3f(right, bottom, -near);
  glVertex3f(right, top, -near);
  glVertex3f(fright, ftop, -far);
  glVertex3f(fright, fbottom, -far);

  
  glEnd();
  }
  {
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(top, right, -near);
    glVertex3f(0, 0, 0);
    glVertex3f(right, bottom, -near);
    glVertex3f(0, 0, 0);
    glVertex3f(left, bottom, -near);
    glVertex3f(0, 0, 0);
    glVertex3f(left, top, -near);
    glEnd();
  }
  glPopMatrix();
}
