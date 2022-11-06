#pragma once
#include "../debug/debug.hpp"
#include <GL/glut.h>
#include <cmath>
namespace gundam {
class hand {
  float point[36][3] = {{0.7, 0.7, 0}, {0.7, -0.7, 0}, {-0.7, -0.7, 0}, {-0.7, 0.7, 0},
                        {0.7, 1, 1}, {0.7, -0.7, 1}, {-0.7, -0.7, 1}, {-0.7, 1, 1}};
  int face[6][4] = {{0, 1, 2, 3}, {0, 1, 5, 4}, {1, 2, 6, 5},
                    {4, 5, 6, 7}, {2, 3, 7, 6}, {0, 3, 7, 4}};
  float finger1[8][3] = {{0, 0, 0}, {0, -0.7, 0}, {0.35, -0.7, 0}, {0.35, 0, 0},
                         {0, 0, 1}, {0, -0.7, 1}, {0.35, -0.7, 1}, {0.35, 0, 1}};
  int face1[6][4] = {{0, 1, 2, 3}, {0, 1, 5, 4}, {1, 2, 6, 5},
                    {4, 5, 6, 7}, {2, 3, 7, 6}, {0, 3, 7, 4}};
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();

public:
  void draw(int mode, int grasp) {
    glPushMatrix();

//    draw_axes();
    glColor3d(0.07450980392, 0.39215686274, 0.31764705882);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // gluSphere(sphere, 1, 10, 10);
    // glColor3d(0.74117647058, 0.78823529411, 0.78823529411);
    // gluCylinder(cylinder, 0.6, 0.6, 2.3, 10, 10);
    for (int i = 0; i < 6; i++) {
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
      for(int i = 0; i < 4; i++) {
        {
          glPushMatrix();
          glColor3d(0.07450980392, 0.39215686274, 0.31764705882);
          for(int j = 0; j < 6; j++) {
            glBegin(GL_POLYGON);
            for(int k = 0; k < 4; k++) {
              glVertex3fv(finger1[face1[j][k]]);
            }
            glEnd();
          }
          if(i != 3) {
            glColor3d(0.07450980392 * 0.8, 0.39215686274 * 0.8, 0.31764705882 * 0.8);
            glBegin(GL_LINE_STRIP);
              glVertex3f(finger1[3][0], finger1[3][1], finger1[3][2]);
              glVertex3f(finger1[7][0], finger1[7][1], finger1[7][2]);
            glEnd();
          }
          
          glTranslated(0, 0, 1);
          glRotated(angle, 1, 0, 0);
          glColor3d(0.07450980392, 0.39215686274, 0.31764705882);
          for(int j = 0; j < 6; j++) {
            glBegin(GL_POLYGON);
            for(int k = 0; k < 4; k++) {
              glVertex3fv(finger1[face1[j][k]]);
            }
            glEnd();
          }
          
          if(i != 3) {
            glColor3d(0.07450980392 * 0.8, 0.39215686274 * 0.8, 0.31764705882 * 0.8);
            glBegin(GL_LINE_STRIP);
              glVertex3f(finger1[3][0], finger1[3][1], finger1[3][2]);
              glVertex3f(finger1[7][0], finger1[7][1], finger1[7][2]);
            glEnd();
          }
          
          glTranslated(0, 0, 1);
          glScaled(1, 1, 0.5);
          glRotated(angle, 1, 0, 0);
          glColor3d(0.07450980392, 0.39215686274, 0.31764705882);
          for(int j = 0; j < 6; j++) {
            glBegin(GL_POLYGON);
            for(int k = 0; k < 4; k++) {
              glVertex3fv(finger1[face1[j][k]]);
            }
            glEnd();
          }

          if(i != 3) {
            glColor3d(0.07450980392 * 0.8, 0.39215686274 * 0.8, 0.31764705882 * 0.8);
            glBegin(GL_LINE_STRIP);
              glVertex3f(finger1[3][0], finger1[3][1], finger1[3][2]);
              glVertex3f(finger1[7][0], finger1[7][1], finger1[7][2]);
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
