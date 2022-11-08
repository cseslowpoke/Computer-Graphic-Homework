#include <GL/glut.h>
#include <cmath>
namespace gundam {
class thigh {
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();

public:
  void draw() {
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRotatef(-90, 1, 0, 0);
    glColor3d(0.74117647058, 0.78823529411, 0.78823529411);
    gluCylinder(cylinder, 1, 1, 4, 10, 10);
    glPopMatrix();
  }
};
} // namespace gundam
