#include <GL/glut.h>
#include <cmath>
namespace gundam {
class lower_arm {
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();
  const double PI = 3.14159265358979323846;

public:
  void draw() {
    glPushMatrix();
    glColor3d(0.07450980392, 0.39215686274, 0.31764705882);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // draw_axes();
    gluCylinder(cylinder, 1.2, 1.2, 3.5, 10, 10);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 36; i++) {
      glVertex3f(1.2 * cos(2 * PI / 36 * i), 1.2 * sin(2 * PI / 36 * i), 0);
    }
    glEnd();
    // gluSphere(sphere, 1, 10, 10);
    // glColor3d(0.74117647058, 0.78823529411, 0.78823529411);
    glTranslated(0, 0, 3.5);
    glColor3d(0.94901960784, 0.54117647058, 0.13333333333);
    gluCylinder(cylinder, 1.2, 1.2, 1.5, 10, 10);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 36; i++) {
      glVertex3f(1.2 * cos(2 * PI / 36 * i), 1.2 * sin(2 * PI / 36 * i), 0);
    }
    glEnd();
    glPopMatrix();
  }
};
} // namespace gundam