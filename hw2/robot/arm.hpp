#include "hand.hpp"
#include <GL/glut.h>
namespace robot {
class arm {
  float points[8][3] = {{0.7, 0.7, 3},   {0.7, -0.7, 3}, {-0.7, 0.7, 3},
                        {-0.7, -0.7, 3}, {0.7, 0.7, 0},  {0.7, -0.7, 0},
                        {-0.7, 0.7, 0},  {-0.7, -0.7, 0}};
  int face[6][4] = {{0, 1, 3, 2}, {0, 1, 5, 4}, {1, 3, 7, 5},
                    {4, 5, 7, 6}, {2, 3, 7, 6}, {0, 2, 6, 4}};
  hand handla;
  GLUquadricObj *sphere;

public:
  void draw() {
    /* forearm */
    glPushMatrix();
    // glColor3f(1, 0, 0);
    gluSphere(sphere, 0.7, 5, 5);
    glTranslatef(0, 0, 0.35);
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
    /**/
    glTranslated(0, 0, 3);
    gluSphere(sphere, 0.7, 5, 5);
    glTranslatef(0, 0, 0.35);
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
    glTranslated(0, 0, 3);
    handla.draw();
    glPopMatrix();
  }
  void init() { sphere = gluNewQuadric(); }
  void set_obj(item::item *obj) { handla.set_obj(obj); }
  item::item *get_grasp() { return handla.get_obj(); }
};
}; // namespace robot