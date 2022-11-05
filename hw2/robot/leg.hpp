#include "../debug/debug.hpp"
#include <GL/glut.h>
namespace robot {
class leg {
  float points[8][3] = {{0.7, 4, 0.7},   {0.7, 0, 0.7},  {-0.7, 4, 0.7},
                        {-0.7, 0, 0.7},  {0.7, 4, -0.7}, {0.7, 0, -0.7},
                        {-0.7, 4, -0.7}, {-0.7, 0, -0.7}};
  int face[6][4] = {{0, 1, 3, 2}, {0, 1, 5, 4}, {1, 3, 7, 5},
                    {4, 5, 7, 6}, {2, 3, 7, 6}, {0, 2, 6, 4}};
  float walk = 0;
  int jump = 0;
  GLUquadricObj *sphere;

public:
  void draw() {
    /* m */
    glPushMatrix();
    glColor3f(1, 0, 0);
    gluSphere(sphere, 0.7, 5, 5);
    glTranslatef(0, 0.35, 0);
    glColor3f(1, 0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (int i = 0; i < 6; i++) {
      glBegin(GL_POLYGON);
      for (int j = 0; j < 4; j++) {
        glVertex3fv(points[face[i][j]]);
      }
      glEnd();
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0, 0, 0);
    glLineWidth(2);
    for (int i = 0; i < 6; i++) {
      glBegin(GL_LINE_LOOP);
      for (int j = 0; j < 4; j++) {
        glVertex3fv(points[face[i][j]]);
      }
      glEnd();
    }
    /* wakj */
    glTranslated(0, 4, 0);
    if (walk < 0) {
      glRotatef(-30 * (float)walk / 45, 1, 0, 0);
    }
    /* jump*/
    if (0 < jump && jump <= 1000) {
      glRotated(90 * (float)jump / 1000, 1, 0, 0);
    } else if (1000 < jump && jump <= 2000) {
      glRotated(90 * (float)(2000 - jump) / 1000, 1, 0, 0);
    } else if (6000 < jump && jump <= 7000) {
      glRotated(60 * (float)(jump - 6000) / 1000, 1, 0, 0);
    } else if (7000 < jump && jump <= 8000) {
      glRotated(60 * (float)(8000 - jump) / 1000, 1, 0, 0);
    }
    gluSphere(sphere, 0.7, 5, 5);
    glTranslatef(0, 0.35, 0);
    glColor3f(1, 0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (int i = 0; i < 6; i++) {
      glBegin(GL_POLYGON);
      for (int j = 0; j < 4; j++) {
        glVertex3fv(points[face[i][j]]);
      }
      glEnd();
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0, 0, 0);
    glLineWidth(2);
    for (int i = 0; i < 6; i++) {
      glBegin(GL_LINE_LOOP);
      for (int j = 0; j < 4; j++) {
        glVertex3fv(points[face[i][j]]);
      }
      glEnd();
    }

    glPopMatrix();
  }
  void init() { sphere = gluNewQuadric(); }
  void set_walk(int w) { walk = w; }
  void set_jump(int j) { jump = j; }
};
} // namespace robot