
#include <GL/glut.h>
#include <cmath>
namespace gundam {
class head {
  GLUquadricObj *cylinder = gluNewQuadric();

  float horn1[21][3] = {
      {0, -1.2, 0},
      {0.37082, -1.14127, 0},
      {0.705342, -0.97082, 0},
      {0.97082, -0.705342, 0},
      {1.14127, -0.37082, 0},
      {1.2, 0, 0},
      {1.14127, 0.37082, 0},
      {0.97082, 0.705342, 0},
      {0.705342, 0.97082, 0},
      {0.37082, 1.14127, 0},
      {0, 1.2, 0},
      {0, 0.96, 0},
      {0, 0.72, 0},
      {0, 0.48, 0},
      {0, 0.24, 0},
      {0, 0, 0},
      {0, -0.24, 0},
      {0, -0.48, 0},
      {0, -0.72, 0},
      {0, -0.96, 0},
      {0, -1.2, 0},
  };
  float horn2[21][3] = {{7.34788e-17, 1.2, 0},
                        {-0.37082, 1.14127, 0},
                        {-0.705342, 0.97082, 0},
                        {-0.97082, 0.705342, 0},
                        {-1.14127, 0.37082, 0},
                        {-1.2, 1.46958e-16, 0},
                        {-1.14127, -0.37082, 0},
                        {-0.97082, -0.705342, 0},
                        {-0.705342, -0.97082, 0},
                        {-0.37082, -1.14127, 0},
                        {0, -1.2, 0},
                        {0, -0.96, 0},
                        {0, -0.72, 0},
                        {0, -0.48, 0},
                        {0, -0.24, 0},
                        {0, 0, 0},
                        {0, 0.24, 0},
                        {0, 0.48, 0},
                        {0, 0.72, 0},
                        {0, 0.96, 0},
                        {0, 1.2, 0}};
  float eye1[11][3] = {{0.0871558, -0.996195, 0}, {0.173648, -0.984808, 0},
                       {0.258819, -0.965926, 0},  {0.34202, -0.939693, 0},
                       {0.422618, -0.906308, 0},  {0.5, -0.866025, 0},
                       {0.573576, -0.819152, 0},  {0.642788, -0.766044, 0},
                       {0.707107, -0.707107, 0},  {0.766044, -0.642788, 0},
                       {0.819152, -0.573576, 0}};
  float eye2[11][3] = {{-0.0871558, -0.996195, 0}, {-0.173648, -0.984808, 0},
                       {-0.258819, -0.965926, 0},  {-0.34202, -0.939693, 0},
                       {-0.422618, -0.906308, 0},  {-0.5, -0.866025, 0},
                       {-0.573576, -0.819152, 0},  {-0.642788, -0.766044, 0},
                       {-0.707107, -0.707107, 0},  {-0.766044, -0.642788, 0},
                       {-0.819152, -0.573576, 0}};

  float top_mouth[11][3] = {
      {-0.393323, -1.08065, 1.25}, {-0.316983, -1.10545, 1.25},
      {-0.239098, -1.12487, 1.25}, {-0.160049, -1.13881, 1.25},
      {-0.0802199, -1.1472, 1.25}, {7.04172e-17, -1.15, 1.25},
      {0.0802199, -1.1472, 1.25},  {0.160049, -1.13881, 1.25},
      {0.239098, -1.12487, 1.25},  {0.316983, -1.10545, 1.25},
      {0.393323, -1.08065, 1.25},
  };
  float bottom_mouth[11][3] = {
      {-0.549404, -1.1782, 0},  {-0.444626, -1.2216, 0},
      {-0.336465, -1.2557, 0},  {-0.225743, -1.28025, 0},
      {-0.113303, -1.29505, 0}, {7.9602e-17, -1.3, 0},
      {0.113303, -1.29505, 0},  {0.225743, -1.28025, 0},
      {0.336465, -1.2557, 0},   {0.444626, -1.2216, 0},
      {0.549404, -1.1782, 0}};
  const double PI = acos(-1);

public:
  void draw() {
    glPushMatrix();

    glColor3d(0.07450980392, 0.39215686274, 0.31764705882);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    gluCylinder(cylinder, 1.3, 1, 2.5, 10, 10);
    /*push*/
    {
      glPushMatrix();
      glTranslated(0, 0, 2.5);
      glColor3d(0.07450980392 * 0.95, 0.39215686274 * 0.95,
                0.31764705882 * 0.95);
      gluCylinder(cylinder, 1.5, 1.2, 0.7, 10, 10);
      {
        glPushMatrix();
        glTranslated(0, 0, 0.7);
        // glTranslated(-0.3, 0, 1);
        // draw_axes();

        for (int i = 0; i < 20; i++) {
          glBegin(GL_POLYGON);
          glVertex3fv(horn1[i]);
          glVertex3fv(horn1[i + 1]);
          glVertex3f(0.7, 0, 1);
          glEnd();
        }
        for (int i = 0; i < 20; i++) {
          glBegin(GL_POLYGON);
          glVertex3fv(horn2[i]);
          glVertex3fv(horn2[i + 1]);
          glVertex3f(-0.7, 0, 1);
          glEnd();
        }
        glPopMatrix();
      }
      glColor3d(0.74117647058, 0.78823529411, 0.78823529411);
      // glTranslated(0, 0, 2.5);
      for (int i = 0; i < 10; i++) {
        glBegin(GL_POLYGON);
        glVertex3fv(eye1[i]);
        glVertex3fv(eye1[i + 1]);
        glVertex3f(1.11 * cos(-(float)60 / 180 * PI),
                   1.11 * sin(-(float)60 / 180 * PI), -0.83333333333);
        glEnd();
      }
      for (int i = 0; i < 10; i++) {
        glBegin(GL_POLYGON);
        glVertex3fv(eye2[i]);
        glVertex3fv(eye2[i + 1]);
        glVertex3f(1.11 * cos(-(float)120 / 180 * PI),
                   1.11 * sin(-(float)120 / 180 * PI), -0.83333333333);
        glEnd();
      }
      glPopMatrix();
    }
    for (int i = 0; i < 10; i++) {
      glBegin(GL_POLYGON);
      glVertex3fv(top_mouth[i]);
      glVertex3fv(top_mouth[i + 1]);
      glVertex3fv(bottom_mouth[i + 1]);
      glVertex3fv(bottom_mouth[i]);
      glEnd();
    }

    {
      glPushMatrix();
      glColor3d(0.94901960784, 0.54117647058, 0.13333333333);
      glTranslated(0, 0, 1.3);
      glRotated(90, 0, 1, 0);

      gluCylinder(cylinder, 0.5, 0.5, 1.3, 10, 10);
      {
        glPushMatrix();
        glTranslated(0, 0, 1.3);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 30; i++) {
          glVertex3f(0.5 * cos((float)i / 30 * 2 * PI),
                     0.5 * sin((float)i / 30 * 2 * PI), 0);
        }
        glEnd();
        glPopMatrix();
      }
      glRotated(180, 0, 1, 0);
      gluCylinder(cylinder, 0.5, 0.5, 1.3, 10, 10);
      {
        glPushMatrix();
        glTranslated(0, 0, 1.3);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 30; i++) {
          glVertex3f(0.5 * cos((float)i / 30 * 2 * PI),
                     0.5 * sin((float)i / 30 * 2 * PI), 0);
        }
        glEnd();
        glPopMatrix();
      }
      glPopMatrix();
    }
    glPopMatrix();
  }
};
} // namespace gundam