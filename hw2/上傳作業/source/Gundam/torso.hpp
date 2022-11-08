
#include <GL/glut.h>
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
  float point2[12][3] = {{0, 0, 2},   {0, 0, -1},  {5, 0, 5},    {5, 0, 4},
                         {-5, 0, 5},  {-5, 0, 4},  {0, 0.3, 2},  {0, 0.3, -1},
                         {5, 0.3, 5}, {5, 0.3, 4}, {-5, 0.3, 5}, {-5, 0.3, 4}};
  int face2[10][4] = {{0, 1, 3, 2}, {0, 1, 5, 4},  {6, 7, 9, 8}, {6, 7, 11, 10},
                      {0, 2, 8, 6}, {0, 4, 10, 6}, {1, 3, 9, 7}, {1, 5, 11, 7},
                      {2, 3, 9, 8}, {4, 5, 11, 10}};

public:
  void draw() {
    glPushMatrix();
    glColor3d(0.07450980392, 0.39215686274, 0.31764705882);

    glRotated(-90, 1, 0, 0);
    {
      glPushMatrix();

      for (int i = 0; i < 36; i++) {
        glVertex3f(3 * cos(2 * PI / 36 * i), 3 * sin(2 * PI / 36 * i), 0);
      }
      glEnd();
      glTranslated(0, 0, 4);
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
      glColor3d(0.74117647058, 0.78823529411, 0.78823529411);
      gluCylinder(cylinder, 2, 2, 1.5, 10, 10);
      glTranslated(0, 0, 1.5);
      glColor3d(0.07450980392, 0.39215686274, 0.31764705882);
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

      glColor3d(0.07450980392 * 0.9, 0.39215686274 * 0.9, 0.31764705882 * 0.9);
      for (int i = 0; i < 6; i++) {
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
        glColor3d(0.07450980392 * 0.9, 0.39215686274 * 0.9,
                  0.31764705882 * 0.9);
        gluCylinder(cylinder, 0.5, 0.5, 3, 10, 10);
        glTranslated(0, 0, 3);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 36; i++) {
          glVertex3f(0.5 * cos(2 * PI / 36 * i), 0.5 * sin(2 * PI / 36 * i), 0);
        }
        glEnd();
        glTranslated(0, 0, 0.01);
        glColor3d(0.94901960784, 0.54117647058, 0.13333333333);
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
        glColor3d(0.07450980392 * 0.9, 0.39215686274 * 0.9,
                  0.31764705882 * 0.9);
        gluCylinder(cylinder, 0.5, 0.5, 3, 10, 10);
        glTranslated(0, 0, 3);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 36; i++) {
          glVertex3f(0.5 * cos(2 * PI / 36 * i), 0.5 * sin(2 * PI / 36 * i), 0);
        }
        glEnd();
        glTranslated(0, 0, 0.01);
        glColor3d(0.94901960784, 0.54117647058, 0.13333333333);
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
      glColor3d(0.07450980392 * 0.9, 0.39215686274 * 0.9, 0.31764705882 * 0.9);
      glTranslated(0, 3, 2);
      // draw_axes();
      for (int i = 0; i < 10; i++) {
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
        glColor3d(0.07450980392, 0.39215686274, 0.31764705882);
        gluCylinder(cylinder, 0.5, 0.5, 4, 10, 10);
        glTranslated(0, 0, 4);
        gluSphere(sphere, 0.5, 10, 10);
        glPopMatrix();
      }
      {
        glPushMatrix();
        glTranslated(-0.7, 0.5, -1.5);
        // draw_axes();
        glColor3d(0.07450980392, 0.39215686274, 0.31764705882);
        gluCylinder(cylinder, 0.5, 0.5, 4, 10, 10);
        glTranslated(0, 0, 4);
        gluSphere(sphere, 0.5, 10, 10);
        glPopMatrix();
      }
      glPopMatrix();
    }
    glPopMatrix();
  }
};
} // namespace gundam