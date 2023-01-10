#include "allmaterial.hpp"
#include <GLUT/glut.h>
#include <cmath>
namespace gundam {
class calf {
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();

public:
  calf() {
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluQuadricTexture(cylinder, GL_TRUE);
  }
  void draw() {
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRotatef(-90, 1, 0, 0);
    glTranslated(0, 0, -0.7);
    green_material();
    // glBegin(GL_POLYGON);
    // for (int i = 0; i < 36; i++) {
    //   glVertex3f(1.3 * cos(10 * i * M_PI / 180), 1.3 * sin(10 * i * M_PI /
    //   180),
    //              0);
    // }
    // glEnd();
    gluCylinder(cylinder, 1.3, 1.3, 5, 10, 10);
    glBegin(GL_POLYGON);
    glNormal3d(0, 0, 1);
    for (int i = 0; i < 36; i++) {
      glVertex3f(1.3 * cos(10 * i * M_PI / 180), 1.3 * sin(10 * i * M_PI / 180),
                 0);
    }
    glEnd();
    glPopMatrix();
  }
};
} // namespace gundam
