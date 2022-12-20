
#include <GL/glut.h>
#include <cmath>

namespace gundam {
class upper_arm {
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();

public:
  void draw() {
    glPushMatrix();
    glColor3d(0.07450980392, 0.39215686274, 0.31764705882);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    gluSphere(sphere, 1, 10, 10);
    glColor3d(0.74117647058, 0.78823529411, 0.78823529411);
    gluCylinder(cylinder, 0.6, 0.6, 2.3, 10, 10);

    glPopMatrix();
  }
};
} // namespace gundam
