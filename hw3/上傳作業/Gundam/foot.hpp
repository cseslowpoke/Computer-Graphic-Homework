
#include <GL/glut.h>
#include <cmath>
namespace gundam {
class foot {
  float point[36][3] = {{1.3, 0, 1.3},   {1.3, 0, -1.3},   {-1.3, 0, -1.3},
                        {-1.3, 0, 1.3},  {1.3, 0.5, -2.6}, {-1.3, 0.5, -2.6},
                        {1.3, 0.5, 2.6}, {-1.3, 0.5, 2.6}, {1.3, 1, -2.6},
                        {-1.3, 1, -2.6}, {1.3, 1, 2.6},    {-1.3, 1, 2.6}};
  int face[10][4] = {{0, 1, 2, 3}, {1, 2, 5, 4},   {0, 3, 7, 6},
                     {0, 1, 4, 6}, {2, 3, 7, 5},   {6, 7, 11, 10},
                     {4, 5, 9, 8}, {8, 9, 11, 10}, {4, 6, 10, 8},
                     {5, 7, 11, 9}};
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();

public:
  void draw() {
    glPushMatrix();

    // draw_axes();
    glColor3d(0.07450980392, 0.39215686274, 0.31764705882);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // gluSphere(sphere, 1, 10, 10);
    // glColor3d(0.74117647058, 0.78823529411, 0.78823529411);
    // gluCylinder(cylinder, 0.6, 0.6, 2.3, 10, 10);
    for (int i = 0; i < 10; i++) {
      glBegin(GL_POLYGON);
      for (int j = 0; j < 4; j++) {
        glVertex3fv(point[face[i][j]]);
      }
      glEnd();
    }
    glPopMatrix();
  }
};
} // namespace gundam
