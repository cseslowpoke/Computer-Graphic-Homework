#include "../Gundam/head.hpp"
#include <GL/glut.h>
namespace robot {
class head {
  float points[8][3] = {{1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0},
                        {1, 1, 3}, {-1, 1, 3}, {1, -1, 3}, {-1, -1, 3}};
  int face[6][4] = {{0, 1, 3, 2}, {0, 1, 5, 4}, {1, 3, 7, 5},
                    {4, 5, 7, 6}, {2, 3, 7, 6}, {0, 2, 6, 4}};
  GLUquadricObj *cylinder;
  gundam::head myhead;

public:
  void draw() {
    myhead.draw();
    // glPushMatrix();
    // draw_axes();
    // glColor3f(0, 0, 1);
    // gluCylinder(cylinder, 0.5, 0.5, 2, 5, 5);
    // glTranslated(0, 0, 0.5);
    // glColor3f(0, 0, 1);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // for (int i = 0; i < 6; i++) {
    //   glBegin(GL_POLYGON);
    //   for (int j = 0; j < 4; j++) {
    //     glVertex3fv(points[face[i][j]]);
    //   }
    //   glEnd();
    // }
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glColor3f(0, 0, 0);
    // glLineWidth(2);
    // for (int i = 0; i < 6; i++) {
    //   glBegin(GL_POLYGON);
    //   for (int j = 0; j < 4; j++) {
    //     glVertex3fv(points[face[i][j]]);
    //   }
    //   glEnd();
    // }
    // glPopMatrix();
  }
  void init() { cylinder = gluNewQuadric(); }
};
} // namespace robot