
#include "allmaterial.hpp"
#include <GL/glut.h>
#include <cmath>
namespace gundam {
class hand {
  float point[8][3] = {{0.7, 0.7, 0},   {0.7, -0.7, 0}, {-0.7, -0.7, 0},
                       {-0.7, 0.7, 0},  {0.7, 1, 1},    {0.7, -0.7, 1},
                       {-0.7, -0.7, 1}, {-0.7, 1, 1}};
  int face[6][4] = {{0, 3, 2, 1}, {0, 4, 5, 1}, {1, 5, 6, 2},
                    {4, 7, 6, 5}, {2, 6, 7, 3}, {0, 3, 7, 4}};
  float normalp[6][3];
  float finger1[8][3] = {{0, 0, 0},       {0, -0.7, 0}, {0.35, -0.7, 0},
                         {0.35, 0, 0},    {0, 0, 1},    {0, -0.7, 1},
                         {0.35, -0.7, 1}, {0.35, 0, 1}};
  int face1[6][4] = {{0, 3, 2, 1}, {0, 1, 5, 4}, {1, 2, 6, 5},
                     {4, 5, 6, 7}, {2, 3, 7, 6}, {0, 4, 7, 3}};
  float normalf1[6][3];
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();

public:
  hand() {
    for (int i = 0; i < 6; i++) {
      // find cross product of two vectors
      float v1[3] = {point[face[i][1]][0] - point[face[i][0]][0],
                     point[face[i][1]][1] - point[face[i][0]][1],
                     point[face[i][1]][2] - point[face[i][0]][2]};
      float v2[3] = {point[face[i][2]][0] - point[face[i][0]][0],
                     point[face[i][2]][1] - point[face[i][0]][1],
                     point[face[i][2]][2] - point[face[i][0]][2]};
      float cross[3] = {v1[1] * v2[2] - v1[2] * v2[1],
                        v1[2] * v2[0] - v1[0] * v2[2],
                        v1[0] * v2[1] - v1[1] * v2[0]};
      normalp[i][0] = cross[0];
      normalp[i][1] = cross[1];
      normalp[i][2] = cross[2];
    }
    for (int i = 0; i < 6; i++) {
      // find cross product of two vectors
      float v1[3] = {finger1[face1[i][1]][0] - finger1[face1[i][0]][0],
                     finger1[face1[i][1]][1] - finger1[face1[i][0]][1],
                     finger1[face1[i][1]][2] - finger1[face1[i][0]][2]};
      float v2[3] = {finger1[face1[i][2]][0] - finger1[face1[i][0]][0],
                     finger1[face1[i][2]][1] - finger1[face1[i][0]][1],
                     finger1[face1[i][2]][2] - finger1[face1[i][0]][2]};
      float cross[3] = {v1[1] * v2[2] - v1[2] * v2[1],
                        v1[2] * v2[0] - v1[0] * v2[2],
                        v1[0] * v2[1] - v1[1] * v2[0]};
      normalf1[i][0] = cross[0];
      normalf1[i][1] = cross[1];
      normalf1[i][2] = cross[2];
    }
  }
  void draw(int mode, int grasp) {
    glPushMatrix();

    // glColor3d(0.07450980392, 0.39215686274, 0.31764705882);
    green_material();
    for (int i = 0; i < 6; i++) {
      glNormal3fv(normalp[i]);
      glBegin(GL_POLYGON);
      for (int j = 0; j < 4; j++) {
        glVertex3fv(point[face[i][j]]);
      }
      glEnd();
    }
    int angle = grasp == 0 ? 10 : 60;
    glLineWidth(3);
    {
      glPushMatrix();
      glTranslated(-0.7, 1, 1);
      for (int i = 0; i < 4; i++) {
        {
          glPushMatrix();
          green_material();
          for (int j = 0; j < 6; j++) {
            glNormal3fv(normalf1[j]);
            glBegin(GL_POLYGON);
            for (int k = 0; k < 4; k++) {
              glVertex3fv(finger1[face1[j][k]]);
            }
            glEnd();
          }
          if (i != 3) {
            glBegin(GL_LINE_STRIP);
            glVertex3f(finger1[3][0], finger1[3][1], finger1[3][2]);
            glVertex3f(finger1[7][0], finger1[7][1], finger1[7][2]);
            glEnd();
            glBegin(GL_LINE_STRIP);
            glVertex3f(finger1[2][0], finger1[2][1], finger1[2][2]);
            glVertex3f(finger1[6][0], finger1[6][1], finger1[6][2]);
            glEnd();
          }

          glTranslated(0, 0, 1);
          glRotated(angle, 1, 0, 0);
          for (int j = 0; j < 6; j++) {
            glNormal3fv(normalf1[j]);
            glBegin(GL_POLYGON);
            for (int k = 0; k < 4; k++) {
              glVertex3fv(finger1[face1[j][k]]);
            }
            glEnd();
          }

          if (i != 3) {
            glBegin(GL_LINE_STRIP);
            glVertex3f(finger1[3][0], finger1[3][1], finger1[3][2]);
            glVertex3f(finger1[7][0], finger1[7][1], finger1[7][2]);
            glEnd();
            glBegin(GL_LINE_STRIP);
            glVertex3f(finger1[2][0], finger1[2][1], finger1[2][2]);
            glVertex3f(finger1[6][0], finger1[6][1], finger1[6][2]);
            glEnd();
          }

          glTranslated(0, 0, 1);
          glScaled(1, 1, 0.5);
          glRotated(angle, 1, 0, 0);
          for (int j = 0; j < 6; j++) {
            glNormal3fv(normalf1[j]);
            glBegin(GL_POLYGON);
            for (int k = 0; k < 4; k++) {
              glVertex3fv(finger1[face1[j][k]]);
            }
            glEnd();
          }

          if (i != 3) {
            glBegin(GL_LINE_STRIP);
            glVertex3f(finger1[3][0], finger1[3][1], finger1[3][2]);
            glVertex3f(finger1[7][0], finger1[7][1], finger1[7][2]);
            glEnd();
            glBegin(GL_LINE_STRIP);
            glVertex3f(finger1[2][0], finger1[2][1], finger1[2][2]);
            glVertex3f(finger1[6][0], finger1[6][1], finger1[6][2]);
            glEnd();
          }

          glPopMatrix();
        }
        glTranslated(0.35, 0, 0);
      }
      glPopMatrix();
    }
    glPopMatrix();
  }
};
} // namespace gundam
