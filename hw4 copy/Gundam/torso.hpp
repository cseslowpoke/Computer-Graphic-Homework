
#include "allmaterial.hpp"
#include <GLUT/glut.h>
#include <cmath>
#include <iostream>
namespace gundam {
class torso {
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();
  const double PI = 3.14159265358979323846;
  float point[8][3] = {{0.5, 0, 0.5},  {0.5, 0, -0.5},  {-0.5, 0, -0.5},
                       {-0.5, 0, 0.5}, {0.5, -3, -0.5}, {-0.5, -3, -0.5},
                       {0.5, -3, 0.5}, {-0.5, -3, 0.5}};
  int face[6][4] = {{0, 1, 2, 3}, {1, 2, 5, 4}, {0, 3, 7, 6},
                    {0, 1, 4, 6}, {2, 3, 7, 5}, {6, 7, 5, 4}};
  float normal[6][3] = {{0, 0, 1},  {0, 1, 0}, {0, 0, -1},
                        {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}};
  float point2[12][3] = {{0, 0, 2},   {0, 0, -1},  {5, 0, 5},    {5, 0, 4},
                         {-5, 0, 5},  {-5, 0, 4},  {0, 0.3, 2},  {0, 0.3, -1},
                         {5, 0.3, 5}, {5, 0.3, 4}, {-5, 0.3, 5}, {-5, 0.3, 4}};
  int face2[10][4] = {{0, 1, 3, 2}, {1, 0, 4, 5},  {6, 8, 9, 7}, {6, 7, 11, 10},
                      {0, 2, 8, 6}, {0, 6, 10, 4}, {1, 7, 9, 3}, {1, 5, 11, 7},
                      {2, 3, 9, 8}, {4, 10, 11, 5}};
  float normal2[10][3];

public:
  torso() {
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluQuadricTexture(cylinder, GL_TRUE);

    for (int i = 0; i < 6; i++) {
      // find cross product of two vectors
      float v1[3] = {point[face[i][2]][0] - point[face[i][1]][0],
                     point[face[i][2]][1] - point[face[i][1]][1],
                     point[face[i][2]][2] - point[face[i][1]][2]};
      float v2[3] = {point[face[i][0]][0] - point[face[i][1]][0],
                     point[face[i][0]][1] - point[face[i][1]][1],
                     point[face[i][0]][2] - point[face[i][1]][2]};
      float cross[3] = {v1[1] * v2[2] - v1[2] * v2[1],
                        v1[2] * v2[0] - v1[0] * v2[2],
                        v1[0] * v2[1] - v1[1] * v2[0]};
      normal[i][0] = cross[0];
      normal[i][1] = cross[1];
      normal[i][2] = cross[2];
    }

    for (int i = 0; i < 10; i++) {
      float v1[3] = {point2[face2[i][2]][0] - point2[face2[i][1]][0],
                     point2[face2[i][2]][1] - point2[face2[i][1]][1],
                     point2[face2[i][2]][2] - point2[face2[i][1]][2]};
      float v2[3] = {point2[face2[i][0]][0] - point2[face2[i][1]][0],
                     point2[face2[i][0]][1] - point2[face2[i][1]][1],
                     point2[face2[i][0]][2] - point2[face2[i][1]][2]};
      float cross[3] = {v1[1] * v2[2] - v1[2] * v2[1],
                        v1[2] * v2[0] - v1[0] * v2[2],
                        v1[0] * v2[1] - v1[1] * v2[0]};
      normal2[i][0] = cross[0];
      normal2[i][1] = cross[1];
      normal2[i][2] = cross[2];
    }
  }
  void draw() {
    glPushMatrix();
    green_material();
    glRotated(-90, 1, 0, 0);
    {
      glPushMatrix();
      glTranslated(0, 0, 4);
      glNormal3d(0, 0, 1);
      glBegin(GL_POLYGON);
      for (int i = 0; i < 36; i++) {
        glVertex3f(3 * cos(2 * PI / 36 * i), 3 * sin(2 * PI / 36 * i), 0);
      }
      glEnd();
      glPopMatrix();
    }
    {
      glPushMatrix();
      for (float i = 2.5; i < 3; i += 0.05) {
        gluCylinder(cylinder, i, i, (double)2, 10, 10);
        glNormal3d(0, 0, 1);
        glBegin(GL_POLYGON);
        for (int j = 0; j < 36; j++) {
          glVertex3f(i * cos(2 * PI / 36 * j), i * sin(2 * PI / 36 * j), 0);
        }
        glEnd();
        glTranslated(0, 0, 0.2);
      }
      glPopMatrix();
    }
    {
      glPushMatrix();
      glRotated(180, 1, 0, 0);
      white_material();
      gluCylinder(cylinder, 2, 2, 1.5, 10, 10);
      glTranslated(0, 0, 1.5);
      green_material();
      glNormal3d(0, 0, 1);
      glBegin(GL_POLYGON);
      for (int i = 0; i < 36; i++) {
        glVertex3f(2.5 * cos(2 * PI / 36 * i), 2.5 * sin(2 * PI / 36 * i), 0);
      }
      glEnd();
      gluCylinder(cylinder, 2.5, 2.5, 1.5, 10, 10);
      for (float i = 2.5; i > 1.5; i -= 0.2) {
        glTranslated(0, 0, 0.2);
        gluCylinder(cylinder, i, i, (double)2, 10, 10);
      }
      glNormal3d(0, 0, 1);
      glBegin(GL_POLYGON);
      for (int i = 0; i < 36; i++) {
        glVertex3f(1.5 * cos(2 * PI / 36 * i), 1.5 * sin(2 * PI / 36 * i), 0);
      }
      glEnd();
      glPopMatrix();
    }
    {
      glPushMatrix();
      glTranslated(0, 0, 2);

      green_material();
      for (int i = 0; i < 6; i++) {
        glNormal3fv(normal[i]);
        glBegin(GL_POLYGON);
        for (int j = 0; j < 4; j++) {
          glVertex3f(point[face[i][j]][0], point[face[i][j]][1],
                     point[face[i][j]][2]);
        }
        glEnd();
      }
      {
        glPushMatrix();
        glTranslated(-1.5, 0, 0);
        glRotated(90, 1, 0, 0);
        green_material();
        gluCylinder(cylinder, 0.5, 0.5, 3, 10, 10);
        glTranslated(0, 0, 3);
        glNormal3d(0, 0, 1);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 36; i++) {
          glVertex3f(0.5 * cos(2 * PI / 36 * i), 0.5 * sin(2 * PI / 36 * i), 0);
        }
        glEnd();
        glTranslated(0, 0, 0.01);
        orange_material();
        glNormal3d(0, 0, 1);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 36; i++) {
          glVertex3f(0.3 * cos(2 * PI / 36 * i), 0.3 * sin(2 * PI / 36 * i), 0);
        }
        glEnd();
        // draw_axes();
        glPopMatrix();
      }
      {
        glPushMatrix();
        glTranslated(1.5, 0, 0);
        glRotated(90, 1, 0, 0);
        green_material();
        gluCylinder(cylinder, 0.5, 0.5, 3, 10, 10);
        glTranslated(0, 0, 3);
        glBegin(GL_POLYGON);
        glNormal3d(0, 0, 1);
        for (int i = 0; i < 36; i++) {
          glVertex3f(0.5 * cos(2 * PI / 36 * i), 0.5 * sin(2 * PI / 36 * i), 0);
        }
        glEnd();
        glTranslated(0, 0, 0.01);
        orange_material();
        glNormal3d(0, 0, 1);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 36; i++) {
          glVertex3f(0.3 * cos(2 * PI / 36 * i), 0.3 * sin(2 * PI / 36 * i), 0);
        }
        glEnd();
        // draw_axes();
        glPopMatrix();
      }
      glPopMatrix();
    }
    {
      glPushMatrix();
      green_material();
      glTranslated(0, 3, 2);
      for (int i = 0; i < 10; i++) {
        glNormal3fv(normal2[i]);
        glBegin(GL_POLYGON);
        for (int j = 0; j < 4; j++) {
          glVertex3f(point2[face2[i][j]][0], point2[face2[i][j]][1],
                     point2[face2[i][j]][2]);
        }
        glEnd();
      }
      {
        glPushMatrix();
        glTranslated(0.7, 0.5, -1.5);
        // draw_axes();
        green_material();
        gluCylinder(cylinder, 0.5, 0.5, 4, 10, 10);
        glTranslated(0, 0, 4);
        gluSphere(sphere, 0.5, 10, 10);
        glPopMatrix();
      }
      {
        glPushMatrix();
        glTranslated(-0.7, 0.5, -1.5);
        green_material();
        gluCylinder(cylinder, 0.5, 0.5, 4, 10, 10);
        glTranslated(0, 0, 4);
        gluSphere(sphere, 0.5, 10, 10);
        glPopMatrix();
      }
      glPopMatrix();
    }
    glPopMatrix();
  }
    // glLightfv(GL_LIGHT3, GL_POSITION, pos);
    // glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir);
    // glLightfv(GL_LIGHT2, GL_POSITION, pos);
    // glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir);
    // glEnable(GL_LIGHTING);
    // return;
  void draw_light() {
    glDisable(GL_LIGHTING);
    float pos[4] = {0, 0, 0, 1};
    float dir[4] = {0, 0, 1, 1};
    glPushMatrix();
    glRotated(-90, 1, 0, 0);
    {
      glPushMatrix();
      glTranslated(0, 0, 2);
      {
        glPushMatrix();
        glTranslated(-1.5, 0, 0);
        glRotated(90, 1, 0, 0);
        glTranslated(0, 0, 3);
        glTranslated(0, 0, 0.01);
        glColor3f(0.8, 0.4, 0);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 36; i++) {
          glVertex3f(0.3 * cos(2 * PI / 36 * i), 0.3 * sin(2 * PI / 36 * i), 0);
        }
        glEnd();
        glLightfv(GL_LIGHT2, GL_POSITION, pos);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir);
        glPopMatrix();
      }
      {
        glPushMatrix();
        glTranslated(1.5, 0, 0);
        glRotated(90, 1, 0, 0);
        glTranslated(0, 0, 3);
        glTranslated(0, 0, 0.01);
        glColor3f(0.8, 0.4, 0);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 36; i++) {
          glVertex3f(0.3 * cos(2 * PI / 36 * i), 0.3 * sin(2 * PI / 36 * i), 0);
        }
        glEnd();
        glLightfv(GL_LIGHT3, GL_POSITION, pos);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir);
        glPopMatrix();
      }
      glPopMatrix();
    }
    glPopMatrix();
    glEnable(GL_LIGHTING);
  }
};
} // namespace gundam