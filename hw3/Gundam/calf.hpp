#include <GL/glut.h>
#include <cmath>
namespace gundam {
class calf {
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();

public:
  void draw() {
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRotatef(-90, 1, 0, 0);
    glTranslated(0, 0, -0.7);
    glColor3d(0.07450980392, 0.39215686274, 0.31764705882);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 36; i++) {
      glVertex3f(1.3 * cos(10 * i * M_PI / 180), 1.3 * sin(10 * i * M_PI / 180),
                 0);
    }
    glEnd();
    gluCylinder(cylinder, 1.3, 1.3, 5, 10, 10);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 36; i++) {
      glVertex3f(1.3 * cos(10 * i * M_PI / 180), 1.3 * sin(10 * i * M_PI / 180),
                 0);
    }
    glEnd();
    glPopMatrix();
  }
};
} // namespace gundam
